# Linux下代码覆盖率工具gcov使用

## 前言

gcov是linux下常用编译工具gcc模块下的代码覆盖测试率工具。安装gcc编译工具后gcov可以直接使用。gcov测试工具在一定程度上可以发现代码中的逻辑错误以及测试哪部分代码耗时较多，可以进行优化。

## gcov介绍

## 如何使用

### 代码示例
	
示例代码:gcov_test.cpp

	#include <stdio.h>
	#include <stdlib.h>
 
	int main(void)
	{
     	int iTmp = 0;
     	long int lTmp = 0;

     	for(iTmp; iTmp < 10; iTmp++)
     	{
			lTmp = random();
          	printf("随机产生的数是:%ld\n", lTmp);
          	if (0 == (lTmp % 2))
          	{
               printf("随机产生数为偶数\n");
          	}
          	else
          	{
               printf("随机产生数为奇数\n");
          	}
     	}
  
     	return 0;
 	}

### 如何编译

1. g++ -fprofile-arcs -ftest-coverage gcov_test.cpp -o gcov_test 生成gcov_test.gcno文件
2. ./gcov_test执行二进制程序，生成相应的.gcda文件gcov_test.gcda文件
3. gcov gcov_test.cpp生成最终的覆盖率文件gcov_test.cpp.gcov，同时终端也会显示代码的覆盖率情况

### Makefile如何添加编译参数
编写Makefile时需要添加编译参数以及链接静态库。

主要包括下面2项内容:

- CFLAGS += -fprofile-arcs -ftest-coverage
- LDLIBS += -lgcov
 
注: 因为公司老防火墙中可能由于编译参数的原因的问题，必须在链接标志位写入编译参数**LDLIBS += -fprofile-arcs -ftest-coverage**。

### 守护进程形式如何输出信息
DEAMON程序在未停止之前是无法输出所有的运行数据。相应的办法是使用信号(SIGNAL)来控制相应的日志输出。示例如下:

	主函数
	signal(SIGINT, signal_handler)

	信号处理函数文件：
	extern "C" void __gcov_flush();
	void signal_handler(int nSig)
	{
		switch (nSig)
		{
		case SIGINT:
			#以前的代码
			__gcov_flush();
			break;
		default:
			break;
		}
	}

按照使用gcov的编译方式编译文件后正常执行。

此时SIGINT信号已经可以输出相应的信息，使用`killall 程序 -2`或者其他可以触发SIGINT信号的方式即可输出相应信息。

## lcov的使用

lcov只是将生成的.gcov统计文件以web页面进行展示，具体展示内容和.gcov文件相同。

### 安装lcov
	
1. 默认情况，lcov是未安装的。
2. git clone https://github.com/linux-test-project/lcov.git
3. cd lcov
4. make install

### 使用lcov

1. 使用lcov最好在生成.gcov文件的目录下
2. lcov -b ./ -d ./ –gcov-tool /usr/bin/gcov -c -o output.info -b和-d俩个参数都是指定目录，lcov会检测相应目录下的gcov文件，生成部分信息存储在output.info文件中
3. genhtml output.info -o gcovdir 生成web界面所需要的组件并且存储在gcovdir目录下。
4. 使用浏览器打开目录中的index.html就可以查看所有文件的覆盖率统计文件

## gcov测试说明
gcov工具只是会记录已执行代码行数的情况，但是由于某些测试条件的影响，有些正常代码执行次数也可以较少。例如将上述gcov_test.cpp文件中for循环中在添加一个条件`if(ltmp==5) {printf("测试gcov\n")}`,那么printf这句能执行到的次数极少。