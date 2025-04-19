.section ".text.boot"
.globl _start

_start:

.section .vectors, "a"
.align 5

.global _vector_table
_vector_table:
    ldr pc, =reset
    ldr pc, =undefined_instruction
    ldr pc, =svc_handler
    ldr pc, =prefetch_abort
    ldr pc, =data_abort
    ldr pc, =.
    ldr pc, =irq_handler
    ldr pc, =fiq_handler

.section ".text.boot"
reset:
    // by default qemu starts with all cores enabled
    mrc p15, #0, r1, c0, c0, #5
    and r1, r1, #3
    cmp r1, #0
    bne hang

    // Save cpsr and setup sp in svc mode
    mrs r0, cpsr
    bic r1, r0, #0x1F
    orr r1, r1, #0x13
    msr cpsr_c, r1
    mov sp, #0x8000

    // Set VBAR
    ldr r0, =_vector_table
    mcr p15, 0, r0, c12, c0, 0

    // Clear BSS
    ldr r4, =__bss_start
    ldr r9, =__bss_end
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b 2f

1:
    stmia r4!, {r5-r8}
2:
    cmp r4, r9
    blo 1b

    //MMU init
    ldr r3,=mmu_init
    blx r3

    // Call kernel_main
    ldr r3,=kmain
    blx r3

hang:
    wfi
    b hang
