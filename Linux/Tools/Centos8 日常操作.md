# centos8 日常操作

1. yum 安装 crond 工具 `yum -y install crontabs`
2. 更换 centos8 软件源 `wget -O /etc/yum.repos.d/CentOS-Base.repo https://mirrors.aliyun.com/repo/Centos-8.repo && make cache`
3. yum 卸载工具 `yum remov 工具名`