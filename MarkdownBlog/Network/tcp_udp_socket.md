# TCP和UDP

## TCP通讯流程

|-|-|-|-|
|client|-|server|-|
|-|-|-|-|
|socket()|创建client端socket|socket()|创建server端socket|
|bind(client可省略)|-|bind()|选择监听的IP与端口|
|-|-|listen()|开始监听所绑定的IP和PORT(阻塞等待)|
|connect()|连接到server端地址|-|-|
|||accept()|等待client来进行连接|
|send()|-|recv()|-|
|recv()|-|send()|-|
|close()|client在使用close函数时，server端的recv()函数返回值会变为0|-|-|
|-|-|recv()=0|client端调用close()函数后，此时server返回0|
|-|-|close()|此时调用close关闭已经建立的连接,等待下次连接的建立,(阻塞到listen())|

TCP是面向连接的数据传输，主要是传输可靠，不存在丢包或者什么情况，主要的缺点可能就是传输慢(对于日常用户足够,慢只是相对于UDP传输方式)。

### 通讯描述
一般情况，server端会监听某个指定的端口，等待client来连接指定端口，**server端必须要使用bind来绑定一个地址以及端口**。绑定端口后server端会使用listen(默认为阻塞)来监听是否有连接连入此端口。client使用connect()建立一个连接，建立连接后就可以使用recv()和send()函数来进行数据的收发。需要注意的是recv()函数的返回值。**在最初的判断中何时断开连接是通过判断一个特殊的数据包来进行标识**，但是想想应该是有某一个未了解的机制来帮助实现此功能，那么也最有可能是recv()函数来实现。

### recv函数

### send函数

## UDP通讯流程
|-|-|-|-|
|client|-|server|-|
|-|-|-|-|
|socket()|创建client端socket|socket()|创建server端socket|
|bind(client可省略)|-|bind()|选择监听的IP与端口|
|sendto()|-|recvfrom()|-|
|recvfrom()|-|sendto()|-|
|close()|client在使用close函数时，server端的recv()函数返回值会变为0|close()|此时调用close关闭已经建立的连接,等待下次连接的建立,(阻塞到listen())|

### 通讯描述

### sendto

### recvfrom

## 特殊说明
sendto = send
recvfrom = recv
其实这两个函数可以互相代替使用(跟是否为TCP、UDP无关)。

## 编码使用
inet_addr() 将字符串IP地址转化为网络字节序 
htons() 将本地端口转换为网络序【不可以使用htonl,因为结构体中是short类型】

## 参考博客
- [https://blog.csdn.net/keheinash/article/details/52069471](https://blog.csdn.net/keheinash/article/details/52069471) 此博客主要对于recv的返回值进行了讲解，而且其有很大的帮助作用

## 套接字
套接字的本质类似于创建了一段空间，其中包含着一些网络传输的消息，包括bind绑定的ip和port等内容。我们通过套接字发送的内容并不是真正将数据发送出去，最终真正发送数据还是需要协议栈来完成