%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LABEL_LEN 32
#define MAX_LABELS 256

typedef unsigned char byte_t;

unsigned int line_num = 0;

typedef struct label_t {
  char name[MAX_LABEL_LEN];
  int value;
} label;

label labels[MAX_LABELS];
int label_count = 0;

int yyerror(const char *s);
int yylex(void);

void parse_op0(byte_t opcode);
void parse_jmp(byte_t opcode, int jump_to);
void parse_swr(byte_t opcode, byte_t reg_spec);
void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec);
void parse_op2(byte_t opcode, byte_t operand, byte_t reg_spec);

void add_label();
int get_label_value();
%}

%union {
  unsigned char byte;
  unsigned char lit_val;
  char *label;
}

/* Token declarations */

// Opcode mnemonics
%token <byte> NOP RST
%token <byte> SWR
%token <byte> FLG
%token <byte> ADR PSH POP STV LDV ADD ADC SUB SBC ORR AND XOR ROT
%token <byte> JMP JNE JEQ JLT JGE JDC

// Registers
%token <byte> ACC CTR ADH ADL TMR DAT

// Other tokens
%token <byte> LABEL LABEL_DEF
%token <byte> LIT STK IMM IND DIR

%type <byte> ins
%type <byte> op0 swr flg adr pop op2 jmp
%type <byte> reg_spec flg_spec adr_spec adr_reg wrk_reg

/* Grammar rules */
%%
program : program ins { printf("\n"); }
        | program label
        |;

ins : op0                   { parse_op0($1);          }
    | jmp LABEL             { parse_jmp($1, get_label_value()); }
    | swr reg_spec          { parse_swr($1, $2);      }
    | flg adr_spec flg_spec { parse_flg($1, $2, $3);  }
    | pop wrk_reg           { parse_op2($1, 0, $2);   }
    | adr adr_spec adr_reg  { parse_op2($1, $2, $3);  }
    | op2 adr_spec wrk_reg  { parse_op2($1, $2, $3);  };

label : LABEL LABEL_DEF { add_label(); };

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

pop : POP { $$ = 0x05; }

op2 : PSH { $$ = 0x04; }
    | STV { $$ = 0x06; }
    | LDV { $$ = 0x07; }
    | ADD { $$ = 0x08; }
    | ADC { $$ = 0x09; }
    | SUB { $$ = 0x0A; }
    | SBC { $$ = 0x0B; }
    | ORR { $$ = 0x0C; }
    | AND { $$ = 0x0D; }
    | XOR { $$ = 0x0E; }
    | ROT { $$ = 0x0F; };

flg_spec: AND { $$ = 0; }
        | ORR { $$ = 1; }
        | XOR { $$ = 2; };

reg_spec: CTR { $$ = 0; }
        | FLG { $$ = 1; }
        | DAT { $$ = 2; }
        | TMR { $$ = 3; };

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
  printf("%02X", opcode);
  line_num++;
}

void parse_jmp(byte_t opcode, int jump_to) {
  printf("%02X%02X", 0x08 | (3 << 5), (jump_to >> 8)); // Setting ADH
  printf("%02X%02X", 0x08 | (2 << 5), (jump_to & 0xFF)); // Setting ADL
  printf("%02X", opcode);
  line_num++;
}

void parse_swr(byte_t opcode, byte_t reg_spec) {
  printf("%02X", opcode | reg_spec);
  line_num++;
}

void parse_flg(byte_t opcode, byte_t operand, byte_t flg_spec) {
  printf("%02X", opcode | (operand << 6) | flg_spec);
  line_num++;
  printf("%02X", yylval.lit_val);
  line_num++;
}

void parse_op2(byte_t opcode, byte_t operand, byte_t reg_spec) {
  printf("%02X", opcode | (operand << 6) | (reg_spec << 5));
  line_num++;
  if (operand & 1) {
    printf("%02X", yylval.lit_val);
    line_num++;
  }
}

void add_label() {
  if (label_count < MAX_LABELS) {
    strncpy(labels[label_count].name, yylval.label, 32);
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

// Error handling
int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main() {
    yyparse();
    return 0;
}
