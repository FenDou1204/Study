## 数据类型

### 整数
任意大小的整数，包括`0`,`100`,`-666`等    
十六进制表示为`0xff00`,`0x1234`,后面各位选择范围为`0-F`

### 浮点数
叫小数更好听一些。例如`1.23`,`-1.23`,`1.23e10(1.23*(10^10))`等    
关于四舍五入还有等等一些特别的内容这里先不谈论。

### 字符串string
由一对`英文单引号''`或者`英文双引号""`包含的文本，但是引号本身不属于字符串。例如`"xiaoming"`、`'abd'`。    
在实际情况中有时候字符串内容就包含单引号或者双引号，如果字符串中包换`''`,那么整体字符串用`""`包含，例`"xiao's"`；反之用`''`包含，例`'Tom "money"'`；如果文本中既有`'`又有`"`，需要用将属于字符串的`'`和`"`前面加上转义字符`\`，例
`"I \'m \"OK\"!"`来表示`I 'm "OK"!`

转义字符`\`可以转义很多字符，`\n`代表换行，`\t`代表制表符，`\\`代表字符`\`

常见的打印函数`print`，完全抛弃python2中的用法，只在偶尔遇到的示例代码调试中进行使用，在以后的代码编写完全建议使用python3

使用`print函数`可以查看转义字符的作用。  
`print(r"")`表示内部字符串所有的转义字符不起作用

### 布尔型bool
布尔型只包括两个值`True`和`False`    
在进行逻辑判断中，返回的值必定为其一。    
`1>2`返回值为`False`而`2>1`返回值为`True`    
俩布尔值可以进行`and`、`or`、`not`运算。分别为逻辑`与`、`或`、`非`，与C语言中的`&&`、`||`、`!`是一样的功能。    
`A and B`只有A为True并且B为True，返回值为True，其他都为False（两个条件同时成立返回True）    
`A or B`只有A为False并且B为False，返回值为False，其他都为True（两个条件只要有一个成立即返回True）
`not True`返回值为False（真变为假，假变为真）

### 空值None
python中的一个特殊值，用`None`来表示，跟`0`是两种完全不同的东西，所以想到`None`一定不要想到`0`值。

### 变量
变量在程序中就是用一个变量名表示了，变量名必须是大小写英文、数字和_的组合，且不能用数字开头    
`a = 5`,a就代表一个变量，它的值为5，是个整型数。  
`name = "Nick"`,name是一个字符串变量，它的值为Nick。

在python中使用`a=5`后还可以使用`a="Nick"`,python会自动指明类型；
而在C等一些语言中`int a = 5`后如果使用`a = "Nick"`,C编译器是会报错的。

这种变量本身类型不固定的语言称之为动态语言（Python），与之对应的是静态语言（C，Java等）

### 常量
类似于π这种约定俗成或者是一些科学测定出的精确值，这个值是不能改变的，通常用大写变量名来表示。

### 列表[list]
列表由一对`[]`所包括，其中各元素之间用`,`隔开    
列表是python内置的数据类型。list是一种有序的集合，可以随时添加和删除其中的元素。list主要是将同一种属性的元素放在一起（当然，不同的数据类型也可以放入）

使用`len()`函数可以获取list元素的个数。访问列表的元素，索引是从0开始的。如果列表共有4个元素，那么索引的最大值为3，如果访问下标为4，python解释器会报错。    
索引的值也可以为负数，-1为访问最后一个元素，-2访问倒数第二个元素，以此类推。

classmates = ['a', 'b', 'c']
classmates[1]值为'b'    
classmates[-1]值为'c'    
classmates.append('d')		在原来列表的最后添加入元素
classmates.insert(1,'e')	在下标为1的地方插入e
classmates.pop()			将最后一个元素删除，它的输出为最后一个元素    
classmates.pop(i)			将i下标元素删除（注意越界），它的输出为被删除元素    

list中数据的替换方式为：直接修改下标对应的值    
list中的数据类型可不同
list中的元素可以为另一个list，如果访问list中list的元素，使用classmates[2][1]这样的格式，第一个下标2代表为classmates列表的第三个元素（列表），第二个下标1代表第三个元素（列表）中的第二个值。    

### 元组(tuple)
列表由一对`()`所包括，其中各元素之间用`,`隔开 
元组也是一种有序列表，和list非常类似，**tuple最重要的特点是：一旦初始化后 不能进行【增删改】操作，只能进行【查】操作**

如果定义只有一个元素的tuple，一定要写为`a=(1,)`,一定不能写为`a=(1)`,后者的写法a的类型成为了整型，已经不再是tuple。

元组里边的数值能修改吗？答案：能。
还是廖大婶的例子
a = ('1', '2', ['3', '4'])    
a[2][0] = 3

print(a)
('1', '2', [3, '4'])

tuple所谓的“不变”是说，tuple的每个元素，指向永远不变。如果悄悄通过某些方法将所指向内存中数据进行修改，也是可以改变的。

### 字典{dict}
字典有极快的查询速度，以key-value的方式存储；
chengji = {A:94, B:95, C:96}
chengji[A] 的值便是 94

如果要向字典添加内容，可以直接chengji[key] = value 就可以

判断是否存在某个key
1、可以直接使用`in`来进行判断。
```'A' in chengji```
2、dict提供的get()方法，key不存在会返回`None`,或者指定的value
chengji.get(A,-1)	#-1即为自己的value

从字典删除某对值
chengji.pop(key)    

*Warning:dict内部存放的顺序和key放入的顺序是没有关系的。*

**字典**和**列表**异同

dict有以下几个特点：     
查找和插入的速度极快，不会随着key的增加而变慢；    
需要占用大量的内存，内存浪费多。     
而list相反：     
查找和插入的时间随着元素的增加而增加；     
占用空间小，浪费内存很少。    
dict是用空间来换取时间的一种方法。   

哪些类型能作为key值呢？这里同时还有一个**不可变对象需要进行**

### set([ ])
set是一组key的集合，但是不会存储value。key是不能重复的，所有在set中，不存在重复的key。创建一个set，需要提供一个list作为输入集合。如果list中有重复元素会被直接过滤。    

添加元素add(key)。多次重复添加同一个key不会有效果。   
删除元素remove(key)。   

s1 = set([1, 2, 3])	  
s2 = set([2, 3, 4])	  
s1 & s2		#交集	  
{2, 3}	  
s1 | s2	  	#并集
{1, 2, 3, 4}	  

## 字符编码
计算机能处理的数据只能为0和1。    
1Byte = 8bits 二进制`11111111`  最大值为十进制2^8-1=255    
2Bytes = 16 bits 二进制为16个1   最大值为2^16-1=65535    
4Bytes表示的最大整数为2^31-1=4294967295    

由于历史原因，最早只有127个字符被编码到计算机中。包括大小写英文字母，数字和一些常用不常用的符号，也就是ASCII码表。一共127个，这一个字节就能搞定了。

随着计算机发展，各国都有自己的编码，这就2个字节也不会能够放的下。

Unicode把所有的语言统一到一套编码来解决乱码问题。
编码问题看廖大婶的讲解吧，附上连接：    
[廖雪峰讲解字符编码](https://www.liaoxuefeng.com/wiki/0014316089557264a6b348958f449949df42a6d3a2e542c000/001431664106267f12e9bef7ee14cf6a8776a479bdec9b9000)

python3中字符串是Unicode编码的，所以python支持多语言。   
对于单个字符的编码，Python提供了ord()函数获取字符的整数表示，chr()函数把编码转换为对应的字符；

**FBI Warning**   
由于Python的字符串类型是str，在内存中以Unicode表示，一个字符对应若干个字节。如果要在网络上传输，或者保存到磁盘上，就需要把str变为以字节为单位的bytes。   
Python对bytes类型的数据用带b前缀的单引号或双引号表示

想了想，这个问题出在在网络传输出过程中和本地显示中对于不同字符的处理方式。

中文的`str`无法用`ascii`来编码，超过了一个字节。

以Unicode表示的str通过`encode()`方法可以将编码变为`bytes`,在网络上传输汉语字符串应该需要使用这个方法来转变格式。

`len('中文')`和`len('中文'.encode('utf-8'))`的结果是不同的，前者为2，后者为6.

一个中文字符经过utf-8编码以后通常会占3个字节，而一个英文字母通常会占一个字节。

`# -*- coding: utf-8 -*-`
来申明按照utf-8编码格式来读取源代码。

