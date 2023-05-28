from math import floor
#from functools import map
from random import randint
import random as rnd
from array import ArrayType
import time

##
# \brief Radix Sort Python implementation
# 
# {
# Auxilary space: [O(n + b)] where [n] is the number of elements in the input array and [b] is the base. 
# Time complexity: O(d * (n + b)), where [n] is the number of elements in the input array
#                                        [d] is the number of digits in the maximum element
#                                        [b] is the base (usually 10 for decimal numbers).
# }
#
# \file radix.py
# \author Jakob Balkovec
# 
#{
# \PRO: Radix sort is a stable sorting algorithm that means that the relative order 
#       of elements with equal values is preserved during the sorting process. 
# 
# \CON: The space complexity [O(n + b)] of radix sort is influenced by the number of elements
#       and the base used (usually 10 for decimal numbers). As the input grows larger and larger
#       more memory and space is required to sort the array/container.
#
#       Therefore radix sort is not prefered for sorting large data-sets
#}
##

#{
# Pyhton does not support templates but also determines the type of a varible at runtime so it doesn't really matter
#}

def get_max(arr):
    max_value = arr[0]
    for i in range(1, len(arr)):
        if arr[i] > max_value:
            max_value = arr[i]
    return max_value

def counting_sort(arr, exp):
    n = len(arr)
    output = [0] * n
    count = [0] * 10

    for i in range(n):
        count[(arr[i] // exp) % 10] += 1

    for i in range(1, 10):
        count[i] += count[i - 1]

    for i in range(n - 1, -1, -1):
        output[count[(arr[i] // exp) % 10] - 1] = arr[i]
        count[(arr[i] // exp) % 10] -= 1

    arr[:] = output

def radix_sort(arr):
    max_value = get_max(arr)

    exp = 1
    while max_value // exp > 0:
        counting_sort(arr, exp)
        exp *= 10

def print_array(arr):
    print("[" + " ".join(map(str, arr)) + "]")

def fill_array(arr):
    for i in range(10):
        arr.append(rnd.randint(1, 100))

def is_sorted(arr):
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True

def main():
    print("\n")
    arr = []
    fill_array(arr)
    print("[#1]:", end=" ")
    print_array(arr)

    start_time = time.time()
    radix_sort(arr)
    end_time = time.time()

    print("[#2]:", end=" ")
    print_array(arr)
    print("\n[sorted]: ", is_sorted(arr))
    print("\nExecution time: %.6f seconds" % (end_time - start_time))
    print("\n")
    
if __name__ == "__main__":
    main()
