#include "mem.h"

void Memory::read() { *_data_bus = _memory[*_addr_bus % _size]; }
void Memory::write() { _memory[*_addr_bus % _size] = *_data_bus; }
