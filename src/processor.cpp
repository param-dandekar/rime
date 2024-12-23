#include "processor.h"
#include "util.h"

const word Processor::addr() { return (rb_adh << 8) | rb_adl; }

const bool Processor::get_flag(e_FlagBit flag) { return rb_flg[flag]; }

void Processor::set_flag(e_FlagBit flag, bool condition) {
  if (condition) {
    rb_flg = rb_flg | (1 << flag);
  } else {
    rb_flg = rb_flg & ~(1 << flag);
  }
}

/* True if has an operand */
const bool Processor::has_operand() {
  return (rb_ins[4] || is_ADR() || is_FLG());
}

const bool Processor::is_ADR() { return (rb_ins & 0x1F) == 0x08; }

/* True if instruction matches ___0 01__ */
const bool Processor::is_FLG() { return (rb_ins & 0x1C) == 0x0C; }

/* True if instruction matches ___1 0110 */
const bool Processor::is_STV() { return (rb_ins & 0x1F) == 0x16; }

/* True if instruction matches ___1 0100 */
const bool Processor::is_PSH() { return (rb_ins & 0x1F) == 0x14; }

/* True if instruction matches ___1 0100 */
const bool Processor::is_POP() { return (rb_ins & 0x1F) == 0x15; }

/* False if instruction matches ___1 010_ */
const bool Processor::is_STK_op() { return (rb_ins & 0x1E) == 0x14; }

/* True if instruction matches ___1 1___ */
const bool Processor::is_ALU_op() { return (rb_ins & 0x18) == 0x18; }

void Processor::reset() {
  rw_prg_ctr = 0;
  rw_stk_ptr = 0;

  rb_flg = 0;

  rb_ins = 0;
  rb_opd = 0;
  rb_aux = 0;
  rw_aux = 0;

  RW = 0;

  rb_acc = 0;
  rb_ctr = 0;
  rb_adh = 0;
  rb_adl = 0;

  pw_addr = 0;
  pb_data = 0;
}

void Processor::readROM(const word addr, byte *dest) {
  pw_addr = addr;
  RW = READ;
  _ROM->update();
  *dest = pb_data;
}

void Processor::readRAM(const word addr, byte *dest) {
  pw_addr = addr;
  RW = READ;
  _RAM->update();
  *dest = pb_data;
}

void Processor::writeRAM(const word addr, byte *dest) {
  pw_addr = addr;
  pb_data = *dest;
  RW = WRITE;
  _RAM->update();
}

void Processor::push(byte *dest) {
  pw_addr = rw_stk_ptr++;
  pb_data = *dest;
  RW = WRITE;
  _RAM->update();
}

void Processor::pop(byte *dest) {
  pw_addr = rw_stk_ptr--;
  RW = READ;
  _RAM->update();
  *dest = pb_data;
}

void Processor::fetch(byte *dest) {
  pw_addr = rw_prg_ctr++;
  RW = READ;
  _ROM->update();
  *dest = pb_data;
}

void Processor::set_operand() {
  /* Bit 6 indicates whether the next bit has to be read */
  if (rb_ins[6]) {
    fetch(&rb_opd);
  }

  /* If both bits are unset, the operand is in the stack */
  set_flag(SS, (rb_ins & 0xC0) == 0);
  ;
  /* Bit 7 indicates whether the operand is in memory */
  set_flag(SM, rb_ins[7]);
}

void Processor::exec_operation(bool is_jump) {
  if (is_jump) {
    set_flag(JP, 0);
    if ((rb_ins & 0x0F) == 0x3) {
      if (!rb_ctr) {
        return;
      }
      rb_ctr--;
      set_flag(JP, 1);
    } else {
      switch ((rb_ins & 0x0F)) {
      case 0:
        set_flag(JP, 1);
        break;
      case 1:
        set_flag(JP, get_flag(ZE));
        break;
      case 2:
        set_flag(JP, get_flag(CY));
        break;
      }
    }

    if (get_flag(JP) ^ rb_ins[7]) {
      rw_prg_ctr = addr() + 1;
    }
  } else {
    if ((rb_ins & 0xFC) == 0x04) { // SWR
      if ((rb_ins & 0x03) == 0x03) {
        set_flag(TO, 0);
        rb_aux = rb_ctr;
        rb_ctr = (rw_timer & 0xFF);
        rw_timer = (rw_timer & 0xFF00) | (rb_aux);
        rb_aux = rb_acc;
        rb_acc = (rw_timer >> 8) & 0xFF;
        rw_timer = (rw_timer & 0x00FF) | (rb_aux << 8);
      } else {
        switch (rb_ins & 0x03) {
        case 0:
          rb_aux = rb_ctr;
          rb_ctr = rb_acc;
          break;
        case 1:
          rb_aux = rb_flg;
          rb_flg = rb_acc;
          break;
        case 2:
          rb_aux = pb_data;
          pb_data = rb_acc;
          break;
        }
        rb_acc = rb_aux;
      }
    }
    switch (rb_ins & 0x0F) {
    case 0: // NOP
      return;
    default: // NOP
      return;
    }
  }
}

