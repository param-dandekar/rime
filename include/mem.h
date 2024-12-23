#pragma once

#include "util.h"
#include <cstdint>

class Memory {
private:
  byte *_memory;
  uint64_t _size;

public:
  byte *_data_bus;
  word *_addr_bus;

  Memory(byte *memory, uint64_t size) : _memory(memory), _size(size) {}

  /* The I/O operations below wrap around if the address is too large */
  /* Reads the value from memory at _addr_bus to _data_bus */
  void read();
  /* Writes the value at _data_bus to memory at _addr_bus */
  void write();
};
