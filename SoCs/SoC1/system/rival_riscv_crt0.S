/*
* @file riscv_crt0.S
* @author Michael Maierhofer (IFAT DCGR ATV PTS PD CDF)
* @author Evren Kenanoglu (IFAT DCGR ATV PS PD CDF)
* @date 29/10/2021
* @brief startup code to initialise stack- and global-pointer
* NOT USED ANYMORE...
*/

.global __global_pointer$
__global_pointer$=__data_start__+ 0x800
.section .init, "ax"
.global _start
_start:
  .cfi_startproc
  .cfi_undefined ra
  .option push
  .option norelax
  /* set global pointer */
  la gp, __global_pointer$
  .option pop
  /* set stack pointer */
  la sp, __stack_start__
  add s0, sp, zero
  //jal zero, main
  j startup
  .cfi_endproc
  .end
