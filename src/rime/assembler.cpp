#include "rime.h"
#include <cstring>
#include <fstream>

int assemble(std::string input_file, std::string output_file) {
  int res;

  char filename[MAX_FILENAME];
  strncpy(filename, input_file.c_str(), MAX_FILENAME);

  res = run_assembler(filename);

  if (res) {
    return res;
  }

  std::ofstream output_file_stream(output_file);
  for (int i = 0; i < PROGRAM_SIZE; i++) {
    output_file_stream << program[i];
  }
  output_file_stream.close();

  return 0;
}