### 格式化
`%`运算符用来格式化字符串。    
%d 整数 %f 浮点数  %s 字符串  %x 十六进制数    

print()输出格式对齐
print("%10s")指定占位符宽度并且右对齐    
print("%-10s")指定占位符宽度并且左对齐

## 条件判断

### if语句
if语句的基本格式为:    
```
if 条件：    
	print()		#如果条件为True  
elif 条件:
	print()		#如果此条件成立  
else：    
	print()		#如果条件为False
```

if x：
	print("True")    
只要x是非零数值、非空字符串、非空list等，就判断为True，否则为False。


### 关于input()函数
input()函数的返回值为str类型，如果要进行整数比较的话，需要使用int()函数来进行数据类型转换。

## 循环语句
包括while和for...in...循环俩种    

#### for...in...循环
迭代列表中的内容：   
names = [1,2,3,4,5,6]
for name in names:
	print(name)

##### 关于range()函数
range()函数返回的是一个range类型的数据结构，查看他的内容需要使用list()函数进行显示。
list(range(5))----->[0,1,2,3,4]    
如果range()只有一个参数，那么这个参数就是生成整数序列的个数

#### while循环
while 条件:    
	...   
	...
只要条件符合，循环会一直进行下去；    

while 1：
	...
条件为1就相当于条件恒成立，相当于循环会一直执行

