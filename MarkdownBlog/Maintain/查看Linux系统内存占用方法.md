
# 如何查看 Linux 系统内存占用情况

查看内存占用有 2 种命令，`top` 或者 `free`。

## top 命令

### 使用方法

>top -hv|-bcHiOSs -d secs -n max -u|U user -p pid -o fld -w [cols]

### 命令参数

```bash
c： 显示完整的命令
d： 更改刷新频率
f： 增加或减少要显示的列(选中的会变成大写并加*号)
F： 选择排序的列
h： 显示帮助画面
H： 显示线程
i： 忽略闲置和僵死进程
k： 通过给予一个PID和一个signal来终止一个进程。（默认signal为15。在安全模式中此命令被屏蔽）
l:  显示平均负载以及启动时间（即显示影藏第一行）
m： 显示内存信息
M： 根据内存资源使用大小进行排序
N： 按PID由高到低排列
o： 改变列显示的顺序
O： 选择排序的列，与F完全相同
P： 根据CPU资源使用大小进行排序
q： 退出top命令
r： 修改进程的nice值(优先级)。优先级默认为10，正值使优先级降低，反之则提高的优先级
s： 设置刷新频率（默认单位为秒，如有小数则换算成ms）。默认值是5s，输入0值则系统将不断刷新
S： 累计模式（把已完成或退出的子进程占用的CPU时间累计到父进程的MITE+ ）
T： 根据进程使用CPU的累积时间排序
t： 显示进程和CPU状态信息（即显示影藏CPU行）
u： 指定用户进程
W： 将当前设置写入~/.toprc文件，下次启动自动调用toprc文件的设置
<： 向前翻页
>： 向后翻页
?： 显示帮助画面
1(数字1)： 显示每个CPU的详细情况
```

### 排序

- 键入大写 `P` 按照 cpu 使用率排序各进程
- 键入大写 `M` 按照使用内存率排序各进程

## free 命令

### free 使用方法

```bash
[root@Tencent ~]# free --help

Usage:
 free [options]

Options:
 -h, --human         show human-readable output
 -t, --total         show total for RAM + swap
 -s N, --seconds N   repeat printing every N seconds
 -c N, --count N     repeat printing N times, then exit
 -w, --wide          wide output

     --help     display this help and exit
 -V, --version  output version information and exit

For more details see free(1).
```

### free 常用命令

- `free -h` 转换为方便人类阅读的单位输出(自动换算单位)
- `free -s 数字` 每隔多少秒输出，可以与 `-h` 等同时使用

### 各字段内容

```bash
total: 表示物理内存总量
used: 表示总计分配给缓存（包含buffers与cach）使用的数量，但其中可能有部分缓存并未实际使用
free: 未被分配的内存
shared: 多个进程共享的内存总额
bufers: 系统已分配但未被使用的buffers数量
cached: 系统已分配但未被使用的cache数量
```