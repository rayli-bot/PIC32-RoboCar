/* Default linker script, for normal executables */
/*OUTPUT_FORMAT("elf32-littlemips")*/
OUTPUT_FORMAT("elf32-tradlittlemips")
OUTPUT_ARCH(mips)
ENTRY(_reset)
/*
 * Provide for a minimum stack and heap size
 * - _min_stack_size - represents the minimum space that must be made
 *                     available for the stack.  Can be overridden from
 *                     the command line using the linker's --defsym option.
 * - _min_heap_size  - represents the minimum space that must be made
 *                     available for the heap.  Can be overridden from
 *                     the command line using the linker's --defsym option.
 */
EXTERN (_min_stack_size _min_heap_size)
PROVIDE(_min_stack_size = 0x400) ;
/* PROVIDE(_min_heap_size = 0) ; Defined on the command line */
/*************************************************************************
 * Processor-specific object file.  Contains SFR definitions.
 *************************************************************************/
INPUT("../../p32mx250f128/processor.o")

/*************************************************************************
 * Processor-specific peripheral libraries are optional
 *************************************************************************/
/* OPTIONAL("libmchp_peripheral.a")              */
/* OPTIONAL("libmchp_peripheral_32MX250F128D.a") */

/*************************************************************************
 * For interrupt vector handling
 *************************************************************************/
PROVIDE(_vector_spacing = 0x00000001);
_ebase_address =  0x9D003000;

/*************************************************************************
 * Memory Address Equates
 * _RESET_ADDR      -- Reset Vector
 * _BEV_EXCPT_ADDR  -- Boot exception Vector
 * _DBG_EXCPT_ADDR  -- In-circuit Debugging Exception Vector
 * _DBG_CODE_ADDR   -- In-circuit Debug Executive address
 * _DBG_CODE_SIZE   -- In-circuit Debug Executive size
 * _GEN_EXCPT_ADDR  -- General Exception Vector
 *************************************************************************/
_RESET_ADDR              = 0x9D004000;
_BEV_EXCPT_ADDR          = 0x9D004380;
_DBG_EXCPT_ADDR          = 0x9D004480;
_DBG_CODE_ADDR           = 0xBFC02000;
_DBG_CODE_SIZE           = 0x760     ;
_GEN_EXCPT_ADDR          = _ebase_address + 0x180;

/*************************************************************************
 * Memory Regions
 *
 * Memory regions without attributes cannot be used for orphaned sections.
 * Only sections specifically assigned to these regions can be allocated
 * into these regions.
 *************************************************************************/
MEMORY
{
  kseg0_program_mem    (rx)  : ORIGIN = 0x9D004010, LENGTH = 0x1BFF0 /* All C Files will be located here */ 
  exception_mem              : ORIGIN = 0x9D003000, LENGTH = 0xA00 /* Interrupt vector table */
  debug_exec_mem             : ORIGIN = 0x9FC00490, LENGTH = 0x760
  kseg0_boot_mem             : ORIGIN = 0x9D003A00, LENGTH = 0x600
  kseg1_boot_mem             : ORIGIN = 0x9D004000, LENGTH = 0x10 /* C Startup code */
  devcfg3                    : ORIGIN = 0xBFC00BF0, LENGTH = 0x4
  devcfg2                    : ORIGIN = 0xBFC00BF4, LENGTH = 0x4
  devcfg1                    : ORIGIN = 0xBFC00BF8, LENGTH = 0x4
  devcfg0                    : ORIGIN = 0xBFC00BFC, LENGTH = 0x4
  boot_software_key          : ORIGIN = 0xA0000000, LENGTH = 0x4
  kseg1_data_mem       (w!x) : ORIGIN = 0xA0000004, LENGTH = 0x7FFC
  sfrs                       : ORIGIN = 0xBF800000, LENGTH = 0x100000
  devcfg                     : ORIGIN = 0xBFC00BF0, LENGTH = 0x10
}

/*************************************************************************
 * Configuration-word sections
 *************************************************************************/
SECTIONS
{
  .config_BFC00BF0 : {
    KEEP(*(.config_BFC00BF0))
  } > devcfg3
  .config_BFC00BF4 : {
    KEEP(*(.config_BFC00BF4))
  } > devcfg2
  .config_BFC00BF8 : {
    KEEP(*(.config_BFC00BF8))
  } > devcfg1
  .config_BFC00BFC : {
    KEEP(*(.config_BFC00BFC))
  } > devcfg0
}

INCLUDE ../../p32mx250f128/elf32pic32mx.x
