/**
 * @file register_fucntions.h
 * @author Michael Maierhofer (IFAT DCGR ATV PTS PD CDF)
 * @author Evren Kenanoglu
 * @date 01/09/2019
 * @brief access functions for registers and memory
 */

#ifndef FILE_REGISTER_FUNCTIONS_H
#define FILE_REGISTER_FUNCTIONS_H

//#include "config.h"
#include "config/config.h"
#include "../library/types.h"

//**************** REGISTERS ******************//

extern uint8_t  REGISTER_READ8(volatile const uint32_t* adr);
extern void     REGISTER_WRITE8(volatile uint32_t* adr, const uint8_t value);
extern uint16_t REGISTER_READ16(volatile const uint16_t* adr);
extern void     REGISTER_WRITE16(volatile uint16_t* adr, const uint16_t value);
extern uint32_t REGISTER_READ32(volatile const uint32_t* adr);
extern void     REGISTER_WRITE32(volatile uint32_t* adr, const uint32_t value);

extern uint8_t  MEM_READ8(volatile const uint8_t* adr);
extern void     MEM_WRITE8(volatile uint8_t* adr, const uint8_t value);
extern uint16_t MEM_READ16(volatile const uint16_t* adr);
extern void     MEM_WRITE16(volatile uint16_t* adr, const uint16_t value);
extern uint32_t MEM_READ32(volatile const uint32_t* adr);
extern void     MEM_WRITE32(volatile uint32_t* adr, const uint32_t value);

// extern uint32_t CSR_READ(volatile const uint16_t* csr);
// extern void     CSR_WRITE(volatile const uint16_t* csr, const uint32_t value);
// extern uint32_t CSR_SWAP(volatile const uint16_t* csr, const uint32_t value);
// extern uint32_t CSR_SET(volatile const uint16_t* csr, const uint32_t value);
// extern uint32_t CSR_CLEAR(volatile const uint16_t* csr, const uint32_t value);

INLINE uint32_t CSR_READ(volatile const uint16_t* csr)
{
    uint32_t tmp;
    __asm__ volatile("csrr %0, %1" : "=r"(tmp) : "i"(csr));
    return tmp;
}

INLINE void CSR_WRITE(volatile const uint16_t* csr, const uint32_t value)
{
    if (__builtin_constant_p(value) && (uint32_t)value < 32U)
        __asm__ volatile("csrw %0, %1" : : "i"(csr), "K"(value));
    else
        __asm__ volatile("csrw %0, %1" : : "i"(csr), "r"(value));
}

INLINE uint32_t CSR_SWAP(volatile const uint16_t* csr, const uint32_t value)
{
    uint32_t tmp;
    if (__builtin_constant_p(value) && (uint32_t)value < 32U)
        __asm__ volatile("csrrw %0, %1, %2" : "=r"(tmp) : "i"(csr), "K"(value));
    else
        __asm__ volatile("csrrw %0, %1, %2" : "=r"(tmp) : "i"(csr), "r"(value));
    return tmp;
}

INLINE uint32_t CSR_SET(volatile const uint16_t* csr, const uint32_t value)
{
    uint32_t tmp;
    if (__builtin_constant_p(value) && (uint32_t)value < 32U)
        __asm__ volatile("csrrs %0, %1, %2" : "=r"(tmp) : "i"(csr), "K"(value));
    else
        __asm__ volatile("csrrs %0, %1, %2" : "=r"(tmp) : "i"(csr), "r"(value));
    return tmp;
}

INLINE uint32_t CSR_CLEAR(volatile const uint16_t* csr, const uint32_t value)
{
    uint32_t tmp;
    if (__builtin_constant_p(value) && (uint32_t)value < 32U)
        __asm__ volatile("csrrc %0, %1, %2" : "=r"(tmp) : "i"(csr), "K"(value));
    else
        __asm__ volatile("csrrc %0, %1, %2" : "=r"(tmp) : "i"(csr), "r"(value));
    return tmp;
}
#endif /* FILE_REGISTER_FUNCTIONS_H */
