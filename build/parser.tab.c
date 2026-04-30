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
#line 1 "src/parser/parser.y"

#include "ast.h"
#include "semantic.h"
#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

extern int yylineno; // Declare yylineno from lexer
extern FILE* yyin;   // Declare yyin from lexer
extern int yylex();  // Declare yylex
extern char** global_argv;

// Define yyerror
void yyerror(const char *s) {
    fprintf(stderr, COLOR_RED "Error at line %d: %s\n" COLOR_RESET, yylineno, s);
}

#line 96 "build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PACKAGE = 3,                    /* PACKAGE  */
  YYSYMBOL_IMPORT = 4,                     /* IMPORT  */
  YYSYMBOL_FUNC = 5,                       /* FUNC  */
  YYSYMBOL_RETURN = 6,                     /* RETURN  */
  YYSYMBOL_VAR = 7,                        /* VAR  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_FOR = 10,                       /* FOR  */
  YYSYMBOL_INT_TYPE = 11,                  /* INT_TYPE  */
  YYSYMBOL_FLOAT64_TYPE = 12,              /* FLOAT64_TYPE  */
  YYSYMBOL_STRING_TYPE = 13,               /* STRING_TYPE  */
  YYSYMBOL_BOOL_TYPE = 14,                 /* BOOL_TYPE  */
  YYSYMBOL_VOID_TYPE = 15,                 /* VOID_TYPE  */
  YYSYMBOL_TRUE = 16,                      /* TRUE  */
  YYSYMBOL_FALSE = 17,                     /* FALSE  */
  YYSYMBOL_STRUCT = 18,                    /* STRUCT  */
  YYSYMBOL_INTERFACE = 19,                 /* INTERFACE  */
  YYSYMBOL_MAP = 20,                       /* MAP  */
  YYSYMBOL_SLICE = 21,                     /* SLICE  */
  YYSYMBOL_CHAN = 22,                      /* CHAN  */
  YYSYMBOL_TYPE = 23,                      /* TYPE  */
  YYSYMBOL_IDENTIFIER = 24,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 25,                    /* STRING  */
  YYSYMBOL_INTEGER = 26,                   /* INTEGER  */
  YYSYMBOL_INCREMENT = 27,                 /* INCREMENT  */
  YYSYMBOL_FLOAT = 28,                     /* FLOAT  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 31,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 32,                    /* DIVIDE  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_EQ = 34,                        /* EQ  */
  YYSYMBOL_NEQ = 35,                       /* NEQ  */
  YYSYMBOL_LT = 36,                        /* LT  */
  YYSYMBOL_GT = 37,                        /* GT  */
  YYSYMBOL_LTE = 38,                       /* LTE  */
  YYSYMBOL_GTE = 39,                       /* GTE  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_LSHIFT = 42,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 43,                    /* RSHIFT  */
  YYSYMBOL_BITAND = 44,                    /* BITAND  */
  YYSYMBOL_BITOR = 45,                     /* BITOR  */
  YYSYMBOL_BITXOR = 46,                    /* BITXOR  */
  YYSYMBOL_LPAREN = 47,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 48,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 49,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 50,                    /* RBRACE  */
  YYSYMBOL_SEMICOLON = 51,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 52,                     /* COMMA  */
  YYSYMBOL_DOT = 53,                       /* DOT  */
  YYSYMBOL_DECLARE_ASSIGN = 54,            /* DECLARE_ASSIGN  */
  YYSYMBOL_YYACCEPT = 55,                  /* $accept  */
  YYSYMBOL_program = 56,                   /* program  */
  YYSYMBOL_imports = 57,                   /* imports  */
  YYSYMBOL_type_decls = 58,                /* type_decls  */
  YYSYMBOL_field_decls = 59,               /* field_decls  */
  YYSYMBOL_method_decls = 60,              /* method_decls  */
  YYSYMBOL_type = 61,                      /* type  */
  YYSYMBOL_functions = 62,                 /* functions  */
  YYSYMBOL_receiver = 63,                  /* receiver  */
  YYSYMBOL_return_type = 64,               /* return_type  */
  YYSYMBOL_parameters = 65,                /* parameters  */
  YYSYMBOL_statements = 66,                /* statements  */
  YYSYMBOL_statement = 67,                 /* statement  */
  YYSYMBOL_arguments = 68,                 /* arguments  */
  YYSYMBOL_expression = 69                 /* expression  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   371

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  71
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    64,    64,    90,    91,   100,   101,   107,   117,   118,
     127,   128,   136,   138,   140,   142,   144,   146,   148,   150,
     152,   158,   159,   169,   170,   179,   180,   186,   187,   192,
     201,   202,   212,   217,   222,   227,   232,   237,   242,   247,
     252,   259,   268,   269,   271,   276,   282,   288,   293,   299,
     305,   310,   315,   320,   325,   330,   335,   340,   345,   350,
     355,   360,   365,   370,   375,   380,   385,   390,   395,   400,
     405,   410
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
  "\"end of file\"", "error", "\"invalid token\"", "PACKAGE", "IMPORT",
  "FUNC", "RETURN", "VAR", "IF", "ELSE", "FOR", "INT_TYPE", "FLOAT64_TYPE",
  "STRING_TYPE", "BOOL_TYPE", "VOID_TYPE", "TRUE", "FALSE", "STRUCT",
  "INTERFACE", "MAP", "SLICE", "CHAN", "TYPE", "IDENTIFIER", "STRING",
  "INTEGER", "INCREMENT", "FLOAT", "PLUS", "MINUS", "MULTIPLY", "DIVIDE",
  "ASSIGN", "EQ", "NEQ", "LT", "GT", "LTE", "GTE", "AND", "OR", "LSHIFT",
  "RSHIFT", "BITAND", "BITOR", "BITXOR", "LPAREN", "RPAREN", "LBRACE",
  "RBRACE", "SEMICOLON", "COMMA", "DOT", "DECLARE_ASSIGN", "$accept",
  "program", "imports", "type_decls", "field_decls", "method_decls",
  "type", "functions", "receiver", "return_type", "parameters",
  "statements", "statement", "arguments", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-31)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       2,     4,    31,   -18,   -94,    32,    47,    53,    26,    59,
      79,    32,    56,    38,   -94,   -94,    37,    45,    83,    84,
     103,   230,   231,   214,   311,   225,   234,   239,   251,   293,
     -94,   -94,   -94,   -94,   -94,   269,   278,   311,   -94,   283,
     285,   293,   286,   -94,   311,   290,   311,   289,   -94,   103,
      53,   292,    53,   291,   311,   294,   311,   -94,   -94,   311,
     -94,   293,   -94,   296,   311,   -94,   295,   -94,    63,   -94,
     230,   297,   -15,   317,   -15,   318,   -27,   299,    63,   -94,
     -94,   -94,   -94,   -35,   -94,   -94,   -94,   -15,    99,   311,
     207,   298,   -15,   -15,   323,    79,   -94,   -15,   326,   228,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,   -15,
     -15,   -15,   -15,   -15,   -15,   -15,   -15,   -94,   -14,    63,
     -15,   117,   303,    80,   -26,   -94,   305,   307,   -94,   275,
     275,    -6,    -6,    60,    60,    36,    36,    36,    36,   266,
     248,   284,   284,   -94,   -94,   -94,   -15,   -94,   306,   135,
     -94,   304,   -15,   -15,   -15,   -94,   -15,   153,   348,   -15,
     -94,   -94,   171,   310,   312,   -94,   313,   189,   -94,   308,
     -94,    63,   337,   -94,   314,   336,   -94,   316,    63,   319,
     -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     5,     0,     0,
      21,     3,     0,    23,     2,     4,     0,     0,     0,     0,
       8,    10,     0,     0,     0,     0,     0,     0,     0,    27,
      12,    13,    14,    15,    16,     0,     0,     0,    20,     0,
       0,    27,     0,    24,     0,     0,     0,     0,    19,     8,
       5,     0,     5,    29,    25,     0,     0,     9,     6,     0,
       7,    27,    26,     0,     0,    18,     0,    28,     0,    17,
      10,     0,     0,     0,     0,     0,     0,     0,     0,    11,
      41,    48,    49,    50,    47,    45,    46,     0,     0,     0,
       0,     0,     0,    42,     0,    21,    31,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,     0,     0,
       0,     0,     0,    43,     0,    22,     0,    51,    71,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,     0,    33,     0,     0,
      35,     0,    42,     0,    42,    53,    42,     0,     0,     0,
      38,    44,     0,     0,     0,    34,     0,     0,    36,     0,
      52,     0,     0,    37,     0,     0,    39,     0,     0,     0,
      40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   355,   -28,   321,   301,   -29,   272,   -94,   -94,
     -38,   -78,   -94,   -93,   -58
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     7,    10,    25,    27,    39,    14,    19,    63,
      45,    77,    78,   122,   123
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      96,    81,    82,    51,   126,     1,    92,   153,    48,    83,
      84,    85,    97,    86,    88,    53,    90,    55,    98,   146,
      93,   154,    58,    67,    60,    62,    94,    65,     3,    99,
      66,     4,    87,     5,   121,    69,     6,   147,   114,   115,
     116,   148,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   161,
     118,   163,   149,   164,    71,   100,   101,   102,   103,    72,
      73,    74,     8,    75,    16,    17,     9,    11,   112,   113,
     114,   115,   116,    12,    13,    18,    20,    76,   157,   100,
     101,   102,   103,   174,    21,   162,   106,   107,   108,   109,
     179,   167,   112,   113,   114,   115,   116,    22,    23,   100,
     101,   102,   103,   -30,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    24,   100,   101,
     102,   103,   152,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   100,   101,   102,   103,
     117,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   100,   101,   102,   103,   150,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   100,   101,   102,   103,   159,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     100,   101,   102,   103,   165,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   100,   101,
     102,   103,   168,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   100,   101,   102,   103,
     172,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,    26,    28,   119,   100,   101,   102,
     103,    29,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,    40,   128,   100,   101,   102,
     103,    41,   104,   105,   106,   107,   108,   109,   110,    42,
     112,   113,   114,   115,   116,   100,   101,   102,   103,    43,
     104,   105,   106,   107,   108,   109,   102,   103,   112,   113,
     114,   115,   116,   100,   101,   102,   103,    44,    46,   114,
     115,   116,    30,    31,    32,    33,    34,    47,   114,   115,
     116,    35,    36,    37,    49,    38,    50,    52,    54,    56,
      59,    89,    91,    61,    64,    68,    70,   124,    80,    95,
     127,   151,   120,   155,   156,   160,   158,   166,   169,   173,
     170,   175,   171,   177,   176,   178,    15,   125,     0,   180,
      57,    79
};

static const yytype_int16 yycheck[] =
{
      78,    16,    17,    41,    97,     3,    33,    33,    37,    24,
      25,    26,    47,    28,    72,    44,    74,    46,    53,    33,
      47,    47,    50,    61,    52,    54,    53,    56,    24,    87,
      59,     0,    47,    51,    92,    64,     4,    51,    44,    45,
      46,   119,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   152,
      89,   154,   120,   156,     1,    29,    30,    31,    32,     6,
       7,     8,    25,    10,    18,    19,    23,    51,    42,    43,
      44,    45,    46,    24,     5,    47,    49,    24,   146,    29,
      30,    31,    32,   171,    49,   153,    36,    37,    38,    39,
     178,   159,    42,    43,    44,    45,    46,    24,    24,    29,
      30,    31,    32,    50,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    24,    29,    30,
      31,    32,    52,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    29,    30,    31,    32,
      51,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    29,    30,    31,    32,    51,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    29,    30,    31,    32,    51,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      29,    30,    31,    32,    51,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    29,    30,
      31,    32,    51,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    29,    30,    31,    32,
      51,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    24,    24,    49,    29,    30,    31,
      32,    47,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    50,    48,    29,    30,    31,
      32,    47,    34,    35,    36,    37,    38,    39,    40,    50,
      42,    43,    44,    45,    46,    29,    30,    31,    32,    48,
      34,    35,    36,    37,    38,    39,    31,    32,    42,    43,
      44,    45,    46,    29,    30,    31,    32,    24,    49,    44,
      45,    46,    11,    12,    13,    14,    15,    49,    44,    45,
      46,    20,    21,    22,    51,    24,    51,    51,    48,    50,
      48,    24,    24,    52,    50,    49,    51,    24,    51,    50,
      24,    48,    54,    48,    47,    51,    50,     9,    48,    51,
      48,    24,    49,    27,    50,    49,    11,    95,    -1,    50,
      49,    70
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    56,    24,     0,    51,     4,    57,    25,    23,
      58,    51,    24,     5,    62,    57,    18,    19,    47,    63,
      49,    49,    24,    24,    24,    59,    24,    60,    24,    47,
      11,    12,    13,    14,    15,    20,    21,    22,    24,    61,
      50,    47,    50,    48,    24,    65,    49,    49,    61,    51,
      51,    65,    51,    61,    48,    61,    50,    59,    58,    48,
      58,    52,    61,    64,    50,    61,    61,    65,    49,    61,
      51,     1,     6,     7,     8,    10,    24,    66,    67,    60,
      51,    16,    17,    24,    25,    26,    28,    47,    69,    24,
      69,    24,    33,    47,    53,    50,    66,    47,    53,    69,
      29,    30,    31,    32,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    51,    61,    49,
      54,    69,    68,    69,    24,    62,    68,    24,    48,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    33,    51,    66,    69,
      51,    48,    52,    33,    47,    48,    47,    69,    50,    51,
      51,    68,    69,    68,    68,    51,     9,    69,    51,    48,
      48,    49,    51,    51,    66,    24,    50,    27,    49,    66,
      50
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    58,    59,    59,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    63,    63,    64,    64,    65,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    68,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     0,     4,     0,     8,     8,     0,     4,
       0,     7,     1,     1,     1,     1,     1,     5,     4,     2,
       1,     0,    11,     0,     4,     0,     1,     0,     4,     2,
       0,     2,     3,     4,     6,     4,     6,     7,     5,     9,
      12,     2,     0,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     6,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3
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
  case 2: /* program: PACKAGE IDENTIFIER SEMICOLON imports type_decls functions  */