#### break结束循环
在for循环或者是while循环中，可以使用break提前结束整个循环。

#### continue跳出本次循环
在for循环或者是while循环中，使用continue跳出本次循环还要执行的后续代码，直接从循环体开始执行。

**break和continue必须使用`if判断`语句来进行配合。**

## 函数fun()
当代码出现有规律重复的时候，就可以封装为一个函数；或者叫抽象成一个函数。抽象是数学中常见的概念。

例如算圆面积的函数：s=πr^2

我们只需要知道半径或者周长或者直径等等参数便可以得到半径，进而求的半径，代入函数便可以得到。
```
def yuanmianji(r):
	S = PI * r * r
	return S
```

如果半径为5，yuanmianji(5).

**一些常见的内置函数**    

**绝对值函数**：`abs()`，只有一个参数，参数类型整型和浮点数    
**比较大小**：`max()`，参数个数不限，参数类型整型和浮点数
**数据类型检测**：`isinstance()`,

#### 定义函数

def fun_name(can shu ):    
	return 
如果定义的函数不需要执行什么操作，可以在函数内容直接pass。pass在代码块执行预留等情况下有较大作用

如果返回值写为 `return x,y`，其实这个返回值还是一个tuple。

编写函数，如果有必要需要对于函数参数进行类型检测；如果函数没有return语句的话，使用变量来获取返回值为None。

#### 参数检查
函数的参数个数是确定的，参数的数据类型也是确定的；

python内置的一些函数对于错误检测是比较完善的；   
对于函数参数类型检测使用`isinstance()`来实现；
在检测类型后，`raise TypeError('bad operand type')`，如果遇到类型不符合会抛出异常`bad operand type`.

#### 多值返回
直接使用`return a,b`，其实返回的为一个元组(a,b);

## 函数参数
函数参数主要有位置参数，默认参数，关键字参数和可变参数四种；
还有一种命名关键字参数。

#### 位置参数
这个举例子演示最好了。
2的3次方和3的2次方
```
 1 '''计算x的y次方'''   
  2 def func(x, y):     
  3     result=1    
  4     if(x==0):    
  5         return 0
  6     else:
  7         if(y==0):
  8             return 1
  9         else:
 10             while(y>0):
 11                 result*=x
 12                 y-=1
 13     return result
 14  
 15 while 1:
 16     a,b=input("请输入两个值(空格区分):").split()
 17     print(func(int(a),int(b)))
```

#### 默认参数
计算x的y次方时，有时候传入变量可能只传了一个，那么我们默认输出传入参数的平方。
```
def func(x, y=2):
```
这样，就算你只传入一个参数，解释器也不会抛出错误；只是默认算一个值的平方；如果要算不为2的n次方，那么就应该明确指出n的值。
如果有默认参数，默认参数必须放在参数的最后；    
**定义默认参数要牢记一点：默认参数必须指向不变对象！**

#### 关键字参数
定义函数：
def info(name，hometown)：

