/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_MNT_C_USERS_PARAM_PARAM_PROGRAMMING_C_RIME_BUILD_PARSER_H_INCLUDED
# define YY_YY_MNT_C_USERS_PARAM_PARAM_PROGRAMMING_C_RIME_BUILD_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    START = 258,                   /* START  */
    END = 259,                     /* END  */
    NOP = 260,                     /* NOP  */
    RST = 261,                     /* RST  */
    SWR = 262,                     /* SWR  */
    FLG = 263,                     /* FLG  */
    ADR = 264,                     /* ADR  */
    PSH = 265,                     /* PSH  */
    POP = 266,                     /* POP  */
    STV = 267,                     /* STV  */
    LDV = 268,                     /* LDV  */
    ADD = 269,                     /* ADD  */
    ADC = 270,                     /* ADC  */
    SUB = 271,                     /* SUB  */
    SBC = 272,                     /* SBC  */
    ORR = 273,                     /* ORR  */
    AND = 274,                     /* AND  */
    XOR = 275,                     /* XOR  */
    ROT = 276,                     /* ROT  */
    JMP = 277,                     /* JMP  */
    JNE = 278,                     /* JNE  */
    JEQ = 279,                     /* JEQ  */
    JLT = 280,                     /* JLT  */
    JGE = 281,                     /* JGE  */
    JDC = 282,                     /* JDC  */
    ACC = 283,                     /* ACC  */
    CTR = 284,                     /* CTR  */
    ADH = 285,                     /* ADH  */
    ADL = 286,                     /* ADL  */
    TMR = 287,                     /* TMR  */
    FRG = 288,                     /* FRG  */
    SP = 289,                      /* SP  */
    PC = 290,                      /* PC  */
    DP = 291,                      /* DP  */
    AP = 292,                      /* AP  */
    LABEL = 293,                   /* LABEL  */
    COL = 294,                     /* COL  */
    DEF = 295,                     /* DEF  */
    FUN = 296,                     /* FUN  */
    RET = 297,                     /* RET  */
    LIT = 298,                     /* LIT  */
    STK = 299,                     /* STK  */
    IMM = 300,                     /* IMM  */
    IND = 301,                     /* IND  */
    DIR = 302,                     /* DIR  */
    SW = 303,                      /* SW  */
    INC = 304,                     /* INC  */
    DEC = 305,                     /* DEC  */
    LSH = 306,                     /* LSH  */
    RSH = 307,                     /* RSH  */
    CIR = 308                      /* CIR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 73 "src/rime/parser.y"

  unsigned char byte;
  unsigned char lit_val;
  char *label;

#line 123 "/mnt/c/Users/param/Param/Programming/C++/rime/build/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_MNT_C_USERS_PARAM_PARAM_PROGRAMMING_C_RIME_BUILD_PARSER_H_INCLUDED  */
