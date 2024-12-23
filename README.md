# Architecture

## Registers

There are six 8-bit registers and five 16-bit registers. They can be divided into the following categories:

### General-purpose registers

These are used directly during programming.

**8-bit registers:**
- Accumulator (`A` or `ACC`)
- Counter (`C` or `CTR`)

**16-bit registers:**
- Address register (`ADDR`; `H/L` or `ADH/ADL` for the individual bytes)

### State registers

These keep track of the state of the processor.

**8-bit registers:**
- Flag register (`FR` or `FLG`)
- Opcode register (`OPC`)
- Operand register (`OPD`)
- Auxiliary register 1 (`AUX1`)

**16-bit registers:**
- Program counter (`PC`)
- Stack pointer (`SP`)
- Auxiliary register 2 (`AUX2`)
- Timer/counter register (`TMR` or `TIMER`)

## Flags

There are five main flags:

- `CY`: carry flag
- `OF`: overflow flag
- `ZE`: zero flag
- `TO`: timer on/off flag
- `TF`: timer overflow flag

There are also three internal flags:

- `JP`: jump flag
- `SS` and `SM`: flags used for retrieval of operand from memory

They are arranged in the following order:

| 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0  |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
| `SM` | `SS` | `JP` | `TF` | `TR` | `ZE` | `OF` | `CY` |

# Instruction set

Instructions may have zero or two operands. For instructions with two operands, one operand is determined by the addressing mode, which is specified by the first two bits in the opcode; the other operand is one of the general-purpose registers, and is chosen by the third bit. The `ADR` instruction (set address register), this is either `H` or `L`, and for all other two-operand instructions, it is `A` or `C`.

If the first bit in a jump instruction is set, the jump condition is inverted. This does not apply to the `JDC` instruction (decrement counter and jump if not zero).

The last two bits of the `SWR` instruction (swap register) are used to choose the registers to swap. The last two bits of the `FLG` instruction (operate on flag register) choose the operation to execute.

## Addressing modes

| Value | Mode | Syntax | Description |
|:-:|:-:|:-:|:-:|
| 00 | Stack     | `STK`  | The top of the stack is popped and taken as operand. |
| 01 | Immediate | `#XX`  | The next byte is the operand.                        |
| 10 | Indirect  | `@ADR` | The address register points to the operand address.  |
| 11 | Direct    | `&XX`  | The next byte points to the operand address.         |

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
- `b0`: 1 = right-shift/decrement, 0 = left-shift/increment
- `b1`: 1 = shift/rotation, 0 = crement
- `b2`: 1 = circular, 0 = not circular (no effect on crements)