在传参的时候info(name='Nick', hometown='shanxi')

#### 可变参数
简单的加法计算器，参数的个数是不固定的
def calculate(*num):

在调用函数是calculate(1,2,3,4,5)时，所传入的所有参数都会被封装在一个元组中。

Python允许你在list或tuple前面加一个*号，把list或tuple的元素变成可变参数传进去。

#### 命名关键字参数
def calculate(**canshu):
如果传入的是**，可以将字典当成可变参数。

#### 递归函数
自身调用自身的函数
算阶乘的函数
def jiecheng(n):
	if n==1:
		return 1
	return n*jiecheng(n-1)
递归可能会导致栈溢出，这是缺点

递归有个经典案例是`汉诺塔`，可以好好进行了解。

## 切片
目前主要涉及到 list 和 tuple
L = [1, 2, 3, 4, 5, 6]   
取前俩值可以使用L[0],L[1]   
也可以使用L[0:2],从索引0开始，取2个元素；
第一个索引为 0可以省略，写为L[:2]      
L[1:3],从索引1开始，取2个元素；   

取结尾的数据呢，如果不知道元组或者列表的个数的话，取最后一个数可以使用循环，简单的办法可以L[-1]取得最后一个元素。

L[:10]	前十个数
L[-10:]	后十个数
L[:10:2]步长为2，隔2个数取一个
L[::5]	所有数，每5个取一个
L[:]	完全复制一个list

tuple也是同样的操作，切片也是tuple。   
字符串也是一种list，所以也可以进行切片操作，结果仍是字符串。    
**去除首尾的空格**
```
def trim(s): 
    while s[:1] == ' ': 
        s = s[1:] 
   while s[-1:] == ' ': 
        s = s[:-1] 
    return s
``` 

## 迭代
使用for循环或者while循环来获取string、list、tuple等里边的每一项数据称为迭代。
普通的迭代比较简单，主要是来说说dict。   

**dict中默认迭代的是key，也就是说使用for循环打印出来所有的key**
**如果要迭代value，就的使用`for value in zidian.values()`**
**同时迭代使用for k，v in 字典.items()**

如果判断一个对象是可迭代对象，通过collections模块的iterable类型。
```
from collections import Iterable

isinstance(**, Iterable)
```

python内置函数 `enumerate` 把一个list变为索引-元素对，可以使用for循环来获取索引和元素。   

## 列表生成式
List Comprehensions  Python内置的list生成式。    
list（range（1，11））   

[x*x for x in range(1,11)]   
[x*x for x in range(1,11) if x%2 == 0]   

两层循环全排列
[m+n for m in 'ABC' for n in 'XYZ']

## 生成器(generator)
Python中，这种一边循环一边计算的机制，称为生成器：generator    
把列表生成式的[]改为()，想要访问其中的元素，需要使用next(*)函数。    

**如果一个函数中包括yield函数，这个函数就成为了generator。**

一个斐波那契数列
```
def fib(max):
	n,a,b=0,0,1
	while n<max:
		yield b
		a,b=b,a+b
		n=n+1
	return 'done'
```
**以下这块还需要努力理解一下**
最难理解的就是generator和函数的执行流程不一样。函数是顺序执行，遇到return语句或者最后一行函数语句就返回。而变成generator的函数，在每次调用next()的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行。

杨辉三角

## 迭代器
for循环数据：list、tuple、dict、set、str等，这些都是Iterable，却不是Iterator。可以直接使用for循环的对象都是可迭代对象；    
   
还包括generator，包括生成器和yield的函数；

```
为什么list、dict、str等数据类型不是Iterator？

这是因为Python的Iterator对象表示的是一个数据流，Iterator对象可以被next()函数调用并不断返回下一个数据，直到没有数据时抛出StopIteration错误。可以把这个数据流看做是一个有序序列，但我们却不能提前知道序列的长度，只能不断通过next()函数实现按需计算下一个数据，所以Iterator的计算是惰性的，只有在需要返回下一个数据时它才会计算。

Iterator甚至可以表示一个无限大的数据流，例如全体自然数。而使用list是永远不可能存储全体自然数的。
```

**Python的for循环本质上就是通过不断调用next()函数实现的**
**把list、dict、str等Iterable变成Iterator可以使用iter()函数：**


