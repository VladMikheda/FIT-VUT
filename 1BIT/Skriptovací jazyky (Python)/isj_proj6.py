#!/usr/bin/env python3


def test():
    assert str(Polynomial(0,1,0,-1,4,-2,0,1,3,0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial([-5,1,0,-1,4,-2,0,1,3,0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
    assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3= -1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial(x2=0)) == "0"
    assert str(Polynomial(x0=0)) == "0"
    assert Polynomial(x0=2, x1=0, x3=0, x2=3) == Polynomial(2,0,3)
    assert Polynomial(x2=0) == Polynomial(x0=0)
    assert str(Polynomial(x0=1)+Polynomial(x1=1)) == "x + 1"
    assert str(Polynomial([-1,1,1,0])+Polynomial(1,-1,1)) == "2x^2"
    pol1 = Polynomial(x2=3, x0=1)
    pol2 = Polynomial(x1=1, x3=0)
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(Polynomial(x0=-1,x1=1)**1) == "x - 1"
    assert str(Polynomial(x0=-1,x1=1)**2) == "x^2 - 2x + 1"
    pol3 = Polynomial(x0=-1,x1=1)
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(Polynomial(x0=2).derivative()) == "0"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative()) == "6x^2 + 3"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative().derivative()) == "12x"
    pol4 = Polynomial(x3=2,x1=3,x0=2)
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert Polynomial(-2,3,4,-5).at_value(0) == -2
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3) == 20
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3,5) == 44
    pol5 = Polynomial([1,0,-2])
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-1,3.6) == -23.92
    assert pol5.at_value(-1,3.6) == -23.92


class Polynomial:
    """
    Class Polynimial, input data coefficients of the polynomial.
    Polynomial of type ax^2 + bx^1 + cx^0 where a b c input data.
    Has methods for outputting as a string, addition, derivative,
    finding a value by root, comparing two polynomials
    """

    list_x = []

    def __init__(self, *metod_1, **metod_2):
        """
        Initialization Polynomial
        """

        self.list_x = []
        if metod_1: # let's find out by what method the input data is given
            if isinstance(metod_1[0], list): # as a list
                self.list_x.extend(metod_1[0])
            else:
                self.list_x = list(metod_1) # as numbers
        elif metod_2:
            max_n = 0                           # with using the indices x0 =
            for key, value in metod_2.items():
                if max_n < int(key[1:]):        #when specifying special indexes, indexes can be omitted
                    max_n = int(key[1:])        #find out which serial number is the highest
                for index in range(max_n + 1):
                    self.list_x.append(0)       #fill the list with the same number of 0 as expected
            for key, value in metod_2.items():
                if not isinstance(key, str) or key[0] != 'x':
                    raise TypeError("arguments of this type are not defined")

                self.list_x[int(key[1:])] = value #we put x in their ordinal places in the list

        else:
            # if the call occurred without arguments, it throws an error
            raise TypeError("polynomial class must contain arguments")

        for index in range(len(self.list_x)):           #the set value which is set by the user in the list
            if not isinstance(self.list_x[index], int) and not isinstance(self.list_x[index], float):
                raise TypeError("arguments of this type are not defined")


    def __add__(self, second):
        """
        The method adds two polynomials and returns their sum
        """
        # find the longest polynomial
        add_x = (self.list_x.copy() if len(self.list_x) >= len(second.list_x) else second.list_x.copy())

        # find a polynomial of smaller size and add its coefficients with the first
        for index in range(len(self.list_x if len(self.list_x) <= len(second.list_x) else second.list_x)):
            add_x[index] = self.list_x[index] + second.list_x[index]
        return Polynomial(add_x)


    def __mul__(self, second):
        """
        The multiplication method is used to implement the exponentiation method
        """
        pol0 = list(self.list_x)
        pol1 = list(second.list_x)
        mul_list_x = [0] * (1 + len(pol0) + len(pol1))       #The coefficients of polynomials are multiplied and
        for n_0 in range(len(pol0)):                         #  shuffled in the list to the place that is found by
            for n_1 in range(len(pol1)):                     #  summing their position in the lists before multiplying
                mul_list_x[n_0+n_1] += pol0[n_0] * pol1[n_1]
        return Polynomial(mul_list_x)


    def __pow__(self, number):
        """
        Exponentiation method, takes a degree
        """
        #check the number degree
        #must not be negative and integer, also 0 to the degree of 0 not defined
        if not isinstance(number, int):
            raise ArithmeticError('not a whole degree polynomial is not allowed')
        if  number < 0:
            raise ArithmeticError('negative degree polynomial is not allowed')
        elif number == 0:
            if self.list_x[0] == 0:
                raise ArithmeticError('0 to degree 0 is not allowed')
            else:
                return 1
        elif number == 1:   #if the degree is 1, then we return the polynomial itself
            return Polynomial(self.list_x)
        pow_x = self
        for index in range(0, number - 1): #multiply polynomials for exponentiation
            pow_x *= self
        return pow_x


    def __eq__(self, second):
        """
        The method of comparing a polynomial
        in the case of identical polynomials returns true
        in the case of different polynomials return false
        """
        return str(Polynomial(self.list_x)) == str(Polynomial(second.list_x))


    def derivative(self):
        """
        Derivative method, returns the derivative of a polynomial
        """
        if len(self.list_x) == 1: #if there is only one coefficient in the polynomial returns 0
            return 0
        deriv_x = self.list_x.copy()
        deriv_x.pop(0)                                      #The derivative method is performed
        for index in range(len(deriv_x)):                   # with the help of multiplying the coefficient by
            deriv_x[index] = deriv_x[index] * (index + 1)   # the degree and decreasing the degree by
        return Polynomial(deriv_x)                          # moving coefficient back in the one position on list


    def at_value(self, number_0, number_1=None):
        """
        Method for finding the answer of a polynomial for a given root
        for two given arguments, return their quotient
        """
        value = self.list_x.copy()
        value.reverse()
        def vel(num, val):          #finding the answer with a Horner's method
            root = val[0]
            for index in range(1, len(val)):
                root = num * root + val[index]
            return root
        if number_1 is not None:
            return vel(number_1, value) - vel(number_0, value)
        return vel(number_0, value)


    def __str__(self):
        """
        The method outputs the standard notation of the polynomial
        """
        list_polynom = []
        if self.list_x[0] != 0:             #print x^0
            list_polynom.insert(0, abs(self.list_x[0]))
            list_polynom.insert(0, ' ')
            list_polynom.insert(0, '+' if self.list_x[0] > 0 else '-')
            list_polynom.insert(0, ' ')
        for index in range(1, len(self.list_x)):
            if self.list_x[index] != 0:
                #write out x if the coefficient index is 1, if not then  x^index
                list_polynom.insert(0, f'x^{index}' if index != 1 else 'x')
                #will write out the number if it is not equal to 1
                list_polynom.insert(0, str(abs(self.list_x[index])) if abs(self.list_x[index]) != 1 else '')
                list_polynom.insert(0, ' ') #will write a space
                #depending on the sign of the number, it will write out + or -
                list_polynom.insert(0, '+' if self.list_x[index] > 0 else '-')
                list_polynom.insert(0, ' ') #will write a space
        if len(list_polynom) != 0:
            for index in range(3):  #remove unnecessary spaces and signs
                list_polynom.pop(0)
        else:
            list_polynom.append(0) #if all coefficients are 0, will write 0
        return f'{"".join(map(str,list_polynom))}'


if __name__ == '__main__':
    test()
