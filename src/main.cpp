#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>

#include "mem.h"
#include "processor.h"
#include "util.h"

#define ROM_SIZE 65536
#define RAM_SIZE 65536

int MEM_PRT_SRT = 0;
int MEM_PRT_END = 0;

// using namespace std;

byte registers[REG_CNT] = {0};

byte a_ROM[ROM_SIZE] = {0};
byte a_RAM[RAM_SIZE] = {0};

int read_program(byte *a_ROM);
void print_registers();

int main(int argc, char *argv[]) {

  Memory ROM(a_ROM, ROM_SIZE);
  Memory RAM(a_RAM, RAM_SIZE);

  Processor p(&ROM, &RAM);

  read_program(a_ROM);

  p.reset();

  int iter = atoi(argv[1]);
  MEM_PRT_SRT = atoi(argv[2]);
  MEM_PRT_END = atoi(argv[3]);

  std::cout << "FR PC    SP    INS   H  L  A  C  TMR   A8 A16   DP AP";

  std::cout << "    |";

  for (int i = MEM_PRT_SRT; i < MEM_PRT_END; i++) {
    std::cout << " " << std::hex << std::uppercase << std::setfill('0')
              << std::setw(2) << i;
  }

  std::cout << std::endl;

  for (int i = 0; i < iter; i++) {
    //    p.get_registers(registers);
    //    print_registers();
    p.cycle();
  }
  p.get_registers(registers);
  print_registers();

  return 0;
}

void print_registers() {
  /*
  std::cout << "T           Registers           T          Flags          T\n";
  std::cout << "| PC   SP   INS  ADR  A C  TMR  | -- -- -- -- -- ZE OF CY |\n";

  std::cout << "| ";

  */

  for (int i = 0; i < REG_CNT; i++) {
    std::cout << registers[i].hex() << ' ';
  }

  std::cout << "| ";
  for (int i = MEM_PRT_SRT; i < MEM_PRT_END; i++) {
    std::cout << a_RAM[i].hex() << ' ';
  }

  std::cout << std::endl;
  /*
  std::cout << "| ";
  byte FR = registers[REG_CNT];
  for (int i = 0; i < 8; i++) {

    std::cout << FR[7 - i];
    std::cout << "  ";
  }

  std::cout << "| ";
  std::cout << std::endl;
  */
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
