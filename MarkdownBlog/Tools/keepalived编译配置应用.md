# keepalived编译安装运行


测试设备:centos7无界面版本，无gcc，内核版本3.10.0-862.11.6.el7.x86_64。

keepalived和heartbeat是两款常用的开源热备软件。相对来说keepalived使用配置比heartbeat更方便简单。相比heartbeat来说，keepalived可以对于监测的各项业务设置权重值，根据权重值来进行切换，而且整体配置相当简单，优点明显

具备功能:   
- 主备切换后执行相应的业务（脚本控制）
- 权重控制（脚本控制）
- 抢占非抢占模式设置

## 源码编译安装

### 参考
- [https://blog.csdn.net/baidu_37781025/article/details/72400773](https://blog.csdn.net/baidu_37781025/article/details/72400773) 源码编译安装

### 安装gcc、openssl等组件
1. `yum -y install gcc`  
2. `yum -y install openssl openssl-devel`
3. `yum -y install libnl libnl-devel`

### 编译安装keepalived
- `wget http://www.keepalived.org/software/keepalived-2.0.12.tar.gz` 在线下载源码安装包
- `tar -xzvf keepalived-2.0.12.tar.gz` 解压
- `cd keepalived-2.0.12`
- `./configure --prefix=/usr/local/keepalived`
- `make && make install`

**如果遇到其他组件缺失直接寻求解决办法即可**

## 配置文件

### 配置文件部署
- `mkdir /etc/keepalived`
- `cp /usr/local/keepalived/etc/keepalived/keepalived.conf /etc/keepalived/keepalived.conf`
- `cp /usr/local/keepalived/etc/sysconfig/keepalived /etc/sysconfig/`
- `cp /usr/local/keepalived/sbin/keepalived /usr/sbin/`
- `cp /usr/local/keepalived/sbin/keepalived /etc/init.d/`
- `chkconfig keepalived on` #创建开机启动服务

### 如何启动keepalived
`/usr/local/keepalived/sbin/keepalived -f /etc/keepalived/keepalived.conf`

### 配置文件内容说明参考
- [https://www.cnblogs.com/liyasen/p/6611079.html](https://www.cnblogs.com/liyasen/p/6611079.html)
- [http://www.linuxe.cn/post-266.html](http://www.linuxe.cn/post-266.html)

研究一下keepalived.conf中各配置选项的内容:

	global_defs {
	#此部分主要是对于邮件设置等内容，可以直接注释掉
	}
	vrrp_instance VI_1 {
		state MASTER	#配置为主节点，并不起实际作用
		interface eth0	#配置VIP需要绑定的网卡
		virtual_router_id 51	#1-255的值，主备需要相同，构成一个组
		priority 100	#初始权重，数值高的为master，后续权重根据实时计算来获取

		advert_int 1	#主备通讯间隔，判断主节点是否存活
		authentication {#此块内容不需要进行配置，默认的即可使用
			auth_type PASS	#安全认证方式
			auth_pass 1111	#密码
		}
		virtual_ipaddress {#在eth0上虚拟一个新的IP，此IP用来提供服务
			192.168.10.10
		}
	}

## 配置文件的修改

### 抢占模式下示例配置
**MASTER配置文件:**

	global_defs {
	#此部分主要是对于邮件设置等内容，可以直接注释掉
	}
	vrrp_instance VI_1 {
		...
		state MASTER	#配置为主节点
		virtual_router_id 51	#主备需要相同，构成一个组
		priority 100	#初始权重，数值高的为master，后续权重根据实时计算来获取
		...
	}
**BACKUP配置文件:**

	global_defs {
	#此部分主要是对于邮件设置等内容，可以直接注释掉
	}
	vrrp_instance VI_1 {
		...
		state BACKUP	#配置为备节点
		virtual_router_id 51	#主备需要相同，构成一个组
		priority 99		#初始权重，数值高的为master，后续权重根据实时计算来获取，要比主节点低
		...
	}

### 非抢占模式下配置
**MASTER配置文件:**

	global_defs {
	#此部分主要是对于邮件设置等内容，可以直接注释掉
	}
	vrrp_instance VI_1 {
		...
		state BACKUP			#配置为主节点
		nopreempt
		virtual_router_id 51	#主备需要相同，构成一个组
		priority 100	#初始权重，数值高的为master，后续权重根据实时计算来获取
		...
	}
**BACKUP配置文件:**

	global_defs {
	#此部分主要是对于邮件设置等内容，可以直接注释掉
	}
	vrrp_instance VI_1 {
		...
		state BACKUP			#配置为备节点
		nopreempt
		virtual_router_id 51	#主备需要相同，构成一个组
		priority 99		#初始权重，数值高的为master，后续权重根据实时计算来获取，要比主节点低
		...
	}
**在非抢占模式下，两台设备的state参数都要配置为backup，同时需要添加nopreempt配置选项**

#### nopreempt选项解释
*nopreempt allows the lower priority machine to maintain the master role, even when a higher priority machine comes back online*

### 配置文件中设置切换脚本
参考链接:[http://blog.51cto.com/13520924/2094236](http://blog.51cto.com/13520924/2094236) 主备切换执行脚本

主备切换后如何来控制需要执行的业务，keepalived中设置了3个参数来处理这些问题:

- notify_master "成为master执行脚本以及接受参数"
- notify_backup "成为backup执行脚本以及接受参数"
- notify_fault "节点转为失败状态执行的脚本"

举例说明:
`control.sh`脚本是热备组切换时要执行的脚本。

	#!/bin/bash
	DATE=`date +'%F %T'`
	case $1 in
	start)
		#执行自己的业务
		echo "$(hostname) to be master"
		;;
	stop)
		#执行自己的业务
		echo "$(hostname) to be backup"
		;;
	status)
		;;
	*)
		echo "Usage: $0 {start|stop|status}"
		exit 1
		;;

