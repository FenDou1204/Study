<!-- TOC -->

- [arptables使用说明](#arptables使用说明)
  - [使用手册](#使用手册)
  - [Chains](#chains)
  - [Targets](#targets)
  - [Tables](#tables)
  - [Command](#command)
    - [规则选项](#规则选项)
    - [规则参数](#规则参数)
    - [mangle options](#mangle-options)
  - [arptables规则配置](#arptables规则配置)

<!-- /TOC -->

# arptables使用说明

arptables主要对于arp报文来进行控制。

目前arptables在大多数版本中是v0.0.0.4版本。其中的man手册和当前网页上的man手册在部分内容上较大差异的,在使用时需要注意.但是在大部分使用方法是相同的。

## 使用手册
**百度或google搜索`man arptables`得到最详细的介绍**。Linux系统下的手册具有一定参考价值，但是内容可能会有缺失。

[arptables官方手册](https://linux.die.net/man/8/arptables)

## Chains
**table filter**

- INPUT
- OUTPUT
- FORWARD（Linux kernels 2.6.0以后版本才有此链）

## Targets
- ACCEPT 接收符合规则的数据包
- DROP 丢弃符合规则的数据包
- QUEUE 将数据包直接传递给用户空间
- RETURN 结束在此链中遍历规则,继续后续链规则匹配；如果是到达最后一个匹配,不管是否匹配以当前链动作决定如何操作。

## Tables
- filter表
 
## Command
在使用下列所有参数之前,使用`-t tables`来指定相应的。

### 规则选项

- `-A chain 规则信息` #添加一条规则
- `-D chain 规则信息` #删除一条规则
- `-D chain 规则num` #根据行号删除一条规则
- `-I chain [规则num] 规则具体内容`
- `-R chain 规则num 规则具体内容`
- `-L [chain] 显示指定链规则`
- `-F [chain] 清空指定链规则（如果未选择链清空所有内容）`
- `-Z [chain] 清空指定链的包计数`
- `-N chain 创建一个自定义链`
- `-X chain 删除一个自定义链`
- `-P chain target 更改某一个链的默认动作`
- `-E old-chain new-chain 更改自定义链的名称`

### 规则参数

- `-s [!] IP/mask 指定源IP,可以使用【网络名、主机名、带掩码的一组IP地址或一个IP地址】,[!]代表为可选反转`
- `-d [!] IP/mask 用法类似-s`
- `-z [!] MAC/mask 指定源MAC`
- `-y [!] MAC/mask 指定目的MAC`
- `-i [!] nic_name 指定入网口(只针对INchain)`
- `-o [!] nic_name 指定出网口(只针对OUTchain)`
- `-a [!] value[mask] 指定数据包长度`
- `-p [!] value[mask] 指定arp种类`
- `-H [!] value[mask] 指定硬件类型种类`
- `-w [!] value[value] Specify the protocol type field of the packet`
- `-j target 匹配策略后的动作`
- `-c PKTS BYTES 初始化包、字节计数器（INSERT、APPEND、REPLACE使用）`
- `-n 将所有的显示转换为数字`
- `-x 显示所有的包数和字节数确切的值。需要伴随-L选项使用`
- `--line-numbers 显示规则的行号`
- `--modprobe=command 添加规则时加载重要的模块`

### mangle options
mangle是个target。

`arptables -A OUT -s aaa ! -d cccc -j mangle --mangle-ip-s  bbbb`

`--mangle-ip-s address`
`--mangle-ip-d address`


## arptables规则配置
- `arptables -t filter -A INPUT -j DROP`

