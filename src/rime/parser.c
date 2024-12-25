/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/rime/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rime.h"

#define MAX_LABEL_LEN 32
#define MAX_LABELS 256
#define PROGRAM_SIZE 65536

#define PROGRAM_START_ADDR 0x02
#define FUNC_CALL_OFFSET 0x07

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

typedef unsigned char byte_t;

byte_t program[PROGRAM_SIZE] = {0};

unsigned int line_num = PROGRAM_START_ADDR;

typedef struct label_t {
  char name[MAX_LABEL_LEN];
  int value;
} label;

label labels[MAX_LABELS];
int label_count = 1; // labels[0] is reserved for START

int yyerror(const char *s);
int yylex(void);
void yyrestart(FILE*);

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

#line 148 "src/rime/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_START = 3,                      /* START  */
  YYSYMBOL_END = 4,                        /* END  */
  YYSYMBOL_NOP = 5,                        /* NOP  */
  YYSYMBOL_RST = 6,                        /* RST  */
  YYSYMBOL_SWR = 7,                        /* SWR  */
  YYSYMBOL_FLG = 8,                        /* FLG  */
  YYSYMBOL_ADR = 9,                        /* ADR  */
  YYSYMBOL_PSH = 10,                       /* PSH  */
  YYSYMBOL_POP = 11,                       /* POP  */
  YYSYMBOL_STV = 12,                       /* STV  */
  YYSYMBOL_LDV = 13,                       /* LDV  */
  YYSYMBOL_ADD = 14,                       /* ADD  */
  YYSYMBOL_ADC = 15,                       /* ADC  */
  YYSYMBOL_SUB = 16,                       /* SUB  */
  YYSYMBOL_SBC = 17,                       /* SBC  */
  YYSYMBOL_ORR = 18,                       /* ORR  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_XOR = 20,                       /* XOR  */
  YYSYMBOL_ROT = 21,                       /* ROT  */
  YYSYMBOL_JMP = 22,                       /* JMP  */
  YYSYMBOL_JNE = 23,                       /* JNE  */
  YYSYMBOL_JEQ = 24,                       /* JEQ  */
  YYSYMBOL_JLT = 25,                       /* JLT  */
  YYSYMBOL_JGE = 26,                       /* JGE  */
  YYSYMBOL_JDC = 27,                       /* JDC  */
  YYSYMBOL_ACC = 28,                       /* ACC  */
  YYSYMBOL_CTR = 29,                       /* CTR  */
  YYSYMBOL_ADH = 30,                       /* ADH  */
  YYSYMBOL_ADL = 31,                       /* ADL  */
  YYSYMBOL_TMR = 32,                       /* TMR  */
  YYSYMBOL_FRG = 33,                       /* FRG  */
  YYSYMBOL_SP = 34,                        /* SP  */
  YYSYMBOL_PC = 35,                        /* PC  */
  YYSYMBOL_DP = 36,                        /* DP  */
  YYSYMBOL_AP = 37,                        /* AP  */
  YYSYMBOL_LABEL = 38,                     /* LABEL  */
  YYSYMBOL_COL = 39,                       /* COL  */
  YYSYMBOL_DEF = 40,                       /* DEF  */
  YYSYMBOL_FUN = 41,                       /* FUN  */
  YYSYMBOL_RET = 42,                       /* RET  */
  YYSYMBOL_LIT = 43,                       /* LIT  */
  YYSYMBOL_STK = 44,                       /* STK  */
  YYSYMBOL_IMM = 45,                       /* IMM  */
  YYSYMBOL_IND = 46,                       /* IND  */
  YYSYMBOL_DIR = 47,                       /* DIR  */
  YYSYMBOL_SW = 48,                        /* SW  */
  YYSYMBOL_INC = 49,                       /* INC  */
  YYSYMBOL_DEC = 50,                       /* DEC  */
  YYSYMBOL_LSH = 51,                       /* LSH  */
  YYSYMBOL_RSH = 52,                       /* RSH  */
  YYSYMBOL_CIR = 53,                       /* CIR  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_ins = 56,                       /* ins  */
  YYSYMBOL_label = 57,                     /* label  */
  YYSYMBOL_func_def = 58,                  /* func_def  */
  YYSYMBOL_func_ret = 59,                  /* func_ret  */
  YYSYMBOL_func_call = 60,                 /* func_call  */
  YYSYMBOL_op0 = 61,                       /* op0  */
  YYSYMBOL_jmp = 62,                       /* jmp  */
  YYSYMBOL_swr = 63,                       /* swr  */
  YYSYMBOL_sw = 64,                        /* sw  */
  YYSYMBOL_flg = 65,                       /* flg  */
  YYSYMBOL_adr = 66,                       /* adr  */
  YYSYMBOL_pop = 67,                       /* pop  */
  YYSYMBOL_op2 = 68,                       /* op2  */
  YYSYMBOL_rot = 69,                       /* rot  */
  YYSYMBOL_flg_spec = 70,                  /* flg_spec  */
  YYSYMBOL_rg1_spec = 71,                  /* rg1_spec  */
  YYSYMBOL_rg2_spec = 72,                  /* rg2_spec  */
  YYSYMBOL_adr_spec = 73,                  /* adr_spec  */
  YYSYMBOL_wrk_reg = 74,                   /* wrk_reg  */
  YYSYMBOL_adr_reg = 75                    /* adr_reg  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   68

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  91

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   110,   110,   111,   112,   113,   114,   115,   116,   117,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     130,   132,   133,   134,   136,   137,   139,   140,   141,   142,
     143,   144,   146,   148,   149,   151,   153,   155,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   169,   170,
     171,   172,   174,   175,   176,   178,   179,   180,   181,   182,
     183,   184,   185,   187,   188,   190,   191,   192,   193,   195,
     196,   197,   198
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "START", "END", "NOP",
  "RST", "SWR", "FLG", "ADR", "PSH", "POP", "STV", "LDV", "ADD", "ADC",
  "SUB", "SBC", "ORR", "AND", "XOR", "ROT", "JMP", "JNE", "JEQ", "JLT",
  "JGE", "JDC", "ACC", "CTR", "ADH", "ADL", "TMR", "FRG", "SP", "PC", "DP",
  "AP", "LABEL", "COL", "DEF", "FUN", "RET", "LIT", "STK", "IMM", "IND",
  "DIR", "SW", "INC", "DEC", "LSH", "RSH", "CIR", "$accept", "program",
  "ins", "label", "func_def", "func_ret", "func_call", "op0", "jmp", "swr",
  "sw", "flg", "adr", "pop", "op2", "rot", "flg_spec", "rg1_spec",
  "rg2_spec", "adr_spec", "wrk_reg", "adr_reg", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-16)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -16,     0,   -16,    -4,   -16,   -16,   -16,   -16,   -16,   -16,
      19,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,    -2,   -10,    -6,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,    -8,    24,    -1,    -1,    19,    -1,    19,   -16,   -16,
     -16,   -16,   -16,    15,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,    -7,   -16,    12,   -16,    25,
      45,    36,   -16,    19,   -16,   -16,   -16,   -16,    -9,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       9,     0,     1,     0,     8,    24,    25,    32,    35,    36,
      38,    37,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    26,    27,    28,    29,    30,    31,     0,     0,     0,
      22,    48,    49,    50,    51,     3,     4,     5,     7,     6,
      10,     0,     0,     0,     0,     0,     0,     0,     2,    69,
      70,    15,    20,     0,    23,    12,    11,    62,    55,    59,
      56,    57,    58,    60,    61,     0,    65,     0,    67,     0,
       0,     0,    16,     0,    18,    21,    64,    63,    34,    66,
      68,    53,    52,    54,    14,    72,    71,    17,    19,    33,
      13
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,
     -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -16,   -15,
     -11,   -16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    35,    36,    37,    38,    39,    40,    41,    42,
      90,    43,    44,    45,    46,    47,    84,    65,    78,    70,
      51,    87
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
       2,    55,    76,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    77,    21,    22,    23,    24,    25,    26,    53,    71,
      56,    73,    54,    57,    72,    48,    74,    52,    27,    89,
      28,    29,    30,    66,    67,    68,    69,    49,    50,    31,
      32,    33,    34,    58,    75,    79,    59,    60,    61,    62,
      63,    64,    88,    81,    82,    83,    85,    86,    80
};

static const yytype_int8 yycheck[] =
{
       0,     9,     9,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    28,    22,    23,    24,    25,    26,    27,    38,    44,
      38,    46,    38,     9,    45,    39,    47,    39,    38,    48,
      40,    41,    42,    44,    45,    46,    47,    28,    29,    49,
      50,    51,    52,    29,    39,    43,    32,    33,    34,    35,
      36,    37,    73,    18,    19,    20,    30,    31,    43
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    55,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    22,    23,    24,    25,    26,    27,    38,    40,    41,
      42,    49,    50,    51,    52,    56,    57,    58,    59,    60,
      61,    62,    63,    65,    66,    67,    68,    69,    39,    28,
      29,    74,    39,    38,    38,     9,    38,     9,    29,    32,
      33,    34,    35,    36,    37,    71,    44,    45,    46,    47,
      73,    73,    74,    73,    74,    39,     9,    28,    72,    43,
      43,    18,    19,    20,    70,    30,    31,    75,    74,    48,
      64
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    55,    55,    55,    55,    55,    55,    55,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    58,    59,    60,    61,    61,    62,    62,    62,    62,
      62,    62,    63,    64,    64,    65,    66,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    69,    69,
      69,    69,    70,    70,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    73,    73,    73,    73,    74,
      74,    75,    75
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     2,     2,     2,     2,     2,     0,
       1,     2,     2,     4,     3,     2,     2,     3,     2,     3,
       2,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     1,
       1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: program START COL  */
