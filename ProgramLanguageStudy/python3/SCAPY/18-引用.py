'''
id 方法能够获取到当前变量的地址

a = 100
b = a

在python中和c中存储方式是不一样的


'''
#python中
a = 100
b = a
a = 50

print(b)    #b是多少呢？50
print(id(a))
print(id(b))


'''
可变类型和不可变类型

不可便类型:数字  字符串  元组
可变: 列表  字典(可以直接通过下标来修改内容)
'''
a = 'hello'
a = 'ni hao'

#上述两种情况并不代表ni hao 字符串将hello改变了，而是a指向了ni hao

a = 'hello'
a[0] = 'h'
