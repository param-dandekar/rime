%{
#include "rime.tab.h"

#define MAX_LABEL_LEN 32
%}



digit_hex [0-9a-fA-F]
digit_bin [01]

lit_bin {digit_bin}{8}[bB]?
lit_hex {digit_hex}{1,2}[hH]?

ORR OR{1,2}

label [a-zA-Z0-9_]{1,32}

comment \%.*

%%

{comment} {}

"NOP"   { return NOP; }
"RST"   { return RST; }

"SWR"   { return SWR; }

"ADR"   { return ADR; }
"FLG"   { return FLG; }

"PSH"   { return PSH; }
"POP"   { return POP; }
"STV"   { return STV; }
"LDV"   { return LDV; }
"ADD"   { return ADD; }
"ADC"   { return ADC; }
"SUB"   { return SUB; }
"SBC"   { return SBC; }
{ORR}   { return ORR; }
"AND"   { return AND; }
"XOR"   { return XOR; }
"ROT"   { return ROT; }

"JMP"   { return JMP; }
"JNE"   { return JNE; }
"JEQ"   { return JEQ; }
"JLT"   { return JLT; }
"JGE"   { return JGE; }
"JDC"   { return JDC; }

"A"|"ACC"         { return ACC; }
"C"|"CTR"         { return CTR; }
"L"|"ADL"         { return ADL; }
"H"|"ADH"         { return ADH; }
"FR"              { return FLG; }
"T"|"TMR"|"TIMER" { return TMR; }
"DP"|"DATA"       { return DAT; }

"STK"   { return STK; }
"#"     { return IMM; }
"@ADR"  { return IND; }
"&"     { return DIR; }

{lit_hex} {
  yylval.lit_val = strtol(yytext, NULL, 16);
  return LIT;
}

{lit_bin} {
  yylval.lit_val = strtol(yytext, NULL, 2);
  return LIT;
}

{label} {
  yylval.label = strdup(yytext);
  return LABEL;
}

":" { return LABEL_DEF; }

[ \t\n]+        { /* Ignore whitespace */ }
.               { printf("Unknown token: %s\n", yytext); }

%%
int yywrap() { return 1; }
