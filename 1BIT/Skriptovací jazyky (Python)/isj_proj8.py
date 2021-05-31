#!/usr/bin/env python3

def first_with_given_key(iterable, key=lambda f:f):
    myiter = (i for i in iterable)
    save = set()
    while 1:
        try:
            element = next(myiter)
            if hash(key(repr(element))) not in save:
                save.add((hash(key(repr(element)))))
                yield element
        except StopIteration:
            break


print(tuple(first_with_given_key([[1],[2,3],[4],[5,6,7],[8,9]], key = len)))
