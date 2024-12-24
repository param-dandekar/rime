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

#ifndef YY_YY_RIME_TAB_H_INCLUDED
# define YY_YY_RIME_TAB_H_INCLUDED
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
    NOP = 258,                     /* NOP  */
    RST = 259,                     /* RST  */
    SWR = 260,                     /* SWR  */
    FLG = 261,                     /* FLG  */
    ADR = 262,                     /* ADR  */
    PSH = 263,                     /* PSH  */
    POP = 264,                     /* POP  */
    STV = 265,                     /* STV  */
    LDV = 266,                     /* LDV  */
    ADD = 267,                     /* ADD  */
    ADC = 268,                     /* ADC  */
    SUB = 269,                     /* SUB  */
    SBC = 270,                     /* SBC  */
    ORR = 271,                     /* ORR  */
    AND = 272,                     /* AND  */
    XOR = 273,                     /* XOR  */
    ROT = 274,                     /* ROT  */
    JMP = 275,                     /* JMP  */
    JNE = 276,                     /* JNE  */
    JEQ = 277,                     /* JEQ  */
    JLT = 278,                     /* JLT  */
    JGE = 279,                     /* JGE  */
    JDC = 280,                     /* JDC  */
    ACC = 281,                     /* ACC  */
    CTR = 282,                     /* CTR  */
    ADH = 283,                     /* ADH  */
    ADL = 284,                     /* ADL  */
    TMR = 285,                     /* TMR  */
    DAT = 286,                     /* DAT  */
    LABEL = 287,                   /* LABEL  */
    LABEL_DEF = 288,               /* LABEL_DEF  */
    LIT = 289,                     /* LIT  */
    STK = 290,                     /* STK  */
    IMM = 291,                     /* IMM  */
    IND = 292,                     /* IND  */
    DIR = 293                      /* DIR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 34 "rime.y"

  unsigned char byte;
  unsigned char lit_val;
  char *label;

#line 108 "rime.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_RIME_TAB_H_INCLUDED  */