#line 110 "src/rime/parser.y"
                            { set_start(); }
#line 1272 "src/rime/parser.c"
    break;

  case 8: /* program: program END  */
#line 116 "src/rime/parser.y"
                            { YYACCEPT; }
#line 1278 "src/rime/parser.c"
    break;

  case 10: /* ins: op0  */
#line 119 "src/rime/parser.y"
                                { generate_instruction(INS_OP0, (yyvsp[0].byte), 0, 0, 0);     }
#line 1284 "src/rime/parser.c"
    break;

  case 11: /* ins: jmp LABEL  */
#line 120 "src/rime/parser.y"
                                { generate_instruction(INS_JMP_LBL, (yyvsp[-1].byte), 0, 0, 0); }
#line 1290 "src/rime/parser.c"
    break;

  case 12: /* ins: jmp ADR  */
#line 121 "src/rime/parser.y"
                                { generate_instruction(INS_JMP_ADR, (yyvsp[-1].byte), 0, 0, 0); }
#line 1296 "src/rime/parser.c"
    break;

  case 13: /* ins: swr rg1_spec rg2_spec sw  */
#line 122 "src/rime/parser.y"
                                { generate_instruction(INS_SWR, (yyvsp[-3].byte), (yyvsp[-2].byte), (yyvsp[-1].byte), (yyvsp[0].byte));  }