#line 65 "src/parser/parser.y"
    { 
      (yyval.node) = createProgramNode((yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));
      if (semanticAnalyze((yyval.node))) { // perform semantic analysis
            fprintf(stderr, COLOR_RED "PARSER: Semantic errors detected, exiting...\n" COLOR_RESET);
            YYABORT; // This will make Bison return 1 from yyparse()
      }
      printf(COLOR_GREEN "PARSER: Program parsed successfully\n" COLOR_RESET);
      printAST((yyval.node), 0, 0, NULL); // Print AST for debugging
      printAST((yyval.node), 0, 1, "ast.json"); // Print AST to JSON file
      printf(COLOR_GREEN "PARSER: AST created successfully\n" COLOR_RESET);

        CodegenContext* context = createCodegenContext(
          (global_argv && global_argv[1]) ? global_argv[1] : "input.go",
          "output.ic");
        if (context && generateCode((yyval.node), context) == 0) {
          printf(COLOR_GREEN "BACKEND: Stack IC written to output.ic\n" COLOR_RESET);
        } else {
          fprintf(stderr, COLOR_RED "BACKEND: Code generation failed\n" COLOR_RESET);
        }
        freeCodegenContext(context);
    }
#line 1323 "build/parser.tab.c"
    break;

  case 3: /* imports: %empty  */
