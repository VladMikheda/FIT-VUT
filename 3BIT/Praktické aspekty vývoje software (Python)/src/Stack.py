"""
@author Vladislav Mikheda
@file Stack.py
@brief stack class file
"""


class Stack:
    """!The class implements the stack

    """

    def __init__(self):
        self.head_position = 0
        self.stack = []

    def push(self, value):
        """!The function pushes a value onto the top of the stack

        @param  value   item to be included in the text
        """
        self.stack.append(value)
        self.head_position += 1

    def top(self):
        """!Seeing what's at the top of the stack

        @return returns the top value
        """
        if self.empty():
            return None

        return self.stack[-1]

    def pop(self):
        """!Pop the top value off the stack

        @return top value
        """
        if self.empty():
            return None

        self.head_position -= 1
        return self.stack.pop()

    def empty(self):
        """!Determines if the stack is empty or not

        @return true if the stack is empty and false if the stack is not empty
        """
        if self.head_position == 0:
            return True
        return False

    def clear(self):
        """!Clears the stack

        """
        self.head_position = 0
        self.stack.clear()
        self.stack = []
