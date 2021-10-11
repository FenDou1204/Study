# 如何测试ipv6组播情况下PMTU




## ipv6组播转发

感觉此部分并不是重点

https://blog.csdn.net/bestjie01/article/details/89639197
echo 1 > /proc/sys/net/ipv6/conf/all/mc_forwarding

## 查看当前设备加入的组播组

linux: netstat -gan   
windows: netsh interface ipv4 show joins

## ptmu知识点

1. 姑且认为这篇文章讲的pmtu是正确的  https://www.jianshu.com/p/3bd05c37d3b0
2. ipv6最小mtu为1280

## 测试pmtu步骤（未确认)

1. 设置A设备的某一个网口eth1的最大mtu为1500(默认值)
2. 设置B设备的某一个网口eth2的最大mtu为1400(手动设置)
3. A和B设备加入同一个组播组(感觉会自行设置，不需要手动配置)
4. 在未知iptables、arptables、ebtables以及SElinux等策略是否会对组播包有影响的情况下，清空关闭上述所涉及到的全部策略
5. 如何判断此数据包放过进入内核，需要搭建一个环境，环境比较单纯，能够配置关于组播的配置，保证数据包已经到内核,在ip6tables配置一个INPUT链的策略，是组播包就放过
6. test1  A设备发送一个数据包mtu=1500   会返回icmp error
7. test2  A设备发送一个数据包mtu=1400   不会返回任何东西 