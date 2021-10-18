# IPv6地址冲突检测

## 问题由来


## 解决方案
关于ipv6IP冲突导致的IP不可用问题

在母盘/etc/sysctl.conf中加入下列内容:
net.ipv6.conf.default.accept_dad=0
net.ipv6.conf.eth0.accept_dad=0
net.ipv6.conf.eth1.accept_dad=0
net.ipv6.conf.eth2.accept_dad=0
net.ipv6.conf.eth3.accept_dad=0
net.ipv6.conf.eth4.accept_dad=0
net.ipv6.conf.eth5.accept_dad=0
net.ipv6.conf.all.accept_dad=0
