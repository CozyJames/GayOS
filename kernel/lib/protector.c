#include <stdint.h>
#include "include/protector.h"
#include "include/panic.h"

// Глобальная переменная для stack canary.
uintptr_t __stack_chk_guard = 0xBAADF00D; // В идеале, при загрузке ядра можно поменять её на случайное значение.

// Функция, вызываемая, если при выходе из функции канарейка (__stack_chk_guard) не совпала с сохранённой. Обычно здесь вызывают panic() или останавливают систему.
__attribute__((noreturn)) void __stack_chk_fail(void)
{
    panic("Stack smashing detected!");
}
