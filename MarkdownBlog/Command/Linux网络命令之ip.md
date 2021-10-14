# ip命令

新一代网络管理工具,可以替代以前的ifconfig，arp，route等命令，来设置以及维护系统中的设备网络信息

## ip route
命令等价于linux下route，windows下route print命令。
- ip route show
- ip route get IP #判断某个IP所走的路由
- ip route add default via IP dev NIC #添加一条默认网关，需要指定出接口
- ip route add 172.18.202.2 via IP dev NIC #配置一条静态路由

## ip link
- ip -s -s link ls NIC #显示指定网卡的收发包情况
- ip -s link show #显示所有网卡的收发包情况

- ip link show {NIC} #显示所有网卡的信息
- ip link set NIC [up|down] #设置网卡开启/关闭状态

## ip neigh
- ip neigh show
- ip neigh add 192.168.10.100 lladdr 11:11:11:11:11:11 dev eth0
