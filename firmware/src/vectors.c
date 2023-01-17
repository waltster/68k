#include <types.h>

extern const uint32_t __stack;
extern const uint32_t __start;

/*
 * extern void vector_address_error(void);
 * extern void vector_trap(void);
 * extern void vector_bus_error(void);
 * extern void vector_syscall(void);
 */
extern void vector_fatal(void);

__attribute__((section(".vectors"))) const uint32_t _vectors[256] = {
    (uint32_t)&__stack,     // 00: Reset stack pointer
    (uint32_t)&__start,     // 01: Reset programming counter
    (uint32_t)vector_fatal, // 02: Bus error: cycle couldn't complete properly
    (uint32_t)vector_fatal, // 03: Address error: Odd word exception
    (uint32_t)vector_fatal, // 04: Illegal instruction: invalid opcode
    (uint32_t)vector_fatal, // 05: Division by zero
    (uint32_t)vector_fatal, // 06: CHK instruction
    (uint32_t)vector_fatal, // 07: Trap
    (uint32_t)vector_fatal, // 08: Privilege violation
    (uint32_t)vector_fatal, // 09: Trace exception
    (uint32_t)vector_fatal, // 0A: Line A exception
    (uint32_t)vector_fatal, // 0B: Line B exception
    (uint32_t)vector_fatal, // 0C: Reserved 1
    (uint32_t)vector_fatal, // 0D: Reserved 2
    (uint32_t)vector_fatal, // 0E: Reserved 3
    (uint32_t)vector_fatal, // 0F: Uninitialized interrupt exception
    (uint32_t)vector_fatal, // 10: Reserved 4
    (uint32_t)vector_fatal, // 11: Reserved 5
    (uint32_t)vector_fatal, // 12: Reserved 6
    (uint32_t)vector_fatal, // 13: Reserved 7
    (uint32_t)vector_fatal, // 14: Reserved 8
    (uint32_t)vector_fatal, // 15: Reserved 9
    (uint32_t)vector_fatal, // 16: Reserved 10
    (uint32_t)vector_fatal, // 17: Reserved 11
    (uint32_t)vector_fatal, // 18: Spurious interrupt
    (uint32_t)vector_fatal, // 19: Level 1 interrupt
    (uint32_t)vector_fatal, // 1A: Level 2 interrupt
    (uint32_t)vector_fatal, // 1B: Level 3 interrupt
    (uint32_t)vector_fatal, // 1C: Level 4 interrupt
    (uint32_t)vector_fatal, // 1D: Level 5 interrupt
    (uint32_t)vector_fatal, // 1E: Level 6 interrupt
    (uint32_t)vector_fatal, // 1F: Level 7 interrupt
    (uint32_t)vector_fatal, // 20: Trap 0
    (uint32_t)vector_fatal, // 21: Trap 1
    (uint32_t)vector_fatal, // 22: Trap 2
    (uint32_t)vector_fatal, // 23: Trap 3
    (uint32_t)vector_fatal, // 24: Trap 4
    (uint32_t)vector_fatal, // 25: Trap 5
    (uint32_t)vector_fatal, // 26: Trap 6
    (uint32_t)vector_fatal, // 27: Trap 7
    (uint32_t)vector_fatal, // 28: Trap 8
    (uint32_t)vector_fatal, // 29: Trap 9
    (uint32_t)vector_fatal, // 2A: Trap A
    (uint32_t)vector_fatal, // 2B: Trap B
    (uint32_t)vector_fatal, // 2C: Trap C
    (uint32_t)vector_fatal, // 2D: Trap D
    (uint32_t)vector_fatal, // 2E: Trap E
    (uint32_t)vector_fatal, // 2F: Trap F
    (uint32_t)vector_fatal, // 
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
    (uint32_t)vector_fatal, //
};
