/* ============================================================================
 * Linker Script for Userspace Programs (Flat Binary Format)
 * All sections merged into .text for raw binary output
 * ============================================================================ */

OUTPUT_FORMAT(binary)
ENTRY(_start)

SECTIONS
{
    /* Start at userspace base address */
    . = 0x08000000;
    
    /* Merge all sections into .text for flat binary */
    .text : {
        *(.text*)
        *(.rodata*)
        *(.data*)
        *(.bss*)
    }
    
    /* Discard unnecessary sections */
    /DISCARD/ : {
        *(.note*)
        *(.comment*)
        *(.eh_frame*)
    }
}