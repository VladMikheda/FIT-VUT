'''
@file mathlib_tests.py
@brief tests for mathematical functions from mathlib
@author Jakub Potocek (xpotoc07)
'''

from mathlib import sum, sub, mul, div, fac, pow, root, log

def test():
    assert sum(2,2) == 4
    assert sub(3,2) == 1
    assert mul(3,3) == 9
    assert div(6,2) == 3
    assert div(6,0) == None
    assert fac(5) == 120
    assert pow(3,3) == 27
    assert pow(3,0) == 1
    assert root(27, 3) == 3.0
    assert root(0, 3) == 0.0
    assert root(3, 0) == None
    assert root(3, 1.1) == None
    assert log(1024,2) == 10

if __name__ == '__main__':
    test(),