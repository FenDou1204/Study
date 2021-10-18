'''
读取整个文件内容

open()函数
所必需的参数为要打开的文件，如果是当前目录下的文件，习惯写为./**.txt
其实最好写为绝对路径
关于路径的一个建议：最简单的做法是，要么将数
据文件存储在程序文件所在的目录，要么将其存储在程序文件所在目录下的一个文件夹

打开文件使用下面这种方法，让程序自己在适当的时候关闭打开的文件
'''
'''读取整个文件'''
with open("./pi_digits.txt") as file_object:    #关键字with在不再需要访问文件后将其关闭
    contents = file_object.read()               #read()方法来读取内容
#    print(contents)            #打印完内容会多一个空行
    print(contents.rstrip())    #打印与文本中完全一样的内容

#程序执行问会有一个空行，这是由于read()方法到达文件尾返回一个空字符串,

'''按照每行进行读取'''
with open("./pi_digits.txt") as file_object:    #关键字with在不再需要访问文件后将其关闭
    for line in file_object:
        print(line.rstrip())    #打印与文本中完全一样的内容

