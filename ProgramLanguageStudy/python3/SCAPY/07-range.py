a= range(10)

print(list(a))
print(list(range(0, 10, 1)))

''' 如果直接打印并不能将列表打印出来
这是python3中的一个特性,可以看出b的类型是个range
如果想要将内容打出来，适用list进行种类转化
'''
print(range(0,-1,-1))

b = range(0, 10, 2)     #是一个range类
print(type(b))



