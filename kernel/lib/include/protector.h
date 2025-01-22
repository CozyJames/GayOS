#ifndef STACK_PROTECTOR_H
#define STACK_PROTECTOR_H

#include <stdint.h>

extern uintptr_t __stack_chk_guard;

__attribute__((noreturn)) void __stack_chk_fail(void);

#endif /* STACK_PROTECTOR_H */