那么我们需要在`vrrp_instance VI_1`配置选项中加入不同状态下执行的不同内容。

	vrrp_instance VI_1 {
		...
		...
		...
		notify_master "control.sh start"
		notify_backup "control.sh stop"
		notify_fault "control.sh fault"
	}
两台设备的配置需要相同，这样在切换后，就会执行相应的脚本，保证主备切换后执行的是相同的业务。

### 设备业务监测及权重设置

#### 参考链接
- [https://www.jianshu.com/p/16fe113f391a](https://www.jianshu.com/p/16fe113f391a) 如何添加关于权重检测脚本
- [https://blog.csdn.net/HzSunshine/article/details/62041036](https://blog.csdn.net/HzSunshine/article/details/62041036)关于权重的一个讲解


#### vrrp_script解释
vrrp_script脚本用来监测指定程序或者硬件的状态，并且设置相应的权重，依靠设置的权重来动态调整系统整体的优先级，来进行master和backup的切换。

#### vrrp_script配置
在keepalived的配置文件中加入:

    vrrp_script checkenp1s0
    {
    	script "脚本绝对路径"		//监测的脚本
    	interval 3				//执行间隔
    	weight -20				//权重-20
    }
    
    vrrp_instance VI_1
    {
    	...
    	track_script
    	{
    		checkenp1s0
    	}
    	...
    }
上述配置描述的主要内容是:**如果执行的监测脚本返回0，那么整体的权重就会下降20**
权重值可正可负，我觉得为负比较好理解。

举例说明一下:
现在有两台设备，监听的是eth0网口，如果eth0网口出现问题，就会切换相应的业务到另一台设备。
master:101	eth0:20
backup:100  eth0:20

检测到master的eth0处于down状态返回值为0，那么其整体权重就为81，而backup的权重为100，那么此时就应该进行切换。如果master的eth0口处于up状态，那么相应的增加20的权重，也就是master恢复到权重101，那么整体业务就会恢复到master上。

## 主动切换状态
目前看heartbeat和keepalived两款软件都不支持主动切换运行状态，针对keepalived有两种方式来实现：   

1. 直接杀死keepalived进程来主动进行切换   
2. 根据权重值的设置来进行切换