#line 90 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1329 "build/parser.tab.c"
    break;

  case 4: /* imports: IMPORT STRING SEMICOLON imports  */
#line 92 "src/parser/parser.y"
    { 
      (yyval.node) = createImportNode((yyvsp[-2].str), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Import statement parsed\n" COLOR_RESET); 
    }
#line 1338 "build/parser.tab.c"
    break;

  case 5: /* type_decls: %empty  */
#line 100 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1344 "build/parser.tab.c"
    break;

  case 6: /* type_decls: TYPE IDENTIFIER STRUCT LBRACE field_decls RBRACE SEMICOLON type_decls  */
#line 102 "src/parser/parser.y"
    { 
       (yyval.node) = createStructNode((yyvsp[-6].str), (yyvsp[-3].node));
       (yyval.node)->next = (yyvsp[0].node);
       printf(COLOR_BLUE "PARSER: Struct declaration parsed\n" COLOR_RESET); 
    }
#line 1354 "build/parser.tab.c"
    break;

  case 7: /* type_decls: TYPE IDENTIFIER INTERFACE LBRACE method_decls RBRACE SEMICOLON type_decls  */
#line 108 "src/parser/parser.y"
    { 
       (yyval.node) = createInterfaceNode((yyvsp[-6].str), (yyvsp[-3].node));
       (yyval.node)->next = (yyvsp[0].node);
       printf(COLOR_BLUE "PARSER: Interface declaration parsed\n" COLOR_RESET); 
    }
#line 1364 "build/parser.tab.c"
    break;

  case 8: /* field_decls: %empty  */
#line 117 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1370 "build/parser.tab.c"
    break;

  case 9: /* field_decls: IDENTIFIER type SEMICOLON field_decls  */
#line 119 "src/parser/parser.y"
    { 
      (yyval.node) = createFieldNode((yyvsp[-3].str), (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Field declaration parsed\n" COLOR_RESET); 
    }
#line 1379 "build/parser.tab.c"
    break;

  case 10: /* method_decls: %empty  */
#line 127 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1385 "build/parser.tab.c"
    break;

  case 11: /* method_decls: IDENTIFIER LPAREN parameters RPAREN type SEMICOLON method_decls  */
#line 129 "src/parser/parser.y"
    { 
      (yyval.node) = createMethodNode((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Method declaration parsed\n" COLOR_RESET); 
    }
#line 1394 "build/parser.tab.c"
    break;

  case 12: /* type: INT_TYPE  */
#line 137 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("int"); }
#line 1400 "build/parser.tab.c"
    break;

  case 13: /* type: FLOAT64_TYPE  */
#line 139 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("float64"); }
#line 1406 "build/parser.tab.c"
    break;

  case 14: /* type: STRING_TYPE  */
#line 141 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("string"); }
#line 1412 "build/parser.tab.c"
    break;

  case 15: /* type: BOOL_TYPE  */
#line 143 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("bool"); }
#line 1418 "build/parser.tab.c"
    break;

  case 16: /* type: VOID_TYPE  */
#line 145 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("void"); }
#line 1424 "build/parser.tab.c"
    break;

  case 17: /* type: MAP LBRACE type RBRACE type  */
#line 147 "src/parser/parser.y"
    { (yyval.node) = createMapTypeNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1430 "build/parser.tab.c"
    break;

  case 18: /* type: SLICE LBRACE RBRACE type  */
#line 149 "src/parser/parser.y"
    { (yyval.node) = createSliceTypeNode((yyvsp[0].node)); }
#line 1436 "build/parser.tab.c"
    break;

  case 19: /* type: CHAN type  */
#line 151 "src/parser/parser.y"
    { (yyval.node) = createChanTypeNode((yyvsp[0].node)); }
#line 1442 "build/parser.tab.c"
    break;

  case 20: /* type: IDENTIFIER  */
#line 153 "src/parser/parser.y"
    { (yyval.node) = createTypeNode((yyvsp[0].str)); }
#line 1448 "build/parser.tab.c"
    break;

  case 21: /* functions: %empty  */
#line 158 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1454 "build/parser.tab.c"
    break;

  case 22: /* functions: FUNC receiver IDENTIFIER LPAREN parameters RPAREN return_type LBRACE statements RBRACE functions  */
#line 160 "src/parser/parser.y"
    {
        ASTNode* newFunction = createFunctionNode((yyvsp[-8].str), (yyvsp[-9].node), (yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
        printf(COLOR_BLUE "PARSER: Function parsed : %s\n" COLOR_RESET, (yyvsp[-8].str));
        (yyval.node) = newFunction;
    }
#line 1464 "build/parser.tab.c"
    break;

  case 23: /* receiver: %empty  */
#line 169 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1470 "build/parser.tab.c"
    break;

  case 24: /* receiver: LPAREN IDENTIFIER IDENTIFIER RPAREN  */
#line 171 "src/parser/parser.y"
    {
      (yyval.node) = createReceiverNode((yyvsp[-2].str), (yyvsp[-1].str));
      printf(COLOR_BLUE "PARSER: Receiver parsed\n" COLOR_RESET);
    }
#line 1479 "build/parser.tab.c"
    break;

  case 25: /* return_type: %empty  */
#line 179 "src/parser/parser.y"
    { (yyval.node) = createTypeNode("void"); }
#line 1485 "build/parser.tab.c"
    break;

  case 26: /* return_type: type  */
#line 181 "src/parser/parser.y"
    { (yyval.node) = (yyvsp[0].node); }
#line 1491 "build/parser.tab.c"
    break;

  case 27: /* parameters: %empty  */
#line 186 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1497 "build/parser.tab.c"
    break;

  case 28: /* parameters: IDENTIFIER type COMMA parameters  */
#line 188 "src/parser/parser.y"
    { 
      (yyval.node) = createParameterNode((yyvsp[-3].str), (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Parameter parsed\n" COLOR_RESET); 
    }
#line 1506 "build/parser.tab.c"
    break;

  case 29: /* parameters: IDENTIFIER type  */
#line 193 "src/parser/parser.y"
    { 
      (yyval.node) = createParameterNode((yyvsp[-1].str), (yyvsp[0].node), NULL);
      printf(COLOR_BLUE "PARSER: Parameter parsed\n" COLOR_RESET); 
    }
#line 1515 "build/parser.tab.c"
    break;

  case 30: /* statements: %empty  */
#line 201 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1521 "build/parser.tab.c"
    break;

  case 31: /* statements: statement statements  */
#line 203 "src/parser/parser.y"
    { 
      if ((yyvsp[-1].node) != NULL && (yyvsp[0].node) != NULL) {
        (yyvsp[-1].node)->next = (yyvsp[0].node);
      }
      (yyval.node) = (yyvsp[-1].node);
    }
#line 1532 "build/parser.tab.c"
    break;

  case 32: /* statement: RETURN expression SEMICOLON  */
#line 213 "src/parser/parser.y"
    { 
      (yyval.node) = createReturnNode((yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Return statement parsed\n" COLOR_RESET); 
    }
#line 1541 "build/parser.tab.c"
    break;

  case 33: /* statement: VAR IDENTIFIER type SEMICOLON  */
#line 218 "src/parser/parser.y"
    { 
      (yyval.node) = createVarDeclNode((yyvsp[-2].str), (yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Variable declaration parsed\n" COLOR_RESET); 
    }
#line 1550 "build/parser.tab.c"
    break;

  case 34: /* statement: VAR IDENTIFIER type ASSIGN expression SEMICOLON  */
#line 223 "src/parser/parser.y"
    { 
      (yyval.node) = createVarDeclAssignNode((yyvsp[-4].str), (yyvsp[-3].node), (yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Variable declaration with assignment parsed\n" COLOR_RESET); 
    }
#line 1559 "build/parser.tab.c"
    break;

  case 35: /* statement: IDENTIFIER ASSIGN expression SEMICOLON  */
#line 228 "src/parser/parser.y"
    { 
      (yyval.node) = createAssignNode((yyvsp[-3].str), (yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Assignment statement parsed\n" COLOR_RESET); 
    }
#line 1568 "build/parser.tab.c"
    break;

  case 36: /* statement: IDENTIFIER DOT IDENTIFIER ASSIGN expression SEMICOLON  */
#line 233 "src/parser/parser.y"
    { 
      (yyval.node) = createStructFieldAssignNode((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Struct field assignment parsed\n" COLOR_RESET); 
    }
#line 1577 "build/parser.tab.c"
    break;

  case 37: /* statement: IDENTIFIER DOT IDENTIFIER LPAREN arguments RPAREN SEMICOLON  */
#line 238 "src/parser/parser.y"
    { 
      (yyval.node) = createMethodCallNode((yyvsp[-6].str), (yyvsp[-4].str), (yyvsp[-2].node), NULL);
      printf(COLOR_BLUE "PARSER: Method call parsed\n" COLOR_RESET); 
    }
#line 1586 "build/parser.tab.c"
    break;

  case 38: /* statement: IDENTIFIER LPAREN arguments RPAREN SEMICOLON  */
#line 243 "src/parser/parser.y"
    {
      (yyval.node) = createCallNode((yyvsp[-4].str), (yyvsp[-2].node));
      printf(COLOR_BLUE "PARSER: Function call parsed\n" COLOR_RESET); 
    }
#line 1595 "build/parser.tab.c"
    break;

  case 39: /* statement: IF expression LBRACE statements RBRACE ELSE LBRACE statements RBRACE  */
#line 248 "src/parser/parser.y"
    { 
      (yyval.node) = createIfNode((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-1].node));
      printf(COLOR_BLUE "PARSER: If-else statement parsed\n" COLOR_RESET); 
    }
#line 1604 "build/parser.tab.c"
    break;

  case 40: /* statement: FOR IDENTIFIER DECLARE_ASSIGN expression SEMICOLON expression SEMICOLON IDENTIFIER INCREMENT LBRACE statements RBRACE  */
#line 253 "src/parser/parser.y"
    { 
      // Create an AST node for the increment operation
      ASTNode* incrementNode = createBinaryOpNode("+", createIdentifierNode((yyvsp[-4].str)), createLiteralNode("int", &(int){1}));
      (yyval.node) = createForNode((yyvsp[-8].node), (yyvsp[-6].node), incrementNode, (yyvsp[-1].node));
      printf(COLOR_BLUE "PARSER: For loop parsed\n" COLOR_RESET); 
    }
#line 1615 "build/parser.tab.c"
    break;

  case 41: /* statement: error SEMICOLON  */
#line 260 "src/parser/parser.y"
    { 
      printf(COLOR_RED "PARSER: Error recovery\n" COLOR_RESET); 
      (yyval.node) = NULL;
    }
#line 1624 "build/parser.tab.c"
    break;

  case 42: /* arguments: %empty  */
#line 268 "src/parser/parser.y"
    { (yyval.node) = NULL; }
#line 1630 "build/parser.tab.c"
    break;

  case 43: /* arguments: expression  */
#line 270 "src/parser/parser.y"
    { (yyval.node) = createArgumentNode((yyvsp[0].node), NULL); }
#line 1636 "build/parser.tab.c"
    break;

  case 44: /* arguments: expression COMMA arguments  */
#line 272 "src/parser/parser.y"
    { (yyval.node) = createArgumentNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1642 "build/parser.tab.c"
    break;

  case 45: /* expression: INTEGER  */
#line 277 "src/parser/parser.y"
    { 
      int value = (yyvsp[0].num);
      (yyval.node) = createLiteralNode("int", &value);
      printf(COLOR_BLUE "PARSER: Integer expression parsed\n" COLOR_RESET); 
    }
#line 1652 "build/parser.tab.c"
    break;

  case 46: /* expression: FLOAT  */
#line 283 "src/parser/parser.y"
    { 
      double value = (yyvsp[0].fnum);
      (yyval.node) = createLiteralNode("float", &value);
      printf(COLOR_BLUE "PARSER: Float expression parsed\n" COLOR_RESET); 
    }
#line 1662 "build/parser.tab.c"
    break;

  case 47: /* expression: STRING  */
#line 289 "src/parser/parser.y"
    { 
      (yyval.node) = createLiteralNode("string", (yyvsp[0].str));
      printf(COLOR_BLUE "PARSER: String expression parsed\n" COLOR_RESET); 
    }
#line 1671 "build/parser.tab.c"
    break;

  case 48: /* expression: TRUE  */
#line 294 "src/parser/parser.y"
    { 
      bool value = true;
      (yyval.node) = createLiteralNode("bool", &value);
      printf(COLOR_BLUE "PARSER: True expression parsed\n" COLOR_RESET); 
    }
#line 1681 "build/parser.tab.c"
    break;

  case 49: /* expression: FALSE  */
#line 300 "src/parser/parser.y"
    { 
      bool value = false;
      (yyval.node) = createLiteralNode("bool", &value);
      printf(COLOR_BLUE "PARSER: False expression parsed\n" COLOR_RESET); 
    }
#line 1691 "build/parser.tab.c"
    break;

  case 50: /* expression: IDENTIFIER  */
#line 306 "src/parser/parser.y"
    { 
      (yyval.node) = createIdentifierNode((yyvsp[0].str));
      printf(COLOR_BLUE "PARSER: Identifier expression parsed\n" COLOR_RESET); 
    }
#line 1700 "build/parser.tab.c"
    break;

  case 51: /* expression: IDENTIFIER DOT IDENTIFIER  */
#line 311 "src/parser/parser.y"
    { 
      (yyval.node) = createStructFieldAccessNode((yyvsp[-2].str), (yyvsp[0].str));
      printf(COLOR_BLUE "PARSER: Struct field access parsed\n" COLOR_RESET); 
    }
#line 1709 "build/parser.tab.c"
    break;

  case 52: /* expression: IDENTIFIER DOT IDENTIFIER LPAREN arguments RPAREN  */
#line 316 "src/parser/parser.y"
    { 
      (yyval.node) = createMethodCallNode((yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].node), NULL);
      printf(COLOR_BLUE "PARSER: Method call parsed\n" COLOR_RESET); 
    }
#line 1718 "build/parser.tab.c"
    break;

  case 53: /* expression: IDENTIFIER LPAREN arguments RPAREN  */
#line 321 "src/parser/parser.y"
    { 
      (yyval.node) = createCallNode((yyvsp[-3].str), (yyvsp[-1].node));
      printf(COLOR_BLUE "PARSER: Function call parsed\n" COLOR_RESET); 
    }
#line 1727 "build/parser.tab.c"
    break;

  case 54: /* expression: expression PLUS expression  */
#line 326 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("+", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Addition expression parsed\n" COLOR_RESET); 
    }
#line 1736 "build/parser.tab.c"
    break;

  case 55: /* expression: expression MINUS expression  */
#line 331 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("-", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Subtraction expression parsed\n" COLOR_RESET); 
    }
#line 1745 "build/parser.tab.c"
    break;

  case 56: /* expression: expression MULTIPLY expression  */
#line 336 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("*", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Multiplication expression parsed\n" COLOR_RESET); 
    }
#line 1754 "build/parser.tab.c"
    break;

  case 57: /* expression: expression DIVIDE expression  */
#line 341 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("/", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Division expression parsed\n" COLOR_RESET); 
    }
#line 1763 "build/parser.tab.c"
    break;

  case 58: /* expression: expression EQ expression  */
#line 346 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("==", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Equality expression parsed\n" COLOR_RESET); 
    }
#line 1772 "build/parser.tab.c"
    break;

  case 59: /* expression: expression NEQ expression  */
#line 351 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("!=", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Inequality expression parsed\n" COLOR_RESET); 
    }
#line 1781 "build/parser.tab.c"
    break;

  case 60: /* expression: expression LT expression  */
#line 356 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("<", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Less-than expression parsed\n" COLOR_RESET); 
    }
#line 1790 "build/parser.tab.c"
    break;

  case 61: /* expression: expression GT expression  */
#line 361 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode(">", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Greater-than expression parsed\n" COLOR_RESET); 
    }
#line 1799 "build/parser.tab.c"
    break;

  case 62: /* expression: expression LTE expression  */
#line 366 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("<=", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Less-than-or-equal expression parsed\n" COLOR_RESET); 
    }
#line 1808 "build/parser.tab.c"
    break;

  case 63: /* expression: expression GTE expression  */
#line 371 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode(">=", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Greater-than-or-equal expression parsed\n" COLOR_RESET); 
    }
#line 1817 "build/parser.tab.c"
    break;

  case 64: /* expression: expression AND expression  */
#line 376 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("&&", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Logical AND expression parsed\n" COLOR_RESET); 
    }
#line 1826 "build/parser.tab.c"
    break;

  case 65: /* expression: expression OR expression  */
#line 381 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("||", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Logical OR expression parsed\n" COLOR_RESET); 
    }
#line 1835 "build/parser.tab.c"
    break;

  case 66: /* expression: expression LSHIFT expression  */
#line 386 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("<<", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Left shift expression parsed\n" COLOR_RESET); 
    }
#line 1844 "build/parser.tab.c"
    break;

  case 67: /* expression: expression RSHIFT expression  */
#line 391 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode(">>", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Right shift expression parsed\n" COLOR_RESET); 
    }
#line 1853 "build/parser.tab.c"
    break;

  case 68: /* expression: expression BITAND expression  */
#line 396 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("&", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Bitwise AND expression parsed\n" COLOR_RESET); 
    }
#line 1862 "build/parser.tab.c"
    break;

  case 69: /* expression: expression BITOR expression  */
#line 401 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("|", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Bitwise OR expression parsed\n" COLOR_RESET); 
    }
#line 1871 "build/parser.tab.c"
    break;

  case 70: /* expression: expression BITXOR expression  */
#line 406 "src/parser/parser.y"
    { 
      (yyval.node) = createBinaryOpNode("^", (yyvsp[-2].node), (yyvsp[0].node));
      printf(COLOR_BLUE "PARSER: Bitwise XOR expression parsed\n" COLOR_RESET); 
    }
#line 1880 "build/parser.tab.c"
    break;

  case 71: /* expression: LPAREN expression RPAREN  */
#line 411 "src/parser/parser.y"
    { 
      (yyval.node) = (yyvsp[-1].node);
      printf(COLOR_BLUE "PARSER: Parenthesized expression parsed\n" COLOR_RESET); 
    }
#line 1889 "build/parser.tab.c"
    break;


#line 1893 "build/parser.tab.c"

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

#line 417 "src/parser/parser.y"


char** global_argv;

int main(int argc, char **argv) {
  global_argv = argv;
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }
      int parseResult = yyparse();
      return parseResult || backendErrorFlag;
}
