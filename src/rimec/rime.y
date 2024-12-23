%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_LEN 32
#define MAX_LABELS 256
#define PROGRAM_SIZE 65536

typedef unsigned char byte_t;

byte_t program[PROGRAM_SIZE] = {0};

unsigned int line_num = 2;

typedef struct label_t {
  char name[MAX_LABEL_LEN];
  int value;
} label;

label labels[MAX_LABELS];
int label_count = 1; // labels[0] is reserved for START

int yyerror(const char *s);
int yylex(void);

void parse_op0(byte_t opcode);
void parse_jmp(byte_t opcode, int jump_to);
void parse_swr(byte_t opcode, byte_t rg1_spec, byte_t rg2_spec);
void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec);
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
%token <byte> LABEL LABEL_DEF
%token <byte> DEF FUN RET
%token <byte> LIT STK IMM IND DIR

%type <byte> ins
%type <byte> op0 swr flg adr pop op2 jmp
%type <byte> rg1_spec rg2_spec flg_spec adr_spec adr_reg wrk_reg

/* Grammar rules */
%%
program : program START { set_start(); }
        | program ins
        | program label
        | program func_def
        | program func_call
        | program func_ret
        | program END { set_end(); YYACCEPT; }
        |;

ins : op0                   { parse_op0($1);          }
    | jmp LABEL             { parse_jmp($1, get_label_value()); }
    | jmp ADR               { parse_op0($1);          }
    | swr rg1_spec rg2_spec { parse_swr($1, $2, $3);  }
    | flg adr_spec flg_spec { parse_flg($1, $2, $3);  }
    | pop wrk_reg           { parse_op2($1, 0, $2);   }
    | adr adr_spec adr_reg  { parse_op2($1, $2, $3);  }
    | op2 adr_spec wrk_reg  { parse_op2($1, $2, $3);  }

label : LABEL LABEL_DEF { add_label();  };

func_def  : DEF LABEL { add_label();    };
func_ret  : RET       { func_return();  };
func_call : FUN LABEL { func_call();    };

op0 : NOP { $$ = 0x00; }
    | RST { $$ = 0x01; };

jmp : JMP { $$ = 0x20; }
    | JNE { $$ = 0x21; }
    | JEQ { $$ = 0xA1; }
    | JLT { $$ = 0x22; }
    | JGE { $$ = 0xA2; }
    | JDC { $$ = 0x23; };

swr : SWR { $$ = 0x04; };

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
    | XOR { $$ = 0x1E; }
    | ROT { $$ = 0x1F; };

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
void parse_op0(byte_t opcode) {
  program[line_num++] = (opcode);
  line_num++;
}

void parse_jmp(byte_t opcode, int jump_to) {
  program[line_num++] = (0x08 | (3 << 5));
  program[line_num++] = ((jump_to >> 8)); // Setting ADH
  program[line_num++] = (0x08 | (2 << 5));
  program[line_num++] = ((jump_to & 0xFF)); // Setting ADL
  program[line_num++] = (opcode);
}

void parse_swr(byte_t opcode, byte_t rg1_spec, byte_t rg2_spec) {
  program[line_num++] = (opcode | (rg1_spec << 5) | rg2_spec);
}

void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec) {
  program[line_num++] = (opcode | (operand << 6) | flg_spec);
  program[line_num++] = (yylval.lit_val);
}

void parse_op2(byte_t opcode, byte_t operand, byte_t reg_spec) {
  program[line_num++] = (opcode | (operand << 6) | (reg_spec << 5));
  if (operand & 1) {
    program[line_num++] = (yylval.lit_val);
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
  program[line_num++] = (0x64); // get current address
  program[line_num++] = (0x16);
  program[line_num++] = (0x36); // put current address on stack
  parse_jmp(0x20, get_label_value()); // jump to label
}

void func_return() {
  program[line_num++] = (0x35);
  program[line_num++] = (0x15); // pop return address
  program[line_num++] = (0x78);
  program[line_num++] = (0x07); // add 7 to address
  program[line_num++] = (0x58);
  program[line_num++] = (0x00); // propagate carry
  program[line_num++] = (0xE4); // store in address register
  program[line_num++] = (0x20); // jump to label
}

void set_start() {
  strncpy(labels[0].name, "_START", MAX_LABEL_LEN);
  labels[0].value = line_num;
}

void set_end() {
  int start = labels[0].value % PROGRAM_SIZE;
  printf("%c%c", (start>>8)&0xFF, start&0xFF);
  for (unsigned int i = 2; i < PROGRAM_SIZE; i++) {
    printf("%c", program[i]);
  }
}

// Error handling
int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main() {
    yyparse();
    return 0;
}
