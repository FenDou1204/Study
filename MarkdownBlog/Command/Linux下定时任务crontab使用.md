- [Linux定时任务crontab](#linux定时任务crontab)
  - [crond守护进程](#crond守护进程)
  - [查看crontab命令选项](#查看crontab命令选项)
  - [crontab配置文件基本格式](#crontab配置文件基本格式)
  - [example示例](#example示例)
  - [配置文件](#配置文件)

# Linux定时任务crontab

## crond守护进程

crond 是linux下用来周期性的执行某种任务或等待处理某些事件的一个守护进程，与windows下的计划任务类似，当安装完成操作系统后，默认会安装此服务 工具，并且会自动启动crond进程，crond进程每分钟会定期检查是否有要执行的任务，如果有要执行的任务，则自动执行该任务。

和linux其他系统进程一样，我们可以使用 `systemctl` 系列命令查看进程的运行状态；可以使用 `journalctl` 系列命令查看程序的运行日志。

## 查看crontab命令选项

crontab命令没有-h或者--help选项，随便键入 `crontab -asfasfa` 会报错，同时会提示所有的可选选项。

- `crontab -e` 进行编辑配置文件格式
- `crontab -l` 列出当前所有的定时任务
- `crontab -r` 清空所有的定时任务

## crontab配置文件基本格式

```bash
minute hour day-of-month month-of-year day-of-week 要执行的命令的绝对路径
	
minute 取值范围0-59
hour	0-23
day		1-31
month	1-12
week	0-7	7和0貌似都代表周日，有待测试
```

每个字段都可以包含特殊字符[*],[-],[/],[,]。
	
- [*]代表所有的取值范围
- [-]代表从某个值到另一个值，例如[5-7]
- [,]代表离散型值，例如[1,3,5,7]
- [/]代表每的意思，例如[*/2]代表每2个

## example示例

```bash
* * * * * /usr/bin/python3 /tmp/test.py
每天的每分钟执行一次 /tmp/test.py

6,8	4,5 1-15 1-6 7 /usr/bin/python3 test1.py
每年1-6月的1-15号和每周日，每天的4点和5点的第6和8分钟执行一次脚本
```

注：关于周week和其他日期应该是或的关系，只要满足其中一条就应该可以执行。

## 配置文件

Linux 系统中还有 `/etc/crontab` 配置文件可执行系统的例行性任务。关于用户和系统定时任务之间的区别，这里不过多进行描述。