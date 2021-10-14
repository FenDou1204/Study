- [Centos 安装 Quagga](#centos-安装-quagga)
  - [Quagga 编译安装](#quagga-编译安装)
    - [安装](#安装)
    - [可执行程序及配置文件](#可执行程序及配置文件)
    - [修改端口和服务的对应关系](#修改端口和服务的对应关系)
  - [配置路由](#配置路由)
    - [通过 CLI 命令行配置](#通过-cli-命令行配置)
      - [zebra路由器参数配置](#zebra路由器参数配置)
      - [路由协议 RIP 配置](#路由协议-rip-配置)
    - [通过直接修改配置文件修改配置](#通过直接修改配置文件修改配置)
    - [验证方法](#验证方法)
    - [注意](#注意)
  - [配置组播转发](#配置组播转发)
    - [参考资料](#参考资料)
  - [错误解决方案](#错误解决方案)
    - [错误1](#错误1)
    - [错误2](#错误2)


# Centos 安装 Quagga

Quagga是一款功能比较强大的开源路由软件，支持rip, ospf，bgp等协议。可以通过Quagga生成、维护路有信息。

## Quagga 编译安装

### 安装
1. 下载quagga安装包 `wget http://download.savannah.gnu.org/releases/quagga/quagga-1.2.4.tar.gz`
2. 解压压缩包，并且入相应目录 `tar -xvf quagga-1.2.4.tar.gz; cd quagga-1.2.4`
3. 生成Makefile `./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root` #此操作在有些情况下会导致某个文件头部的 `shebang` 给删除掉，导致后续编译无法正常进行
4. 执行 `make && sudo make instll`

### 可执行程序及配置文件

1. 可执行文件目录为 `quagga-1.2.4/zebra`
2. 配置文件目录 `/usr/local/etc/` 。此目录下的配置文件需要把文件最后面的 `.sample` 去掉才可使用

### 修改端口和服务的对应关系

`/etc/services` 文件包含了服务名和端口号之间的映射，很多的系统程序要使用这个文件。一般情况下，不要修改该文件的内容；如果没有这些内容，需要将下述这些内容进行添加。

```bash
zebrasrv 2600/tcp # zebra service
zebra 2601/tcp # zebra vty
ripd 2602/tcp # RIPd vty
ripngd 2603/tcp # RIPngd vty   
ospfd 2604/tcp # OSPFd vty  
bgpd 2605/tcp # BGPd vty  
ospf6d 2606/tcp # OSPF6d vty  
ospfapi 2607/tcp # ospfapi  
isid 2608/tcp # ISISd vty
```

## 配置路由

配置zebra有两种方式，直接修改配置文件或者通过命令行配置。

终端执行 `zebra -d` 启动程序。按照前述安装过程，程序读取的配置文件为 `/usr/local/etc/zebra.conf`。

### 通过 CLI 命令行配置

#### zebra路由器参数配置

*zebra主要负责的是路由器的基本配置*，配置的 IP 等内容会在 Linux 设备所选择的网口进行配置。

1. 命令行执行 telnet 127.0.0.1 2601，连接到zebra配置命令行

	Password: 输入连接密码，默认为zebra   
	Router> 已经进入用户模式   
	Router> enable 进入特权模式的密码默认为zebra   
	Router# 已经进入特权模式   
	Router# config terminal 进入配置模式  
	Router(config)#   

2. 设置路由器名称
	
	Router(config)# hostname Router1   
	Router1(config)#

3. 配置密码

	Router1(config)# password zebra 配置终端连接密码   
	Router1(config)# enable password zebra 配置进入特权模式的密码  
	Router1(config)# service password-encryption 对口令进行加密

4. 配置路由器接口IP

	Router1(config)# interface eth0 一定要进入接口模式  
	Router1(config-if)# ip address 192.168.10.101/24 设定IP地址，子网掩码  
	Router1(config-if)# no shutdown 激活网络接口   
	Router1(config-if)# exit 退出   
	Router1(config)# interface eth1 添加第二个IP   
	Router1(config-if)# ip address 192.168.20.101/24 设置IP地址、子网掩码   
	Router1(config-if)# no shutdown 激活网络接口   
	Router1(config-if)# exit  
	Router1(config)# exit    
	Router1#copy run start   

#### 路由协议 RIP 配置

终端执行 `rip -d` 启动相应功能。

1. 命令行执行rip -d启动ripd，使用telnet 127.0.0.1 2602连接到cli命令行
2. 配置rip   

	Password: 输入默认密码zebra   
	ripd> enable #开启功能   
	ripd# configure terminal #系统配置模式   
	rip(config)# hostname r1_ripd #起个名字，没太大作用   
	r1_ripd(config)# router rip #启动rip   
    r1_ripd(config-router)# network 192.168.10.0/24   
    r1_ripd(config-router)# network 192.168.20.0/24 #查看英文文档没看明白说什么，感觉这里写实际网口ip也可以，没有影响；感觉是配置那个会从哪个网口来发送组播数据，也就是需要配置的是两个路由器相连接的端口；如果3个路由器，那么处于中间的一个就需要两个接口都配置
	r1_ripd(config)# log file "存放运行日志的路径"   
	r1_ripd# show ip rip status # 查看一些路由信息   
	r1_ripd# debug rip events    
	r1_ripd# debug rip packet	#开启一些日志输出    
	r1_ripd# copy run start #保存配置，写入到文件/usr/local/etc/下ripd.conf文件中        

### 通过直接修改配置文件修改配置

无论是配置 zebra 或 rip 或者其他功能，都可以在 `/usr/local/etc/` 目录中找到相应的配置文件，直接修改其中的配置文件。


### 验证方法

1. 使用tcpdump抓取两个路由器相连网口，能看到相应的组播数据包
2. 查看日志文件，能发现RECV和SEND两种提示

### 注意

需要注意是否有 iptables 等 linux 策略拦截数据包。


## 配置组播转发

需要启动pimd -d。

终端执行 `telnet 127.0.0.1 2611` 进入配置界面。

**未完待续，估计没后续了，有需求自行检索资料...**

### 参考资料
https://github.com/udhos/qpimd/blob/pim/pimd/COMMANDS
https://networkengineering.stackexchange.com/questions/26308/config-pimd-on-linux-to-forward-incoming-multicast-packet-to-openvpn-tunnel-inte
https://fossies.org/linux/quagga/pimd/README

## 错误解决方案

### 错误1

错误提示：
> configure: error: vtysh needs libreadline but was not found and usable on your system.`

解决办法：

```bash
sudo yum install -y readline-devel
```

### 错误2

错误提示：
    
>configure: error: Package requirements (libcares) were not met:
No package 'libcares' found
Consider adjusting the PKG_CONFIG_PATH environment variable if you
installed software in a non-standard prefix.
Alternatively, you may set the environment variables CARES_CFLAGS
and CARES_LIBS to avoid the need to call pkg-config.
See the pkg-config man page for more details.

解决办法:

```bash
wget https://c-ares.haxx.se/download/c-ares-1.14.0.tar.gz
tar -xzvf c-ares-1.14.0.tar.gz
./configure
make
make install 
cp libcares.pc /usr/local/lib/pkgconfig
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
```
