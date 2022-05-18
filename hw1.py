from math import factorial
import numpy as np

i=1

while True:
    first = np.sqrt(2) ** (np.log(i))
    second = factorial(i+2)
    third = i**i
    forth = 0.2*(i**np.sqrt(2))
    fifth = i**(2/(np.log(i)))
    print (third/second)
    # print (i,first,second,third,forth,fifth)
    print("\n")
    i=i*2
    if (i>1000000) :
        break