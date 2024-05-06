#ifndef SRC_BIT_OPERATIONS_H_
#define SRC_BIT_OPERATIONS_H_

#include <stdint.h>


/* Bit-field insert. */
void BFI(uint32_t *pAddr, uint8_t u8LSB, uint8_t u8Width, uint32_t u32Val);

/* Unsigned bit-field extract. */
uint32_t UBFX(uint32_t *pAddr, uint8_t u8LSB, uint8_t u8Width);


#endif /* SRC_BIT_OPERATIONS_H_ */
