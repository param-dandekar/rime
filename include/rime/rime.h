#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

#define PROGRAM_SIZE 65536

#define PROGRAM_START_ADDR 0x02
#define FUNC_CALL_OFFSET 0x07

#define MAX_FILENAME 32

// Declare yyin as extern so both Flex and Bison share it
extern FILE *yyin;

typedef unsigned char byte_t;
extern byte_t program[];

#ifdef __cplusplus
#include <string>
int assemble(std::string input_file, std::string output_file);
extern "C" {
#endif
int run_assembler(char *filename);
#ifdef __cplusplus
}
#endif

#endif // PARSER_H
