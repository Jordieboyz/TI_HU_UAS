#include "bit_operations.h"


void BFI(uint32_t *pAddr, uint8_t u8LSB, uint8_t u8Width, uint32_t u32Val)
{
    uint32_t tmp;
    uint32_t msk = (0x1 << u8Width) - 1;

    tmp = *pAddr;
    tmp &= ~(msk << u8LSB);
    tmp |= (u32Val << u8LSB);
    *pAddr = tmp;
}


uint32_t UBFX(uint32_t *pAddr, uint8_t u8LSB, uint8_t u32Width)
{
    uint32_t tmp;
    uint32_t msk = (0x1U << u32Width) - 1;

    tmp = *pAddr;
    tmp >>= u8LSB;
    tmp &= msk;

    return tmp;
}
