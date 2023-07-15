"""
@author Vladislav Mikheda
@file   logic_core.py
@brief  The file is responsible for the logic in the calculator

The file contains a set of functions for the correct and
consistent execution of mathematical operations
"""
# Imports
from Stack import Stack
from handler import analyzer
from constants import TOKENS_TYPE, RULES_TABLE, RULES_ERROR, RULES_RIGHT, RULES_LEFT, RULES_COMPLIANCE, \
    FIRST_OPERATOR, OPERATIONS_NAME, ERRORS, BRACKET_START
from mathlib import sum, sub, mul, div, pow, fac, log, root


# Functions
def type_changes(number):
    """!This function changes the type of the number.

    It determines whether the number is an integer,
    it can be an integer but of a different type,
    or it can be a floating point number.

    @param  number  a number of which type you need to determine
    @return number with changed type and number type
    """
    if float(number).is_integer():
        return int(number), TOKENS_TYPE["int"]

    return number, TOKENS_TYPE["float"]


def prepare_result(result, numbers_stack):
    """!Checks the type of number and pushes it onto the stackю

    @param  result          the result of a mathematical operation
    @param  numbers_stack   stack for storing numbers
    """
    result, number_type = type_changes(result)  # find out the type of result obtained
    numbers_stack.push([result, number_type])


def sum_operation(numbers_stack):
    """!The function prepares parameters for addition.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    value_second = numbers_stack.pop()
    value_first = numbers_stack.pop()

    # if the plus is used as a single operator (+n)
    if value_first is None and value_second:
        numbers_stack.push(value_second)

    # not a single number was found to perform the operation (+)
    elif value_first is None and value_second is None:
        return ERRORS["NO_NUMBERS"]

    else:
        try:
            result = sum(value_first[0], value_second[0])  # perform an addition operation
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def sub_operation(numbers_stack):
    """!The function prepares parameters for subtracting.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    value_second = numbers_stack.pop()
    value_first = numbers_stack.pop()

    # if the minus is used as a single operator (-n)
    if value_first is None and value_second:
        result = sub(0, value_second[0])
        numbers_stack.push([result, value_second[1]])

    # not a single number was found to perform the operation (-)
    elif value_first is None and value_second is None:
        return ERRORS["NO_NUMBERS"]

    else:
        try:
            result = sub(value_first[0], value_second[0])  # perform a subtraction operation
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def mul_operation(numbers_stack):
    """!The function prepares parameters for multiplication.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """
    value_second = numbers_stack.pop()
    value_first = numbers_stack.pop()

    # not a single number was found to perform the operation (*)
    if value_first is None or value_second is None:
        return ERRORS["NO_NUMBERS"]

    else:
        try:
            result = mul(value_first[0], value_second[0])  # perform a multiplication operation
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def div_operation(numbers_stack):
    """!The function prepares parameters for division.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    value_second = numbers_stack.pop()
    value_first = numbers_stack.pop()

    # not a single number was found to perform the operation (/)
    if value_first is None or value_second is None:
        return ERRORS["NO_NUMBERS"]

    # let's take care division by zero (n/0)
    if value_second[0] == 0:
        return ERRORS["DIVISION_BY_ZERO_ERROR"]

    else:
        try:
            result = div(value_first[0], value_second[0])  # perform a division operation
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def pow_operation(numbers_stack):
    """!The function prepares the parameters for the exponentiation operation.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    value_second = numbers_stack.pop()
    value_first = numbers_stack.pop()

    # not a single number was found to perform the operation (^)
    if value_first is None or value_second is None:
        return ERRORS["NO_NUMBERS"]

    # the degree must be an integer (n^int)
    if value_second[1] == TOKENS_TYPE["float"]:
        return ERRORS["DEGREE_NOT_INTEGER_ERROR"]

    else:
        try:
            result = pow(value_first[0], value_second[0])  # perform an exponentiation operation
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def fac_operation(numbers_stack):
    """!The function prepares parameters for the factorial operation.

    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    value = numbers_stack.pop()

    # number was not found to perform the operation (!)
    if value is None:
        return ERRORS["NO_NUMBERS"]

    if value[1] == TOKENS_TYPE["float"]:
        return ERRORS["FACTORIAL_NOT_INTEGER_ERROR"]

    else:
        try:
            result = fac(value[0])
            prepare_result(result, numbers_stack)
        except OverflowError:
            return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def carry_top_operation(operations_stack, numbers_stack):
    """!This function defines and performs the top operation on stacks.

    @param  operations_stack    stack for storing operations
    @param  numbers_stack       stack for storing numbers
    @return the error number
    """

    operation = operations_stack.pop()
    # error = ERRORS["NO_ERROR"]

    if operation == TOKENS_TYPE["sum"]:
        error = sum_operation(numbers_stack)

    elif operation == TOKENS_TYPE["sub"]:
        error = sub_operation(numbers_stack)

    elif operation == TOKENS_TYPE["mul"]:
        error = mul_operation(numbers_stack)

    elif operation == TOKENS_TYPE["div"]:
        error = div_operation(numbers_stack)

    elif operation == TOKENS_TYPE["pow"]:
        error = pow_operation(numbers_stack)

    elif operation == TOKENS_TYPE["fac"]:
        error = fac_operation(numbers_stack)

    else:
        error = ERRORS["NO_EXIST_OPERATION"]

    return error


def log_operation(value_first, value_second, numbers_stack):
    """!The function prepares parameters for the logarithm operation.

    @param  value_first     first value in expression
    @param  value_second    second value in expression
    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    if value_second[0] < 1:
        return ERRORS["LOG_ERROR"]

    if value_first[0] <= 1:
        return ERRORS["LOG_ERROR"]

    try:
        result = log(value_second[0], value_first[0])
        prepare_result(result, numbers_stack)
    except OverflowError:
        return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def root_operation(value_first, value_second, numbers_stack):
    """!The function prepares parameters for the root operation.

    @param  value_first     first value in expression
    @param  value_second    second value in expression
    @param  numbers_stack   stack for storing numbers
    @return the error number
    """

    if value_first[1] == TOKENS_TYPE["float"]:
        return ERRORS["ROOT_DEGREE_NO_INT_ERROR"]

    if value_second[0] < 0:
        return ERRORS["COMPLEX_NUMBERS_ERROR"]

    try:
        result = root(value_second[0], value_first[0])
        prepare_result(result, numbers_stack)
    except OverflowError:
        return ERRORS["OVERFLOW_ERROR"]

    return ERRORS["NO_ERROR"]


