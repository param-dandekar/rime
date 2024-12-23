#pragma once

#include "mem.h"
#include "util.h"
#include <cstdint>

#define REG_CNT 6
#define PRT_CNT 2

enum e_FlagBit {
  CY, // carry
  OF, // overflow
  ZE, // zero
  TO, // timer on
  TF, // timer overflow
  JP, // internal flag for jumps
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

  bool src_in_stack;
  bool src_in_memory;

  byte rb_acc; // Accumulator register
  byte rb_ctr; // Counter register
  byte rb_adh; // Address register high byte
  byte rb_adl; // Address register low byte

  word pw_addr; // Address port
  byte pb_data; // Data port

  word rw_timer; // 16-bit timer

  /* Working register; usually A or C, except for ADR */
  byte *rb_wrk = &rb_acc;

  Memory *_ROM;
  Memory *_RAM;

  const word addr();
  const bool get_flag(e_FlagBit flag);
  const void set_flag(e_FlagBit flag);
  const void clr_flag(e_FlagBit flag);

  /* These functions are used for decoding instructions */
  const bool has_operand();
  const bool is_ADR();
  const bool is_FLG();
  const bool is_STV();
  const bool is_POP();
  const bool is_PSH();
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
  void exec_operation(bool is_jump);
  void exec_ALU_operation();
  bool eval_overflow(word sum);
  void exec_rotate();

public:
  Processor(Memory *ROM, Memory *RAM) : _ROM(ROM), _RAM(RAM) {
    _ROM->_addr_bus = &pw_addr;
    _ROM->_data_bus = &pb_data;
    _RAM->_addr_bus = &pw_addr;
    _RAM->_data_bus = &pb_data;
  }

  void cycle();

  /* Writes all the registers to dest in the following order:
   * Program counter
   * Stack pointer
   * Current opcode and operand
   * Address register
   * Accumulator and counter
   * Timer
   * Flag register
   * Address port
   * Data port (lower byte only)
   * */
  void get_registers(uint16_t *dest);
};
