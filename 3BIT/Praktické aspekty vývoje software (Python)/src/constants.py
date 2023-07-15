"""
@author Vladislav Mikheda
@file constant.py
@brief The file contains constants that are used in the program
"""

ERRORS = {
    "NO_ERROR": 0,
    "LEXICAL_ERROR": 100,
    "SYNTAX_ERROR": 101,
    "NO_NUMBERS_ERROR": 102,
    "DIVISION_BY_ZERO_ERROR": 103,
    "DEGREE_NOT_INTEGER_ERROR": 104,
    "FACTORIAL_NOT_INTEGER_ERROR": 105,
    "NO_EXIST_OPERATION": 106,
    "NO_EXIST_RULES": 107,
    "LOG_ERROR": 108,
    "ROOT_DEGREE_NO_INT_ERROR": 109,
    "COMPLEX_NUMBERS_ERROR": 110,
    "BRACKET_ERROR": 111,
    "OVERFLOW_ERROR": 150,

}

ERRORS_MESSAGES = {
    100: "NOT CORRECT INPUT",
    101: "NOT CORRECT INPUT",
    102: "NOT CORRECT INPUT",
    103: "DIVISION BY ZERO",
    104: "DEGREE NOT INTEGER",
    105: "FACTORIAL NUMBER NOT INTEGER",
    106: "NOT CORRECT INPUT",
    107: "NOT CORRECT INPUT",
    108: "INVALID LOG VALUES USED",
    109: "ROOT DEGREE NOT INTEGER",
    110: "COMPLEX NUMBERS NOT SUPPORT",
    111: "NOT CORRECT INPUT",
    150: "OVERFLOW",
}


TOKENS_REGX = {
    "int": r"\d+",
    "float": r"\d+(?:\.\d+)",
    "log": r"log",
    "root": r"root",
    "pow": r"\^",
    "sum": r"\+",
    "sub": r"-",
    "mul": r"\*",
    "div": r"/",
    "fac": r"!",
    "l bracket": r"\(",
    "r bracket": r"\)",
    "comma": r",",
    "space": r" ",
    "point": r".",
}

TYPE_NAMES = [
    "sum",
    "sub",
    "mul",
    "div",
    "l bracket",
    "r bracket",
    "log",
    "root",
    "comma",
    "pow",
    "fac",
    "int",
    "float",
    "space",
    "point"
]

OPERATIONS_NAME = TYPE_NAMES[:4] + TYPE_NAMES[6:-3]

TOKENS_TYPE = {
    "sum": 0,
    "sub": 1,
    "mul": 2,
    "div": 3,
    "l bracket": 4,
    "r bracket": 5,
    "log": 6,
    "root": 7,
    "comma": 8,
    "pow": 9,
    "fac": 10,
    "int": 11,
    "float": 12,
    "space": 13,
    "none": 14,
    "point": 15
}

SYNTAX_RULES = {
    "SUM_SUB": [None, TOKENS_TYPE["int"], TOKENS_TYPE["float"], TOKENS_TYPE["r bracket"], TOKENS_TYPE["l bracket"], TOKENS_TYPE["fac"]],

    "MUL_DIV": [TOKENS_TYPE["int"], TOKENS_TYPE["float"], TOKENS_TYPE["r bracket"], TOKENS_TYPE["fac"]],

    "L BRACKET": [None, TOKENS_TYPE["sum"], TOKENS_TYPE["sub"], TOKENS_TYPE["mul"], TOKENS_TYPE["div"],  TOKENS_TYPE["log"],
                  TOKENS_TYPE["l bracket"], TOKENS_TYPE["root"], TOKENS_TYPE["pow"], TOKENS_TYPE["comma"]],

    "R BRACKET": [TOKENS_TYPE["int"], TOKENS_TYPE["float"], TOKENS_TYPE["r bracket"], TOKENS_TYPE["fac"]],

    "LOG_ROOT": [None, TOKENS_TYPE["sum"], TOKENS_TYPE["sub"], TOKENS_TYPE["mul"], TOKENS_TYPE["div"], TOKENS_TYPE["pow"],
                 TOKENS_TYPE["l bracket"], TOKENS_TYPE["comma"]],

    "COMMA": [TOKENS_TYPE["int"], TOKENS_TYPE["float"], TOKENS_TYPE["r bracket"], TOKENS_TYPE["fac"]],

    "POW_FAC": [TOKENS_TYPE["r bracket"], TOKENS_TYPE["fac"], TOKENS_TYPE["int"], TOKENS_TYPE["float"]],

    "INT_FLOAT":  [None, TOKENS_TYPE["sum"], TOKENS_TYPE["sub"], TOKENS_TYPE["mul"], TOKENS_TYPE["div"], TOKENS_TYPE["pow"],
                   TOKENS_TYPE["l bracket"], TOKENS_TYPE["comma"]],

    "LAST": [None, TOKENS_TYPE["int"], TOKENS_TYPE["float"], TOKENS_TYPE["r bracket"], TOKENS_TYPE["fac"]],

    "INT_FLOAT_GUI": [None, TOKENS_TYPE["sum"], TOKENS_TYPE["sub"], TOKENS_TYPE["mul"], TOKENS_TYPE["div"], TOKENS_TYPE["pow"],
                      TOKENS_TYPE["l bracket"], TOKENS_TYPE["comma"], TOKENS_TYPE["int"], TOKENS_TYPE["point"]],
}


GENERAL_REGX = r"[\w\.]+|\S"
BRACKET_START = None
FIRST_OPERATOR = 11
RULES_ERROR = -1
RULES_LEFT = 1
RULES_RIGHT = 2
RULES_COMPLIANCE = 3
# -1 error | 1 < | 2 >
RULES_TABLE = [
    #| + | - | * | / | ( | ) | l | r | , | ^ | ! | # |
    [  2,  2,  1,  1,  1,  2,  1,  1,  2,  1,  1, -1],  # +
    [  2,  2,  1,  1,  1,  2,  1,  1,  2,  1,  1, -1],  # -
    [  2,  2,  2,  2,  1,  2,  1,  1,  2,  1,  1, -1],  # *
    [  2,  2,  2,  2,  1,  2,  1,  1,  2,  1,  1, -1],  # /
    [  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, -1],  # (
    [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],  # )
    [ -1, -1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1],  # log
    [ -1, -1, -1, -1,  1, -1, -1, -1, -1, -1, -1, -1],  # root
    [  1,  1,  1,  1,  1,  3,  1,  1, -1,  1,  1, -1],  # ,
    [  2,  2,  2,  2,  1,  2,  1,  1,  2,  1,  1, -1],  # ^
    [  2,  2,  2,  2, -1,  2, -1, -1,  2,  2,  2, -1],  # !
    [  1,  1,  1,  1,  1, -1,  1,  1, -1,  1,  1, -1],  # #

]