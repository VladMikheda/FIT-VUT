"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     const.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """

QUANTITY_ARGUMENT_0 = 0
QUANTITY_ARGUMENT_1 = 1
QUANTITY_ARGUMENT_2 = 2
QUANTITY_ARGUMENT_3 = 3
NUMBER_FIRST_ARG = 0
NUMBER_SECOND_ARG = 1
NUMBER_THIRD_ARG = 2
GF = "GF"
LF = "LF"
TF = "TF"
SOURCES_FILE = 0
INPUT_FILE = 1

#  instruction array and suitable argument types
INSTRUCTION = {
    "MOVE": [["var"], ["var", "nil", "int", "string", "bool"]],
    "CREATEFRAME": [],
    "PUSHFRAME": [],
    "POPFRAME": [],
    "DEFVAR": [["var"]],
    "CALL": [["label"]],
    "RETURN": [],
    "PUSHS": [["var", "nil", "int", "string", "bool"]],
    "POPS": [["var"]],
    "ADD": [["var"], ["var", "int"], ["var", "int"]],
    "SUB": [["var"], ["var", "int"], ["var", "int"]],
    "MUL": [["var"], ["var", "int"], ["var", "int"]],
    "IDIV": [["var"], ["var", "int"], ["var", "int"]],
    "LT": [["var"], ["var", "int", "string", "bool", "nil"], ["var", "int", "string", "bool", "nil"]],
    "EQ": [["var"], ["var", "int", "string", "bool", "nil"], ["var", "int", "string", "bool", "nil"]],
    "GT": [["var"], ["var", "int", "string", "bool", "nil"], ["var", "int", "string", "bool", "nil"]],
    "AND": [["var"], ["bool", "var"], ["bool", "var"]],
    "OR": [["var"], ["bool", "var"], ["bool", "var"]],
    "NOT": [["var"], ["bool", "var"]],
    "INT2CHAR": [["var"], ["var", "int"]],
    "STRI2INT": [["var"], ["var", "string"], ["var", "int"]],
    "READ": [["var"], ["type"]],
    "WRITE": [["var", "nil", "int", "string", "bool"]],
    "CONCAT": [["var"], ["var", "string"], ["var", "string"]],
    "STRLEN": [["var"], ["var", "string"]],
    "GETCHAR": [["var"], ["var", "string"], ["var", "int"]],
    "SETCHAR": [["var"], ["var", "int"], ["var", "string"]],
    "TYPE": [["var"], ["var", "nil", "int", "string", "bool"]],
    "LABEL": [["label"]],
    "JUMP": [["label"]],
    "JUMPIFEQ": [["label"], ["var", "int", "string", "bool", "nil"], ["var", "int", "string", "bool", "nil"]],
    "JUMPIFNEQ": [["label"], ["var", "int", "string", "bool", "nil"], ["var", "int", "string", "bool", "nil"]],
    "EXIT": [["var", "int"]],
    "DPRINT": [["var", "nil", "int", "string", "bool"]],
    "BREAK": [],
}

INSTRUCTION_COMP = ["LT", "GT", "EQ"]
INSTRUCTION_JUMP = ["JUMPIFEQ", "JUMPIFNEQ", "JUMP", "CALL", "RETURN"]

INT_OCT_R = "^0[0-7][0-7]*$"
INT_HEX_R = "^0[xX][0-9a-fA-F][0-9a-fA-F]*$"
INT_DEC_R = "^[0]+|[+-]?[1-9][0-9]*$"

# Errors
ERROR_PARAMENT = 10
ERROR_OPEN = 11
ERROR_OPEN_TO_WRITE = 12
ERROR_INTER = 99
ERROR_XML_NOT_CORRECT = 31
ERROR_XML_STRUCTION = 32
ERROR_SEMANTIC = 52
ERROR_OPERAND_TYPE = 53
ERROR_VAR_NOT_EXIST = 54
ERROR_FRAME_NOT_EXIST = 55
ERROR_VALUE_IS_EMPTY = 56
ERROR_VALUE_NOT_CORRECT = 57
ERROR_ARRAY = 58

# Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variables is empty")
# Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "type not equal")
# Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "expected string")
# My php code
#  "INT" => "/^int@([+-]?[0-9][0-9]*|0[xX][0-9a-fA-F][0-9a-fA-F]*|0[0-7][0-7]*)$/",
