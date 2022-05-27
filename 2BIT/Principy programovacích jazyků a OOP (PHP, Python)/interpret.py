"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     interpret.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """

from interpretLib import Parse, Executor, Errors
import sys
from interpretLib.const import *


def help_program():
    """
    The function displays information about the launch of the program
    """
    print("correct run:")
    print("python3.8 interpret.py < --help> [--source=file] [--input=file]")
    sys.exit(0)


def arguments_processing(argv, arguments_list):
    """
    argument parser
    :param argv: input arguments
    :param arguments_list: pointer to array arguments
    :return:
    """
    arguments = argv[1:]
    for i in arguments:
        arg = i.split("=")
        if arg[0] == "--help":
            if len(arguments) > 1:
                # if run the program with 'help' argument, input arguments must not contain other arguments
                Errors.Errors.error_print_xml(ERROR_PARAMENT, "--help")
            help_program()
        elif arg[0] == "--source":
            arguments_list[SOURCES_FILE] = arg[1]
        elif arg[0] == "--input":
            arguments_list[INPUT_FILE] = arg[1]
        else:
            # help_program()
            Errors.Errors.error_print_xml(ERROR_PARAMENT, "parameter not exist")

    if arguments_list[INPUT_FILE] is None and arguments_list[SOURCES_FILE] is None:
        Errors.Errors.error_print_xml(ERROR_PARAMENT, "input file or source file must be given")


def main(argv):
    arguments = [None, None]
    arguments_processing(argv, arguments)
    # print(arguments[SOURS_FILE])
    # print(arguments[INPUT_FILE])

    executor = Executor.Executor(arguments[INPUT_FILE])
    parse = Parse.Parse(executor)
    parse.read_xml(arguments[SOURCES_FILE])
    parse.star_parse()


if __name__ == "__main__":
    main(sys.argv)
