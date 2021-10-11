# OPENFEC编译使用

## openfec介绍
openfec是由C语言编写的开源喷泉码库。openfec是前向纠错码中(喷泉码)的一种实现方法。简单介绍一下前向纠错码:**假设要无反馈发送一块数据共100个字节，发送方将100个字节分为10块，并且通过这10个原始数据块额外生成10个冗余数据块，10个冗余数据块包含10个原始块中的部分数据；当接收方收到任意10个数据块后，即可将100个字节完全恢复，在丢包情况下能够极大的保证数据的完整性。**

## openfec编译
此节介绍openfec的安装包来源以及安装方式。

关于编译和使用过程，可以参考解压openfec安装包后产生的README文件。

### 安装编译
编译DEBUG级别的openfec动态库(有DEBUG日志输出)

1. `wget http://www.openfec.org/files/openfec_v1_4_2.tgz` #从官方渠道获取openfec安装包
2. `tar -xzvf openfec_v1_4_2.tgz` #解压安装包
3. `yum -y install cmake` #安装cmake编译工具
4. `cd openfec_v1_4_2`
5. `cd build_debug` #进入安装包下一级目录,此时此目录为空
6. `cmake ../ -DDEBUG:STRING=ON` #进行生成Makefile等操作
7. 此时生成的makefile等内容位于*build_debug*目录下
8. 在此目录下继续执行`make`进行编译

编译RELEASE级别的动态库(无DEBUG日志输出)

1. 前4步同上述过程
2. `cd build_release`
3. `cmake ../ -DDEBUG:STRING=OFF` #进行生成Makefile等操作
4. 在此目录执行`make`操作

由此生成的动态库不包含任何的DEBUG日志输出。

## openfec生成文件
### 生成文件
1. 执行上述8步骤后,会在`openfec_v1.4.2/bin/Debug/`生成openfec的接口动态库,同时还有生成一些示例代码生成的二进制文件
2. 包括`eperftool`、`simple_client`、`simple_server`、`test_code_params`、`test_create_instance`、`test_encoder_instance`五个二进制文件
3. 2中所述5个二进制文件的源码分别位于`openfec_v1.4.2/tests/`和`openfec_v1.4.2/applis/`两个目录下

## 示例代码功能解析
主要分析`openfec_v1.4.2/applis/howto_examples/`目录中关于模拟socket传输的编码和解码功能。编译的结果存储于`openfec_v1.4.2/bin/Debug/`目录中。


## 如何使用openfec

### 开源组件的必须包含内容
**of_openfec_api.h**头文件，头文件中包括所需要的各接口函数的具体说明，同时还需要连接相应的动态库，


### 生成数据原理

|-|-|
|源码|k|
|冗余块|n-k|
|编码后|n|

openfec采用的原理如下:当前有k个源码块，按照特定的编码率生成n个编码块，生成的冗余块为n-k个。当发送端将这些所有的数据块发送，只要接收端接收到大于k个数据块（不管是原来的k个，还是源码块+冗余块>k个），即可将原来的k个源码数据进行完全恢复。

### Linux下编码实现思路

- 假如当前要传输数据共1025个字节
- 分成每个块为64字节的数据包传输（1025/64=17）
- 通过这17个源码块产生9个冗余码，一共26个编码后数据块，每个数据块都包含*数据原长度1025字节*，*每个块大小64字节*，*源码块17个*，*编码后块数26个*，*块的数据编号（必不可少）*，*使用的编码方法（openfec按照编码块数的不同提供了两种编码方式）*


### 编码模块



### 解码模块