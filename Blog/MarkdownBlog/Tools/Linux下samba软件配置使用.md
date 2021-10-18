# samba服务介绍使用

## netbios概念

### 查看netbios信息

win下使用nbtstat和net命令来查看相应信息。

- nbtstat -a {netbios名称}
- nbtstat -c 查看当前各网卡的netbios缓存
- nbtstat -R 清空所有的netbios缓存信息

### netbios提供服务

1. Name service(NetBIOS-NS) 名称注册和解析服务
2. Datagram distribution service (NetBIOS-DGM) 为无连接通信提供数据报分发服务
3. Session service (NetBIOS-SSN) 为面向连接通信提供会话服务

## samba服务
samba服务是Linux下一种实现netbios的软件。

### 参考资料

- [https://wiki.samba.org/index.php/Build_Samba_from_Source](https://wiki.samba.org/index.php/Build_Samba_from_Source)

### centos搭建安装netbios

注:在centos7中，直接使用`yum -y install samba`可以直接安装samba，安装版本使用`nmbd --version`查看是4.9。接下来准备手动编译4.12版本。

#### 安装包编译安装samba流程

试了下，依赖出现了各种问题，暂停使用此种方法进行测试。

尝试了下，使用此种办法进行编译安装出现了各种问题，基于目前的研究特性，不深入研究此问题。

1. wget https://download.samba.org/pub/samba/stable/samba-4.12.1.tar.gz
2. tar -xxvf samba-4.12.1.tar.gz; cd samba-4.12.1
3. ./configure && make && make install

#### yum安装samba

安装版本4.9

1. yum -y install samba

### 配置文件

smb.conf的全部官方说明文档[https://www.freebsd.org/cgi/man.cgi?query=smb.conf](https://www.freebsd.org/cgi/man.cgi?query=smb.conf)。

启用linux下netbios功能，使用的配置文件是`/etc/samba/smb.conf`。

测试netbios配置文件内容:

	[global]
    workgroup = MYGROUP								#这个组默认为MYGROUP
    server string = Samba Server Version %v

    netbios name = WANGZHA							#设置的netbios名称
    netbios aliases = wangzha1 wangzha2 wangzha3	#设置的其他netbios名称

    interfaces = lo ens37 ens38 10.10.10.11/24 11.11.11.11/24 #监听哪个接口的信息，按照配置手册说明lo口必不可少，经过测试，配置的ip为什么，获取netbios信息时，会将此ip返回给请求方

### 测试环境以及结果

	Linux主机A								Windows主机

	配置的netbios名	网口IP
	wangzha			ens37:10.10.10.11		配置IP1:10.10.10.34
	wangzha1								    IP2:11.11.11.34	
	wangzha2		ens38:11.11.11.11
	wangzha3			 :11.11.11.12

测试情况1:当Windows主机删除IP2，通过IP1来获取相应netbios信息，可获取到上述4个netbios名称，对应的IP为10.10.10.11。

测试情况2:当windows主机删除IP1，配置文件中配置的IP为11.11.11.11，那么windows主机可以获取到的IP为11.11.11.11；如果配置文件中的IP为11.11.11.12，那么windows主机获取到的IP为11.11.11.12。

## linux如何通过netbios访问windows

操作方法: 将`/etc/nsswitch.conf`中`hosts:****`的内容修改为`hosts: files wins dns`。

nsswitch.conf(name service switch configuration，名字服务切换配置)文件位于/etc目录下，由它规定通过哪些途径以及按照什么顺序以及通过这些途径来查找特定类型的信息，还可以指定某个方法奏效或失效时系统将采取什么动作。

nsswitch.conf中的每一行配置都指明了如何搜索信息，每行配置的格式如下： 
	
	Info: method[[action]] [method[[action]]...] 
    
其中，info指定该行所描述的信息的类型，method为用来查找该信息的方法，action是对前面的method返回状态的响应。action要放在方括号里。

## netbios数据交互

### 参考文章

1. [https://zhuanlan.zhihu.com/p/115607631](https://zhuanlan.zhihu.com/p/115607631)

### 端口

网络基本输入/输出系统 (NetBIOS) 名称服务器 (NBNS) 协议是 TCP/IP 上的 NetBIOS (NetBT) 协议族的一部分，它在基于 NetBIOS 名称访问的网络上提供主机名和地址映射方法。使用的端口为UDP137。

### 通讯流程

还是上述的网络拓扑，测试具体的通讯流程。假如当前windows主机没有linux主机的任何netbios信息，使用windows主机的`ping wangzha`来触发netbios查询，查看的结果如下:

- 获取一个netbios的地址(NB)

![NB](https://github.com/YangWangXingKong1204/picture/blob/master/network/NETBIOS/netbios_NB.png?raw=true)

初始包为广播包，但是之后的包为单播包。因为上述网口配置了两个11.11.11.0/24段的IP，windows主机的IP为11.11.11.34，可以看到，返回的查询netbios值为11.11.11.12。这个值为smb.conf文件中配置的内容。

- 获取一个netbios状态(NBSTAT)

在windows下使用`nbtstat -a wangzha1`来获取所有的状态，抓包发现，所有的通信流程都变为了单播，可能跟上一步NB操作可能有关。此步中获取到的指定设备的所有配置的netbios名称。

![NBSTAT](https://github.com/YangWangXingKong1204/picture/blob/master/network/NETBIOS/netbios_NBSTAT.png?raw=true)

