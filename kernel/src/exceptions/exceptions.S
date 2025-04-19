.section ".text.boot"

.global undefined_instruction
undefined_instruction:
    b .

.global prefetch_abort
prefetch_abort:
    b .

.global data_abort
data_abort:
    sub sp, sp, #68
    stmia sp, {r0-r12, lr}
    mrs r1, spsr
    str r1, [sp, #64]

    mrs r2, spsr
    tst r2, #0x20
    subne lr, lr, #2
    subeq lr, lr, #4
    add lr, lr, #4

    mov r0, sp
    bl handle_data_abort

    ldr r1, [sp, #64]
    msr spsr_cxsf, r1
    ldmia sp, {r0-r12, lr}
    add sp, sp, #68

    movs pc, lr

.global irq_handler
irq_handler:
    b .

.global fiq_handler
fiq_handler:
    b .

.global svc_handler
svc_handler:
    sub sp, sp, #68
    stmia sp, {r0-r12, lr}
    mrs r1, spsr
    str r1, [sp, #64]

    mov r0, sp
    bl handle_svc

    ldr r1, [sp, #64]
    msr spsr_cxsf, r1
    ldmia sp, {r0-r12, lr}
    add sp, sp, #68

    movs pc, lr
