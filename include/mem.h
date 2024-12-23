#pragma once

#include "util.h"
#include <cstdint>

enum e_MemoryControl {
  READ,
  WRITE,
};

class Memory {
private:
  byte *_memory;
  uint64_t _size;

public:
  bool *RW; // 0: write, 1: read
  byte *_data_bus;
  word *_addr_bus;

  Memory(byte *memory, uint64_t size) : _memory(memory), _size(size) {}

  /* If enabled (EN = 0), reads or writes according to RW
   * Addresses wrap around if they are too large */
  void update();
};