## 高阶函数
函数传参中可以接受其他函数

python内置map()和reduce()函数；

map()		接收2个参数，一个Iterable，另一个是函数。
reduce()	接收2个参数，一个list，另一个是函数。

```
from functools import reduce

DIGITS = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

def char2num(s):
    return DIGITS[s]

def str2int(s):
    return reduce(lambda x, y: x * 10 + y, map(char2num, s))
```

**内置函数filter()**
用来过滤序列
filter也接收一个函数和一个序列，和map不同的是，filter把传入的函数依次作用于每个元素，然后根据返回值是True还是False决定保留还是丢弃。

**还徐理解**

## 排序算法
python内置sorted()函数。sort函数可以对一个list进行排序。
sorted()函数不会改变原来列表的排列顺序。

sorted()函数也是一个高阶函数，可以接收一个key函数来实现自定义排序。
sorted([****], key=abs)		#按绝对值大小排序
sorted([****], key=str.lower)#按小写字母排序
sorted([****], key=str.lower, reverse=True)#倒着排序

默认情况下，对字符串排序，是按照ASCII的大小比较的，由于'Z' < 'a'，结果，大写字母Z会排在小写字母a的前面。

## 函数作为返回值
函数可以作为返回值。

def lazy_sum(*args):
	def sum():
		ax=0
		for n in args:
			ax=ax+n
		return ax
	return sum

f=lazy_sum(1,2,3,4,5) 并不会直接返回结果，还需要调用f()

#### 闭包

## 偏函数
Python中的functools提供了一个偏函数(Partial function)
```
import functools
int2 = functools.partial(int, base=2)
```
int函数默认可以字符串转为十进制数，但是也可以指定base=2，8，10来转变为相应的进制数。

int2()函数可以转变为二进制。如下写：
def int2(x, base=2):
	return int(x, base)
但是如果这样写，int2()函数还可以传参base=10；

import functools
int2=functools.partial(int, base=2)	#将int()函数的base值默认为2，并且不可以改变。

## 面向对象编程(OOP object oriented programming)
一个对象包含了数据和操作数据的函数。

Python中，所有的数据类型都可以视为对象。

#### 类和实例
类是抽象出来的模板，实例（对象）就是根据类创建出来的一个具体的对象，每个对象都有相同的方法，但是各自中存储的数据可能不同；

class Student(object):
	pass

在创建实例时，有些参数是对象所需的，在class有一种特殊的方法__init__方法，__init__方法的第一个参数永远是self，表示创建的实例本身。

有了__init__方法，创建示例就必须要传入相匹配的参数；    

```    
class Student(object):           

	def __init__(self, name, score):
		self.name = name
		self.score = score

	def print_score(self):
		print(self.score)

	def print_A_B_C(self):
		if score > 75:
			print("A")
		elif:
			pass
		else:
			pass
Nick = Student('Nick', 86)   
Nick.print_score()   
Nick.print_A_B_C()         
```

#### 访问限制

Nick = Student('Nick', 100)    
print(Nick.score) -> 100     

如果使用Nick.score = 99 就会修改内部变量的值。    
如果不想要修改内部的值，可以把属性的名称前加上两个下划线·__·。

	def __init__(self, name, score):
		self.__name = name
		self.__score = score

如果现在使用Nick.name或者Nick.score来访问会提示错误。如果想要访问，可以定义函数将数值返回。如果设置数据也可以传参进去修改。

**需要注意的是，在Python中，变量名类似__xxx__的，也就是以双下划线开头，并且以双下划线结尾的，是特殊变量，特殊变量是可以直接访问的，不是private变量，所以，不能用__name__、__score__这样的变量名。**

**有些时候，你会看到以一个下划线开头的实例变量名，比如\_name，这样的实例变量外部是可以访问的，但是，按照约定俗成的规定，当你看到这样的变量时，意思就是，“虽然我可以被访问，但是，请把我视为私有变量，不要随意访问”。	双下划线开头的实例变量是不是一定不能从外部访问呢？其实也不是。不能直接访问\_\_name是因为Python解释器对外把\_\_name变量改成了\_Student\_\_name，所以，仍然可以通过_Student__name来访问__name变量**	

**还有一点 定义的__变量会被解释器内部变为\_lei__bianliang**

#### 继承和多态
