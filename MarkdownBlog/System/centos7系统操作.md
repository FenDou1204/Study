# centos7各种操作整理

主要针对centos7系统进行各种业务配置

## 支持串口通讯
1. dmesg | grep tty
2. 第一步输出**enable**代表支持串口通讯
3. 修改配置文件`vim /etc/default/grub`,添加内容`GRUB_CMDLINE_LINUX_DEFAULT="console=tty0 console=ttyS0,9600"` #其中9600代表波特率,按实际使用；tty0和ttyS0根据步骤一得到
4. 更新grub2配置文件:`grub2-mkconfig -o /boot/grub2/grub.cfg`
5. reboot 

**注意:要保证连接串口的设备功能正常 centos6配置方法和上述不同**

其他情况配置串口:

参考链接:[https://blog.csdn.net/LshuangCC/article/details/80269540]()
[http://www.cnblogs.com/sdphome/archive/2011/10/25/2224585.html]()   
- vim /etc/inittab
- con::respawn:/sbin/getty -L ttyS0 115200 vt100

## yum只下载安装包

### yum下载
1. 正常情况下在线安装使用`sudo yum -y install <package-name>`
2. 只下载安装包不进行安装`sudo yum -y install --downloadonly <package-name>`
3. 下载安装包放在指定目录`sudo yum -y install --downloadonly --downloaddir=/tmp <name>`
**注意:已经在线安装过的软件不能通过上述方法下载安装包，如果已经安装可以使用下述方法进行安装**

### yumdownloader下载
1. 下载工具`sudo yum install yum-utils`
2. 通过工具进行下载`sudo yumdownloader <package-name>`

**yumdownload与yum命令不同的是，任何依赖包不会被下载。**

## yum操作
1. 显示已经安装的软件包`yum list installed`
2. 查找可以安装的软件包`yum list <package-name>`
3. 安装软件`yum install <package-name>`
4. 卸载软件`yum remove <package-name>`
5. 列出依赖`yum deplist <package-name>`