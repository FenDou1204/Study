# shell常见知识点

## shell特殊变量
|-|-|
|变量|含义|
|$0|脚本名称|
|$n|(1-n)脚本的传参|
|$#|除$0的参数总个数|
|$*|传递给脚本或参数的参数|
|$@|传递给脚本或参数的参数|
|$?|上个命令退出状态|
|$$|当前shell的进程ID|

### $*和$@的区别
`$*`和`$@`都表示传递给函数或脚本的所有参数，不被双引号(" ")包含时，都以"$1"、"$2" … "$n" 的形式输出所有参数。

但是当它们被双引号(" ")包含时，"$*" 会将所有的参数作为一个整体，以"$1 $2 … $n"的形式输出所有参数；"$@" 会将各个参数分开，以"$1" "$2" … "$n" 的形式输出所有参数。  

脚本内容:

	#!/bin/bash
	echo "\$*=" $*
	echo "\"\$*\"=" "$*"
	echo "\$@=" $@
	echo "\"\$@\"=" "$@"
	echo "print each param from \$*"
	for var in $*
	do
	echo "$var"
	done
	echo "print each param from \$@"
	for var in $@
	do
	echo "$var"
	done
	echo "print each param from \"\$*\""
	for var in "$*"
	do
	echo "$var"
	done
	echo "print each param from \"\$@\""
	for var in "$@"
	do
	echo "$var"
	done

## 常用的正则
## 字符串多空格压缩为一个空格
`sed 's/  */ /g'`	#单纯包含空格
`sed -e 's/[[:space:]][[:space:]]*/ /g'`	#tab、空格等混用

## shell判断文件为空

shell提供了判断文件是否存在、读写等权限的方法，一般使用在判断语句

1. `-e filename` 如果 filename存在，则为真 
1. `-d filename` 如果 filename为目录，则为真 
1. `-f filename` 如果 filename为常规文件，则为真 
1. `-L filename` 如果 filename为符号链接，则为真 
1. `-r filename` 如果 filename可读，则为真 
1. `-w filename` 如果 filename可写，则为真 
1. `-x filename` 如果 filename可执行，则为真 
1. `-s filename` 如果文件长度不为0，则为真 
1. `-h filename` 如果文件是软链接，则为真

类似用法:

    if [ ! -e file ]   
    then   
        touch file   
    fi  

## shell函数
shell也可以实现自己的函数

	在最近的脚本编写中，定义函数在前面都加入了function。
    function myfunction()
    {
        echo $1
        return 98
    }

- 获取echo返回值为RET=$(myfunction 参数1 参数2)
- 获取return返回值直接使用$?

子字符串
https://blog.csdn.net/zbw18297786698/article/details/77455599