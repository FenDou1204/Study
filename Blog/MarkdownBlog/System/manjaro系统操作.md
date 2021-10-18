# manjaro系统操作

manjaro是操作起来很舒服的操作系统.在此记录一些安装软件包的操作，避免每次都网上查找资料。

## 更换软件源操作

### 设置官方镜像源
- sudo pacman-mirrors -i -c China -m rank
- 更新结束后选择清华的源
- sudo pacman -Syy 更新数据源
- sudo pacman -S archlinux-keyring 更新签名

### 设置archlinuxcn源

- vi /etc/pacman.conf
- 加入下述内容:

	[archlinuxcn]  
	SigLevel = Optional TrustedOnly   
	Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
- sudo pacman -Syy 更新数据源
- sudo pacman -S archlinuxcn-keyring 更新签名

**以上内容在安装系统后一定要进行操作，而且必须在安装其他软件之前，否则会出现各种错误问题**

## 安装常见软件过程

### 安装sogou输入法
1. sudo pacman -S fcitx-sogoupinyin
1. sudo pacman -S fcitx-im
2. sudo pacman -S fcitx-configtool
3. fcitx-configtool來進行配置

**最新版本的sogou中需要安装`sudo pacman -S fcitx-qt4`才能支持输入法，不然会一直提示报错**

### 安装vscode
1. sudo pacman -S yaourt
2. sudo yaourt -S visual-studio-code-bin

### 安装qtcreator
sudo pacman -S qtcreator