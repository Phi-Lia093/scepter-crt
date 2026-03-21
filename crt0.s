/* ============================================================================
 * C Runtime Startup (crt0.s)
 * Entry point for userspace programs
 * ============================================================================ */

.section .text
.global _start

_start:
    /* Set up user stack at top of user space (below kernel at 0xC0000000)
     * Build the address in a way that won't be relocated */
    xor %esp, %esp              /* ESP = 0 */
    not %esp                    /* ESP = 0xFFFFFFFF */
    sub $0x40000003, %esp       /* ESP = 0xBFFFFFC */
    
    /* Call main() - no arguments for now */
    call main
    
    /* main() returned - exit with its return value */
    movl %eax, %ebx             /* exit status from main's return value */
    movl $1, %eax               /* SYS_EXIT */
    int $0x80
    
    /* Should never reach here, but just in case */
.hang:
    hlt
    jmp .hang

/* ============================================================================
 * Data
 * ============================================================================ */

.section .rodata
dev_tty0:
    .asciz "/dev/tty0"