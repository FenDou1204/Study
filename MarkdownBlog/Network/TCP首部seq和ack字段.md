# TCP首部seq和ack

seq和ack是TCP头部中的两个标志位。TCP回话的每一端都包含一个32位的序列号，序列号被用来跟踪该端发送的数据量。在接收端则通过确认号通知发送端数据的成功接收。

开始一个TCP会话时，初始序列号是随机的，大小为0-4294967295之间的任意值。

## 三次握手中seq和ack的变化情况

假如A和B进行通讯，A是主动端，B是被动端。

```
A -> B	seq=0 ack=0 (SYN包) (seq是随机产生的,这里默认为0)
B -> A	seq=0 ack=1 (SYN、ACK包) B的ack是A的seq+1(seq是随机产生的,这里默认为0)
A -> B	seq=1 ack=1 (ACK包) A的seq是A的上一个seq+1,A的ack是B的seq+1
```

现在看，默认情况在TCP三次握手期间seq和ack变化都符合上述规律。

## 数据传输中的变化情况

三次握手结束后,开始进行数据传输。A主动给B进行数据传输。

```
理论值:
A -> B	seq=1 ack=1 应该还是接上述的seq和ack的数值，并没有变化，传输的数据长度为19
B -> A	seq=1 ack=20 B的seq变为A的ack，ack变为A的seq加上数据长度。
B -> A	seq=1 ack=20 数据长度为90
A -> B	seq=20 ack=91 A的seq变为B的ack，ack变为B的sql加上数据长度。

实际数据包:
A -> B	seq=492 ack=590 数据长度为12
B -> A	seq=590 ack=504 seq为A数据包的ack,ack为A数据包seq+12,数据长度15
A -> B	seq=504 ack=605 seq为B的ack,ack为B的seq+15=605，数据长度为30
B -> A	seq=605 seq=534 无数据长度

```

## 保活过程中seq和ack的处理
tcp保活过程以最后一次发数据的seq和ack为准,会一直发送相同的数据包

	B -> A	seq=101	ack=809 数据长度123
	A -> B  seq=809 ack=224 保活包
	B -> A	seq=224 ack=810 保活确认
	A -> B	seq=809 ack=224 保活包
	B -> A	seq=224 ack=810 保活确认
	A -> B	seq=809 ack=224 保活包
	B -> A	seq=224 ack=810 保活确认
	A -> B	seq=809 ack=224 保活包
	B -> A	seq=224 ack=810 保活确认
	
	保活包一直会重复上述流程



## 一直一方持续发送数据
目前有个疑问,传输中间的数据B没有给A应答，能否保证所有数据都能够收到？

	A -> B seq=30 ack=90 len=0
	A -> B seq=30 ack=90 len=30
	A -> B seq=60 ack=90 len=30
	A -> B seq=90 ack=90 len=30

## 四次挥手时的情况
四次挥手和三次握手还是有一定的类似

	B -> A seq=90 ack=120 len=0 ACk
	A -> B seq=120 ack=90 len=0 FIN、ACK
	B -> A seq=90  ack=121 len=0 FIN、ACK
	A -> B seq=121 ack=91 len=0 ACK
	

## seq和ack的记录方式
在修改数据包应用层长度时，由于要替换某些应用层字符，导致应用层数据长度发生了变化，如果不修改相应的seq和ack值，导致数据包出现错误。此处值得数据包长度只包含应用层的长度。