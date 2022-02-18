/** @file       register_functions.c
 *  @brief      Access functions for registers and memory
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Michael Maierhofer (IFAT DCGR ATV PTS PD CDF)
 *  @author     Evren Kenanoglu
 *  @date       04/10/2021
 */
#define FILE_REGISTER_FUNCTIONS_C

/** INCLUDES ******************************************************************/
#include "register_functions.h"

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/

/** VARIABLES *****************************************************************/

/** LOCAL FUNCTION DECLARATIONS ***********************************************/

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

uint8_t REGISTER_READ8(volatile const uint32_t* adr)
{
    return (uint8_t)*adr;
}

void REGISTER_WRITE8(volatile uint32_t* adr, const uint8_t value)
{
    *adr = value;
}

uint16_t REGISTER_READ16(volatile const uint16_t* adr)
{
    return (uint16_t)*adr;
}

void REGISTER_WRITE16(volatile uint16_t* adr, const uint16_t value)
{
    *adr = value;
}

uint32_t REGISTER_READ32(volatile const uint32_t* adr)
{
    return *adr;
}

void REGISTER_WRITE32(volatile uint32_t* adr, const uint32_t value)
{
    *adr = value;
}

uint8_t MEM_READ8(volatile const uint8_t* adr)
{
    return *adr;
}

void MEM_WRITE8(volatile uint8_t* adr, const uint8_t value)
{
    *adr = value;
}

uint16_t MEM_READ16(volatile const uint16_t* adr)
{
    return *adr;
}

void MEM_WRITE16(volatile uint16_t* adr, const uint16_t value)
{
    *adr = value;
}

uint32_t MEM_READ32(volatile const uint32_t* adr)
{
    return *adr;
}

void MEM_WRITE32(volatile uint32_t* adr, const uint32_t value)
{
    *adr = value;
}

/** LOCAL FUNCTION DEFINITIONS ************************************************/
