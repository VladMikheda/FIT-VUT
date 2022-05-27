"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     Executor.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """

import re
import sys

from interpretLib.Variable import *
from interpretLib.const import *
from interpretLib.DataElement import *
from interpretLib import Errors


class Executor:
    """
    The Class is interpreting IPPcode22 language instructions
    """
    global_frame = []
    local_frame = []
    temporary_frame = []
    stack_frame = []
    local_frame_exist = False
    temporary_frame_exist = False
    data_stack = []
    data_stack_not_empty = False
    function_stack = []
    read_number = None
    read_arr = None

    def __init__(self, input_file):
        self.input_file = input_file

    @staticmethod
    def jump_to_label(arg, label_dict, main_program, main_list, instruction_number):
        label = label_dict.get(arg)
        if label is None:
            Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "label not exist")

        index = main_list.index(label)
        for i in range(index, len(main_list)):
            main_program.append(main_list[i])

    def interpret_jump_instruction(self, instruction, label_dict, main_program, main_list, xml_string):

        if instruction["instruction"] == "JUMP":
            arg = instruction["arg1"]
            self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])

        elif instruction["instruction"] in ["JUMPIFEQ", "JUMPIFNEQ"]:
            data_type_1 = instruction["arg2_type"]
            data_type_2 = instruction["arg3_type"]
            data_1 = instruction["arg2"]
            data_2 = instruction["arg3"]

            if data_type_1 == "var":
                var = self.return_variable(instruction["arg2"], instruction)
                self.check_var_exist(var, instruction)
                data_type_1 = var.get_data_type()
                data_1 = var.get_data()
            if data_type_2 == "var":
                var = self.return_variable(instruction["arg3"], instruction)
                self.check_var_exist(var, instruction)
                data_type_2 = var.get_data_type()
                data_2 = var.get_data()

            if data_type_1 is None or data_type_2 is None or data_1 is None or data_2 is None:
                Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variables is empty")

            if data_type_1 != data_type_2:
                if data_type_1 != "nil" and data_type_2 != "nil":
                    Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "type not equal")

            if data_type_1 == "int":
                data_1 = self.return_int(data_1, "int", instruction)
            if data_type_2 == "int":
                data_2 = self.return_int(data_2, "int", instruction)

            if instruction["instruction"] == "JUMPIFEQ":
                if data_type_1 == "nil" or data_type_2 == "nil":
                    if data_type_1 == data_type_2:
                        arg = instruction["arg1"]
                        self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])
                else:
                    if data_1 == data_2:
                        arg = instruction["arg1"]
                        self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])
            else:
                if data_type_1 == "nil" or data_type_2 == "nil":
                    if data_type_1 != data_type_2:
                        arg = instruction["arg1"]
                        self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])
                else:
                    if data_1 != data_2:
                        arg = instruction["arg1"]
                        self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])

        elif instruction["instruction"] == "CALL":
            arg = instruction["arg1"]
            self.function_stack.append(xml_string)
            self.jump_to_label(arg, label_dict, main_program, main_list, instruction["instruction_number"])

        elif instruction["instruction"] == "RETURN":
            if len(self.function_stack) != 0:
                new_xml_string = self.function_stack.pop()
                index = main_list.index(new_xml_string)
                index += 1
                if index >= len(main_list):
                    exit(0)
                for i in range(index, len(main_list)):
                    main_program.append(main_list[i])
            else:
                Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"],
                                          "instruction stack is empty")

    def interpret(self, instruction):
        """
        Root method for instruction, method choose by instruction name
        :param instruction: instruction's and arguments array
        """
        if instruction["instruction"] == "MOVE":
            self.instruction_move(instruction)
        elif instruction["instruction"] == "CREATEFRAME":
            self.instruction_createframe()
        elif instruction["instruction"] == "PUSHFRAME":
            self.instruction_pushframe(instruction)
        elif instruction["instruction"] == "POPFRAME":
            self.instruction_popframe(instruction)
        elif instruction["instruction"] == "DEFVAR":
            self.instruction_defvar(instruction)
        elif instruction["instruction"] == "PUSHS":
            self.instruction_push(instruction)
        elif instruction["instruction"] == "POPS":
            self.instruction_pops(instruction)
        elif instruction["instruction"] in ["ADD", "SUB", "MUL", "IDIV"]:
            self.instruction_math(instruction)
        elif instruction["instruction"] in ["LT", "EQ", "GT"]:
            self.instruction_comparative(instruction)
        elif instruction["instruction"] in ["AND", "OR"]:
            self.instruction_and_or(instruction)
        elif instruction["instruction"] == "NOT":
            self.instruction_not(instruction)
        elif instruction["instruction"] == "INT2CHAR":
            self.instruction_int2char(instruction)
        elif instruction["instruction"] == "STRI2INT":
            self.instruction_str2int(instruction)
        elif instruction["instruction"] == "READ":
            self.instruction_read(instruction)
        elif instruction["instruction"] == "WRITE":
            self.instruction_write(instruction)
        elif instruction["instruction"] == "CONCAT":
            self.instruction_concat(instruction)
        elif instruction["instruction"] == "STRLEN":
            self.instruction_strlen(instruction)
        elif instruction["instruction"] == "GETCHAR":
            self.instruction_getchar(instruction)
        elif instruction["instruction"] == "SETCHAR":
            self.instruction_setchar(instruction)
        elif instruction["instruction"] == "TYPE":
            self.instruction_type(instruction)
        elif instruction["instruction"] == "LABEL":
            return
        elif instruction["instruction"] == "EXIT":
            self.instruction_exit(instruction)
        elif instruction["instruction"] == "DPRINT":
            self.instruction_dprint(instruction)
        elif instruction["instruction"] == "BREAK":
            self.instruction_break()

    # below methods represent single instruction

    def instruction_move(self, instruction):
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)

        data = instruction["arg2"]
        data_type = instruction["arg2_type"]

        if data_type == "var":
            copy_var = self.return_variable(data, instruction)
            self.check_var_exist(copy_var, instruction)  # variables not exist
            var.set_data(copy_var.get_data())
            var.set_data_type(copy_var.get_data_type())
        else:
            var.set_data(data)
            var.set_data_type(data_type)

    def instruction_createframe(self):
        if self.temporary_frame_exist:
            self.temporary_frame = []
        else:
            self.temporary_frame_exist = True

    def instruction_pushframe(self, instruction):
        # if frame not exist, variable could not be created
        if not self.temporary_frame_exist:
            Errors.Errors.error_print(ERROR_FRAME_NOT_EXIST, instruction["instruction_number"],
                                      "temporary frame not exist")
        if self.local_frame_exist:
            self.stack_frame.append(self.local_frame)
        self.local_frame = self.temporary_frame
        self.temporary_frame = []
        self.local_frame_exist = True
        self.temporary_frame_exist = False

    def instruction_popframe(self, instruction):
        if self.local_frame_exist:
            self.temporary_frame = self.local_frame
            self.temporary_frame_exist = True
            if 0 != len(self.stack_frame):  # frame is not  empty
                self.local_frame = self.stack_frame.pop()
                if 0 == len(self.stack_frame):
                    self.stack_frame = []
            else:
                self.local_frame = []
                self.local_frame_exist = False
        else:
            Errors.Errors.error_print(ERROR_FRAME_NOT_EXIST, instruction["instruction_number"],
                                      "local frame not exist")

    def instruction_defvar(self, instruction):
        var_name = instruction["arg1"]
        frame__name = var_name.split("@")
        frame = frame__name[0]
        name = frame__name[1]

        var = self.return_variable(var_name, instruction)
        if var is not None:
            Errors.Errors.error_print(ERROR_SEMANTIC, instruction["instruction_number"],
                                      "variable redefinition")
        # determines in which frame to put the variable
        if frame == GF:
            self.global_frame.append(Variable(frame, name))
        elif frame == LF:
            self.local_frame.append(Variable(frame, name))
        elif frame == TF:
            self.temporary_frame.append(Variable(frame, name))

    def instruction_push(self, instruction):
        data = instruction["arg1"]
        data_type = instruction["arg1_type"]

        if data_type == "var":
            var = self.return_variable(data, instruction)
            self.check_var_exist(var, instruction)
            self.data_stack.append(var)
        else:
            self.data_stack.append(DataElement(data, data_type))
        self.data_stack_not_empty = True

    def instruction_pops(self, instruction):
        # if stack is empty
        if not self.data_stack_not_empty:
            Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"],
                                      "data stack is empty")

        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        data_in_stack = self.data_stack.pop()
        data = data_in_stack.get_data()
        data_type = data_in_stack.get_data_type()
        var.set_data(data)
        var.set_data_type(data_type)
        if len(self.data_stack) == 0:
            self.data_stack_not_empty = False
        # var1 = self.return_variable(instruction["arg1"])
        # print(f" var_ = {var.get_data()}, var1 = {var1.get_data()}")

    def instruction_math(self, instruction):
        """
        interpreting math instructions: ADD, SUB, MULL, DIV
        :param instruction:
        """
        inst = instruction["instruction"]
        calculation_var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(calculation_var, instruction)
        arg_2_type = instruction["arg2_type"]
        arg_2 = instruction["arg2"]
        arg_3_type = instruction["arg3_type"]
        arg_3 = instruction["arg3"]
        # return int type
        data_1 = self.return_int(arg_2, arg_2_type, instruction)
        data_2 = self.return_int(arg_3, arg_3_type, instruction)
        if inst == "ADD":
            calculation_var.set_data(str(data_1 + data_2))
            calculation_var.set_data_type("int")
            # print(calculation_var.get_data())
        elif inst == "SUB":
            calculation_var.set_data(str(data_1 - data_2))
            calculation_var.set_data_type("int")
            # print(calculation_var.get_data())
        elif inst == "MUL":
            calculation_var.set_data(str(data_1 * data_2))
            calculation_var.set_data_type("int")
            # print(calculation_var.get_data())
        elif inst == "IDIV":
            if data_2 == 0:
                Errors.Errors.error_print(ERROR_VALUE_NOT_CORRECT, instruction["instruction_number"],
                                          "division by zero")
            calculation_var.set_data(str(data_1 // data_2))
            calculation_var.set_data_type("int")
            # print(calculation_var.get_data())

    def instruction_comparative(self, instruction):
        """
        interpreting comparative instructions: GT, EQ, LT
        :param instruction:
        """
        inst = instruction["instruction"]
        data_type_1 = instruction["arg2_type"]
        data_type_2 = instruction["arg3_type"]
        data_1 = instruction["arg2"]
        data_2 = instruction["arg3"]
        var_writer = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var_writer, instruction)

        if data_type_1 == "var":
            var = self.return_variable(instruction["arg2"], instruction)
            self.check_var_exist(var, instruction)
            data_type_1 = var.get_data_type()
            data_1 = var.get_data()
        if data_type_2 == "var":
            var = self.return_variable(instruction["arg3"], instruction)
            self.check_var_exist(var, instruction)
            data_type_2 = var.get_data_type()
            data_2 = var.get_data()

        # if variable is not content data
        if data_type_1 is None or data_type_2 is None or data_1 is None or data_2 is None:
            Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variables is empty")

        # comparison data with null type, EQ instruction only
        if instruction["instruction"] == "EQ":
            if data_type_1 != data_type_2:
                if instruction["instruction"] == "EQ" and (data_type_1 != "nil" and data_type_2 != "nil"):
                    Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "type not equal")
        else:
            if data_type_1 != data_type_2:
                Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "type not equal")

        if data_type_1 == "int":
            data_1 = self.return_int(data_1, "int", instruction)
        if data_type_2 == "int":
            data_2 = self.return_int(data_2, "int", instruction)

        if inst == "LT":
            var_writer.set_data(str(data_1 < data_2).lower())
        elif inst == "EQ":
            if data_type_1 == "nil" or data_type_2 == "nil":
                var_writer.set_data(str(data_type_1 == data_type_2).lower())
            else:
                var_writer.set_data(str(data_1 == data_2).lower())
        elif inst == "GT":
            var_writer.set_data(str(data_1 > data_2).lower())

        var_writer.set_data_type("bool")
        # print(var.get_data())

    def instruction_and_or(self, instruction):
        inst = instruction["instruction"]
        data_1 = self.return_bool(instruction["arg2"], instruction["arg2_type"], instruction)
        data_2 = self.return_bool(instruction["arg3"], instruction["arg3_type"], instruction)
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)

        if inst == "AND":
            var.set_data(str(data_1 and data_2).lower())
        else:
            var.set_data(str(data_1 or data_2).lower())

        var.set_data_type("bool")
        # print(var.get_data())

    def instruction_not(self, instruction):
        data = self.return_bool(instruction["arg2"], instruction["arg2_type"], instruction)
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        var.set_data(str(not data).lower())
        var.set_data_type("bool")
        # print(var.get_data())

    def instruction_int2char(self, instruction):
        data = self.return_int(instruction["arg2"], instruction["arg2_type"], instruction)
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        try:
            var.set_data(chr(data))
            var.set_data_type("string")
        except ValueError:
            Errors.Errors.error_print(ERROR_ARRAY, instruction["instruction_number"],
                                      "invalid character ordinal value in Unicode")

    def instruction_str2int(self, instruction):
        data_1 = self.return_string(instruction["arg2"], instruction["arg2_type"], instruction)
        data_2 = self.return_int(instruction["arg3"], instruction["arg3_type"], instruction)
        len_data_1 = len(data_1)
        if data_2 >= len_data_1 or data_2 < 0:
            Errors.Errors.error_print(ERROR_ARRAY, instruction["instruction_number"],
                                      "index not correct")
        char = data_1[data_2]
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        var.set_data(str(ord(char)))
        var.set_data_type("int")

    def instruction_read(self, instruction):
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        data_type = instruction["arg2"]
        data = ""
        # check from where we will read the input
        if self.input_file is not None:
            if self.read_number is None:
                try:
                    file = open(self.input_file, "r")
                    self.read_arr = file.read().splitlines()
                    file.close()
                except OSError:
                    Errors.Errors.error_print(ERROR_OPEN, instruction["instruction_number"],
                                              "file not exist or not open")
                self.read_number = 0
            if self.read_number is not None:
                try:
                    data = self.read_arr[self.read_number]
                    self.read_number += 1
                except IndexError:
                    var.set_data("nil")
                    var.set_data_type("nil")
                    return
        else:
            try:
                data = input()
            except EOFError:
                var.set_data("nil")
                var.set_data_type("nil")
                return

        if data is None:
            data = ""
        data = self.escape_to_char(data)

        # save data for different types
        if data_type == "nil":
            var.set_data("nil")
            var.set_data_type("nil")
        elif data_type == "string":
            var.set_data(data)
            var.set_data_type("string")
        elif data_type == "bool":
            if data.lower() == "true":
                var.set_data("true")
            else:
                var.set_data("false")
            var.set_data_type("bool")
        elif data_type == "int" and len(data) != 0:
            if re.fullmatch(INT_DEC_R, data):
                data = int(data, 10)
            elif re.fullmatch(INT_HEX_R, data):
                data = int(data, 16)
            elif re.fullmatch(INT_OCT_R, data):
                data = int(data, 8)
            else:
                var.set_data("nil")
                var.set_data_type("nil")
                return
            var.set_data(str(data))
            var.set_data_type("int")
        else:
            var.set_data("nil")
            var.set_data_type("nil")

    def instruction_write(self, instruction):
        data = instruction["arg1"]
        data_type = instruction["arg1_type"]

        if data_type == "var":
            var = self.return_variable(data, instruction)
            self.check_var_exist(var, instruction)
            data = var.get_data()
            data_type = var.get_data_type()
            if data is None:
                Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variable is empty")
        # input for different type
        if data_type == "bool":
            data = "true" if data == "true" else "false"
        elif data_type == "nil":
            data = ''
        elif data_type == "int":
            data = self.return_int(data, "int", instruction)
        print(data, end='')

    def instruction_concat(self, instruction):
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        # return string or error
        data_1 = self.return_string(instruction["arg2"], instruction["arg2_type"], instruction)
        data_2 = self.return_string(instruction["arg3"], instruction["arg3_type"], instruction)

        var.set_data(data_1 + data_2)
        var.set_data_type("string")
        # print(data_1)
        # exit(0)

    def instruction_strlen(self, instruction):
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)

        data = self.return_string(instruction["arg2"], instruction["arg2_type"], instruction)
        var.set_data(str(len(data)))
        var.set_data_type("int")

    def instruction_getchar(self, instruction):
        data_1 = self.return_string(instruction["arg2"], instruction["arg2_type"], instruction)
        data_2 = self.return_int(instruction["arg3"], instruction["arg3_type"], instruction)

        if data_2 >= len(data_1) or data_2 < 0:
            Errors.Errors.error_print(ERROR_ARRAY, instruction["instruction_number"], "index not correct")

        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)
        data = data_1[data_2]
        var.set_data(data)
        var.set_data_type("string")

    def instruction_setchar(self, instruction):
        data_arr = self.return_string(instruction["arg1"], instruction["arg1_type"], instruction)
        var = self.return_variable(instruction["arg1"], instruction)
        data_1 = self.return_int(instruction["arg2"], instruction["arg2_type"], instruction)
        data_2 = self.return_string(instruction["arg3"], instruction["arg3_type"], instruction)
        len_arr = len(data_arr)

        # check len string and number
        if data_1 >= len_arr or data_1 < 0 or len(data_2) == 0:
            Errors.Errors.error_print(ERROR_ARRAY, instruction["instruction_number"], "index not correct")

        data_arr = data_arr[:data_1] + data_2[0] + data_arr[data_1 + 1:]
        var.set_data(data_arr)

    def instruction_type(self, instruction):
        var = self.return_variable(instruction["arg1"], instruction)
        self.check_var_exist(var, instruction)

        data_type = instruction["arg2_type"]

        if data_type == "var":
            var_2 = self.return_variable(instruction["arg2"], instruction)
            self.check_var_exist(var_2, instruction)
            data_type = var_2.get_data_type()

        if data_type is None:
            data_type = ""

        var.set_data(data_type)
        var.set_data_type("string")

    def instruction_exit(self, instruction):
        data = self.return_int(instruction["arg1"], instruction["arg1_type"], instruction)
        if data < 0 or data > 49:
            Errors.Errors.error_print(ERROR_VALUE_NOT_CORRECT, instruction["instruction_number"],
                                      "value not correct [0-49]")
        exit(data)

    def instruction_dprint(self, instruction):
        data = instruction["arg1"]
        data_type = instruction["arg1_type"]

        if data_type == "var":
            var = self.return_variable(data, instruction)
            data = var.get_data()
            data_type = var.get_data_type()
            if data is None:
                Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variables is empty")

        if data_type == "nil":
            print("", file=sys.stderr)
        else:
            print(data, file=sys.stderr)

    def instruction_break(self):
        # frames output to stderr
        print(f"Global Frame", file=sys.stderr)
        for var in self.global_frame:
            print(
                f"name:{var.get_name()}, frame:{var.get_frame()}, data:{var.get_data()}, type:{var.get_data_type()}",
                file=sys.stderr)
        print(f"Local Frame", file=sys.stderr)
        for var in self.local_frame:
            print(
                f"name:{var.get_name()}, frame:{var.get_frame()}, data:{var.get_data()}, type:{var.get_data_type()}",
                file=sys.stderr)
        print(f"Temporary Frame", file=sys.stderr)
        for var in self.temporary_frame:
            print(
                f"name:{var.get_name()}, frame:{var.get_frame()}, data:{var.get_data()}, type:{var.get_data_type()}",
                file=sys.stderr)

    # helping methods
    def return_string(self, data, data_type, instruction):
        # check data if string return else error
        if data_type == "var":
            var = self.return_variable(data, instruction)
            self.check_var_type(var, "string", instruction)
            data = var.get_data()
        elif data_type != "string":
            Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "expected type string")
        return data

    def return_bool(self, data, data_type, instruction):
        # check data if bool return else error
        if data_type == "var":
            var = self.return_variable(data, instruction)
            self.check_var_type(var, "bool", instruction)
            data = var.get_data()
        elif data_type != "bool":
            Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "expected type bool")
        return True if data == "true" else False

    def return_int(self, data, data_type, instruction):
        # check data if int return else error
        if data_type == 'var':
            var = self.return_variable(data, instruction)
            self.check_var_type(var, "int", instruction)
            data = var.get_data()
        elif data_type != "int":
            Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"], "expected type int")

        # checking the spelling of a number
        if re.fullmatch(INT_DEC_R, data):
            data = int(data, 10)
            # print(f"dec {data}")
        elif re.fullmatch(INT_HEX_R, data):
            data = int(data, 16)
            # print(f"hex {data}")
        elif re.fullmatch(INT_OCT_R, data):
            data = int(data, 8)
            # print(f"oct {data}")
        else:
            Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"],
                                      "invalid number notation type int")  # todo 32 ?
        return data

    def check_var_type(self, var, expect_type, instruction):
        self.check_var_exist(var, instruction)
        if var.check_empty():
            Errors.Errors.error_print(ERROR_VALUE_IS_EMPTY, instruction["instruction_number"], "variables is empty")
        if not var.check_type(expect_type):
            Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction["instruction_number"],
                                      f"expected type {expect_type}")

    @staticmethod
    def check_var_exist(var, instruction):
        if var is None:
            Errors.Errors.error_print(ERROR_VAR_NOT_EXIST, instruction["instruction_number"], "variables is not exist")

    def return_variable(self, name_var, instruction):
        """
        return variables from the frames stack
        :param name_var:
        :param instruction:
        :return:
        """
        frame_name = name_var.split("@")
        frame = frame_name[0]
        name = frame_name[1]
        var = None
        if frame == GF:
            var = [var_out for var_out in self.global_frame if var_out.get_name() == name]
        elif frame == LF:
            if self.local_frame_exist:
                var = [var_out for var_out in self.local_frame if var_out.get_name() == name]
            else:
                Errors.Errors.error_print(ERROR_FRAME_NOT_EXIST, instruction["instruction_number"],
                                          "local frame not exist")
        elif frame == TF:
            if self.temporary_frame_exist:
                var = [var_out for var_out in self.temporary_frame if var_out.get_name() == name]
            else:
                Errors.Errors.error_print(ERROR_FRAME_NOT_EXIST, instruction["instruction_number"],
                                          "temporary frame not exist")
        return var[0] if len(var) == 1 else None

    # todo kod refactor, add methods for return and check variables for int, string, bool ...

    @staticmethod
    def escape_to_char(data):
        """
        translates the escape sequence into characters
        :param data:
        :return:
        """
        count_sign = 4  # \abc
        start_escape = -1
        while True:
            start_escape = data.find("\\", start_escape + 1)
            stop_escape = start_escape + count_sign
            if start_escape == -1:
                return data
            try:
                data = data[:start_escape] + chr(int(data[start_escape + 1: stop_escape])) + data[stop_escape:]
            except ValueError:
                continue
