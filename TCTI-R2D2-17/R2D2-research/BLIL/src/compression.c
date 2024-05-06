#include <include/compression.h>

#include <errno.h>

#include <include/image.h>
#include "halftone.h"
#include "bit_operations.h"

#include <stdio.h>

/* ------------------------ Static function prototypes ---------------------- */

static 
int compress_rle(struct BinImage *pIn, struct BinImage *pOut, void *pParams);

static
int decompress_rle(struct BinImage *pIn, struct BinImage *pOut);

static
int compress_hme(struct BinImage *pIn, struct BinImage *pOut, void *pParams);

static
int decompress_hme(struct BinImage *pIn, struct BinImage *pOut);

/* recursive algorithm with the goal of encoding a huffman encoding tree, also gives the nodes addresses for later use */
static
void RecNodeEncode(struct Node *node, uint8_t *uEncodedTree, unsigned *uIndex, struct Node *lastNode);

/* recursive algorithm with the goal of decoding a huffman encoding tree */
static
struct Node *RecNodeDecode(struct Node *decodedTree, uint8_t *uEncodedTree, unsigned *uDeIterator, unsigned *uEnBitIterator);

/* recursive algorithm with the goal of decoding a data segment compressed with huffman encoding */
static
uint8_t RecDataDecode(struct BinImage *pIn, unsigned *uInBitIterator, struct Node *node);



/* ----------------------------------- End ---------------------------------- */


/* ------------------------ Static function definitions ---------------------- */

int compress_rle(struct BinImage *pIn, struct BinImage *pOut, void *pParams)
{
    /* Offset of current field in bits starting at pOut->data. */
    unsigned uOff           = pOut->u16Offset << 3;
    unsigned uCurrVal       = ((struct RLEHeader *)pParams)->startVal;
    unsigned uCount         = 0;
    unsigned uFWidth        = ((struct RLEHeader *)pParams)->FieldWidth;
    unsigned uPixels        = pIn->u16Width * pIn->u16Height;
    
    for(unsigned i = 0; i < uPixels; i++)
    {
        uint8_t tmp = pIn->data[(i >> 3) + pIn->u16Offset];
        tmp = tmp >> (i & 0x7U);

        if((tmp & 0x01U) != uCurrVal) 
        {
            BFI((uint32_t*)(pOut->data + (uOff >> 3)), 
            uOff & 0x7U, uFWidth, uCount);
            uOff += uFWidth;

            uCurrVal ^= 1;
            uCount = 0;
        }

        if(++uCount == (1U << uFWidth))
        {
            BFI((uint32_t*)(pOut->data + (uOff >> 3)), 
                    uOff & 0x7U, uFWidth, uCount-1);
            uOff += uFWidth;

            BFI((uint32_t*)(pOut->data + (uOff >> 3)), 
                    uOff & 0x7U, uFWidth, 0);
            uOff += uFWidth;

            uCount = 0;
            i--; /* Decrement i, as the pixel isn't actually written. */
        }
    }     

    pOut->u32DataLen = (uOff >> 3);   

    return 0;
}

/* TODO: Contains significant error that has to be assessed ASAP. */
int decompress_rle(struct BinImage *pIn, struct BinImage *pOut)
{
    int iPixels                 = pIn->u16Width * pIn->u16Height;
    unsigned uFWidth            = ((struct RLEHeader *)pIn->data)->FieldWidth;
    unsigned uCurrVal           = ((struct RLEHeader *)pIn->data)->startVal;
    unsigned uOff               = (pIn->u16Offset << 3);
    unsigned uIterator          = 0;
    uint32_t tmp;

    while(iPixels > 0)
    {
        tmp = UBFX((uint32_t*)(pIn->data + (uOff >> 3)), uOff & 0x7U, uFWidth);

        if(uCurrVal == 1)
            for(unsigned i = 0; i < tmp; i++, uIterator++)
                pOut->data[uIterator >> 3] |= 0x1U << (uIterator & 0x7U);
        else
            for(unsigned i = 0; i < tmp; i++, uIterator++)
                pOut->data[uIterator >> 3] &= ~(0x1U << (uIterator & 0x7U));
                
        uOff += uFWidth;
        iPixels -= tmp;
        uCurrVal ^= 0x1U;
    }

    return 0;
}



