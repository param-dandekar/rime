%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rime.h"

#define MAX_LABEL_LEN 32
#define MAX_LABELS 256

int yyerror(const char *s);
int yylex(void);
void yyrestart(FILE*);

typedef enum CompilerPass_e {
  FIRST,
  SECOND,
} CompilerPass;

CompilerPass pass = FIRST;

typedef enum InstructionType_e {
  INS_OP0,
  INS_JMP_LBL,
  INS_JMP_ADR,
  INS_SWR,
  INS_FLG,
  INS_PSH,
  INS_POP,
  INS_ADR,
  INS_ROT,
  INS_OP2,
} InstructionType;

byte_t program[PROGRAM_SIZE] = {0};

unsigned int line_num = PROGRAM_START_ADDR;

typedef struct label_t {
  char name[MAX_LABEL_LEN];
  int value;
} label;

label labels[MAX_LABELS];
int label_count = 1; // labels[0] is reserved for START

void generate_instruction(InstructionType type,
                          byte_t arg1,
                          byte_t arg2,
                          byte_t arg3,
                          byte_t arg4);

void parse_op0(byte_t opcode);
void parse_jmp(byte_t opcode, int jump_to);
void parse_swr(byte_t opcode, byte_t rg1_spec, byte_t rg2_spec, byte_t sw);
void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec);
void parse_reg_psh(byte_t reg_spec);
void parse_swr(byte_t opcode, byte_t rg1_spec, byte_t rg2_spec, byte_t sw);
void parse_rot(byte_t opcode, byte_t reg_spec);
void parse_op2(byte_t opcode, byte_t operand, byte_t reg_spec);

void add_label();
int get_label_value();

void func_call();
void func_return();

void set_start();
void set_end();

%}

%union {
  unsigned char byte;
  unsigned char lit_val;
  char *label;
}

/* Token declarations */

%token <byte> START END

// Opcode mnemonics
%token <byte> NOP RST
%token <byte> SWR
%token <byte> FLG
%token <byte> ADR PSH POP STV LDV ADD ADC SUB SBC ORR AND XOR ROT
%token <byte> JMP JNE JEQ JLT JGE JDC

// Registers
%token <byte> ACC CTR ADH ADL TMR FRG SP PC DP AP

// Other tokens
%token <byte> LABEL COL
%token <byte> DEF FUN RET
%token <byte> LIT STK IMM IND DIR SW
%token <byte> INC DEC LSH RSH CIR

%type <byte> ins
%type <byte> op0 swr flg adr pop op2 rot jmp
%type <byte> rg1_spec rg2_spec flg_spec adr_spec adr_reg wrk_reg sw

/* Grammar rules */
%%
program : program START COL { set_start(); }
        | program ins
        | program label
        | program func_def
        | program func_call
        | program func_ret
        | program END       { YYACCEPT; }
        |;

ins : op0                       { generate_instruction(INS_OP0, $1, 0, 0, 0);     }
    | jmp LABEL                 { generate_instruction(INS_JMP_LBL, $1, 0, 0, 0); }
    | jmp ADR                   { generate_instruction(INS_JMP_ADR, $1, 0, 0, 0); }
    | swr rg1_spec rg2_spec sw  { generate_instruction(INS_SWR, $1, $2, $3, $4);  }
    | flg adr_spec flg_spec     { generate_instruction(INS_FLG, $1, $2, $3, 0);   }
    | PSH wrk_reg               { generate_instruction(INS_PSH, $2, 0, 0, 0);     }
    | pop wrk_reg               { generate_instruction(INS_OP2, $1, 0, $2, 0);    }
    | adr adr_spec adr_reg      { generate_instruction(INS_OP2, $1, $2, $3, 0);   }
    | rot wrk_reg               { generate_instruction(INS_ROT, $1, $2, 0, 0);    }
    | op2 adr_spec wrk_reg      { generate_instruction(INS_OP2, $1, $2, $3, 0);   };

label : LABEL COL { if (pass == FIRST) { add_label(); } };

func_def  : DEF LABEL COL { add_label();    };
func_ret  : RET           { func_return();  };
func_call : FUN LABEL     { func_call();    };

op0 : NOP { $$ = 0x00; }
    | RST { $$ = 0x01; };

jmp : JMP { $$ = 0x20; }
    | JNE { $$ = 0x21; }
    | JEQ { $$ = 0xA1; }
    | JLT { $$ = 0x22; }
    | JGE { $$ = 0xA2; }
    | JDC { $$ = 0x23; };

swr : SWR { $$ = 0x04; };

sw  : SW { $$ = 1; }
    |    { $$ = 0; };

flg : FLG { $$ = 0x0C; };

adr : ADR { $$ = 0x08; };

pop : POP { $$ = 0x15; }

op2 : PSH { $$ = 0x14; }
    | STV { $$ = 0x16; }
    | LDV { $$ = 0x17; }
    | ADD { $$ = 0x18; }
    | ADC { $$ = 0x19; }
    | SUB { $$ = 0x1A; }
    | SBC { $$ = 0x1B; }
    | ORR { $$ = 0x1C; }
    | AND { $$ = 0x1D; }
    | XOR { $$ = 0x1E; };
 

rot : INC { $$ = 0x1F | (0 << 6); }
    | DEC { $$ = 0x1F | (1 << 6); }
    | LSH { $$ = 0x1F | (2 << 6); }
    | RSH { $$ = 0x1F | (3 << 6); };

flg_spec: AND { $$ = 0; }
        | ORR { $$ = 1; }
        | XOR { $$ = 2; };

