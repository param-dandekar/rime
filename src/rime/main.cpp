#include <cstdio>
#include <iostream>
#include <string>

#include "rime.h"

void print_help() {
  std::cout << "Usage: rc [options] <input_file>\n";
  std::cout << "Options:\n";
  std::cout << "  -h, --help\t\tDisplay this information\n";
  std::cout << "  -o <file>\t\tWrite output to <file>\n";
  std::cout << "  -d\t\t\tWrite debug information to <input_file>.dbg\n";
  std::cout << "  --debug=<file>\tWrite debug information to <file>\n";
}

bool streq(std::string a, std::string b) { return (a.compare(b) == 0); }

int parse_args(int argc, char *argv[]) {
  std::string arg;
  int input_file = 0;

  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    std::cout << argv[i] << "\n";

    if (arg.compare(0, 1, "-") == 0) {
      std::cout << "option: " << arg << "\n";
      if (streq(arg, "-h") | streq(arg, "--help")) {
        print_help();
      }

      continue;
    }

    std::cout << "Input file: " << arg << "\n";
    input_file = i;
  }

  return input_file;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "\033[91mError:\033[0m no input file.\n";
    return 1;
  }

  std::string input_file;
  std::string output_file;
  std::string debug_file;

  bool debug = false;

  std::string arg;

  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (arg.compare(0, 1, "-") == 0) {
      if (streq(arg, "-h") | streq(arg, "--help")) {
        print_help();
        return 0;
      }
      if (streq(arg, "-o")) {
        if (i == argc - 1) {
          std::cerr << "\033[91mError:\033[0m missing filename after -o.\n";
          return 1;
        }
        output_file = argv[++i];
        continue;
      }
      if (streq(arg, "-d")) {
        debug = true;
        continue;
      }
      if (arg.compare(0, 8, "--debug=") == 0) {
        if (i == argc - 1) {
          std::cerr << "\033[91mError:\033[0m missing filename after --debu.\n";
          return 1;
        }
        debug = true;
        debug_file = std::string(argv[i]).substr(8);
        continue;
      }
    }
    input_file = argv[i];
  }

  if (streq(input_file, "")) {
    std::cerr << "\033[91mError:\033[0m no input file.\n";
    return 1;
  }

  if (streq(output_file, "")) {
    output_file = input_file + ".hex";
  }

  if (debug) {
    if (streq(debug_file, "")) {
      debug_file = input_file + ".dbg";
    }
  }

  int res;

  res = assemble(input_file, output_file);

  return res;
}
