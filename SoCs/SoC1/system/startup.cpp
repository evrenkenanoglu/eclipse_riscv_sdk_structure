/** @file       startup.c
 *  @brief      startup in C++
 *  @copyright  (c) 2022- Evren Kenanoglu - All Rights Reserved
 *              Permission to use, reproduce, copy, prepare derivative works,
 *              modify, distribute, perform, display or sell this software and/or
 *              its documentation for any purpose is prohibited without the express
 *              written consent of Evren Kenanoglu.
 *  @author     Evren Kenanoglu
 *  @date       03/01/2022
 */
#define FILE_STARTUP_CPP

/** INCLUDES ******************************************************************/
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string.h>

using namespace std;

/** CONSTANTS *****************************************************************/

/** TYPEDEFS ******************************************************************/
// Generic C function pointer.
typedef void (*function_t)();
/** MACROS ********************************************************************/
#define UNUSED(x) [&x]{}()

/** VARIABLES *****************************************************************/
/** start of data section */
extern "C" uint32_t* __data_source_start__;
/** start of data section */
extern "C" uint32_t* __data_target_start__;
/** start of data section */
extern "C" uint32_t* __data_target_end__;
/** start of data section */
extern "C" uint32_t __data_start__;
/** end of data section */
extern "C" uint32_t __data_end__;
/** start of read only data section */
extern "C" uintptr_t __rodata_start__;
/** end of read only data section */
extern "C" uintptr_t __rodata_end__;
/** data load memory address (i.e. address in ROM from where to load data from) */
extern "C" uintptr_t __data_lma__;
/** entry address for a boot from RAM */
extern "C" uintptr_t __ram_start__;
/** entry address for a boot from ROM */
extern "C" uintptr_t __rom_start__;
/** start of BSS section */
extern "C" uintptr_t __bss_start__;
/** end of BSS section */
extern "C" uintptr_t __bss_end__;
/** start of heap */
extern "C" uintptr_t __heap_start__;
/** end of heap */
extern "C" uintptr_t __heap_end__;
/** start of stack */
extern "C" uintptr_t __stack_start__;
/** end of stack */
extern "C" uintptr_t __stack_end__;

extern "C" function_t __init_array_start[];
extern "C" function_t __init_array_end[];

/** LOCAL FUNCTION DECLARATIONS ***********************************************/

// This function will be placed by the linker script according to the section
extern "C" void _enter(void) __attribute__((naked, section(".init")));

// Define the symbols with "C" naming as they are used by the assembler
extern "C" void _start(void) __attribute__((noreturn));
// extern "C" void copyData(void) __attribute__((noreturn));
extern "C" void _Exit(int exit_code) __attribute__((noreturn));

// Standard entry point, no arguments.
extern int main(void);

/** INTERFACE FUNCTION DEFINITIONS ********************************************/

/** LOCAL FUNCTION DEFINITIONS ************************************************/

// The linker script will place this in the reset entry point.
// It will be 'called' with no stack or C runtime configuration.
// NOTE - this only supports a single hart.
// tp will not be initialized
void _enter(void)
{
    // Setup SP and GP
    // The locations are defined in the linker script
    __asm__ volatile(".option push;"
                     ".option norelax;"
                     "la    gp, __global_pointer$;"
                     "la    sp, __stack_start__;"
                     "add s0, sp, zero;"
                     "jal   zero, _start;"
                     //: /* ".cfi_endproc;" */
                     //: /* output: none %0 */
                     //: /* input: none */
                     //: /* clobbers: none */
    );
    // This point will not be executed, _start() will be called with no return.
}

// At this point we have a stack and global poiner, but no access to global variables.
void _start(void)
{

    // Init memory regions
    // Clear the .bss section (global variables with no initial values)
    fill(&__bss_start__, // BSS Address Start
         &__bss_end__,   // BSS Address End
         0U);            // Initial Value

    // Initialize the .data section (global variables with initial values)
    copy(&__data_target_start__,  // data address start in RAM
         &__data_target_end__,    // data address end in RAM
         &__data_source_start__); // data address source in FLASH

    // Call constructors
    for_each(__init_array_start, __init_array_end, [](const function_t pf) { pf(); });
    // Jump to main
    auto rc = main();
    // Don't expect to return, if so busy loop in the exit function.
    _Exit(rc);
}

// This should never be called. Busy loop with the CPU in idle state.
void _Exit(int exit_code)
{
	UNUSED(exit_code);
    // Halt
    while (true)
    {
        __asm__ volatile("wfi");
    }
}
