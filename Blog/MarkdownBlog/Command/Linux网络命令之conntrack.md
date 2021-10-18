# nf_conntrack模块

nf_conntrack是netfilter的连接跟踪模块,主要是对于流经主机的所有流量进行分析,获取其中一些五元组信息

## 参考文档
- [https://www.cnblogs.com/silvermagic/p/7666093.html](https://www.cnblogs.com/silvermagic/p/7666093.html)

## nf_conntrack和ip_conntrack区别

nf_conntrack模块在kernel 2.6.15（2006-01-03发布） 被引入,支持ipv4和ipv6,取代只支持ipv4的ip_connktrack,用于跟踪连接的状态,供其他模块使用。

## 如何使用nf_conntrack
稍后研究解释。

### nf_conntrack需要加载的模块
   
    modprobe br_netfilter
    modprobe nf_conntrack
    modprobe nf_conntrack_ipv4
    modprobe nf_conntrack_ipv6


## 连接跟踪记录
**连接存储目录:/proc/net/nf_conntrack**

nf_conntrack维护的所有连接信息都在此文件中,通过其中信息,可以分析出当前系统所流经的流量,同时也可以分析出当中有哪些实际的业务。此文件中每一行代表一条连接状态,默认情况下最大的状态连接数为65536,详细的配置数据位于*/proc/sys/net/netfilter/*目录下。我们主要关注每行连接状态不同字段的意义。介于TCP与UDP和ICMP有着本质的差异,我们分别查看这3种协议的不同点。

### 共性
不管协议种类如何,基本的记录格式如下（格式不尽相同）(各字段空格连接):   
`网络层协议名 协议编号 传输层协议名 传输层协议编号 老化剩余时间 连接状态 src_ip= dst_ip= src_port= dst_port= src_ip= dst_ip= src_port= dst_port= `

其中还有其他字段,TCP和UDP以及ICMP整体格式是不相同的,只能分情况讨论。

### TCP
#### IPv4
TCP各字段说明:   

    ipv4 2 tcp 6 299 ESTABLISHED src=192.168.10.101 dst=192.168.10.102 sport=55666 dport=502 src=192.168.10.102 dst=192.168.10.101 sport=502 dport=55666 其他字段...

1. ipv4代表IP层协议
2. 2代表ipv4的数字表示
3. tcp代表传输层协议
4. 6为tcp协议的数字表示
5. 299是老化时间,默认的tcp老化时间432000,具体参考/proc/sys/net/netfilter/下相应的配置
6. ESTABLISH代表当前的连接状态
7. src= 发起连接的源
7. dst= 数据目的IP
8. sport= 源端口
9. dport= 目的端口

### ICMPv6

`icmpv6 58 28 src=abcd::2 dst=abcd::1 type=128 code=0 id=3243 src=abcd::1 dst=abcd::2 type=129 code=0 id=3243 mark=0 secctx=system_u:object_r:unlabeled_t:s0 delta-time=5648 use=1`


## 获取命令行

**获取icmp的时候，需要指定协议为icmpv6**
conntrack -L conntrack -o timestamp -p TCP|UDP|ICMP|ICMP -f ipv4|ipv6 -u ASSURED

## conntrack命令说明
conntrack命令用来获取netfilter生成的连接状态。
conntrack获取的数据位于`/proc/net/nf_conntrack`.

### tables
- conntrack 默认表。包含当前主机生成的所有连接。

- expect 期望表。主要是针对于alg协议（双通道协议）。

### 命令选项
- `-L [table] [options] [-z]` #列出指定表中所有信息
- `-G [table] param` #获取指定内容的conntrack条目
- `-D [table] param` #删除指定内容的conntrack条目
- `-I [table] param` #创建指定内容的conntrack条目
- `-U [table] param` #更新条目
- `-E [table] [option]` #实时更新conntrack条目
- `-F [table]` #刷新整个表条目
- `-C [table]` #统计整个表的条目
- `-S`

### param
- `-z` #与-L一起使用,清空计时器
- `-o [extended,xml,timestamp,id,ktimestamp,labels]` #指定格式输出内容
- `-e [ALL|NEW|UPDATES|DESTROY][,...]` #与`-E`一起使用,设置标志位,用来筛选用户所需要的信息
- `-b value` #value的单位是字节,设置netlink套接字大小。在命令行工具报错**ENOBUFS**错误。设置的具体值在*/proc/sys/net/core/rmem_default*文件中。

### 过滤参数
- `-s IP` #在请求方向上指定源IP
- `-d IP` #在请求方向上指定目的IP
- `-r IP` #在应答方向上指定源IP
- `-q IP` #在请求方向上指定目的IP
- `-p PROTO` #指定四层协议
- `-f PROTO` #指定三层协议，只能与`-L`一起使用
- `-t timeout` #指定超时时间
- `-m MARK[/MASK]`