#line 1302 "src/rime/parser.c"
    break;

  case 14: /* ins: flg adr_spec flg_spec  */
#line 123 "src/rime/parser.y"
                                { generate_instruction(INS_FLG, (yyvsp[-2].byte), (yyvsp[-1].byte), (yyvsp[0].byte), 0);   }
#line 1308 "src/rime/parser.c"
    break;

  case 15: /* ins: PSH wrk_reg  */
#line 124 "src/rime/parser.y"
                                { generate_instruction(INS_PSH, (yyvsp[0].byte), 0, 0, 0);     }
#line 1314 "src/rime/parser.c"
    break;

  case 16: /* ins: pop wrk_reg  */
#line 125 "src/rime/parser.y"
                                { generate_instruction(INS_OP2, (yyvsp[-1].byte), 0, (yyvsp[0].byte), 0);    }
#line 1320 "src/rime/parser.c"
    break;

  case 17: /* ins: adr adr_spec adr_reg  */
#line 126 "src/rime/parser.y"
                                { generate_instruction(INS_OP2, (yyvsp[-2].byte), (yyvsp[-1].byte), (yyvsp[0].byte), 0);   }
#line 1326 "src/rime/parser.c"
    break;

  case 18: /* ins: rot wrk_reg  */
#line 127 "src/rime/parser.y"
                                { generate_instruction(INS_ROT, (yyvsp[-1].byte), (yyvsp[0].byte), 0, 0);    }
