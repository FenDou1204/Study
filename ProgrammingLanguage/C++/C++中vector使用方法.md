# stl vector使用

## 参考链接
- [https://www.cnblogs.com/aminxu/p/4686332.html](https://www.cnblogs.com/aminxu/p/4686332.html)
- [http://www.cplusplus.com/reference/vector/vector/](http://www.cplusplus.com/reference/vector/vector/)

## vector
vector是顺序容器中的一种，vector表示连续的内存地址，基于数组实现。

## vector使用方法
### 头文件
使用vector需要包含头文件`#include <vector>`

### vector初始化
1. vector<int> vec1; //默认初始化,创建个空数组
2. vector<int> vec2(vec1); //通过已有数组进行初始化
3. vector<int> vec3(vec1.begin(),vec1.end()); //自己感觉类似2的初始化
4. vector<int> vec4(10); //初始化数组大小为10个元素,值为0
5. vector<int> vec5(10,4); //初始化数组大小为10个元素,值为4
6. vector<int> vec6 {1,2,3,4,5};
7. vector<int> vec7={1,2,3,4,5};

### vector操作方法

#### 常用操作方法
- vec.size(); //判断数组的大小
- vec.push_back(100); //尾部插入元素100
- vec.pop_back(); //删除尾部元素
- vec.insert(10,100); //在下标10插入数值100,后续元素位置都变大
- vec.clear(); //清空整个vector
- vec.empty(); //判断empty是否为空
- vec.erase(10); //删除第十个位置的元素
- vec.erase(vec.begin(), vec.begin()+3) //删除前3个元素

#### 迭代器
- vector<int>::iterator iter = vec.begin(); //创建迭代器
- vec.begin(); //迭代器的开始
- vec.end(); //迭代器的结束

### vector遍历
#### 下标遍历法
vector和数组也类似,通过使用下标来访问其中的元素数值。
首先需要判断数组中元素的个数

	#include <vector>
	
	int nVectorSize = vec.size();
	for(int i=0; i<nVectorSize; i++)
	{
		printf("第%d个元素的值为%d", i, vec[i]);
	}


#### 迭代器遍历法
使用迭代器的话需要首先创建迭代器

	#include <vector>
	
	//创建迭代器
	vector<int>::iterator iter = vec1.begin();
	//迭代器自增,指向下一个元素
	for (; iter != vec1.end(); iter++)
	{
	}