int compress_hme(struct BinImage *pIn, struct BinImage *pOut, void *pParams)
{
    //TODO: implementeer verschillende clusterLength, en test de feasibility ervan
    //uint8_t uClusterLength     = ((struct HMEHeader *)pParams)->uClusterLength;

    //TODO: van te voren berekenen hoe groot een tree maximaal kan zijn, en dus hoe groot de freqlist moet zijn
    //backwards iterator
    unsigned uNodeStore         = 256;
    //forward iterator
    unsigned uListSortedSize    = 0;

    uint8_t bNodeFound          = 0;
    uint8_t uTmpData            = 0;

    //TODO: formule voor de maximale grootte is makkelijk: namelijk: aantal maximale leaf nodes - 1, dit kun je later automatisch berekent laten worden als clusterlength geinplementeerd is
    //doubles as storage for the tree and sorted list of frequencies
    struct Node freqList[256];
    //TODO: formule voor maximaal aantal leaf nodes is de unsigned integer limit, dus 256 voor 8 bits en 65536 voor 16 bits
    //list with all the leaf nodes, greatly reduces the complexity of the algorithm
    struct Node leafNodeList[256];

    struct Node tmpNode;
    struct Node tmpNode2;

    //make a frequency list of the data
    for(unsigned i = 0; i < pIn->u32DataLen; i++)
    {
        uTmpData = pIn->data[pIn->u16Offset + i];

        for(unsigned j = 0; j < uListSortedSize; j++)
        {
            //if the item already exists, increment freq and re-sort
            if(freqList[j].uItem == uTmpData)
            {
                freqList[j].uFreq++;

                for(unsigned k = 0; k < j; k++)
                {
                    if(freqList[j].uFreq > freqList[k].uFreq)
                    {
                        //switch places if incremented item is now greater than higher items
                        tmpNode = freqList[j];
                        freqList[j] = freqList[k];
                        freqList[k] = tmpNode;
                        break;
                    }
                }

                bNodeFound = 1;
                break;
            }
        }
        //add new Node if new data is not in the list
        if(!bNodeFound)
        {
            freqList[uListSortedSize].uItem = uTmpData;
            freqList[uListSortedSize].uFreq = 1;
            freqList[uListSortedSize].bIsLeafNode = 1;
            uListSortedSize++;
        }

        bNodeFound = 0;
    }

    //set before it changes
    unsigned uEncodedTreeSize = uListSortedSize;

    unsigned uSwitchIndex;
    while(uListSortedSize > 1)
    {
        //store leaf nodes for later
        struct Node *pStore;
        for(unsigned i = 0; i < 2; i++)
        {
            if(freqList[uListSortedSize - (i + 1)].bIsLeafNode)
            {
                leafNodeList[freqList[uListSortedSize - (i + 1)].uItem] = freqList[uListSortedSize - (i + 1)];
                pStore = &leafNodeList[freqList[uListSortedSize - (i + 1)].uItem];
            }
            else
            {
                uNodeStore--;
                freqList[uNodeStore] = freqList[uListSortedSize - (i + 1)];
                pStore = &freqList[uNodeStore];
            }
            if(i == 0){tmpNode.left = pStore;} else {tmpNode.right = pStore;};
        }

        tmpNode.uFreq = freqList[uListSortedSize - 1].uFreq + freqList[uListSortedSize - 2].uFreq;
        tmpNode.bIsLeafNode = 0;
        tmpNode.uAddrLen = 0;

        uListSortedSize--;

        //insert the new node
        for(unsigned i = 0; i < uListSortedSize; i++)
        {
            if(tmpNode.uFreq > freqList[i].uFreq)
            {
                uSwitchIndex = i;
                break;
            }
            uSwitchIndex = uListSortedSize - 1;
        }
        for(unsigned i = uSwitchIndex; i < (uListSortedSize - 1); i++)
        {
            tmpNode2 = freqList[i];
            freqList[i] = tmpNode;
            tmpNode = tmpNode2;
        }
        //store in the sorted list to be counted again
        freqList[uListSortedSize - 1] = tmpNode;
    }

    //calculate the exact size the tree will be, and set offset and buffer size according to it
    uEncodedTreeSize = (((uEncodedTreeSize * 9) + (256 - uNodeStore)) >> 3) + 1;
    uint8_t uEncodedTree[uEncodedTreeSize];
    pOut->u16Offset = uEncodedTreeSize + 1;

    //clean encoded tree storage
    for(unsigned x = 0; x < uEncodedTreeSize; x++)
    {
        uEncodedTree[x] = 0x00;
    }

    //encode the tree
    unsigned uTreeBitIndexer = 0;
    RecNodeEncode(&freqList[0], &uEncodedTree, &uTreeBitIndexer, NULL);

    //store the encoded tree
    pOut->data[0] = ((struct HMEHeader *)pParams)->uClusterLength;
    for(unsigned i = 0; i < uEncodedTreeSize; i++)
    {
        pOut->data[i + 1] = uEncodedTree[i];
    }

    //write the compressed data
    unsigned uDataOutBitIterator = 0;
    for(unsigned i = 0; i < pIn->u32DataLen; i++)
    {
        uTmpData = pIn->data[pIn->u16Offset + i];

        //write the address
        for(int j = 0; j < leafNodeList[uTmpData].uAddrLen; j++)
        {
            pOut->data[pOut->u16Offset + (uDataOutBitIterator >> 3)] |= (((leafNodeList[uTmpData].uAddr >> ((leafNodeList[uTmpData].uAddrLen - j) - 1)) & 0x01) << (7 - (uDataOutBitIterator % 8)));
            uDataOutBitIterator++;
        }
    }

    pOut->u32DataLen = ((uDataOutBitIterator >> 3) + 1 + pOut->u16Offset);
    pOut->eCompression = BLIL_COMPRESSION_HUF;

    return 0;
}

