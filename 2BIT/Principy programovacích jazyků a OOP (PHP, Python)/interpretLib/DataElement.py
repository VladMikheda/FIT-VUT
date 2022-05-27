"""
 # Project:  Interpretator kódu v IPPcode22
 # File:     DataElement.py
 # Subject:  IPP 2022
 # @author:  Vladislav Mikheda  xmikhe00
 """


class DataElement:
    """
    The class is a simple form of data
    """
    data = None
    data_type = None

    def __init__(self, data, data_type):
        self.data = data
        self.data_type = data_type

    def get_data(self):
        return self.data

    def get_data_type(self):
        return self.data_type