rg1_spec: CTR { $$ = 0; }
        | FRG { $$ = 1; }
        | SP  { $$ = 2; }
        | PC  { $$ = 3; }
        | TMR { $$ = 4; }
        | DP  { $$ = 5; }
        | AP  { $$ = 6; }
        | ADR { $$ = 7; };

rg2_spec: ACC { $$ = 0; }
        | ADR { $$ = 1; }

adr_spec: STK     { $$ = 0; }
        | IMM LIT { $$ = 1; }
        | IND     { $$ = 2; }
        | DIR LIT { $$ = 3; };

wrk_reg : ACC { $$ = 0; }
        | CTR { $$ = 1; };
adr_reg : ADL { $$ = 0; }
        | ADH { $$ = 1; };
%%

// Parsing rules

void generate_instruction(InstructionType type,
                          byte_t arg1,
                          byte_t arg2,
                          byte_t arg3,
                          byte_t arg4) {

  switch (type) {
  case INS_OP0:
    parse_op0(arg1);
    break;

  case INS_JMP_LBL:
    parse_jmp(arg1, get_label_value());
    break;

  case INS_JMP_ADR:
    parse_op0(arg1);
    break;

  case INS_SWR:
    parse_swr(arg1, arg2, arg3, arg4);
    break;

  case INS_FLG:
    parse_flg(arg1, arg2, arg3);
    break;

  case INS_PSH:
    parse_reg_psh(arg2);
    break;

  case INS_POP:
    parse_op2(arg1, 0, arg2);
    break;

  case INS_ADR:
    parse_op2(arg1, arg2, arg3);
    break;

  case INS_ROT:
    parse_rot(arg1, arg2);
    break;

  case INS_OP2:
    parse_op2(arg1, arg2, arg3);
    break;
  }
}

void parse_line(byte_t opcode) {
  if (pass == SECOND) { program[line_num] = (opcode); }
  ++line_num;
}

void parse_op0(byte_t opcode) {
  parse_line(opcode);
}

void parse_jmp(byte_t opcode, int jump_to) {
  parse_line(0x08 | (3 << 5));
  parse_line((jump_to >> 8)); // Setting ADH
  parse_line(0x08 | (2 << 5));
  parse_line((jump_to & 0xFF)); // Setting ADL
  parse_line(opcode);
}

void parse_swr(byte_t opcode, byte_t rg1_spec, byte_t rg2_spec, byte_t sw) {
  parse_line(opcode | (rg1_spec << 5) | (sw << 1) | rg2_spec);
}

void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec) {
  parse_line(opcode | (operand << 6) | flg_spec);
  parse_line(yylval.lit_val);
}

void parse_reg_psh(byte_t reg_spec) {
  parse_line(0x16 | (reg_spec << 5));
}

void parse_rot(byte_t opcode, byte_t reg_spec) {
  parse_line(opcode | (reg_spec << 5));
}

void parse_op2(byte_t opcode, byte_t operand, byte_t reg_spec) {
  parse_line(opcode | (operand << 6) | (reg_spec << 5));
  if (operand & 1) {
    parse_line(yylval.lit_val);
  }
}

void add_label() {
  if (label_count < MAX_LABELS) {
    strncpy(labels[label_count].name, yylval.label, MAX_LABEL_LEN);
    labels[label_count].value = line_num;
    label_count++;
  }
}

int get_label_value() {
  for (int i = 0; i < label_count; i++) {
    if (strcmp(labels[i].name, yylval.label) == 0) {
      return labels[i].value;
    }
  }
  return 0;
}

void func_call() {
  parse_line(0x16);
  parse_line(0x36); // push registers onto stack
  parse_line(0x64); // get current address
  parse_line(0x16);
  parse_line(0x36); // push current address on stack (high byte first)
  parse_jmp(0x20, get_label_value()); // jump to label
  parse_line(0x35);
  parse_line(0x15); // restore register state
}

void func_return() {
  parse_line(0xE4); // store result in address register
  parse_line(0x35);
  parse_line(0x15); // pop return address
  parse_line(0x78);
  parse_line(FUNC_CALL_OFFSET); // add offset to address
  parse_line(0x58); // to skip function call
  parse_line(0x00); // propagate carry
  parse_line(0xE4); // write return address to address register
  parse_line(0x20); // jump to label
}

void set_start() {
  strncpy(labels[0].name, "_START", MAX_LABEL_LEN);
  labels[0].value = line_num;
}

// Error handling
int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

void print_info() {
  fprintf(stderr, "Lines: %d\n", line_num);
  fprintf(stderr, "Labels:\n");

  for (int i = 0; i < label_count; i++) {
    fprintf(stderr, "%04X: %s\n", labels[i].value, labels[i].name);
  }
}

int run_assembler(char *filename) {
  // Open the source file
  yyin = fopen(filename, "r");
  if (!yyin) {
      perror("Failed to open file");
      return 1;
  }

  pass = FIRST;
  yyparse();

  print_info();
  line_num = PROGRAM_START_ADDR;

  yyrestart(yyin);
  rewind(yyin);

  pass = SECOND;

  for (int i = 0; i < PROGRAM_START_ADDR; i++) {
    program[i] = (labels[0].value >> (i*8)) & 0xFF;
  }
  line_num = PROGRAM_START_ADDR + 1;
  
  yyparse();

  /*
  int start = labels[0].value % PROGRAM_SIZE;
  printf("%c%c", (start>>8)&0xFF, start&0xFF);
  */

  fclose(yyin);

  return 0;
}