int decompress_hme(struct BinImage *pIn, struct BinImage *pOut)
{
    //TODO: implementatie van clusterlength
    uint8_t uClusterLength = pIn->data[0];

    struct Node decodedTree[512];
    uint8_t uEncodedTree[pIn->u16Offset - 1];

    for(unsigned i = 0; i < pIn->u16Offset - 1; i++)
    {
        uEncodedTree[i] = pIn->data[i + 1];
    }

    struct Node *treeOrigin;

    unsigned uDeIterator = 0;
    unsigned uEnBitIterator = 0;
    treeOrigin = RecNodeDecode(
        &decodedTree, 
        &uEncodedTree, 
        &uDeIterator, 
        &uEnBitIterator);

    unsigned uInBitIterator = 0;
    unsigned uOffIterator = 0;
    while((uInBitIterator >> 3) <= pIn->u32DataLen)
    {
        pOut->data[pOut->u16Offset + uOffIterator] = RecDataDecode(pIn, &uInBitIterator, treeOrigin);
        uOffIterator++;
    }

    return 0;
}


void RecNodeEncode(struct Node *node, uint8_t *uEncodedTree, unsigned *uIndex, struct Node *lastNode)
{
    //update the addres
    if(lastNode != NULL)
    {
        node->uAddr = lastNode->uAddr;
        node->uAddr = node->uAddr << 1;
        if(node == lastNode->right){node->uAddr += 1;};
        node->uAddrLen = lastNode->uAddrLen + 1;
    }
    if(node->bIsLeafNode)
    {
        uint8_t uItem = node->uItem;

        //write 0;
        uEncodedTree[(*uIndex) >> 3] = uEncodedTree[(*uIndex) >> 3] & ~(0x01 << (7 - ((*uIndex) % 8)));
        (*uIndex)++;

        //write item
        for(int i = 0; i < 8; i++)
        {
            uEncodedTree[(*uIndex) >> 3] |= (((uItem >> (7 - i)) & 0x01) << (7 - ((*uIndex) % 8)));
            (*uIndex)++;
        }
        return;
    }
    else
    {
        //write 1
        uEncodedTree[(*uIndex) >> 3] |= (0x01 << (7 - ((*uIndex) % 8)));
        (*uIndex)++;

        RecNodeEncode(node->left, uEncodedTree, uIndex, node);
        RecNodeEncode(node->right, uEncodedTree, uIndex, node);
    }
}

struct Node *RecNodeDecode(struct Node *decodedTree, uint8_t *uEncodedTree, unsigned *uDeIterator, unsigned *uEnBitIterator)
{   
    struct Node tmpNode;

