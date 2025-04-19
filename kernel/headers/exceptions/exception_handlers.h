#ifndef EXCEPTION_HANDLERS_H
#define EXCEPTION_HANDLERS_H

void handle_svc(unsigned int *regs);
void handle_data_abort(unsigned int *regs);
void handle_prefetch_abort(unsigned int *regs);

#endif /* EXCEPTION_HANDLERS_H */