#line 1332 "src/rime/parser.c"
    break;

  case 19: /* ins: op2 adr_spec wrk_reg  */
#line 128 "src/rime/parser.y"
                                { generate_instruction(INS_OP2, (yyvsp[-2].byte), (yyvsp[-1].byte), (yyvsp[0].byte), 0);   }
#line 1338 "src/rime/parser.c"
    break;

  case 20: /* label: LABEL COL  */
#line 130 "src/rime/parser.y"
                  { if (pass == FIRST) { add_label(); } }
#line 1344 "src/rime/parser.c"
    break;

  case 21: /* func_def: DEF LABEL COL  */
#line 132 "src/rime/parser.y"
                          { add_label();    }
#line 1350 "src/rime/parser.c"
    break;

  case 22: /* func_ret: RET  */
#line 133 "src/rime/parser.y"
                          { func_return();  }
#line 1356 "src/rime/parser.c"
    break;

  case 23: /* func_call: FUN LABEL  */
#line 134 "src/rime/parser.y"
                          { func_call();    }
#line 1362 "src/rime/parser.c"
    break;

  case 24: /* op0: NOP  */
#line 136 "src/rime/parser.y"
          { (yyval.byte) = 0x00; }
#line 1368 "src/rime/parser.c"
    break;

  case 25: /* op0: RST  */
#line 137 "src/rime/parser.y"
          { (yyval.byte) = 0x01; }
#line 1374 "src/rime/parser.c"
    break;

  case 26: /* jmp: JMP  */
#line 139 "src/rime/parser.y"
          { (yyval.byte) = 0x20; }
#line 1380 "src/rime/parser.c"
    break;

  case 27: /* jmp: JNE  */
#line 140 "src/rime/parser.y"
          { (yyval.byte) = 0x21; }
#line 1386 "src/rime/parser.c"
    break;

  case 28: /* jmp: JEQ  */
#line 141 "src/rime/parser.y"
          { (yyval.byte) = 0xA1; }
#line 1392 "src/rime/parser.c"
    break;

  case 29: /* jmp: JLT  */
#line 142 "src/rime/parser.y"
          { (yyval.byte) = 0x22; }
#line 1398 "src/rime/parser.c"
    break;

  case 30: /* jmp: JGE  */
#line 143 "src/rime/parser.y"
          { (yyval.byte) = 0xA2; }
#line 1404 "src/rime/parser.c"
    break;

  case 31: /* jmp: JDC  */
#line 144 "src/rime/parser.y"
          { (yyval.byte) = 0x23; }
#line 1410 "src/rime/parser.c"
    break;

  case 32: /* swr: SWR  */
#line 146 "src/rime/parser.y"
          { (yyval.byte) = 0x04; }
#line 1416 "src/rime/parser.c"
    break;

  case 33: /* sw: SW  */
#line 148 "src/rime/parser.y"
         { (yyval.byte) = 1; }
#line 1422 "src/rime/parser.c"
    break;

  case 34: /* sw: %empty  */
#line 149 "src/rime/parser.y"
         { (yyval.byte) = 0; }