    //leaf node
    if(!((uEncodedTree[(*uEnBitIterator) >> 3] >> (7 - ((*uEnBitIterator) % 8))) & 0x01))
    {
        (*uEnBitIterator)++;

        uint8_t uNodeItem = 0x00;

        //read next byte to know the node item
        for(unsigned i = 0; i < 8; i++)
        {
            uNodeItem = uNodeItem << 1;
            uNodeItem |= ((uEncodedTree[(*uEnBitIterator) >> 3] >> (7 - ((*uEnBitIterator) % 8))) & 0x01);

            (*uEnBitIterator)++;
        }

        tmpNode.bIsLeafNode = 1;
        tmpNode.uItem = uNodeItem;
    }
    else
    {
        (*uEnBitIterator)++;

        tmpNode.left = RecNodeDecode(decodedTree, uEncodedTree, uDeIterator, uEnBitIterator);
        tmpNode.right = RecNodeDecode(decodedTree, uEncodedTree, uDeIterator, uEnBitIterator);
        tmpNode.bIsLeafNode = 0;

        //TODO: tmp voor debuggen
        tmpNode.uItem = 42;
    }
    //add node to decoded tree
    decodedTree[(*uDeIterator)] = tmpNode;
    (*uDeIterator)++;
    return &decodedTree[(*uDeIterator) - 1];
}

uint8_t RecDataDecode(struct BinImage *pIn, unsigned *uInBitIterator, struct Node *node)
{
    uint8_t bTmpData;

    //get next bit
    bTmpData = ((pIn->data[pIn->u16Offset + ((*uInBitIterator) >> 3)] >> (7 - ((*uInBitIterator) % 8))) & 0x01);
    (*uInBitIterator)++;

    if(bTmpData)
    {
        //right
        if(node->right->bIsLeafNode)
        {
            return node->right->uItem;
        }
        return RecDataDecode(pIn, uInBitIterator, node->right);
    }
    else
    {
        //left
        if(node->left->bIsLeafNode)
        {
            return node->left->uItem;
        }
        return RecDataDecode(pIn, uInBitIterator, node->left);
    }
}

/* ----------------------------------- End ---------------------------------- */


/* -------------------------------- Interface ------------------------------- */

int BLIL_compress(struct BinImage *pIn, struct BinImage *pOut,
    enum BLIL_COMPRESSION eAlgo, void *pParams)
{
    int iRetVal = 0;

    if(pIn->eCompression != BLIL_COMPRESSION_NONE)
        return -EINVAL;

    pOut->eCompression  = eAlgo;
    pOut->u16Width      = pIn->u16Width;
    pOut->u16Height     = pIn->u16Height;
    pOut->eDither       = pIn->eDither;

    switch(eAlgo)
    {
        case BLIL_COMPRESSION_NONE:
            break;

        case BLIL_COMPRESSION_RLE:
            pOut->u16Offset = sizeof(struct RLEHeader);
            *((struct RLEHeader *)pOut->data) = *((struct RLEHeader *)pParams);
            iRetVal = compress_rle(pIn, pOut, pParams);
            break;

        case BLIL_COMPRESSION_HALFTONE:
            iRetVal = halftone_compress(pIn, pOut, 0);
            break;

        case BLIL_COMPRESSION_HUF:
            pOut->u16Offset = sizeof(struct HMEHeader);
            iRetVal = compress_hme(pIn, pOut, pParams);
            break;
        default:
            iRetVal = -EINVAL;
            break;
    }

    return iRetVal;
}


int BLIL_decompress(struct BinImage *pIn, struct BinImage *pOut)
{
    int iRetVal = 0;
    
    if(pIn->eCompression == BLIL_COMPRESSION_NONE)
        return -EINVAL;

    if(pOut->u32MaxDataLen < (unsigned)(pIn->u16Width * pIn->u16Height >> 3))
        return -EOVERFLOW;

    pOut->eCompression  = BLIL_COMPRESSION_NONE;
    pOut->u16Width      = pIn->u16Width;
    pOut->u16Height     = pIn->u16Height;
    pOut->eDither       = pIn->eDither;
    pOut->u32DataLen    = pIn->u16Width * pIn->u16Height >> 3;
    pOut->u16Offset     = 0;

    switch(pIn->eCompression)
    {
        case BLIL_COMPRESSION_RLE:
            iRetVal = decompress_rle(pIn, pOut);
            break;

        case BLIL_COMPRESSION_HALFTONE:
            iRetVal = halftone_decompress(pIn, pOut);
            break;

        case BLIL_COMPRESSION_HUF:
            iRetVal = decompress_hme(pIn, pOut);
            break;
        default:
            iRetVal = -EINVAL;
            break;
    }

    return iRetVal;
}

/* ----------------------------------- End ---------------------------------- */
