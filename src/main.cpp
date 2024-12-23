#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>

#include "mem.h"
#include "processor.h"
#include "util.h"

#define ROM_SIZE 65536
#define RAM_SIZE 256

// using namespace std;

uint16_t registers[REG_CNT + PRT_CNT] = {0};

int read_program(byte *a_ROM);
void print_registers();

int main(int argc, char *argv[]) {
  byte a_ROM[ROM_SIZE] = {0};
  byte a_RAM[RAM_SIZE] = {0};

  Memory ROM(a_ROM, ROM_SIZE);
  Memory RAM(a_RAM, RAM_SIZE);
  Processor p(&ROM, &RAM);

  read_program(a_ROM);

  int iter = atoi(argv[1]);

  for (int i = 0; i < iter; i++) {
    p.cycle();
    p.get_registers(registers);
    print_registers();
  }

  return 0;
}

void print_registers() {
  std::cout << "T           Registers           T          Flags          T\n";
  std::cout << "| PC   SP   INS  ADR  A C  TMR  | -- -- -- -- -- ZE OF CY |\n";

  std::cout << "| ";
  for (int i = 0; i < REG_CNT; i++) {
    std::cout << std::hex << std::uppercase << std::setw(4) << std::setfill('0')
              << registers[i];
    std::cout << ' ';
  }

  std::cout << "| ";
  byte FR = registers[REG_CNT];
  for (int i = 0; i < 8; i++) {

    std::cout << FR[7 - i];
    std::cout << "  ";
  }

  std::cout << "| ";
  std::cout << std::endl;
}

int read_program(byte *ROM) {
  const char *filename = "program.hex";

  // Open the file in binary mode
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return 1;
  }

  // Read file contents into a fixed-size array
  file.read(reinterpret_cast<char *>(ROM), ROM_SIZE);

  // Get the number of bytes read
  std::streamsize bytesRead = file.gcount();
  if (file.bad()) {
    std::cerr << "Error reading file." << std::endl;
    return 1;
  }

  /* // Print the bytes (for demonstration) */
  /* std::cout << "File contents (" << bytesRead << " bytes):" << std::endl; */
  /* for (std::streamsize i = 0; i < bytesRead; ++i) { */
  /*   std::cout << std::hex << static_cast<int>(ROM[i]) << " "; */
  /* } */
  /* std::cout << std::endl; */

  return 0;
}