"""
@author Vladislav Mikheda
@file handler.py
@brief The file is responsible for checking the data at the entrance to the program
"""

# Imports
from constants import TYPE_NAMES, TOKENS_TYPE, TOKENS_REGX, GENERAL_REGX, ERRORS, SYNTAX_RULES
import re


# Function
def split_string(input_string):
    """!The function splits the string into separate tokens

    @param  input_string    the string passed to the input of the program
    @return set of tokens
    """
    tokens = re.findall(GENERAL_REGX, input_string)
    return tokens


def analyzer(input_string):
    """

    @param  input_string    the string passed to the input of the program
    @return a generator that returns a token its type and error
    """
    tokens = split_string(input_string)
    before = None
    error = ERRORS["NO_ERROR"]

    if len(tokens) != 0:
        for type_name in TYPE_NAMES:
            if re.fullmatch(TOKENS_REGX[type_name], tokens[-1]):
                token_type = TOKENS_TYPE[type_name]
                if token_type not in SYNTAX_RULES["LAST"]:
                    error = ERRORS["SYNTAX_ERROR"]
                break

    for token in tokens:
        token_type = TOKENS_TYPE["none"]

        for type_name in TYPE_NAMES:
            if re.fullmatch(TOKENS_REGX[type_name], token):
                token_type = TOKENS_TYPE[type_name]
                break

        if token_type == TOKENS_TYPE["space"]:
            continue

        elif token_type in [TOKENS_TYPE["none"], TOKENS_TYPE["point"]]:
            error = ERRORS["LEXICAL_ERROR"]

        else:
            if not rule_check(before, token_type, gui=False):
                error = ERRORS["SYNTAX_ERROR"]

        before = token_type

        yield token, token_type, error


def rule_check(before_type, now_type, gui=False):
    """!The function checks the sequence of tokens using rules

    @param  before_type previous token type
    @param  now_type    the type of token that is currently
    @param  gui         the answer is for whether the check occurs for gui or for console input
    @return returns a boolean value whether the given token can go after the previous one
    """
    if now_type in [TOKENS_TYPE["sum"], TOKENS_TYPE["sub"]]:
        if before_type not in SYNTAX_RULES["SUM_SUB"]:
            return False

    elif now_type in [TOKENS_TYPE["mul"], TOKENS_TYPE["div"]]:
        if before_type not in SYNTAX_RULES["MUL_DIV"]:
            return False

    elif now_type == TOKENS_TYPE["l bracket"]:
        if before_type not in SYNTAX_RULES["L BRACKET"]:
            return False

    elif now_type == TOKENS_TYPE["r bracket"]:
        if before_type not in SYNTAX_RULES["R BRACKET"]:
            return False

    elif now_type in [TOKENS_TYPE["log"], TOKENS_TYPE["root"]]:
        if before_type not in SYNTAX_RULES["LOG_ROOT"]:
            return False

    elif now_type == TOKENS_TYPE["comma"]:
        if before_type not in SYNTAX_RULES["COMMA"]:
            return False

    elif now_type in [TOKENS_TYPE["pow"], TOKENS_TYPE["fac"]]:
        if before_type not in SYNTAX_RULES["POW_FAC"]:
            return False

    elif not gui and now_type in [TOKENS_TYPE["float"], TOKENS_TYPE["int"]]:
        if before_type not in SYNTAX_RULES["INT_FLOAT"]:
            return False

    return True


def analyzer_for_gui(before_symbol, symbol, point):
    """!The function produces token type definitions as well as basic checks

    @param  before_symbol   previous symbol type
    @param  symbol          the symbol of token that is currently
    @param  point           whether a dot was used or not
    @return a boolean value whether the given token can go after the previous one and point information
    """
    symbol_type = TOKENS_TYPE["none"]
    before_symbol_type = None

    for type_name in TYPE_NAMES:
        if re.fullmatch(TOKENS_REGX[type_name], symbol):
            symbol_type = TOKENS_TYPE[type_name]
            break

    if before_symbol is not None:
        for type_name in TYPE_NAMES:
            if re.fullmatch(TOKENS_REGX[type_name], before_symbol):
                before_symbol_type = TOKENS_TYPE[type_name]
                break

    if before_symbol is TOKENS_TYPE["int"] and symbol is TOKENS_TYPE["int"]:
        return True, point

    elif symbol_type is TOKENS_TYPE["point"]:
        if point != 0 or before_symbol_type is not TOKENS_TYPE["int"]:
            return False, point
        point = 1

    elif symbol_type in [TOKENS_TYPE["float"], TOKENS_TYPE["int"]]:
        if before_symbol_type not in SYNTAX_RULES["INT_FLOAT_GUI"]:
            return False, point

    else:
        if not rule_check(before_symbol_type, symbol_type, gui=True):
            return False, point
        point = 0

    return True, point
