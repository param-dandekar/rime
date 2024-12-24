# Architecture

## Registers

There are seven 8-bit registers and six 16-bit registers. They can be divided into the following categories:

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

### Ports

These are output ports.

8-bit registers:
- Data port (`DP`)

16-bit registers:
- Address port (`AP`)

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

The addressing modes work differently for the `STV` instruction (store value of register). This is elaborated on in the instruction description.

## Addressing modes

| Value | Mode | Syntax | Description |
|:-:|:-:|:-:|:-:|
| 00 | Stack     | `STK`  | The top of the stack is popped and taken as operand. |
| 01 | Immediate | `#XX`  | The next byte is the operand.                        |
| 10 | Indirect  | `@ADR` | The address register points to the operand address.  |
| 11 | Direct    | `&XX`  | The next byte points to the operand address.         |

When direct or immediate addressing is used, the program counter is autoincremented as the operand is read.

For example:
```
LDV #XX A // 0101 0110 : Load the literal value XX into A

ADD @HL C // 1011 1000 : Add the value in RAM pointed to by the address registers, to C

ADR STK H // 0010 1000: Store value at the top of the stack in H
```

## Primitive instructions

These instructions exist in the processor itself.

### Zero-operand instructions

#### `NOP` : 0000 0000
**No operation.**\
The processor does nothing on this clock cycle, and goes ahead to the next instruction.

#### `RST` : 0000 0001
**Resets the processor.**\
All registers are set to 0. This has the effect of moving the execution of the program to the start.

#### `SWR` : 0000 01__
**Swap registers.**\
The exact action depends on the last two bits:
- 00, 01, or 02: `ACC` is switched with `CTR`, `FLG`, or `DP`, respectively
- 11: `TIMER` is switched with `A` (high byte) and `C` (low byte)

#### `ADR` : ___0 1000
**Set address register.**\
Stores the operand in the specified byte of the address register.

#### `FLG` : ___0 11__
**Operate on flag registers.**\
Executes a bitwise AND, OR, or XOR on the flag register. The last two bits specify the operation:

- 00 = AND
- 01 = OR
- 10 = XOR

This can be used to set, clear, or flip flags.

#### `PSH` : ___1 0100
**Push value to stack.**\
This stores the value of the working register to the top of the stack (the location pointed to by the stack pointer), and increments the stack pointer.

#### `POP` : 0001 0101
**Pop value from stack.**\
This stores the value of the top of the stack to the working register, and decrements the stack pointer.

#### `STV` : ___1 0110
**Store value from register.**\
This stores the value of the working register to the specified location:
- Stack addressing: the value is pushed to the top of the stack
- Direct and indirect addressing: the value is stored at the location pointed to by the address register

Immediate addressing is invalid for this instruciton and results in a NOP.

#### `LDV` : ___1 0111
**Load value to register.**\
The operand is loaded into the working register.

#### `ADD` : ___1 1000
**Add without carry.**\
#### `ADC` : ___1 1001
**Add with carry.**\
#### `SUB` : ___1 1010
**Subtract without carry.**\
This is also used for comparison of two numbers:
- If the operand is smaller than the register, no flag is set
- If the operand and register value are equal, the zero flag is set.
- If the operand is larger than the register, the overflow flag is set.

#### `SBC` : ___1 1011
**Subtract with carry.**\
#### `ORR` : ___1 1100
**Logical OR.**\
#### `AND` : ___1 1101
**Logical AND.**\
#### `XOR` : ___1 1110
**Logical XOR/**\
#### `ROT` : ___1 1111
**Bit-shift, rotate, increment, or decrement.**\
This instruction operates on the working register. The last three bits of the operand determine the action:
- `bit 0`: 1 = right-shift/decrement, 0 = left-shift/increment
- `bit 1`: 1 = shift/rotation, 0 = increment/decrement
- `bit 2`: 1 = circular, 0 = not circular (no effect on increment or decrement)

#### `JMP` : _010 0000
**Jump unconditionally.**\
#### `JNE` : 0010 0001
**Jump if not equal to.**\
Jumps if the zero flag is set.

#### `JEQ` : 1010 0001
**Jump if equal to.**\
Jumps if the zero flag is not set.

#### `JLT` : 0010 0010
**Jump if less than.**\
Jumps if the overflow flag is set and the zero flag is not set.

#### `JGE` : 1010 0010
**Jump if greater than or equal to.**\
Jumps if the overflow flag is not set or the zero flag is set.

#### `JDC` : 0010 0011
**Decrement counter and jump if not zero.**\
If `CTR` is zero, do nothing. Otherwise, decrement the value of `CTR`.


