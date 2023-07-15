'''
@file mathlib.py
@brief mathematical functions
@author Jakub Potocek (xpotoc07)
'''
import math


def sum(a, b) :
    '''
    Funkcia pre sčítanie
    @param a
    @param b
    @return súčet
    '''
    return a + b

def sub(a, b) :
    '''
    Funkcia pre odčítanie
    @param a
    @param b
    @return rozdiel b od a
    '''
    return a - b

def mul(a, b) :
    '''
    Funkcia pre násobenie
    @param a
    @param b
    @return násobok
    '''
    return a * b

def div(a, b) :
    '''
    Funkcia pre sdelenie
    @param a
    @param b
    @return podiel
    '''
    try :
        return a / b
    except :
        return None
    
def fac(a) :
    '''
    Funkcia pre faktorial
    @param a
    @return faktoriál
    '''
    return math.factorial(a)

def pow(a, b) :
    '''
    Funkcia pre umocnenie
    @param a
    @param b
    @return b mocnina a
    '''
    if isinstance(b, int):
        return a ** b
    else:
        return None
    
def root(a, b) :
    '''
    Funkcia pre odmocnenie
    @param a
    @param b
    @return b odmocnina a
    '''
    
    if isinstance(b, int) :
        try :
            return a ** (1/b)
        except :
            return None
    else :
        return None
    
def log(a, b) :
    '''
    Funkcia pre logarotmus
    @param a
    @param b
    @return logaritmus a o základe b
    '''
    return math.log(a, b)

if __name__ == "__main__":
    import doctest
    doctest.testmod()