from multiprocessing import *
import multiprocessing
'''
学习list中for循环的用法

'''
'''
list_test = [ i*2 for i in [1,3,5,7,9]]

print(list_test)
'''
a = [1, 2, 3, 4, 5, 6]

for i in range(len(a)):
    if a[i] == 3:
        a[i] = 4

print(a)
