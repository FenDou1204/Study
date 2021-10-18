# Iptables使用介绍

## 参考文档
- [http://www.zsythink.net/archives/category/%E8%BF%90%E7%BB%B4%E7%9B%B8%E5%85%B3/%E9%98%B2%E7%81%AB%E5%A2%99/](http://www.zsythink.net/archives/category/%E8%BF%90%E7%BB%B4%E7%9B%B8%E5%85%B3/%E9%98%B2%E7%81%AB%E5%A2%99/)
- [https://blog.csdn.net/achejq/article/details/53067170](https://blog.csdn.net/achejq/article/details/53067170)
- 你好
## iptables介绍
iptables是linux下的防火墙，开源组织netfilter.org项目。iptables相当于下发策略的工具，具体功能是由netfilter实现。

## 数据包在本机的处理流程

						----->----->上层协议栈----->---->-----
						^									|
						|									v
						|								 路由判决
					  INPUT	      							|
						|									v
						|								  OUTPUT
						^									|
						|									v
      -->PREROUTING-->路由判决--------->FORWARD-------->POSTROUTING-->数据包出口-->




本地网卡接收到数据包会判断此数据包是否要本地（目的MAC是本地网卡的MAC地址）处理的（本地处理或者转发处理）。网卡收到数据后确认是本地数据包，会将数据包拷贝到内核模块

## 四表五链


### 表介绍（tables）
表中存的是配置的策略（匹配的规则），数据包经过

|-|-|-|
|表名|表的作用|内核模块|可被使用的链|
|raw|数据包是否被状态连接追踪机制处理|iptable_raw|PREROUTING、OUTPUT|
|mangle|拆解、修改、重新封装报文|iptable_mangle|PREROUTING、INPUT、FORWARD、OUTPUT、POSTROUTING|
|nat|网络地址转换功能|iptable_nat|PREROUTING、INPUT、OUTPUT、POSTROUTING|
|filter|负责过滤功能，防火墙|iptable_filter|INPUT、FORWARD、OUTPUT|

### 链介绍（chains）
链相当于数据包处理流程的节点

|-|-|
|链名|作用域|可使用的表规则|
|INPUT|接收到本机地址的数据包时（入站）|filter、mangle|
|OUTPUT|防火墙本机向外发送数据包时（出站）|raw、mangle、nat、filter|
|FORWARD|接收到通过防火墙发送给其他地址数据包时（转发）|filter、mangle|
|PREROUTING|对数据包做出路由选择之前（DNAT）|raw、mangle、nat|
|POSTROUTING|对数据包做出路由选择之后（SNAT）|mangle、nat|



### 优先级
在一条链中可以使用多个表中的规则，表的优先级是不同的:**raw>mangle>nat>filter**。
例如:INPUT链中可以使用mangle、nat、filter三个表中的内容。如果mangle、nat、filter表中都有配置的策略，最先匹配的策略是mangle表中的内容。


## iptables指令

### 指令选项
- `-t` 指定所操作的表，默认是filter表
- `-A` 添加的规则到规则表尾
- ``
- `-I` 添加的规则到规则表头
- `-L` 列出链所有规则
- `-L INPUT|OUTPUT` #指定相应链
- `-n` 不对IP地址进行反解,显示IP地址
- `-v` 显示详细信息，包括流量什么的
- `-x` 显示精确的数值,例如接收多少数据包会显示精确个数
- `--line` 显示行数
- `-E` 创建新链
- `-E 旧自定义链名称 新自定义链名称` 修改自定义链名称

### 常用指令
- `iptables -nL` 显示默认表filter中内容
- `iptables -t mangle -N HA` 创建自定义链
- `iptables -F` 清空默认表filter中内容
- `iptables -X 自定义链` 删除自定义链
- `iptables -D INPUT 1` 删除INPUT链filter表第一条策略



## 规则
规则由**匹配条件**和**动作**两部分组成。

### 匹配条件
#### 基本匹配条件
- 源IP
- 目的IP

#### 扩展匹配条件
- 源端口
- 目的端口

### 动作
- ACCEPT #允许数据包通过
- DROP #丢弃数据包，不给请求方任何应答
- REJECT #拒绝数据包，必要时会回复相应的拒绝信息
- SNAT #做SNAT
- MASQUERADE #SNAT特殊
- DNAT #做DNAT
- REDIRECT #本机做端口映射
- LOG #记录下日志信息

### 操作学习