#line 1428 "src/rime/parser.c"
    break;

  case 35: /* flg: FLG  */
#line 151 "src/rime/parser.y"
          { (yyval.byte) = 0x0C; }
#line 1434 "src/rime/parser.c"
    break;

  case 36: /* adr: ADR  */
#line 153 "src/rime/parser.y"
          { (yyval.byte) = 0x08; }
#line 1440 "src/rime/parser.c"
    break;

  case 37: /* pop: POP  */
#line 155 "src/rime/parser.y"
          { (yyval.byte) = 0x15; }
#line 1446 "src/rime/parser.c"
    break;

  case 38: /* op2: PSH  */
#line 157 "src/rime/parser.y"
          { (yyval.byte) = 0x14; }
#line 1452 "src/rime/parser.c"
    break;

  case 39: /* op2: STV  */
#line 158 "src/rime/parser.y"
          { (yyval.byte) = 0x16; }
#line 1458 "src/rime/parser.c"
    break;

  case 40: /* op2: LDV  */
#line 159 "src/rime/parser.y"
          { (yyval.byte) = 0x17; }
#line 1464 "src/rime/parser.c"
    break;

  case 41: /* op2: ADD  */
#line 160 "src/rime/parser.y"
          { (yyval.byte) = 0x18; }
#line 1470 "src/rime/parser.c"
    break;

  case 42: /* op2: ADC  */
#line 161 "src/rime/parser.y"
          { (yyval.byte) = 0x19; }
#line 1476 "src/rime/parser.c"
    break;

  case 43: /* op2: SUB  */
#line 162 "src/rime/parser.y"
          { (yyval.byte) = 0x1A; }
#line 1482 "src/rime/parser.c"
    break;

  case 44: /* op2: SBC  */
#line 163 "src/rime/parser.y"
          { (yyval.byte) = 0x1B; }
#line 1488 "src/rime/parser.c"
    break;

  case 45: /* op2: ORR  */
#line 164 "src/rime/parser.y"
          { (yyval.byte) = 0x1C; }
#line 1494 "src/rime/parser.c"
    break;

  case 46: /* op2: AND  */
#line 165 "src/rime/parser.y"
          { (yyval.byte) = 0x1D; }
#line 1500 "src/rime/parser.c"
    break;

  case 47: /* op2: XOR  */
#line 166 "src/rime/parser.y"
          { (yyval.byte) = 0x1E; }
#line 1506 "src/rime/parser.c"
    break;

  case 48: /* rot: INC  */
#line 169 "src/rime/parser.y"
          { (yyval.byte) = 0x1F | (0 << 6); }
#line 1512 "src/rime/parser.c"
    break;

  case 49: /* rot: DEC  */
#line 170 "src/rime/parser.y"
          { (yyval.byte) = 0x1F | (1 << 6); }
#line 1518 "src/rime/parser.c"
    break;

  case 50: /* rot: LSH  */
#line 171 "src/rime/parser.y"
          { (yyval.byte) = 0x1F | (2 << 6); }
#line 1524 "src/rime/parser.c"
    break;

  case 51: /* rot: RSH  */
#line 172 "src/rime/parser.y"
          { (yyval.byte) = 0x1F | (3 << 6); }
#line 1530 "src/rime/parser.c"
    break;

  case 52: /* flg_spec: AND  */
#line 174 "src/rime/parser.y"
              { (yyval.byte) = 0; }
#line 1536 "src/rime/parser.c"
    break;

  case 53: /* flg_spec: ORR  */
#line 175 "src/rime/parser.y"
              { (yyval.byte) = 1; }
#line 1542 "src/rime/parser.c"
    break;

  case 54: /* flg_spec: XOR  */
#line 176 "src/rime/parser.y"
              { (yyval.byte) = 2; }
#line 1548 "src/rime/parser.c"
    break;

  case 55: /* rg1_spec: CTR  */
