| Copyright 2022, Walter Pach. All rights reserved
| 
| Provides the firmware stabilization for the Motorola 68k processor.
| Startup and exception vectors. Must be placed in the first few bytes of ROM

| These will be linked into ROM.
| These will be linked into RAM
|.section .interrupt_vectors,"a"
/*
.long _stack                        | 00: Reset stack pointer (effectively read-only)
.long start                         | 01: Reset program counter (effectively read-only)
.long interrupt_fatal               | 02: Bus error: cycle couldn't complete properly

.long interrupt_fatal               | 03: Address error: Odd word exception
.long interrupt_fatal               | 04: Illegal instruction: invalid opcode
.long interrupt_fatal               | 05: Division by zero
.long interrupt_fatal               | 06: CHK instruction
.long interrupt_fatal               | 07: Trap
.long interrupt_fatal               | 08: Privilege violation
.long interrupt_fatal               | 09: Trace exception
.long interrupt_fatal               | 0A: Line A exception
.long interrupt_fatal               | 0B: Line B exception
.long interrupt_fatal               | 0C: Reserved 1
.long interrupt_fatal               | 0D: Reserved 2
.long interrupt_fatal               | 0E: Reserved 3
.long interrupt_fatal               | 0F: Uninitialized interrupt exception
.long interrupt_fatal               | 10: Reserved 4
.long interrupt_fatal               | 11: Reserved 5
.long interrupt_fatal               | 12: Reserved 6
.long interrupt_fatal               | 13: Reserved 7
.long interrupt_fatal               | 14: Reserved 8
.long interrupt_fatal               | 15: Reserved 9
.long interrupt_fatal               | 16: Reserved 10
.long interrupt_fatal               | 17: Reserved 11
.long interrupt_fatal               | 18: Spurious interrupt
.long interrupt_fatal               | 19: Level 1 interrupt
.long interrupt_fatal               | 1A: Level 2 interrupt
.long interrupt_fatal               | 1B: Level 3 interrupt
.long interrupt_fatal               | 1C: Level 4 interrupt
.long interrupt_fatal               | 1D: Level 5 interrupt
.long interrupt_fatal               | 1E: Level 6 interrupt
.long interrupt_fatal               | 1F: Level 7 interrupt
.long interrupt_fatal               | 20: Trap 0
.long interrupt_fatal               | 21: Trap 1
.long interrupt_fatal               | 22: Trap 2
.long interrupt_fatal               | 23: Trap 3
.long interrupt_fatal               | 24: Trap 4
.long interrupt_fatal               | 25: Trap 5
.long interrupt_fatal               | 26: Trap 6
.long interrupt_fatal               | 27: Trap 7
.long interrupt_fatal               | 28: Trap 8
.long interrupt_fatal               | 29: Trap 9
.long interrupt_fatal               | 2A: Trap A
.long interrupt_fatal               | 2B: Trap B
.long interrupt_fatal               | 2C: Trap C
.long interrupt_fatal               | 2D: Trap D
.long interrupt_fatal               | 2E: Trap E
.long interrupt_fatal               | 2F: Trap F
.long interrupt_fatal               | 30: Reserved
.long interrupt_fatal               | 31: Reserved
.long interrupt_fatal               | 32: Reserved
.long interrupt_fatal               | 33: Reserved
.long interrupt_fatal               | 34: Reserved
.long interrupt_fatal               | 35: Reserved
.long interrupt_fatal               | 36: Reserved
.long interrupt_fatal               | 37: Reserved
.long interrupt_fatal               | 38: Reserved
.long interrupt_fatal               | 39: Reserved
.long interrupt_fatal               | 3A: Reserved
.long interrupt_fatal               | 3B: Reserved
.long interrupt_fatal               | 3C: Reserved
.long interrupt_fatal               | 3D: Reserved
.long interrupt_fatal               | 3E: Reserved
.long interrupt_fatal               | 3F: Reserved
.long interrupt_user                | 40: User 0
.long interrupt_user                | 41: User 1
.long interrupt_user                | 42: User 2
.long interrupt_user                | 43: User 3
.long interrupt_user                | 44: User 4
.long interrupt_user                | 45: User 5
.long interrupt_user                | 46: User 6
.long interrupt_user                | 47: User 7
.long interrupt_user                | 48: User 8
.long interrupt_user                | 49: User 9
.long interrupt_user                | 4A: User 10
.long interrupt_user                | 4B: User 11
.long interrupt_user                | 4C: User 12
.long interrupt_user                | 4D: User 13
.long interrupt_user                | 4E: User 14
.long interrupt_user                | 4F: User 15
.long interrupt_user                | 50: User 16
.long interrupt_user                | 51: User 17
.long interrupt_user                | 52: User 18
.long interrupt_user                | 53: User 19
.long interrupt_user                | 54: User 20
.long interrupt_user                | 55: User 21
.long interrupt_user                | 56: User 22
.long interrupt_user                | 57: User 23
.long interrupt_user                | 58: User 24
.long interrupt_user                | 59: User 25
.long interrupt_user                | 5A: User 26
.long interrupt_user                | 5B: User 27
.long interrupt_user                | 5C: User 28
.long interrupt_user                | 5D: User 29
.long interrupt_user                | 5E: User 30
.long interrupt_user                | 5F: User 31
.long interrupt_user                | 60: User 32
.long interrupt_user                | 61: User 33
.long interrupt_user                | 62: User 34
.long interrupt_user                | 63: User 35
.long interrupt_user                | 64: User 36
.long interrupt_user                | 65: User 37
.long interrupt_user                | 66: User 38
.long interrupt_user                | 67: User 39
.long interrupt_user                | 68: User 40
.long interrupt_user                | 69: User 41
.long interrupt_user                | 6A: User 42
.long interrupt_user                | 6B: User 43
.long interrupt_user                | 6C: User 44
.long interrupt_user                | 6D: User 45
.long interrupt_user                | 6E: User 46
.long interrupt_user                | 6F: User 47
.long interrupt_user                | 70: User 48
.long interrupt_user                | 71: User 49
.long interrupt_user                | 72: User 50
.long interrupt_user                | 73: User 51
.long interrupt_user                | 74: User 52
.long interrupt_user                | 75: User 53
.long interrupt_user                | 76: User 54
.long interrupt_user                | 77: User 55
.long interrupt_user                | 78: User 56
.long interrupt_user                | 79: User 57
.long interrupt_user                | 7A: User 58
.long interrupt_user                | 7B: User 59
.long interrupt_user                | 7C: User 60
.long interrupt_user                | 7D: User 61
.long interrupt_user                | 7E: User 62
.long interrupt_user                | 7F: User 63
.long interrupt_user                | 80: User 64
.long interrupt_user                | 81: User 65
.long interrupt_user                | 82: User 66
.long interrupt_user                | 83: User 67
.long interrupt_user                | 84: User 68
.long interrupt_user                | 85: User 69
.long interrupt_user                | 86: User 70
.long interrupt_user                | 87: User 71
.long interrupt_user                | 88: User 72
.long interrupt_user                | 89: User 73
.long interrupt_user                | 8A: User 74
.long interrupt_user                | 8B: User 75
.long interrupt_user                | 8C: User 76
.long interrupt_user                | 8D: User 77
.long interrupt_user                | 8E: User 78
.long interrupt_user                | 8F: User 79
.long interrupt_user                | 90: User 80
.long interrupt_user                | 91: User 81
.long interrupt_user                | 92: User 82
.long interrupt_user                | 93: User 83
.long interrupt_user                | 94: User 84
.long interrupt_user                | 95: User 85
.long interrupt_user                | 96: User 86
.long interrupt_user                | 97: User 87
.long interrupt_user                | 98: User 88
.long interrupt_user                | 99: User 89
.long interrupt_user                | 9A: User 90
.long interrupt_user                | 9B: User 91
.long interrupt_user                | 9C: User 92
.long interrupt_user                | 9D: User 93
.long interrupt_user                | 9E: User 94
.long interrupt_user                | 9F: User 95
.long interrupt_user                | A0: User 96
.long interrupt_user                | A1: User 97
.long interrupt_user                | A2: User 98
.long interrupt_user                | A3: User 99
.long interrupt_user                | A4: User 100
.long interrupt_user                | A5: User 101
.long interrupt_user                | A6: User 102
.long interrupt_user                | A7: User 103
.long interrupt_user                | A8: User 104
.long interrupt_user                | A9: User 105
.long interrupt_user                | B0: User 106
.long interrupt_user                | B1: User 107
.long interrupt_user                | B2: User 108
.long interrupt_user                | B3: User 109
.long interrupt_user                | B4: User 110
.long interrupt_user                | B5: User 111
.long interrupt_user                | B6: User 112
.long interrupt_user                | B7: User 113
.long interrupt_user                | B8: User 114
.long interrupt_user                | B9: User 115
.long interrupt_user                | BA: User 116
.long interrupt_user                | BB: User 117
.long interrupt_user                | BC: User 118
.long interrupt_user                | BD: User 119
.long interrupt_user                | BE: User 120
.long interrupt_user                | BF: User 121
.long interrupt_user                | C0: User 122
.long interrupt_user                | C1: User 123
.long interrupt_user                | C2: User 124
.long interrupt_user                | C3: User 125
.long interrupt_user                | C4: User 126
.long interrupt_user                | C5: User 127
.long interrupt_user                | C6: User 128
.long interrupt_user                | C7: User 129
.long interrupt_user                | C8: User 130
.long interrupt_user                | C9: User 131
.long interrupt_user                | CA: User 132
.long interrupt_user                | CB: User 133
.long interrupt_user                | CC: User 134
.long interrupt_user                | CD: User 135
.long interrupt_user                | CE: User 136
.long interrupt_user                | CF: User 137
.long interrupt_user                | D0: User 138
.long interrupt_user                | D1: User 139
.long interrupt_user                | D2: User 140
.long interrupt_user                | D3: User 141
.long interrupt_user                | D4: User 142
.long interrupt_user                | D5: User 143
.long interrupt_user                | D6: User 144
.long interrupt_user                | D7: User 145
.long interrupt_user                | D8: User 146
.long interrupt_user                | D9: User 147
.long interrupt_user                | DA: User 148
.long interrupt_user                | DB: User 149
.long interrupt_user                | DC: User 150
.long interrupt_user                | DD: User 151
.long interrupt_user                | DE: User 152
.long interrupt_user                | DF: User 153
.long interrupt_user                | E0: User 154
.long interrupt_user                | E1: User 155
.long interrupt_user                | E2: User 156
.long interrupt_user                | E3: User 157
.long interrupt_user                | E4: User 158
.long interrupt_user                | E5: User 159
.long interrupt_user                | E6: User 160
.long interrupt_user                | E7: User 161
.long interrupt_user                | E8: User 162
.long interrupt_user                | E9: User 163
.long interrupt_user                | EA: User 164
.long interrupt_user                | EB: User 165
.long interrupt_user                | EC: User 166
.long interrupt_user                | ED: User 167
.long interrupt_user                | EE: User 168
.long interrupt_user                | EF: User 169
.long interrupt_user                | F0: User 170
.long interrupt_user                | F1: User 171
.long interrupt_user                | F2: User 172
.long interrupt_user                | F3: User 173
.long interrupt_user                | F4: User 174
.long interrupt_user                | F5: User 175
.long interrupt_user                | F6: User 176
.long interrupt_user                | F7: User 177
.long interrupt_user                | F8: User 178
.long interrupt_user                | F9: User 179
.long interrupt_user                | FA: User 180
.long interrupt_user                | FB: User 181
.long interrupt_user                | FC: User 182
.long interrupt_user                | FD: User 183
.long interrupt_user                | FE: User 184
.long interrupt_user                | FF: User 185
*/
| Ends at 1kb


| This section will be loaded into ROM
.section .text

.global __start
__start:
    nop
    bra __start

.global vector_fatal
vector_fatal:
.loop:
    move 0xFFFF, 0x800000
    bra .loop
