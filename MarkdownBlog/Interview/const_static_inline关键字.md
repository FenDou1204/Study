# C语言常见关键字

## const关键字

### 修饰变量
1. const char *ptr；
2. char const *ptr；
3. char* const ptr；

**1.2两种情况所代表结果相同**

#### const char *ptr和char const ptr
*ptr的值为const，不能修改。

	char cp1[] = "ni hao";
	const char *cp2 = cp1;
	cp2[1] = 'a'; //错误用法，不可以修改
	cp1[1] = 'a'; //正确用法

#### char* const ptr;
	
	char cp1[] = "ni hao";
	char cp2[] = "ni bu hao";
	char* const cp3 = cp1; //可以
	char* const cp3 = cp2；//不可以
	cp3[1] = 'm'; //可以
const修饰变量必须要初始化。
### const修饰函数返回值
函数返回值使用const来修饰。

## static关键字

参考文章:[https://blog.csdn.net/lq18811566072/article/details/82047637](https://blog.csdn.net/lq18811566072/article/details/82047637)

### 面向过程的static
 
#### 静态全局变量
在全局变量前加上static关键字，此变量就为静态全局变量。
    
    #include <stdio.h>
	// a,b变量都存放于全局数据区。生存区为整个程序运行时间。
       b变量可以被其他模块使用extern int b来使用，而a变量
	   只能被当前模块所使用
	static int a = 1; //不可以被extern
	int b =2; //可以被extern

特点:   
1. 在全局数据区分配内存  
2. 未初始化变量会默认初始化   
3. 对声明变量的整个文件全局可见，文件之外不可见(不可以extern)

#### 静态局部变量
在局部变量前加上static关键字，此变量就为静态局部变量。

	#include <stdio.h>
	void func(void)
	{	
		// 全局数据区申请内存
		static int a = 1;
		a++；
		// 栈区
		int b = 2;
		printf("a=%d b=%d\n", a, b);
	}

	多次调用上述函数，可以发现a的值会逐渐递增,而b每次的值都为2
特点:    
1. 静态局部变量内存也在全局数据区
2. 首次执行函数被初始化，后续不会初始化，使用上次的值，
3. 未初始化变量默认为0
3. 它始终驻留在全局数据区，直到程序运行结束，但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束


#### 静态函数
在函数返回类型之前加上static关键字，函数被定义为静态函数。

特点:    
1. 限定了函数的作用域，不能被其他文件所用
2. 多个文件定义相同名字函数不会发生冲突

### 面向对象的static
**==在详细解读**

## inline关键字(少用)

有些函数被频繁的调用，不断有函数入栈（函数栈），会造成栈空间和栈内存大量消耗。

### 特点
1. 内联函数内的代码会直接替换调用函数位置的代码，被调用函数不需要每次调用都出入栈。
2. inline只适合函数体内代码简单的函数使用，不能包含复杂的结构控制语句例如while、switch，并且内联函数本身不能是直接递归函数(自己内部还调用自己的函数)。