#line 178 "src/rime/parser.y"
              { (yyval.byte) = 0; }
#line 1554 "src/rime/parser.c"
    break;

  case 56: /* rg1_spec: FRG  */
#line 179 "src/rime/parser.y"
              { (yyval.byte) = 1; }
#line 1560 "src/rime/parser.c"
    break;

  case 57: /* rg1_spec: SP  */
#line 180 "src/rime/parser.y"
              { (yyval.byte) = 2; }
#line 1566 "src/rime/parser.c"
    break;

  case 58: /* rg1_spec: PC  */
#line 181 "src/rime/parser.y"
              { (yyval.byte) = 3; }
#line 1572 "src/rime/parser.c"
    break;

  case 59: /* rg1_spec: TMR  */
#line 182 "src/rime/parser.y"
              { (yyval.byte) = 4; }
#line 1578 "src/rime/parser.c"
    break;

  case 60: /* rg1_spec: DP  */
#line 183 "src/rime/parser.y"
              { (yyval.byte) = 5; }
#line 1584 "src/rime/parser.c"
    break;

  case 61: /* rg1_spec: AP  */
#line 184 "src/rime/parser.y"
              { (yyval.byte) = 6; }
#line 1590 "src/rime/parser.c"
    break;

  case 62: /* rg1_spec: ADR  */
#line 185 "src/rime/parser.y"
              { (yyval.byte) = 7; }
#line 1596 "src/rime/parser.c"
    break;

  case 63: /* rg2_spec: ACC  */
#line 187 "src/rime/parser.y"
              { (yyval.byte) = 0; }
#line 1602 "src/rime/parser.c"
    break;

  case 64: /* rg2_spec: ADR  */
#line 188 "src/rime/parser.y"
              { (yyval.byte) = 1; }
#line 1608 "src/rime/parser.c"
    break;

  case 65: /* adr_spec: STK  */
#line 190 "src/rime/parser.y"
                  { (yyval.byte) = 0; }
#line 1614 "src/rime/parser.c"
    break;

  case 66: /* adr_spec: IMM LIT  */
#line 191 "src/rime/parser.y"
                  { (yyval.byte) = 1; }
#line 1620 "src/rime/parser.c"
    break;

  case 67: /* adr_spec: IND  */
#line 192 "src/rime/parser.y"
                  { (yyval.byte) = 2; }
#line 1626 "src/rime/parser.c"
    break;

  case 68: /* adr_spec: DIR LIT  */
#line 193 "src/rime/parser.y"
                  { (yyval.byte) = 3; }
#line 1632 "src/rime/parser.c"
    break;

  case 69: /* wrk_reg: ACC  */
#line 195 "src/rime/parser.y"
              { (yyval.byte) = 0; }
#line 1638 "src/rime/parser.c"
    break;

  case 70: /* wrk_reg: CTR  */
#line 196 "src/rime/parser.y"
              { (yyval.byte) = 1; }
#line 1644 "src/rime/parser.c"
    break;

  case 71: /* adr_reg: ADL  */
#line 197 "src/rime/parser.y"
              { (yyval.byte) = 0; }
#line 1650 "src/rime/parser.c"
    break;

  case 72: /* adr_reg: ADH  */
#line 198 "src/rime/parser.y"
              { (yyval.byte) = 1; }
#line 1656 "src/rime/parser.c"
    break;


#line 1660 "src/rime/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 199 "src/rime/parser.y"


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

int main(int argc, char* argv[]) {
  if (argc < 2) {
      printf("Usage: %s <source-file>\n", argv[0]);
      return 1;
  }

  // Open the source file
  yyin = fopen(argv[1], "r");
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
  yyparse();

  int start = labels[0].value % PROGRAM_SIZE;
  printf("%c%c", (start>>8)&0xFF, start&0xFF);
  for (unsigned int i = 2; i < PROGRAM_SIZE; i++) {
    printf("%c", program[i]);
  }
  
  fclose(yyin);

  return 0;
}
