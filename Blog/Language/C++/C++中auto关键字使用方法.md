 # auto关键字
C++11后支持
auto用作类型指定符。   
auto关键字修饰变量会自动识别变量,最好要初始化,默认初始化为int类型。

## auto的一些用法

### auto(拷贝)
`for(auto it : 元素)`
会拷贝原元素的值,修改it不会改变元素的值；
### auto&(非拷贝)
`for(auto& it : 元素)`
不会拷贝原元素的值,修改it会改变元素的值；
### const auto&(非拷贝)
`for (const auto& it : 元素)`
不会拷贝原元素的值,修改it会报错   
**使用迭代器可以使用此方法来替代**
### const auto
`for (const auto it : 元素)`
会拷贝原元素的值,拷贝的值不能进行修改

## auto修饰变量
- **C++中的auto关键字是一个类型说明符，通过变量的初始值或者表达式中参与运算的数据类型来推断变量的类型。**   
- **C++11中使用auto修饰变量必须要进行初始化。**
- **auto关键字修饰多个变量必须初始化为相同类型。**

	auto a; //错误的用法
	auto b=1, c=1.1;
	double b=1.1, c=2.2;
	auto d = b+c; //d被默认设置为int类型

## decltype关键字
- `decltype`关键字判断一个变量或者函数的返回值,并且定义新的变量。
	
	int a = 1;
	char b = 'a';
	decltype(a) c = 2; //c的类型即为int类型
	decltype(b) d = 'b'; //
	decltype(func()) sum = x; //sum的类型是函数func()的返回值的类型, 但是这时不会实际调用函数func()

- const关键字修饰的变量会完整的被decltype保留下来。
	
	const int a = 1;
	decltype(a) b = 2;
	b = 4; //这句会报错

- decltype修饰引用类型
	
	int a = 1, &b = a;
	decltype(b) c = 5; //引用类型
	decltype(b+0) d = 6; //int类型

- 如果一个表达式的类型不是引用, 但是我们需要推断出引用, 那么可以加上一对括号, 就变成了引用类型了

	int a = 1;
	decltype((a)) b = a; //b为引用类型
	
- 指针的解引用返回是引用类型

	int a=1, b=2, *p=&a;
	decltype(*p) c = b;
	