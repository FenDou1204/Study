# SHELL知识点梳理

## 终端输出

### echo 和 printf
1. echo会自动加入'\n',printf需要手动添加
2. printf使用方法和C语言printf()类似，可以有左右对齐等
3. 特殊的符号或者不确定的符号可以使用转义字符'\'来进行修饰
4. 使用echo和printf，选项位于所有内容之前
5. `echo -e "`包含转义字符的字符串"
6. 打印彩色输出:`echo -e "\e[1;31m      \e[0m"`,其中颜色30-37代表文本颜色,40-47代表背景颜色

## 环境变量
1. 获取进程的环境变量 `cat /proc/$PID/environ`
2. 获取进程的进程号 `pgrep 进程名`
3. 替换指令 `tr '\0' '\n'`
4. 由1输出的内容不太明显,需要将其中的'\0'更改为'\n'
5. export用来设置环境变量,环境变量设置后可以被所有进程来使用。
6. echo $PATH PATH是常用的环境变量

### eval关键字
- 示例:prepend() { [ -d "$2" ] && eval $1=\"$2':'\$$1\" && export $1; }
-使用说明: prepend PATH /opt/bin 给第一个参数配置环境变量为第二个。PATH="/opt/bin:$PATH"

## 普通变量
1. shell中变量是由=来赋值的,但是等号两侧不能有空格,A=1是赋值,A = 1已经是判断了。
2. 字符串普通变量的长度len=${#var}
3. echo {$SHELL|$0} 当前是哪种shell
4. UID是区分普通用户和root用户的环境变量,0代表root用户
5. 更改终端的提示字符串:终端输入PS1="BYD>"

## 数学运算
shell语言属于弱类型语言,创建的变量可以随便转换数据类型.

### 关键字加减
#### 基本算数操作
no1=4
no2=5

- let

使用let变量之前不能加$符号，表达式之间不能有空格


    let res=no1+no2   
    let no1++   
    let no1--    
    let no1+=6   
    let no1-=6   
    let no1=no1+6  
    let no1=no1-6

- (())

使用此运算符一定要记得加$，表达式对于空格没有要求，不会报错

    res=$(( no1 + no2 ))

- []

使用此运算符一定要记得加$，表达式对于空格没有要求，不会报错

    res=$[ no1 + no2 ]
    res=$[ $no1 + 5 ]

#### 高级算数操作
- expr

如果使用\`\`来执行加减呢，必须是整数，不能是变量   
如果使用$()来执行变量，但是必须注意参数之间必须有空格

    res=`expr 3 + 4`   
    res=$(expr $no1 + 5)

- bc

bc工具是用于数学运算的高级工具。

普通用法:

    res=`echo "4 * 0.45" | bc`
    res=`echo "$no1*9" | bc`

设定小数精度:(page 13)

    res=`echo "scale=2; 3/8" | bc` 设置为2位小数
    res=`echo "obase=2; $no1" | bc` 转为2进制数
    res=`echo "obase=10;ibase=2;$no1" | bc` ##测试

平方和平方根:

    res=`echo "sqrt(100)" | bc` 100的平方根
    res=`echo "10^10" | bc` 10的10次方

### 直接相加减

## 逻辑运算
`command1 | command2` #1的返回结果当作2的输入
`command1 && command2` #1的结果为真2才会执行
`command1 || command2` #1的结果为假2才会执行
`command1 ; command2` #执行完1就执行2

## 重定向

- 0 标准输入 stdin
- 1 标准输出 stdout
- 2 标准错误输出 stderr

重定向过多的不介绍,主要说标准错误输出怎么以标准输出来处理。








# shell第9章

## 进程相关

相关重要指令:top、ps、pgrep。

### ps

ps是收集进程信息的重要工具。它提供的信息包括：拥有进程的用户、进程的起始时间、进程对应的命令行路径、PID、进程所属的终端（TTY）、进程使用的内存、进程占用的CPU等

- `-f` full 显示更多的内容
- `-e` every 每个
- `-ax` all 所有

#### 常用选项
ps -e
ps -ef
ps -ax
pa -axf

#### 指定输出内容
ps -ef -o 选项1,选项2,...

选项可以是:

|-|-|
|pcpu|CPU占用率|
|pid|进程ID|
|ppid|父进程ID|
|pmem|内存使用率|
|comm|可执行文件名|
|cmd|简单命令|
|user|启动进程的用户|
|nice|优先级|
|time|累计的CPU时间|
|etime|进程启动后流逝的时间|
|tty|所关联的TTY设备|
|euid|有效用户ID|
|stat|进程状态|

#### 进程线程的相关信息
通常与进程线程相关的信息在ps输出中是看不到的。我们可以用选项 –L 在ps输出中显示
线程的相关信息。这会显示出两列：NLWP和NLP。NLWP是进程的线程数量，NLP是ps输出中
每个条目的线程ID。

### top
top指令会每隔几秒刷新出来cpu占用率的进程。
使用时需要man top来查看，但是常见的排序等内容需要

### pgrep
获取指定进程的pid号

### which
查找某个**指令**的位置，只会在$PATH环境变量下查找

### whereis
类似于which，在which基础上会返回man手册位置以及源代码(如果有)

### file 
确定文件的类型

### whatis
whatis命令会输出作为参数的命令的简短描述信息

### apropos
有时候我们需要搜索和某个单词相关的命令是否存在。那么可以
搜索包含该字符串命令的手册页。

### 平均负载
uptime指令。
uptime可以显示系统的启动时间。平均负载是系统总负载量的一个重要参数。它指明了系统中可运行进程总量的平均值。平均负载由三个值来指定，第一个值指明了1分钟内的平均值，第二个值指明了5分钟内的平均值，第三个值指明了15分钟内的平均值。

## kill和killall
类Unix环境中与进程相关的一个重要概念就是信号。信号是一种进程间通信机制，它用来中断运行中的进程以执行某些操作。终止程序也是通过使用信号技术来实现。

- 每一个信号都与一个整数值相关联
- 进程接收信号会有相应的处理函数来执行
- kill命令用于终止进程的信号

**kill命令可用来向进程发送信号，trap命令用来处理所接收的信号。**

### kill指令详解
- kill -l #输出所有的信号编号以及信号名称
- kill PID PID1 ... #默认发出一个TERM信号，空格区分多个进程
- kill -s SIGNAL PID #向指定进程发送信号，可以是信号名称也可以是信号编号

### 常用进程编号
SIGINT 2 ctrl+c 
SIGKILL 9 强行kill进程
SIGTERM 15 终止进程

### killall指令
- killall PROCESS_NAME
- killall -s SIGNAL PROCESS_NAME 
- 强行kill进程:killall -9 PROCESS_NAME
- 通过名称以及所属用户名指定进程：$ killall -u USERNAME process_name
- 如果需要在杀死进程前进行确认，可以使用killall的-i选项

### pkill指令
- 用法类似于kill
- pkill PROCESS_NAME
- pkill不接受信号名称

### trap命令
trap命令在**脚本**中用来为信号分配信号处理程序。一旦使用trap将某个函数分配给一个信号，那么当脚本运行收到该信号时，其对应的函数就会开始执行。

使用方法:`trap 'signal_handler_function_name' SIGNAL LIST`

用法举例:
    
    function handler()
    {
        echo "received signal"
    }
    trap 'handler' SIGINT或者其他信号
    #保证此脚本可以处于一直运行状态，发送相应信号，就可以出发handler中的函数。


## 向用户终端发送消息
wall命令用来向当前所有登录用户的终端写入消息。它可以将消息传递给一台服务器中所有的登录用户或是多台分散主机中的用户。给所有的用户发送消息未必总是靠谱。在Linux系统中，终端是作为设备存在的。因此那些打开的终端在/dev/pts/中都会有对应的设备节点文件。向特定的设备写入数据将会在对应的终端中显示出消息。

- root用户可以不需要开启直接发送消息
- 允许写入消息，使用mesg y
- 禁止写入消息，使用mesg n
page 277
这个主要涉及的文件/dev/pts.

## 获取系统信息
- 当前系统主机名:`hostname`或者`uname -n`
- linux内核版本、架构信息:`uname -a`
- linux内核发行版本:`uname -r`
- 主机类型:`uname -m`
- CPU相关信息:`cat /proc/cpuinfo`
处理器名称:`cat /proc/cpuinfo | sed -n 5p` #文件第五行是cpu信息
- 内存信息:`cat /proc/meminfo`
可用内存总量:`cat /proc/meminfo | head -l`
- 系统分区信息:`cat /proc/partitions`或者`fdisk -l`
- 获取系统详细信息:`lshw`

## proc系统
- /proc是一个在内存中的伪文件系统（pseudo filesystem）。它的引入
是为了提供一个可以从用户空间读取系统参数的接口。
- 系统中每一个运行的进程在/proc中都有一个对应的目录。目录名和进程ID相同。

在相应的进程目录下
1. environ：包含与进程相关的环境变量。使用cat /proc/4295/environ，可以显示所有传递给该进程的环境变量。
2. cwd：是一个到进程工作目录（working directory）的符号链接。
3. exe：是一个到当前进程所对应的可执行文件的符号链接。
4. fd：包含了进程所使用的文件描述符。

## cron调度工具
我们经常会需要安排脚本在某个时间或每隔一段时间来运行。所有的GNU/Linux发布版默认都包含了cron调度工具。只要在cron表中写入条目，对应的命令就会在指定的时间执行。crontab命令用来添加作业（job）。cron表不过是一个简单的文本文件而已，每位用户都有自己的副本。

示例:
02 * * * * /home/slynux/test.sh

cron表中的每一个条目都由6部分组成，并按照下列顺序排列：
分钟（0～59） 小时（0～23） 天（1～31） 月份（1～12） 工作日（0～6） 命令（在指定时间执行的脚本或命令）

### 使用方法
- `crontab -e`默认使用vi打开cron表
- 最好使用root权限执行
- cron作业中指定的命令需要使用完整路径
- 系统启动时执行命令：要在启动时运行命令，将下面一行加入crontab：
`@reboot command`
- `crontab -l` 展示当前系统中的启动任务
- `crontab -r` 删除当前用户的cron表

## Bash读取MySQL数据库
chapter 9.8

### shell登录mysql

    简单写个模拟示例:
    USER="user" #登录数据库用户名
    PASSWORD="pass" #登录数据库密码
    
	#登录数据库
    mysql -u $USER -p$PASSWORD {--default-character=utf8 等其他登录参数} <<EOF 2>/dev/null
    #创建表
    CREATE DATABASE students；
	EOF

其他基本的操作包括增删改查、创建表、设置标参数等等一些列数据库内容操作都可以通过上述类似操作进行完善，基本只需要修改两个EOF之间的内容即可，剩余内容都是mysql操作。

## ImageMagick软件包

### 图像文件的缩放及格式转换

convert指令，来自Imagemagick软件包。

格式转换:
  
- convert file1.png file2.png
   
缩放图像：
     
- convert file1.png -resize WIDTHxHEIGHT file2.png   
必须提供WIDTH或HEIGHT参数的一个，以方便来按比例进行缩放。   

按比例来缩放图像:

- convert image1.png -resize "50%" image2.png

### 终端截图
import 工具来进行截图   

取整个屏幕：
   
- import -window root screenshot.png
   
手动选择部分区域进行抓取:
    
- import screenshot.png
   
抓取特定窗口：   
- import -window window_id screenshot.png
使用命令xwininfo,点击需要抓取截图的窗口来获得window_id 。然后将window_id传递给import命令的-window选项。

## 管理多个终端

GNU screen软件包

使用screen可以打开多个终端。

- ctrl+A+C 新打开一个终端
- ctrl+A+ 查看已经打开的所有终端
- Ctrl+A或者ctrl+N 切换到下一个接口
- Ctrl+A或者ctrl+P 切换到下一个接口
- 关联与脱离screen：screen具备一个有用的特性，能够让你保持、载入screen会话，用screen的术语来说，叫做脱离（detaching）与关联（attaching）。使用Ctrl+A和Ctrl+D脱离当前screen
会话。要关联到一个已有的screen会话，可以使用：screen –r –d
该命令告诉screen关联到上一个screen会话。如果已脱离的会话不止一个，screen会用列表输出会话，然后可以使用下述命令：screen –r –d PID。这里，PID是你想关联到的screen会话的PID。

# shell第8章

## 监视系统磁盘使用情况

指令默认结果都是以字节来标识大小

df和du指令

df = disk free
du = disk usage

### du命令

#### 基本使用方法
- `du -a test/` #显示test目录每个文件大小
- `du test/` #显示目录的总体大小
- `-h` #默认输出为B，-h会根据情况输出相应单位
- `du -c file|dir` #在输出结果后添加一行总量的输出
- `du -s file|dir` #只输出总量结果
- `du -b|-k|-m|<-B 大小> file|dir` #-b字节输出 -k千字节输出 -m兆字节输出 

#### 排除统计文件
- `du --exclude "文件名|正则表达式" dir` #排除一个文件
- `du --exclude-from EXCLUDE.txt dir` #EXCLUDE.txt是排除文件列表
- `du --max-depth 2 dir` #遍历两层目录
- `du -ak SOURCE_DIR | sort -nrk 1 | head` #遍历某个目录找出最大文件，包含目录大小
- `find . -type f -exec du -k {} \; | sort -nrk 1 | head` #遍历某个目录找出最大的文件
- `df -h` 查看硬盘的使用情况

### time命令
time命令主要用来查看执行某个程序所需要消耗的时间。

**time命令的可执行二进制文件位于/usr/bin/time，还有一个
shell内建命令也叫做time。当运行time时，默认调用的是shell的
内建命令。shell内建的time命令选项有限。因此，如果我们需要
使用另外的功能， 就应该使用可执行文件time 的绝对路径
（/usr/bin/time）。**

- `time 程序` 
- `/usr/bin/time -o 保存文件名 执行命令`
- ``

#### 使用time指令输出结果后的时间介绍
- Real时间指的是挂钟时间（wall clock time），也就是命令从开始执行到结束的时间。这段时间包括其他进程所占用的时间片（time slice）以及进程被阻塞时所花费的时间（例如，为等待I/O操作完成所用的时间）。
- User时间是指进程花费在用户模式（内核之外）中的CPU时间。这是唯一真正用于执行进程所花费的时间。执行其他进程以及花费在阻塞状态中的时间并没有计算在内。
- Sys时间是指进程花费在内核中的CPU时间。它代表在内核中执行系统调用所使用的时间，这和库代码（library code）不同，后者仍旧运行在用户空间。与“user时间”类似，这也是真正由进程使用的CPU时间。

#### who、w、users、uptime、last、lastb
上述命令主要用来维护系统