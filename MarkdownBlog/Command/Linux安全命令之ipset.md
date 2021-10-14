# IPset

## IPset主要作用
1. 提供一些ip集合供iptables来使用
1. 减少iptables的配置条目
2. 大幅度的提高策略的匹配速率（100倍）

## 学习ipset

- **man ipset** #尽量使用网络来查看ipset的man手册，本地man手册可能缺少内容
- man手册中有具体的ipset类型

## 基本命令行使用
- `ipset create 名称 类型 [其他选项]` #创建某个类型的ipset
- `ipset add 名称 条目` #将某个条目加入到指定名称ipset
- `ipset del 名称 条目` #将某个条目从指定名称ipset删除
- `ipset test 名称 条目` #测试某个条目是否在指定名称ipset中
- `ipset destroy [名称]` #删除某个集合
- `ipset list [名称]` #输出所有或者指定set的数据
- `ipset save [名称]` #保存所有或者指定set数据
- `ipset restore`
- `ipset flush [名称]`
- `ipset rename 旧set_name 新set_name`
- `ipset swap 旧set_name 新set_name`

## iptables如何使用ipset
- `-m set --match-set set名称`

## ipset类型

ipset创建一个条目时需要指定相应类型

- 【TYPENAME】= 【method:datatype[,datatype[,datatype]]】
- 【methods】=【bitmap】【hash】【list】
- 【datatypes】=【ip】【net】【mac】【port】【iface】

## 注意问题
- 创建一个ipset后，如果没有给集合指定timeout选项，默认所有条目都不允许添加
- 如果指定timeout=90，添加的条目timeout>90也被认为是合法的

bitmap:ip

bitmap:ip,mac

bitmap:port

hash:ip
hash:mac
hash:net
hash:net,net
hash:ip,port
hash:net,port
hash:ip,port,ip
hash:ip,port,net
hash:ip,mark
hash:net,port,net
hash:net,iface