# ebtables使用说明

以太网桥接帧表管理.

ebtables是以太网桥防火墙，工作在数据链路层，主要对于设备桥模式下的流量控制。

ebtables在linux系统中更新获取的版本是v2.0.10-4。网页的man手册用的版本是v2.0.9-1。可能会有一些差异。

## 使用手册
**百度或google搜索`man ebtables`得到最详细的介绍**。Linux系统下的手册具有一定参考价值，但是内容可能会有缺失。

## 链位置
![](https://i.imgur.com/pV3EZbQ.jpg)

参考具体的数据链位置能够有效的配置相应的策略。

## Chains
**table broute**

- BROUTING

**table nat**
   
- PREROUTING
- OUTPUT
- POSTROUTING

**table filter**

- INPUT
- FORWARD
- OUTPUT

## Targets
### 正常情况下Targets使用

- ACCEPT 允许帧通过
- DROP 丢弃数据帧
- CONTINUE 跳过当前规则，匹配下一条
- RETURN 停止在当前链进行匹配，到下一链进行匹配

### 特殊情况下Targets使用
**BROUTING链的处理**
broute用于制作一个brouter，它有一个内置链：BROUTING。目标DROP和ACCEPT在broute表中具有特殊含义（使用这些名称而不是更具描述性的名称来保持实现通用）。DROP实际上意味着必须路由帧，而ACCEPT意味着帧必须被桥接。BROUTING链很早就被遍历了。但是，它只能通过进入处于转发状态的桥接端口的帧来遍历。通常情况下，这些框架会被桥接，但您可以在此处另行决定。重定向目标在这里非常方便。

## Tables
- filter表
- nat表
- broute表

## Command
配置策略之前,使用`-t tables`指定所操作的tables。

- `-A chain 规则信息` #追加一条策略
- `-D chain 规则信息` #根据内容删除一条策略
- `-D chain start_line[:end_line]` #根据行号删除一条或者多条规则
- `-C chain start_line[:end_line]` #根据行号清空一条或者多条规则的统计计数
- `-I chain [line_num]` #根据行号指定插入一条规则
- `-P chain {ACCEPT|DROP|RETURN}` #修改指定链的默认动作？
- `-F [chain]` #根据chain清空所有规则
- `-Z [chain]` #清空某个链的计数
- `-L [chain]` #显示所有的链规则
- `-N UserChain` #创建新链
- `-X UserChain` #删除创建的链
- `-E oldChain newChain` #重命名一个链

- `--init-table`
- `--atomic-init`
- `--atomic-save`
- `--atomic-commit`

### 规则参数
- `-j {target}` #规则的处理动作(ACCEPT,DROP,CONTINUE,RETURN或者用户自定义链)
- `-M {内核模块}` #使用规则时添加一个内核模块
- `-p [!] {protocol}` #指定协议
- `-i [!] {nic_name}` #接收数据帧的网口(INPUT、FORWARD、PREROUTING、BROUTING)
- `--logical-in [!] {bridge_name}` #接收数据帧的桥接口(INPUT、FORWARD、PREROUTING、BROUTING)
- `-o [!] {nic_name}` #发送数据帧的网口(OUTPUT、FORWARD、POSTROUTING)
- `--logical-out [!] {bridge_name}` #发送数据帧的桥接口(OUTPUT、FORWARD、POSTROUTING)

- `-s [!] MAC[/mask]` #源mac
- `-d [!] MAC[/mask]` #目的mac
- `-c pcnt bcnt` #############################

### 其他协议支持

#### 802_3

#### among

#### arp


#### ip
使用前提:必须指定协议为IPv4(`-p IPv4`).
- `--ip-source [!] address[/mask]` #(--ip-src)源IP
- `--ip-destination [!] address[/mask]` #(--ip-dst)目的IP
- `--ip-tos [!] tos` #IP类型的服务,十六进制数
- `--ip-protocol [!] protocol` #(--ip-proto)IP协议

**使用下述两项必须指定上一项**
- `--ip-source-port [!] port1[:port2]` #(--ip-sport)源端口
- `--ip-destination-port [!] port1[:port2]` #(--ip-dport)目的端口

#### ip6
使用前提:必须指定协议为IPv6(`-p IPv6`).
- `--ip6-source [!] address[/mask]` #(--ip6-src)源IP
- `--ip6-destination [!] address[/mask]` #(--ip6-dst)目的IP
- `--ip6-tclass [!] tos` #IP类型的服务,十六进制数
- `--ip6-protocol [!] protocol` #(--ip6-proto)IP协议

**使用下述两项必须指定上一项**
- `--ip6-source-port [!] port1[:port2]` #(--ip6-sport)源端口
- `--ip6-destination-port [!] port1[:port2]` #(--ip6-dport)目的端口


#### vlan
需要`-p 802_1Q`指定相应的协议

- `--vlan-id [!] id`
- `--vlan-prio [!] prio`
- `--vlan-encap [!] type`