#include "mem.h"

void Memory::update() {
  if (*RW == READ) { // read
    *_data_bus = _memory[*_addr_bus % _size];
  } else { // write
    _memory[*_addr_bus % _size] = *_data_bus;
  }
}
