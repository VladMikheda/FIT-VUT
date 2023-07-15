#IMPORTS
import mathlib as math
import sys
import re
import os
import cProfile, pstats
from random import randint

def parseData(data):
    fixedData = data.replace(",", ".") #in case floats are with comma
    fixedList = re.split("\s+", fixedData) #split to list when space is reached \n \r " "
    finalList = []

    for element in fixedList:
        element = element.strip() # remove leading and trailing spaces
        #check if element is a number
        try:
            element = float(element)

        except:
            continue

        else:
            finalList.append(element)

    return finalList

def calculateAverage(list):
    result = 0
    for n in list:
        result = math.sum(result, n)
    return math.div(result, len(list))

def calculateExpression(list, average):
    temp = 0
    for n in list:
        temp += math.pow(n, 2)
    return math.root(math.mul(math.sub(temp, math.mul(math.pow(average, 2), len(list))), math.div(1, math.sub(len(list), 1))), 2)

#can be used for generating numbers to test
def genNumbers():
    N = 1000
    try:
        f = open("profiling/profilerNumbers.txt", "w+")
    except:
        print("couldnt open file \n")
    else:
        for i in range (N):
            temp = randint(10, math.pow(10, 6))
            f.write(str(temp) + "\n")
    finally:
        f.close()

def calculateProfiling():
    numbers = parseData(sys.stdin.read())

    if (len(numbers)):
        average = calculateAverage(numbers) # x̅
        deviation = calculateExpression(numbers, average)
        print(deviation)
    else:
        print("not enough numbers \n")

if __name__ == "__main__":
    #genNumbers()   #in case u wanna gen new text file of numbers
    profiler = cProfile.Profile()
    profiler.enable()
    calculateProfiling()
    profiler.disable()
    dir = os.getcwd() + "/output"
    if (not os.path.isdir(dir)):
        os.mkdir(dir)
    profiler.dump_stats(dir + "/output.prof")
    try:
        f = open(dir + "/output.txt", "a") #append to output file so we can compare with different amount of numbers
    except:
        ("couldnt open file")
    else:
        stats = pstats.Stats(dir + "/output.prof", stream=f)
        stats.sort_stats("tottime")
        stats.print_stats()
    finally:
        f.close()
