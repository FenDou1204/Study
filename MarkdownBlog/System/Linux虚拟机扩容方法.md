# Linux虚拟机扩容

## 虚拟机使用
很多初学者或者开发者都喜欢使用VMware虚拟机来学习或者开发。安装虚拟机会初始化一些存储空间来供使用，随着开发内容的增多(尤其是开发者，可能会同时开发几个大的项目)，磁盘分配的存储空间剩余不多，导致部分操作无法进行。如何来解决这种情况？

[参考路径https://blog.csdn.net/u012468263/article/details/52023518](https://blog.csdn.net/u012468263/article/details/52023518)

## 当前系统容量及系统介绍

### 查看当前虚拟机存储
执行`df -h`获取当前设备的存储情况:
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E8%99%9A%E6%8B%9F%E6%9C%BA%E5%AD%98%E5%82%A8%E5%8D%B3%E5%B0%86%E7%94%A8%E5%B0%BD.jpg)

## 物理层面扩容方式
以下方式为VMware平台下centos系统的扩容方式：   

1. 关闭虚拟机
2. 点击【虚拟机设置】
3. 选择【硬盘】
4. 点击【实用工具】（不同版本此步骤可能有差异）
5. 选择【扩展】
6. 选择扩展后的大小
6. 启动虚拟机

![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%89%A9%E5%B1%95%E6%96%B9%E5%BC%8F.jpg)

### 扩容后的系统信息

1. 使用`fdisk -l`能够获取到当前系统的存储已经变为40G多
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%89%A9%E5%AE%B9%E5%88%B040.jpg)
2. 使用`df -h`可以看到实际还是为20G左右
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E5%AE%9E%E9%99%85%E8%BF%98%E6%98%AF20.jpg)

## 系统层面扩容具体流程

### 第一流程
1. `fdisk /dev/sda`
2. 键入n
3. 键入p
4. 键入3或者键入回车
5. 键入回车
6. 键入回车
7. 键入w
8. 使用`fdisk -l`,新建分区已经有/dev/sda3，格式却不是LVM的。第二流程使用`fdisk命令`将其改成LVM格式。
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%A0%BC%E5%BC%8F%E4%B8%BA%E9%9D%9ELVM.jpg)
### 第二流程
1. fdisk /dev/sda
2. 键入t
3. 键入3
3. 键入8e
4. 键入w
5. 重启
6. 使用`fdisk -l`,/dev/sda3的格式已经变为LVM格式。
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%A0%BC%E5%BC%8F%E5%8F%98%E4%B8%BALVM.jpg)

### 第三流程
1. `mkfs -t ext3 /dev/sda3`

### 第四流程
2. `pvcreate /dev/sda3`
3. `df -h` 获取到类似/dev/mapper/centos-root中`centos`和`root`字段
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/df%E5%91%BD%E4%BB%A4%E8%8E%B7%E5%8F%96%E4%B8%A4%E4%B8%AA%E5%AD%97%E6%AE%B5.jpg)
3. `vgextend centos /dev/sda3`
4. `vgdisplay`获取`Free PE/Size 5119/<20.00GB`字段中的20.00G值，代表可扩充空间。
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/vgdisplay%E8%8E%B7%E5%8F%96%E6%95%B0%E5%80%BC.jpg)
4. `lvextend -L +39G /dev/centos/root /dev/sda3` 其中的数值不能大于第四步获取的数据
5. `xfs_growfs /dev/centos/root` 此步根据不同系统执行可能会有差异
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%89%A9%E5%AE%B9%E7%BB%93%E6%9E%9C%E6%8A%A5%E5%91%8A.jpg)
6. 使用`df -h`查看是否是扩容后的大小
![](https://raw.githubusercontent.com/GrapeSky04/picture/master/%E8%99%9A%E6%8B%9F%E6%9C%BA%E6%89%A9%E5%AE%B9/%E6%89%A9%E5%AE%B9%E6%88%90%E5%8A%9F.jpg)

## 总结
升级流程不难，按照整个教程即可成功。