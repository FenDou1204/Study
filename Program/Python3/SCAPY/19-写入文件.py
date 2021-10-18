file_name = 'programming.txt'

with open(file_name, 'w') as file_object:
    file_object.write("I love Xiao JieJie!\n")
    file_object.write("TEST!")

'''
open()方法，提供了2个实参，第一个是要打开的文件，第二个是以什么方式打开
模式可以为(r:读，w:写，a:附加模式，r+:读写模式)

附加模式的意思就是不覆盖前面的所有内容

如果省略了模式，Python以只读模式打开文件
'''
'''
python只能将字符串写入文件，如果要写入数字，需要使用str()转换为字符串格式。
'''
