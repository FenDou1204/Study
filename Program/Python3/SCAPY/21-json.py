'''
使用json来处理保存数据文件
json.dump()
json.load()

'''
import json

num = [1, 2, 3, 4, 5, 6]
filename = 'numbers.json'
with open(filename, 'w') as f_obj:
    json.dump(num, f_obj)


