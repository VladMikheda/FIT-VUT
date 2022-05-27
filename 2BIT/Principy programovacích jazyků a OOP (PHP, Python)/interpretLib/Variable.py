"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     Variable.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """

from interpretLib.DataElement import DataElement


class Variable(DataElement):
    """
    The class that represents the variable is inherited from the date element.
    """
    name = None
    frame = None

    def __init__(self, name, frame):
        super().__init__(None, None)
        self.frame = name
        self.name = frame

    def set_frame(self, frame):
        self.frame = frame

    def get_frame(self):
        return self.frame

    def set_data(self, content):
        self.data = content

    def get_name(self):
        return self.name

    def set_data_type(self, data_type):
        self.data_type = data_type

    def check_type(self, data_type):
        return False if self.data_type != data_type else True

    def check_empty(self):
        return True if self.data is None else False
