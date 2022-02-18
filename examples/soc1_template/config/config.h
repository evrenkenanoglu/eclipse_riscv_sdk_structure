/** @file       config.h
 *  @brief      Target Configuration
 *  @copyright  (c) 2021- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       15/11/2021
 */
#ifndef FILE_CONFIG_H
#define FILE_CONFIG_H

/** INCLUDES ******************************************************************/

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/

/** MACROS ********************************************************************/

#ifndef FILE_CONFIG_C
#define INTERFACE extern
#else
#define INTERFACE
#endif

///******** SoCs Definitions **************///
#ifndef _SOC1_
#define _SOC1_ 1
#endif

///********* Target Selection *************///
#ifndef _TARGET_SOC_
#define _TARGET_SOC_ _SOC1_
#endif

#if (_TARGET_SOC_ == _RIVAL1_)
#include "../SoCs/SoC1/soc1.h"
#endif


/** VARIABLES *****************************************************************/

/** FUNCTIONS *****************************************************************/

#undef INTERFACE // Should not let this roam free

#endif // FILE_CONFIG_H
