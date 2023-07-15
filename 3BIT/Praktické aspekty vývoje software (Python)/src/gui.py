#LIBRARIES
import sys
from pathlib import Path
from PyQt5.QtWidgets import QApplication, QGridLayout, QHBoxLayout, QWidget, QLabel, QLineEdit, QPushButton, QMainWindow, QVBoxLayout, QToolBar, QToolButton
from PyQt5.QtCore import Qt
import PyQt5.QtGui as QtGui
from logic_core import calculate
from handler import analyzer_for_gui
from constants import ERRORS, ERRORS_MESSAGES
#CONSTANTS

class CalcWindow(QWidget):

    def __init__(self):
        super().__init__()
        self.setWindowTitle("Calculator")
        self.setLayout(QVBoxLayout())
        self.layout().setContentsMargins(0,0,0,0)
        self.setFixedSize(450, 450)
        self.text = ''
        self.point = 0
        self.result = None
        self.createKeypad()
        self.show()

    #in total 24 buttons + display
    def createKeypad(self):
        #set layout of the keypad
        container = QWidget()
        container.setLayout(QGridLayout())
        container.layout().setAlignment(Qt.AlignmentFlag.AlignBaseline)
        container.layout().setSpacing(15)
        container.layout().setContentsMargins(20, 0, 20, 0)
        toolbar = QToolBar()
        helpContainer = QWidget()
        #display
        display = QLineEdit(objectName = 'display')
        display.setText(self.text) #just for implementing gui
        display.setReadOnly(True)
        display.setAlignment(Qt.AlignmentFlag.AlignRight)
        display.setContentsMargins(20, 50, 20, 0)
        #operation buttons
        resultButton = QPushButton('=')
        resultButton.clicked.connect(lambda: self.calc(self.text,display))
        resultButton.setShortcut("Return")

        clearButton = QPushButton('C')
        clearButton.clicked.connect(lambda: self.clearText(display))
        clearButton.setShortcut("Ctrl+Backspace")

        deleteButton = QPushButton('←', objectName = 'symbol')
        deleteButton.clicked.connect(lambda: self.deleteSymbol(display))
        deleteButton.setShortcut("Backspace")

        multiplyButton = QPushButton('×', objectName = 'symbol')
        multiplyButton.clicked.connect(lambda: self.appendSymbol('×', display))
        multiplyButton.setShortcut("x")

        divideButton = QPushButton('÷', objectName = 'symbol')
        divideButton.clicked.connect(lambda: self.appendSymbol('÷', display))
        divideButton.setShortcut("/")

        substractButton = QPushButton('-', objectName = 'symbol')
        substractButton.clicked.connect(lambda: self.appendSymbol('-', display))
        substractButton.setShortcut("-")
    
        addButton = QPushButton('+', objectName = 'symbol')
        addButton.clicked.connect(lambda: self.appendSymbol('+', display))
        addButton.setShortcut("+")

        logButton = QPushButton('log', objectName = 'upperBar')
        logButton.clicked.connect(lambda: self.appendSymbol('log', display))
        logButton.setShortcut("l")

        sqrtButton = QPushButton('√ ', objectName = 'upperBar')
        sqrtButton.clicked.connect(lambda: self.appendSymbol('root', display))
        sqrtButton.setShortcut("r")

        powerButton = QPushButton('xʸ', objectName = 'upperBar')
        powerButton.clicked.connect(lambda: self.appendSymbol('^', display))
        powerButton.setShortcut("^")
        
        factorialButton = QPushButton('n!')
        factorialButton.clicked.connect(lambda: self.appendSymbol('!', display))
        factorialButton.setShortcut("!")
        #float button
        floatButton = QPushButton('.', objectName = 'number')
        floatButton.clicked.connect(lambda: self.appendSymbol('.', display))
        floatButton.setShortcut(".")
        #comma button
        commaButton = QPushButton(',', objectName = 'number')
        commaButton.clicked.connect(lambda: self.appendSymbol(',', display))
        commaButton.setShortcut(",")
        #brackets buttons
        leftBracketButton = QPushButton('(')
        leftBracketButton.clicked.connect(lambda: self.appendSymbol('(', display))
        leftBracketButton.setShortcut("(")

        rightBracketButton = QPushButton(')')
        rightBracketButton.clicked.connect(lambda: self.appendSymbol(')', display))
        rightBracketButton.setShortcut(")")
        #number buttons
        button0 = QPushButton('0', objectName = 'number')
        button0.clicked.connect(lambda: self.appendSymbol('0', display))
        button0.setShortcut("0")

        button01 = QPushButton('1', objectName = 'number')
        button01.clicked.connect(lambda: self.appendSymbol('1', display))
        button01.setShortcut("1")

        button02 = QPushButton('2', objectName = 'number')
        button02.clicked.connect(lambda: self.appendSymbol('2', display))
        button02.setShortcut("2")

        button03 = QPushButton('3', objectName = 'number')
        button03.clicked.connect(lambda: self.appendSymbol('3', display))
        button03.setShortcut("3")

        button04 = QPushButton('4', objectName = 'number')
        button04.clicked.connect(lambda: self.appendSymbol('4', display))
        button04.setShortcut("4")

        button05 = QPushButton('5', objectName = 'number')
        button05.clicked.connect(lambda: self.appendSymbol('5', display))
        button05.setShortcut("5")

        button06 = QPushButton('6', objectName = 'number')
        button06.clicked.connect(lambda: self.appendSymbol('6', display))
        button06.setShortcut("6")

        button07 = QPushButton('7', objectName = 'number')
        button07.clicked.connect(lambda: self.appendSymbol('7', display))
        button07.setShortcut("7")

        button08 = QPushButton('8', objectName = 'number')
        button08.clicked.connect(lambda: self.appendSymbol('8', display))
        button08.setShortcut("8")

        button09 = QPushButton('9', objectName = 'number')
        button09.clicked.connect(lambda: self.appendSymbol('9', display))
        button09.setShortcut("9")

        backButton = QToolButton(objectName = 'back')
        backButton.setText("Calculator")
        backButton.setCheckable(True)
        toolbar.addWidget(backButton)
        backButton.clicked.connect(lambda: container.setVisible(True))
        backButton.clicked.connect(lambda: display.setVisible(True))
        backButton.clicked.connect(lambda: helpContainer.setVisible(False))

        helpButton = QToolButton(objectName = 'help')
        helpButton.setText("Help")
        helpButton.setCheckable(True)
        toolbar.addWidget(helpButton)
        helpButton.clicked.connect(lambda: container.setVisible(False))
        helpButton.clicked.connect(lambda: display.setVisible(False))
        helpButton.clicked.connect(lambda: helpContainer.setVisible(True))

        helpContainer.setLayout(QVBoxLayout())
        helpContainer.layout().setAlignment(Qt.AlignmentFlag.AlignCenter)
        helpContainer.layout().addWidget(QLabel("+ : add two numbers together: 2+3=5"))
        helpContainer.layout().addWidget(QLabel("- : subtract one number from another: 3-2=1"))
        helpContainer.layout().addWidget(QLabel("× : multiply two numbers: 2×3=6"))
        helpContainer.layout().addWidget(QLabel("÷ : divide one number by another: 4/2=2"))
        helpContainer.layout().addWidget(QLabel("log : logarithm of a number to the base: log(3,9)=2"))
        helpContainer.layout().addWidget(QLabel("! : factorial of non-negative integer: 4!=24"))
        helpContainer.layout().addWidget(QLabel("     n^n! == n^(n!)"))
        helpContainer.layout().addWidget(QLabel("√ : root of a number: root(3,27)=3"))
        helpContainer.layout().addWidget(QLabel("xʸ : power of a number: 2^3=8"))
        helpContainer.layout().addWidget(QLabel("      n^n^n == n^(n^n)"))
        helpContainer.layout().addWidget(QLabel("xʸ : power of a number: 2^3=8"))
        helpContainer.layout().addWidget(QLabel("operator precedence: ! > ^ > × = / > + = -"))

        #add all of the buttons to grid layout 
        #1st row
        container.layout().addWidget(powerButton, 2, 0)
        container.layout().addWidget(sqrtButton, 2, 1)
        container.layout().addWidget(logButton, 2, 2)
        container.layout().addWidget(deleteButton, 2, 3)
        container.layout().addWidget(clearButton, 2, 4)
        #2nd row
        container.layout().addWidget(button07, 3, 0)
        container.layout().addWidget(button08, 3, 1)
        container.layout().addWidget(button09, 3, 2)
        container.layout().addWidget(addButton, 3, 3)
        container.layout().addWidget(rightBracketButton, 3, 4)
        #3rd row
        container.layout().addWidget(button04, 4, 0)
        container.layout().addWidget(button05, 4, 1)
        container.layout().addWidget(button06, 4, 2)
        container.layout().addWidget(substractButton, 4, 3)
        container.layout().addWidget(leftBracketButton, 4, 4)
        #4th row   
        container.layout().addWidget(button01, 5, 0)
        container.layout().addWidget(button02, 5, 1)
        container.layout().addWidget(button03, 5, 2)
        container.layout().addWidget(divideButton, 5, 3)
        container.layout().addWidget(factorialButton, 5, 4)
        #5th row
        container.layout().addWidget(button0, 6, 0)
        container.layout().addWidget(commaButton, 6, 1)
        container.layout().addWidget(floatButton, 6, 2)
        container.layout().addWidget(multiplyButton, 6, 3)
        container.layout().addWidget(resultButton, 6, 4)
        

        #add to main window
        self.layout().addWidget(toolbar)
        self.layout().addWidget(display)
        self.layout().addWidget(container)
        self.layout().addWidget(helpContainer)
        helpContainer.setVisible(False)
        container.setVisible(True)
    
    def appendSymbol(self, symbol, display):
        if self.result is not None:
            self.check_new_input(symbol)

        check_symbol = symbol.replace("×", "*")
        check_symbol = check_symbol.replace("÷", "/")

        before_symbol = self.check_before_symbol()

        permit, self.point = analyzer_for_gui(before_symbol, check_symbol, self.point)

        if permit:
            self.text = self.text + str(symbol)
        display.setText(self.text)

    def calc(self, string, display):
        string = string.replace("×", "*")
        string = string.replace("÷", "/")

        self.result = calculate(string)

        if self.result[1] == ERRORS["NO_ERROR"]:
            display.setText(self.text + " = " + str(self.result[0]))
        else:
            display.setText(ERRORS_MESSAGES[self.result[1]])

    def clearText(self, display):
        self.text = ''
        self.point = 0
        self.result = None
        display.setText(self.text)
        
    def deleteSymbol(self, display):
        if self.result is None:
            if self.text[-1:] == ".":
                self.point = 0
                self.text = self.text[:-1]
            elif self.text[-3:] == "log":
                self.text = self.text[:-3]
            else:
                self.text = self.text[:-1]
            display.setText(self.text)
        else:
            self.result = None
            display.setText(self.text)

    def check_new_input(self, symbol):
        if symbol in ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]:
            self.result = None
            self.text = ""
        elif self.result[1] == ERRORS["NO_ERROR"]:
            self.text = str(self.result[0])
            self.result = None
        else:
            self.result = None

    def check_before_symbol(self):
        before_symbol = self.text[-1:]
        if before_symbol == "":
            before_symbol = None
        elif self.text[-3:] == "log":
            before_symbol = self.text[-3:]
        elif self.text[-4:] == "root":
            before_symbol = self.text[-4:]

        if before_symbol is not None:
            before_symbol = before_symbol.replace("×", "*")
            before_symbol = before_symbol.replace("÷", "/")

        return before_symbol

def run():
    app = QApplication([])
    window = CalcWindow()
    window.setStyleSheet(Path("calc.qss").read_text())
    sys.exit(app.exec())

if __name__ == "__main__":
    run()