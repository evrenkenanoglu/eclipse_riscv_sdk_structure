OUTPUT_ARCH( "riscv" )

ENTRY(_enter)

/* Define memory layout */

/* ROM PLACEMENT */
ROM_OFFSET 	    = 0x00009000;
ROM_SIZE 	      = 0x00003FFF;       /*16k Boot rom Size */
ROM_END         = ROM_OFFSET + ROM_SIZE;

/* RAM Memory */
RAM_OFFSET 	    = 0x00002000;
RAM_SIZE 	      = 0x00001fff;
RAM_END         = RAM_OFFSET + RAM_SIZE;

/* Define stack and heap size */
__stack_size__    = 2048; 
__heap_size__     = 2048;

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
}

MEMORY {
  /* BOOT_FLASH(rx):   ORIGIN = BOOT_ROM_OFFSET,   LENGTH = BOOT_ROM_SIZE  size of BootLoader Memory */
  FLASH1 (rx)   :   ORIGIN = ROM_OFFSET,        LENGTH = ROM_SIZE       /* size of Instruction Memory */
  RAM1 (!rx)    :   ORIGIN = RAM_OFFSET,        LENGTH = RAM_SIZE       /* size of Data Memory and offset */
}

SECTIONS {
  
  __FLASH1_segment_start__    = ORIGIN(FLASH1);
  __FLASH1_segment_size__     = LENGTH(FLASH1);
  __FLASH1_segment_end__      = __FLASH1_segment_start__ + __FLASH1_segment_size__;

  __RAM1_segment_start__      = ORIGIN(RAM1);
  __RAM1_segment_size__       = LENGTH(RAM1);
  __RAM1_segment_end__        = __RAM1_segment_start__ + __RAM1_segment_size__;

  PROVIDE(__rom_start__ = ORIGIN(FLASH1));
  PROVIDE(__ram_start__ = ORIGIN(RAM1));

  .text	: ALIGN(4) {
    PROVIDE(__text_start__ = .);
     KEEP (*(.init))
    *(.text)
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.startup .text.startup.*)
    *(.text.hot .text.hot.*)
    *(.stub .text.* .gnu.linkonce.t.*)
	  *(.lit)
    *(.shdata)
    PROVIDE(__text_end__ = .);
  } > FLASH1
  
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);	
  PROVIDE (_endtext = .);

  /* 
   * This section includes the program code and C++ constructors and destructors 
   */
  .ctors : {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } > FLASH1
  
  .dtors : {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } > FLASH1

  /* 
   * This section includes read only data 
   */
  .rodata : ALIGN(8) 
  {
    PROVIDE(__rodata_start__ = .); 
    *(.rodata .rodata.*); 
    PROVIDE(__rodata_end__ = .); 
  }> FLASH1
  
  /* > RAM1 AT > FLASH1 :data  */
  /* 
   * This section includes global/static variables/data 
   */
  .data : ALIGN(8) 
  { 
    PROVIDE(__data_start__ = .);
    *(.data .data.*);
    *(.gnu.linkonce.d.*);
    . = ALIGN(8);
    PROVIDE( __global_pointer$ = . + 0x800 ); 
    *(.sdata .sdata.* .sdata2.*);
    *(.gnu.linkonce.s.*)
    PROVIDE(__data_end__ = .);
  } > RAM1 AT > FLASH1 :data

  /*
  * Data VMA (Virtual Memory Address) in RAM but LMA (Load Memory Address) in FLASH
  * LOADADDR load the physical address in FLASH
  * ADDR load the VMA in RAM  
  */
  PROVIDE( __data_source_start__ = LOADADDR(.data) );
  PROVIDE( __data_target_start__ = ADDR(.data) );
  PROVIDE( __data_target_end__ = ADDR(.data) + SIZEOF(.data) );

  /* RAM SECTION
   *
   * Following sections are stored in the RAM1
   */
   /* 
   * Contains handler if c exceptions are used
   */
   .gcc_except_table : ALIGN(4){
       KEEP (*(.gcc_except_table*))
   } > RAM1
   /* 
    * These next three sections are needed for C runtime function initialization and release
    */
  .preinit_array : ALIGN(4) {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } > RAM1

  .init_array : ALIGN(4) {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } > RAM1

  .fini_array : ALIGN(4) {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } > RAM1
  
  /* 
   * This section includes uninitialized data and will NOT be programmed 
   */
  .bss (NOLOAD) : ALIGN(4) {
    __bss_start__ = .;
    *(*.bss)
    *(.bss.*)
    *(.sbss)
    *(.sbss.*)
    *(COMMON)
    _bss_end = .;
    PROVIDE(end = .);
    PROVIDE(_end = .);
    PROVIDE(__bss_end__ = .);
  } > RAM1
  
  .heap (NOLOAD): ALIGN(16) {
    PROVIDE(__heap_start__ = .);
    *(.heap .heap.*)
    . += __heap_size__ ;
    . = ALIGN(16);
    PROVIDE(__heap_end__ = .);
  } > RAM1
  
  . = ASSERT(__heap_start__ == __heap_end__ || (__heap_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .heap is too large to fit in RAM1 memory segment");

  /* ensure there is enough room for stack */
  .stack (NOLOAD): ALIGN(4) {
    PROVIDE(__stack_start__ = .);
    *(.stack .stack.*);
    . += __stack_size__ ;
    . = ALIGN(4);
    stack = . ;
    _stack = . ;
    PROVIDE(__stack_end__ = .);
  } > RAM1

  . = ASSERT(__stack_start__ == __stack_end__ || (__stack_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .stack is too large to fit in RAM1 memory segment");
  . = ASSERT(__heap_end__ <= __stack_start__ , "error: section .heap overlaps absolute placed section .stack");
 
}