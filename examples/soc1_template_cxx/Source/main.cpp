/************************************************************************
*               Eclipse Rival Risc-V Template Project                   *
*                          Evren Kenanoglu                              *
*************************************************************************

-------------------------- END-OF-HEADER -----------------------------
*/

/**
 * @file main.c
 * @author Evren Kenanoglu
 * @brief
 * @version 0.1
 * @date 2021-10-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <cstdint>
void main(void)
{
	volatile uint32_t mult1 = 5;
	volatile uint32_t mult2 = 19;
	volatile uint32_t result;
	while (1)
    {
		result = mult1 * mult2;
    }
}

/*************************** End of file ****************************/
