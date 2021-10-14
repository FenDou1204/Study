# 如何书写一个systemctl控制的服务？

- 参考链接1：[阮一峰介绍systemd服务](http://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html)
- 参考链接2：[https://blog.csdn.net/djskl/article/details/46671453](https://blog.csdn.net/djskl/article/details/46671453)

## systemd工具介绍

Systemd 是 Linux 系统工具，用来启动守护进程，已成为大多数发行版的标准配置。

## systemd用来做什么

曾经，我们设置linux开机启动项可以是service服务，但是发现这种启动方式速度慢慢，启动脚本需要自己完善细节，整体脚本变得复杂。使用systemd以后，systemd成为了系统的1号进程，所有的其他进程都为1号进程的子进程。

## systemctl命令查看

常规使用方法：
systemctl命令行包含多种工具，常规使用能够掌握通过命令控制某个服务的启停等即可。

```bash
systemctl start		#启动服务
systemctl stop 		#停止服务
systemctl enable	#设置开机启动
systemctl disable	#开机不启动
systemctl restart	#重启服务
systemctl is-active	#查看后台进程是否在运行
systemctl status	#查看运行状态
```

进阶使用方法(简单介绍一下)：
通过systecmctl相关命令，我们可以分析整个系统的启动流程以及系统在启用每个组件所消耗的时间。

```bash
	systemd-analyze		#分析systemd启动流程耗时
	systemd-analyze blame #分析每个进程在引导时花费的时间
```

## systemctl配置文件

配置管理路径: `/usr/lib/systemd/system/`。
主要有四种类型文件 `.mount`,`.service`,`.target`,`.wants`。还有其他的`.socket`等。

## 如何书写一个systemctl服务的配置文件

系统配置文件路径:**/etc/systemd/system/**。

先来查看下系统调度任务crond进程的.service文件。
```bash
[Unit]
Description=Command Scheduler
After=auditd.service nss-user-lookup.target systemd-user-sessions.service time-sync.target ypbind.service

[Service]
EnvironmentFile=/etc/sysconfig/crond
ExecStart=/usr/sbin/crond -n $CRONDARGS
ExecReload=/bin/kill -HUP $MAINPID
KillMode=process
Restart=on-failure
RestartSec=30s

[Install]
WantedBy=multi-user.target
```

基本格式：
```bash
[Unit]
Description=	#关于服务的描述，会在日志中体现
Wants=		#可以理解为依赖于哪个服务
After=		#定义启动顺序，加入启动模块在A模块之后，那么需要写为After=A.service

[Service]
Type = 		#指定服务的类型
ExecStart=	#启动服务需要执行的内容；可以使用换行符[\]分为多行；所有执行内容包括shell都必须使用绝对路径。
ExecStop=	#停止服务需要执行的内容，必须使用绝对路径
			#还有其他选项遇到在详细研究，目前有这些内容足够写出所需要的功能

[Install]
WantedBy=multi-user.target #通常都写为前述内容。可以理解为此服务被那个用户拥有。
Alias= 		#给你自己的别名，可以用此名称操作相应服务
Also= 

## Install说明
WantedBy 选项务必选择上述内容。如果此选项为空，开机不会执行相应内容，状态为static，而非enable或者disable。