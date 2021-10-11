'''
方法readlines()从文件中读取每一行，并将其存储在一个列表中；
'''


filename = 'pi_digits.txt'

with open(filename) as file_object:
    lines = file_object.readlines()

print(lines)

pi_line = ''
for line in lines:
#    print(line.rstrip())#移除尾的空格字符
    print(line.strip()) #移除首尾的空格字符
#    pi_line += line.rstrip()
    pi_line += line.strip()


print(pi_line)
print(len(pi_line))