def compliance_operation(operations_stack, numbers_stack):
    """!The function conducts the preparation and execution of operations with brackets.

    @param  operations_stack    stack for storing operations
    @param  numbers_stack       stack for storing numbers
    @return the error number
    """
    error = ERRORS["NO_ERROR"]
    previous_on_stack = operations_stack.pop()

    if previous_on_stack is None:
        return ERRORS["SYNTAX_ERROR"]

    # when the expression is in bracket, just remove the bracket
    if previous_on_stack is TOKENS_TYPE["l bracket"]:
        value = numbers_stack.pop()
        if value is None:
            return ERRORS["NO_NUMBERS"]
        if numbers_stack.top() is None and not numbers_stack.empty():
            numbers_stack.pop()
        numbers_stack.push(value)
    # if there was a comma on top of the stacks,
    # this means that the expression refers either to the log or to the root
    elif previous_on_stack is TOKENS_TYPE["comma"]:
        left_bracket = operations_stack.pop()

        if left_bracket is not TOKENS_TYPE["l bracket"]:
            return ERRORS["SYNTAX_ERROR"]

        main_operation = operations_stack.pop()
        value_second = numbers_stack.pop()
        value_first = numbers_stack.pop()

        if numbers_stack.top() is None and not numbers_stack.empty():
            numbers_stack.pop()

        if value_first is None or value_second is None:
            return ERRORS["NO_NUMBERS"]

        if main_operation is TOKENS_TYPE["log"]:
            error = log_operation(value_first, value_second, numbers_stack)

        elif main_operation is TOKENS_TYPE["root"]:
            error = root_operation(value_first, value_second, numbers_stack)

        else:
            return ERRORS["NO_EXIST_OPERATION"]  # another operation

    else:
        return ERRORS["SYNTAX_ERROR"]  # argument not exist

    return error


