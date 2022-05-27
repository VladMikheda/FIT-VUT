"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     Parse.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """

import xml.etree.ElementTree as ET
from interpretLib.Executor import *


class Parse:
    """
    The parser class accepts and parses a file or standard entry as an XML file.
    And divides into parts, separates instructions, arguments and their types,
    checks the semantics and sends to the interpreter
    """
    stop = False
    second = False
    jump = {}
    file_XML = sys.stdin
    sort_main_list = []
    root_list = None
    main_program = None

    pseudo_global_frame = []
    pseudo_local_frame = []
    pseudo_temporary_frame = []
    pseudo_stack_frame = []

    def __init__(self, executor):
        self.interpret = executor
        self.instruction = {"instruction": None,
                            "arg1": None,
                            "arg1_type": None,
                            "arg2": None,
                            "arg2_type": None,
                            "arg3": None,
                            "arg3_type": None,
                            "instruction_number": None,
                            }

    def read_xml(self, file_name):
        """
        Read the XML input and strip the root and headers. Sends for semantic control and sorts by order
        :param file_name:
        """
        document = None
        if file_name is not None:
            self.file_XML = file_name
        try:
            document = ET.parse(self.file_XML)
        except ET.ParseError:
            Errors.Errors.error_print_xml(ERROR_XML_NOT_CORRECT, "XML file is not correct")
        except FileExistsError:
            Errors.Errors.error_print_xml(ERROR_OPEN, "File not find")
        except FileNotFoundError:
            Errors.Errors.error_print_xml(ERROR_OPEN, "File not find")
        self.root_list = document.getroot()
        program_header = self.root_list.findall(".")
        self.root_list = self.root_list.findall("./*")
        # print(program_header[0].attrib)  # language IPPcode22 todo
        self.header_heck(program_header)
        self.sort()
        self.main_program = iter(self.sort_main_list.copy())

    @staticmethod
    def header_heck(header):
        """
        checks the header
        :param header:
        :return:
        """
        dict_headers = header[0].attrib
        language = False
        for key, value in dict_headers.items():
            if key == "language":
                language = True
                if value != "IPPcode22":
                    Errors.Errors.error_print_xml(ERROR_XML_STRUCTION, "interpreter only supports IPPcode22 language")
            elif key not in ["name", "description"]:
                Errors.Errors.error_print_xml(ERROR_XML_STRUCTION, "xml attribute not specified")
        if not language:
            Errors.Errors.error_print_xml(ERROR_XML_STRUCTION, "xml language attribute not specified")

    def star_parse(self):
        self.parse_xml()
        self.main_program = iter(self.sort_main_list.copy())
        while not self.stop:
            self.stop = True
            self.parse_xml()

    def write_label(self, element):
        """
        checks labels
        :param element:
        """
        if element.attrib.get("opcode") == "LABEL":
            if QUANTITY_ARGUMENT_1 != len(element):  # comparison number of arguments
                instruction_number = element.attrib.get("order")
                Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "amount elements is not correct")
            argument_1 = element[NUMBER_FIRST_ARG]
            if argument_1.attrib.get("type") != "label":
                instruction_number = element.attrib.get("order")
                Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "elements type is not correct")
            if self.jump.get(argument_1.text) is not None:  # label repeat
                instruction_number = element.attrib.get("order")
                Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "label name repeats")
            self.jump.update({argument_1.text: element})

    def sort(self):
        """
        sorts the xml file
        """
        sort_dict = {}
        for elem in self.root_list:
            if elem.tag == "instruction":  # check xml tags
                self.write_label(elem)
                try:
                    # checking and rearranging instruction arguments
                    arg1 = arg2 = arg3 = None
                    for sub_elem in elem:
                        if sub_elem.tag == "arg1" and arg1 is None:
                            arg1 = sub_elem
                        elif sub_elem.tag == "arg2" and arg2 is None:
                            arg2 = sub_elem
                        elif sub_elem.tag == "arg3" and arg3 is None:
                            arg3 = sub_elem
                        else:
                            Errors.Errors.error_print(ERROR_XML_STRUCTION, elem.attrib.get("order"), "tag not correct")
                    if arg3 is not None and (arg2 is None or arg1 is None):
                        Errors.Errors.error_print(ERROR_XML_STRUCTION, elem.attrib.get("order"), "tag not correct")
                    if arg2 is not None and arg1 is None:
                        Errors.Errors.error_print(ERROR_XML_STRUCTION, elem.attrib.get("order"), "tag not correct")
                    if arg1 is not None:
                        elem[0] = arg1
                    if arg2 is not None:
                        elem[1] = arg2
                    if arg3 is not None:
                        elem[2] = arg3

                    # if instruction's order repeat in xml file -> error
                    num = elem.attrib["order"]
                    try:
                        if num is None or int(num) <= 0:
                            Errors.Errors.error_print(ERROR_XML_STRUCTION, "-", "order number not correct")
                    except:
                        Errors.Errors.error_print(ERROR_XML_STRUCTION, "-", "order number not correct")
                    exist = sort_dict.get(num)
                    if exist is not None:
                        instruction_number = elem.attrib.get("order")
                        Errors.Errors.error_print(ERROR_XML_STRUCTION, instruction_number, "order number repeats")
                    sort_dict.update({num: elem})
                except KeyError:
                    instruction_number = elem.attrib.get("order")
                    Errors.Errors.error_print(ERROR_XML_STRUCTION, instruction_number, "order not correct")
            else:
                instruction_number = elem.attrib.get("order")
                Errors.Errors.error_print(ERROR_XML_STRUCTION, instruction_number, "expected instruction")
        numbers_list = []
        try:
            numbers_list = [*sort_dict]
            numbers_list.sort(key=int)
        except ValueError:
            Errors.Errors.error_print(ERROR_XML_STRUCTION, "-", "order number not correct")
        for num in numbers_list:
            self.sort_main_list.append(sort_dict.get(num))

    def parse_xml(self):
        for xml_string in self.main_program:
            element_number = iter([0, 1, 2])
            # get instruction array
            instruction_opcode = xml_string.attrib.get("opcode")
            if instruction_opcode is None:
                Errors.Errors.error_print(ERROR_XML_STRUCTION, xml_string.attrib.get("order"), "opcode not correct")
            arguments_list = INSTRUCTION.get(instruction_opcode)
            # print(xml_string.attrib["opcode"])
            if arguments_list is None:
                # ERROR_SEMANTIC
                instruction_number = xml_string.attrib.get("order")
                Errors.Errors.error_print(ERROR_XML_STRUCTION, instruction_number, "instruction not exist")

            if not self.second:
                # only check the first pass
                if len(arguments_list) != len(xml_string):
                    # ERROR_SEMANTIC
                    instruction_number = xml_string.attrib.get("order")
                    Errors.Errors.error_print(ERROR_XML_STRUCTION, instruction_number, "amount elements is not correct")
                for arg in arguments_list:
                    argument_in_string = xml_string[next(element_number)]
                    if argument_in_string.attrib.get("type") not in arg:
                        instruction_number = xml_string.attrib.get("order")
                        Errors.Errors.error_print(ERROR_OPERAND_TYPE, instruction_number,
                                                  "type argument in xml not correct")
                    if xml_string.attrib["opcode"] == "DEFVAR":
                        var = argument_in_string.text
                        self.pseudo_var(var, xml_string.attrib.get("order"))
                if xml_string.attrib["opcode"] == "PUSHFRAME":
                    self.pseudo_push()
                elif xml_string.attrib["opcode"] == "POPFRAME":
                    self.pseudo_pop()
                elif xml_string.attrib["opcode"] == "CREATEFRAME":
                    self.pseudo_create_frame()
                elif xml_string.attrib["opcode"] in ["CALL", "JUMP", "JUMPIFEQ", "JUMPIFNEQ"]:
                    name_label = xml_string[0].text
                    if self.jump.get(name_label) is None:
                        instruction_number = xml_string.attrib.get("order")
                        Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "label not exist")
            else:
                # second pass add instruction and arguments to array and send to interpret
                if xml_string.attrib["opcode"] in INSTRUCTION_JUMP:
                    # if it is jump instruction, method  call only for jump instructions
                    self.filling_instruction(xml_string, len(arguments_list))
                    new_program = []
                    self.interpret.interpret_jump_instruction(self.instruction, self.jump, new_program,
                                                              self.sort_main_list, xml_string)
                    if len(new_program) != 0:
                        self.main_program = iter(new_program.copy())
                        self.stop = False
                        break
                else:
                    self.filling_instruction(xml_string, len(arguments_list))
                    # print(self.instruction)
                    self.interpret.interpret(self.instruction)

        self.second = True

    def filling_instruction(self, xml_string, count_element=0):
        """
        array filling for instruction and arguments and arguments type
        :param xml_string:
        :param count_element:
        :return:
        """
        arg_1 = arg1_type = arg_2 = arg2_type = arg_3 = arg3_type = None

        instruction = xml_string.attrib.get("opcode")

        if count_element != QUANTITY_ARGUMENT_0:
            if xml_string[NUMBER_FIRST_ARG].attrib["type"] == "string":
                arg_str = xml_string[NUMBER_FIRST_ARG].text
                if arg_str is None:
                    arg_str = ""
                arg_1 = self.interpret.escape_to_char(arg_str)
            else:
                arg_1 = xml_string[NUMBER_FIRST_ARG].text
            arg1_type = xml_string[NUMBER_FIRST_ARG].attrib["type"]
        if count_element >= QUANTITY_ARGUMENT_2:
            if xml_string[NUMBER_SECOND_ARG].attrib["type"] == "string":
                arg_str = xml_string[NUMBER_SECOND_ARG].text
                if arg_str is None:
                    arg_str = ""
                arg_2 = self.interpret.escape_to_char(arg_str)
            else:
                arg_2 = xml_string[NUMBER_SECOND_ARG].text
            arg2_type = xml_string[NUMBER_SECOND_ARG].attrib["type"]
        if count_element == QUANTITY_ARGUMENT_3:
            if xml_string[NUMBER_THIRD_ARG].attrib["type"] == "string":
                arg_str = xml_string[NUMBER_THIRD_ARG].text
                if arg_str is None:
                    arg_str = ""
                arg_3 = self.interpret.escape_to_char(arg_str)
            else:
                arg_3 = xml_string[NUMBER_THIRD_ARG].text
            arg3_type = xml_string[NUMBER_THIRD_ARG].attrib["type"]

        self.instruction["instruction"] = instruction
        self.instruction["arg1"] = arg_1
        self.instruction["arg1_type"] = arg1_type
        self.instruction["arg2"] = arg_2
        self.instruction["arg2_type"] = arg2_type
        self.instruction["arg3"] = arg_3
        self.instruction["arg3_type"] = arg3_type
        self.instruction["instruction_number"] = xml_string.attrib.get("order")

    def pseudo_var(self, name_var, instruction_number):
        """
        check variables redefinitions
        :param name_var:
        :param instruction_number:
        """
        frame_name = name_var.split("@")
        frame = frame_name[0]
        var = ""
        if frame == GF:
            var = [var_out for var_out in self.pseudo_global_frame if var_out == name_var]
            self.pseudo_global_frame.append(name_var)
        elif frame == LF:
            var = [var_out for var_out in self.pseudo_local_frame if var_out == name_var]
            self.pseudo_local_frame.append(name_var)
        elif frame == TF:
            var = [var_out for var_out in self.pseudo_temporary_frame if var_out == name_var]
            self.pseudo_temporary_frame.append(name_var)

        if len(var) != 0:
            Errors.Errors.error_print(ERROR_SEMANTIC, instruction_number, "variable redefinition")

    def pseudo_push(self):
        self.pseudo_stack_frame.append(self.pseudo_local_frame)
        self.pseudo_local_frame = self.pseudo_temporary_frame
        self.pseudo_temporary_frame = []

    def pseudo_pop(self):
        self.pseudo_temporary_frame = self.pseudo_local_frame
        if len(self.pseudo_stack_frame) != 0:
            self.pseudo_local_frame = self.pseudo_stack_frame.pop()

    def pseudo_create_frame(self):
        self.pseudo_temporary_frame = []
