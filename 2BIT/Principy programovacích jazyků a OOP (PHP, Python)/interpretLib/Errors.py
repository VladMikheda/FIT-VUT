"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     Errors.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """


import sys


class Errors:
    """
    Output errors message and exit program with error code
    Errors code represented as constants in const.py file
    """

    @staticmethod
    def error_print(error_code, line_number, text):
        """
        Errors output at interpreting
        :param error_code:
        :param line_number:
        :param text:
        :return:
        """
        print(f"ERROR: instruction number #{line_number}", file=sys.stderr)
        print(f"{text}", file=sys.stderr)
        exit(error_code)

    @staticmethod
    def error_print_xml(error_code, text):
        """
        Errors output in XML struct
        :param error_code:
        :param text:
        :return:
        """
        print(f"ERROR: {text}", file=sys.stderr)
        exit(error_code)
