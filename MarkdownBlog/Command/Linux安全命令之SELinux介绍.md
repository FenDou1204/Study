# SELinux 是什么？

- [SELinux 是什么？](#selinux-是什么)
  - [参考文档](#参考文档)
  - [问题由来](#问题由来)
  - [简单测试](#简单测试)
  - [SELinux是什么](#selinux是什么)
  - [SELinux操作](#selinux操作)
    - [查询SELinux状态](#查询selinux状态)
    - [关闭SELinux](#关闭selinux)
    - [开启SELinux](#开启selinux)
    - [其他问题](#其他问题)

## 参考文档
- SELinux是什么:[https://blog.csdn.net/yanjun821126/article/details/80828908](https://blog.csdn.net/yanjun821126/article/details/80828908)
- SELinux操作:[https://blog.csdn.net/qq_39698293/article/details/79505285](https://blog.csdn.net/qq_39698293/article/details/79505285)

## 问题由来
如果你准备在开机启动时准备启动某些deamon程序，但是无论如何修改开启启动脚本，开机自启动都是失败；设备成功启动之后，手动执行开机启动脚本，发现一切安好，那么，此篇文章或多或少能够起到一些作用。

## 简单测试

在你执行的未生效命令之前先执行**setenforce 0**，然后
重新执行命令查看效果；如果发现成功执行，那么恭喜你，问题的解决办法找到了。
  
```shell
修改centos7系统/etc/rc.d/rc.local启动脚本，开机自启动clamd

touch /var/lock/subsys/local

source /etc/profile
# 自行添加的启动clamd
clamd
```
上述段代码在开机自启动阶段，clamd都无法启动（root用户都无法启动）；但是如果手动执行此脚本，clamd成功执行并且功能正常;将上述代码修改为:
```
setenforce 0
clamd
```
reboot设备。奇迹发生了，clamd成功启动了！

## SELinux是什么
安全增强型 Linux（Security-Enhanced Linux）简称 SELinux，它是一个 Linux 内核模块，也是 Linux 的一个安全子系统。**SELinux 主要作用就是最大限度地减小系统中服务进程可访问的资源（最小权限原则）。**

## SELinux操作
### 查询SELinux状态
执行指令:
`getenforce`
返回结果:
**permissive**处于关闭SELinux模式
**enforcing**处于开启SELinux模式

### 关闭SELinux
临时关闭SELinux(及时生效):
`setenforce 0`

永久关闭SELinux(reboot生效):
```
vim /etc/selinux/config
SELINUX=disabled
```

### 开启SELinux
临时开启SELinux(及时生效):
`setenforce 0`

永久开启SELinux(reboot生效):
```
vim /etc/selinux/config
SELINUX=enforcing
```
### 其他问题
目前只在centos7下发现有SELinux默认处于开启状态，简单推测Redhat应该也存在相同问题。在Ubuntu和ArchLinux的manjaro中却没有发现相应的执行命令，同时相应的配置文件都不存在，在这两种系统中应该默认没有安装，但仍需注意。