void Processor::exec_operation() {
  if (is_FLG()) {
    switch (rb_ins & 0x13) {
    case 0:
      rb_flg = rb_flg & rb_opd;
      break;
    case 1:
      rb_flg = rb_flg | rb_opd;
      break;
    case 2:
      rb_flg = rb_flg ^ rb_opd;
      break;
    }
    return;
  }
  /* For STV, the addressing modes work differently:
   * Stack addressing: this pushes from the working register
   * Direct and indirect addressing: these store the value of the working
   * register at the given address
   * Immediate addressing is not legal for STV and results in a NOP */
  if (is_STV()) {
    if (get_flag(SS)) {
      push(rb_wrk);
    } else if (get_flag(SM)) {
      if (rb_ins[6]) {
        writeRAM(rb_opd, rb_wrk);
      } else {
        writeRAM(addr(), rb_wrk);
      }
    }
    return;
  }

  /* For instructions other than STV, the operand may have to be read
   * from RAM or the stack */
  if (get_flag(SS)) { // Pop the stack
    pop(&rb_opd);
  } else if (get_flag(SM)) {
    if (rb_ins[6]) {
      readRAM(rb_opd, &rb_opd);
    } else {
      readRAM(addr(), &rb_opd);
    }
  }

  /* PSH: push operand to stack */
  if (is_PSH()) {
    push(&rb_opd);
    return;
  }

  if (is_ALU_op()) {
    exec_ALU_operation();
  } else {
    rb_aux = rb_opd;
  }

  *rb_wrk = rb_aux;
}

void Processor::exec_ALU_operation() {
  if (!rb_ins[2]) { // arithmetic operation
    rw_aux = 0;
    if (rb_ins[1]) // subtraction
      rb_opd = ~rb_opd;

    if (!rb_ins[0]) {                        // no carry/borrow
      rw_aux = *rb_wrk + rb_opd + rb_ins[1]; // adding 1 for subtraction
    } else {
      rw_aux = *rb_wrk + rb_opd + (get_flag(CY) ^ rb_ins[1]);
    }

    set_flag(CY, rw_aux[8] ^ rb_ins[1]);

    set_flag(OF, eval_overflow(rw_aux));

    rb_aux = (rw_aux & 0xFF);

  } else {
    switch (rb_ins & 0x03) {
    case 0:
      rb_aux = *rb_wrk | rb_opd;
      break;
    case 1:
      rb_aux = *rb_wrk & rb_opd;
      break;
    case 2:
      rb_aux = *rb_wrk ^ rb_opd;
      break;
    case 3:
      exec_rotate();
      break;
    }
  }

  return;
}

bool Processor::eval_overflow(word rw_aux) {
  if (rw_aux[7]) {
    return !(*rb_wrk)[7] && !(rb_opd[7]);
  } else {
    return (*rb_wrk)[7] && (rb_opd[7]);
  }
}

void Processor::exec_rotate() {
  if (rb_opd[1]) {
  } else {
    if (rb_opd[0]) {         // decrement
      if (*rb_wrk == 0x00) { // roll-over
        set_flag(OF, 1);
      }
      rb_aux = *rb_wrk - 1;
    } else {                 // increment
      if (*rb_wrk == 0xFF) { // roll-over
        set_flag(OF, 1);
      }
      rb_aux = *rb_wrk + 1;
    }
  }
}

void Processor::decode() {
  if (has_operand()) { // instruction has operand
    /* First the working register is set */
    if (is_ADR()) { // ADR instruction
      rb_wrk = (rb_ins[5]) ? &rb_adh : &rb_adl;
    } else { // other instructions
      rb_wrk = (rb_ins[5]) ? &rb_ctr : &rb_acc;
    }

    if (is_POP()) {
      pop(rb_wrk);
    } else {
      rb_opd = 0;
      set_operand();
      exec_operation();
    }

  } else {
    rb_opd = 0x00;
    rb_wrk = &rb_acc;
    exec_operation(rb_ins[5]);
  }

  set_flag(ZE, *rb_wrk);
}

void Processor::cycle() {
  if (get_flag(TO)) {
    if (rw_timer == 0xFFFF) {
      rw_timer = 0x0000;
      set_flag(TO, 0);
      set_flag(TF, 1);
    } else {
      rw_timer++;
    }
  }
  fetch(&rb_ins);
  decode();
}

void Processor::get_registers(byte *dest) {
  *dest++ = rb_flg;

  *dest++ = (rw_prg_ctr >> 8);
  *dest++ = (rw_prg_ctr & 0xFF);

  *dest++ = (rw_stk_ptr >> 8);
  *dest++ = (rw_stk_ptr & 0xFF);

  *dest++ = rb_ins;
  *dest++ = rb_opd;
  *dest++ = rb_adh;
  *dest++ = rb_adl;
  *dest++ = rb_acc;
  *dest++ = rb_ctr;

  *dest++ = (rw_timer >> 8);
  *dest++ = (rw_timer & 0xFF);

  *dest++ = rb_aux;
  *dest++ = (rw_aux >> 8);
  *dest++ = (rw_aux & 0xFF);

  *dest++ = pb_data;
  *dest++ = (pw_addr >> 8);
  *dest++ = (pw_addr & 0xFF);
}
