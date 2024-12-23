# Architecture

## Flags

There are the following flags:

 - C: carry flag
 - O: overflow flag
 - Z: zero flag
 - R0, R1, R2: rotation control flags

They are arranged in the following order:

R2 R1 R0 -- -- Z  O  C

## Memory layout

There are 256 bytes of RAM:

| Start | End | Length | Name        |
| :---: | :-: | :----: | :---------: |
| 0x00  | 0x0F| 16     | Stack (STK) |
| 0x10  | 0xFF| 240    | Memory (MEM)|

There are also some internal registers:

1. Accumulator (A, ACC)
2. Counter (C, CTR)
3. Address high (H, ADH)
4. Address low (L, ADL)


# Instruction set

Instructions are divided into the following three types:

1. Memory instructions
2. ALU instructions
3. Jump instructions

Instructions may have zero, one or two operands. The first operand is determined by the addressing mode, which is specified by the first two bits in the opcode.
If the first bit in a jump instruction is set, the jump condition is inverted.

## Addressing modes

| Value | Mode | Syntax | Description |
|:-:|:-:|:-:|:-:|
| 00 | Stack     | STK | The top of the stack is popped and taken as operand. |
| 01 | Immediate | #XX | The next byte is the operand.                        |
| 10 | Indirect  | @HL | The address registers point to the operand address.  |
| 11 | Direct    | &XX | The next byte points to the operand address.         |

When direct or immediate addressing is used, the program counter is autoincremented.

The third bit indicates which register instructions with two operands should operate on (0 for `A`, 1 for `C`). For example:
```
0101 0100 : STV #XX,A : Store the hex value XXh in A
1011 1000 : ADD @HL,C : Add the value pointed by the address registers in RAM, to C
```
The only exception to this is the `set address register` instruction, which uses the third bit to choose the byte of the address register (0 for `L`, 1 for `H`):
```
0010 0100 : ADR STK,H : Store value at the top of the stack in H
0100 0100 : ADR #XX,H : Store the hex value XXh in L
```

## Instructions

#### SWR

The action depends on the last two bits. If they are 00, 01, or 02, the accumulator with the counter, flag register, or data port, respectively. If they are 11, the value of the timer register is switched with A and C


### ALU instructions

#### ROT

This performs shifts, rotations, and crements on the working register, according to the operand:
 - b0: 1 = right-shift/decrement, 0 = left-shift/increment
 - b1: 1 = shift/rotation, 0 = crement
 - b2: 1 = circular, 0 = not circular (no effect on crements)
