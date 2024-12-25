#pragma once

#include "mem.h"
#include "util.h"

#define REG_CNT 19

enum e_FlagBit {
  CY, // carry
  OF, // overflow
  ZE, // zero
  TO, // timer on
  TF, // timer overflow
  IN, // internal flag for jumps and SWR
  SS, // internal flag for when operand is on stack
  SM, // internal flag for when operand is in memory
};

/* Prefixes:
 * rb/rw: register (internal byte or word)
 * pb/pw: port (external byte or word) */
class Processor {
private:
  word rw_prg_ctr; // Program counter
  word rw_stk_ptr; // Stack pointer

  byte rb_flg; // Flag register

  byte rb_ins; // Instruction register
  byte rb_opd; // Operand register
  byte rb_aux; // Auxiliary register 1
  word rw_aux; // Auxiliary register 2

  bool RW;

  byte rb_acc; // Accumulator register
  byte rb_ctr; // Counter register
  byte rb_adh; // Address register high byte
  byte rb_adl; // Address register low byte

  word pw_addr; // Address port
  byte pb_data; // Data port

  word rw_timer; // 16-bit timer

  /* Working register; usually A or C, except for ADR */
  byte *rb_wrk = &rb_acc;
  word *rw_wrk;

  Memory *_ROM;
  Memory *_RAM;

  const word addr();
  const bool get_flag(e_FlagBit flag);

  void set_flag(e_FlagBit flag, bool condition);

  /* These functions are used for decoding instructions */
  const bool has_operand();
  const bool is_JMP();
  const bool is_ADR();
  const bool is_FLG();
  const bool is_STV();
  const bool is_POP();
  const bool is_PSH();
  const bool is_ROT();
  const bool is_ALU_op();
  const bool is_STK_op();

  void readROM(const word addr, byte *dest);
  void readRAM(const word addr, byte *dest);
  void writeRAM(const word addr, byte *data);

  /* Push and pop operations on the stack (first 16 bytes of RAM).
   * These do NOT safeguard against stack overflow. */
  void push(byte *data);
  void pop(byte *dest);

  /* Fetch the next instruction. This increments the program counter. */
  void fetch(byte *dest);
  /* Decode the current instruction. */
  void decode();
  void set_operand();
  void exec_operation();
  void exec_SWR_operation();
  void exec_operation(bool is_jump);
  void exec_ALU_operation();
  bool eval_overflow(word sum);
  void exec_rotate();

public:
  Processor(Memory *ROM, Memory *RAM) : _ROM(ROM), _RAM(RAM) {
    _ROM->_addr_bus = &pw_addr;
    _ROM->_data_bus = &pb_data;
    _ROM->RW = &RW;

    _RAM->_addr_bus = &pw_addr;
    _RAM->_data_bus = &pb_data;
    _RAM->RW = &RW;
  }

  void reset();

  void cycle();

  /* Writes all the registers to dest in the following order:
   * Flag register        (1)
   * Program counter      (2)
   * Stack pointer        (2)
   * Opcode               (1)
   * Operand              (1)
   * Address register     (2)
   * Accumulator          (1)
   * Counter              (1)
   * Timer                (2)
   * Auxiliary register 1 (1)
   * Auxiliary register 2 (2)
   * Data port            (1)
   * Address port         (2)
   * */
  void get_registers(byte *dest);
};
