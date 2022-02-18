/**
 * @file startup.c
 * @author Michael Maierhofer
 * @author Evren Kenanoglu
 * @brief Startup Code to Initialise Sections
 * @date 2022-02-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/** adapted from https://github.com/danielinux/riscv-boot/ */

#include "library/types.h"
#include "library/register_functions.h"
/**
 * @defgroup BOOT_ROM Startup and Boot Code for Boot ROM
 * @{
 */

/** start of data section */
extern uint32_t __data_source_start__;
/** start of data section */
extern uint32_t __data_target_start__;
/** start of data section */
extern uint32_t __data_target_end__;

extern uint32_t __data_start__;
/** end of data section */
extern uint32_t __data_end__;
/** start of read only data section */
extern uint32_t __rodata_start__;
/** end of read only data section */
extern uint32_t __rodata_end__;
/** data load memory address (i.e. address in ROM from where to load data from) */
extern uint32_t __data_lma__;
/** entry address for a boot from RAM */
extern uint32_t __ram_start__;
/** entry address for a boot from ROM */
extern uint32_t __rom_start__;
/** start of BSS section */
extern uint32_t __bss_start__;
/** end of BSS section */
extern uint32_t __bss_end__;
/** start of heap */
extern uint32_t __heap_start__;
/** end of heap */
extern uint32_t __heap_end__;
/** start of stack */
extern uint32_t __stack_start__;
/** end of stack */
extern uint32_t __stack_end__;

/**
 * @brief copies data from ROM to RAM
 */
void copy_data(void)
{
  uint32_t* src = &__data_source_start__;
  uint32_t* dst = &__data_target_start__;
  while (dst < ((uint32_t*)&__data_target_end__))
  {
    MEM_WRITE32(dst, MEM_READ32(src));
    dst++;
    src++;
  }
  return;
}

/**
 * @brief initialises data in BSS section with 0
 */
 void init_bss(void)
{
  uint32_t* dst = &__bss_start__;
  while (dst < ((uint32_t*)&__bss_end__))
  {
    MEM_WRITE32(dst, 0U);
    dst++;
  }
  return;
}

/**
 * @brief fills the heap with 0xDEADBEEF
 */
 void fill_heap(void)
{
  uint32_t* dst = &__heap_start__;
  while (dst < ((uint32_t*)&__heap_end__))
  {
    MEM_WRITE32(dst, 0xDEADBEEF);
    dst++;
  }
  return;
}

/**
 * @brief fills the heap with 0xC0FEBABE
 */
 void fill_stack(void)
{
  uint32_t* dst = &__stack_start__;
  while (dst < ((uint32_t*)&__stack_end__))
  {
    MEM_WRITE32(dst, 0xC0FEBABE);
    dst++;
  }
  return;
}

/**
 * @brief Standart Entry Point for Application
 * 
 */
extern void main();

/**
 * @brief The linker script will place this in the reset entry point.
 * It will be 'called' with no stack or C runtime configuration.
 * NOTE - this only supports a single hart.
 * tp will not be initialized
 * 
 */
__attribute__((section(".init")))
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

/**
 * @brief Initialize data and bss sections 
 * At this point we have a stack and global poiner, but no access to global variables.
 * 
 */
__attribute__((section(".init")))
 void _start(void)
{
  UNUSED(__data_start__)
  UNUSED(__data_end__)
  UNUSED(__rodata_start__)
  UNUSED(__rodata_end__)
  UNUSED(__data_lma__)
  UNUSED(__ram_start__)
  UNUSED(__rom_start__)
  while (1)
  {
      copy_data();
      fill_heap();
      fill_stack();
      init_bss();
      main();
  }
}
/** @} */