def check_rules(operations_stack, numbers_stack, operation):
    """!The function defines what to do with the new operation.

    The function looks at the top operation on the stack and the last operation that was read
    and determines what to do with the operation that was read.
    Execute an already existing operation on the stack, or push that operation onto the stack.

    @param  operations_stack    stack for storing operations
    @param  numbers_stack       stack for storing numbers
    @param  operation           last read operation
    @return the error number
    """
    while True:

        top_operation = operations_stack.top()

        # if the stack is empty, then this will be the first operation
        if operations_stack.empty():
            top_operation = FIRST_OPERATOR

        # determine what needs to be done
        action = RULES_TABLE[top_operation][operation]

        if action == RULES_ERROR:
            return ERRORS["SYNTAX_ERROR"]

        elif action == RULES_RIGHT:
            error = carry_top_operation(operations_stack, numbers_stack)
            if error != ERRORS["NO_ERROR"]:
                return error
            continue

        elif action == RULES_LEFT:
            operations_stack.push(operation)
            return ERRORS["NO_ERROR"]

        elif action == RULES_COMPLIANCE:
            error = compliance_operation(operations_stack, numbers_stack)
            if error != ERRORS["NO_ERROR"]:
                return error
            return ERRORS["NO_ERROR"]

        else:
            return ERRORS["NO_EXIST_RULES"]


# @param input_string string entered by the user
# @return result and the error number
def calculate(input_string):
    """!The main loop in which tokens are gradually processed

    @param  input_string    string entered by the user
    @return result and the error number
    """
    left_bracket_count = 0
    right_bracket_count = 0

    operations_stack = Stack()
    numbers_stack = Stack()

    token_generator = analyzer(input_string)

    # gradually take tokens
    for token, token_type, error in token_generator:

        # if error in analyzer
        if error != ERRORS["NO_ERROR"]:
            # print("error")
            return None, error

        if token_type == TOKENS_TYPE["float"]:
            try:
                numbers_stack.push([float(token), token_type])
            except OverflowError:
                return None, ERRORS["OVERFLOW_ERROR"]

        elif token_type == TOKENS_TYPE["int"]:
            try:
                numbers_stack.push([int(float(token)), token_type])
            except OverflowError:
                return None, ERRORS["OVERFLOW_ERROR"]

        elif token_type == TOKENS_TYPE["l bracket"]:
            left_bracket_count += 1
            error = check_rules(operations_stack, numbers_stack, TOKENS_TYPE["l bracket"])
            numbers_stack.push(BRACKET_START)
            if error != ERRORS["NO_ERROR"]:
                return None, error

        elif token_type == TOKENS_TYPE["r bracket"]:
            right_bracket_count += 1
            error = check_rules(operations_stack, numbers_stack, TOKENS_TYPE["r bracket"])
            if error != ERRORS["NO_ERROR"]:
                return None, error

        else:
            for operation_name in OPERATIONS_NAME:
                if token_type == TOKENS_TYPE[operation_name]:
                    error = check_rules(operations_stack, numbers_stack, TOKENS_TYPE[operation_name])
                    if error != ERRORS["NO_ERROR"]:
                        return None, error
                    break

    if left_bracket_count != right_bracket_count:
        return None, ERRORS["BRACKET_ERROR"]

    # act after all tokens have been distributed
    while True:
        if not operations_stack.empty():
            error = carry_top_operation(operations_stack, numbers_stack)
            if error != ERRORS["NO_ERROR"]:
                return None, error
        else:
            break

    # calculation result
    result = numbers_stack.pop()

    if not numbers_stack.empty():
        return None, ERRORS["SYNTAX_ERROR"]

    if result[1] == TOKENS_TYPE["float"]:
        result[0] = float(format(result[0], ".6f"))

    if result is not None:
        result = result[0]
    else:
        result = 0

    return result, ERRORS["NO_ERROR"]
