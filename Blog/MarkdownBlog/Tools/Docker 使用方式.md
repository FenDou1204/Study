# Docker 使用

---
软件开发最大的麻烦事之一，就是环境配置。用户计算机的环境都不相同，你怎么知道自家的软件，能在那些机器跑起来？

用户必须保证两件事：操作系统的设置，各种库和组件的安装。只有它们都正确，软件才能运行。举例来说，安装一个 Python 应用，计算机必须有 Python 引擎，还必须有各种依赖，可能还要配置环境变量。如果某些老旧的模块与当前环境不兼容，那就麻烦了。开发者常常会说："它在我的机器可以跑了"（It works on my machine），言下之意就是，其他机器很可能跑不了。

环境配置如此麻烦，换一台机器，就要重来一次，旷日费时。很多人想到，能不能从根本上解决问题，软件可以带环境安装？也就是说，安装的时候，把原始环境一模一样地复制过来。以上摘自阮一峰博客，在我看来，Docker 的核心思想就是解决软件开发的环境问题以及程序运行环境独立的问题。


## Docker 安装

我们使用 Docker 主要是在 Centos 系列、Manjaro 系列虚拟机进行使用。Docker 也存在多种安装方法，下面介绍几种常用安装方法。

### 通用的安装方法
1. 终端直接执行以下 bash 语句，即可静默安装 docker
	
	`$  curl -sSL https://get.daocloud.io/docker | sh`

2. centos 系列直接可以使用 yum 进行安装，具体可参考(https://docs.docker.com/engine/install/centos/)[https://docs.docker.com/engine/install/centos/]


**安装结束后，直接在终端执行 `docker version` 可简单验证 docker 是否安装成功**

## 启动 Docker 服务

Docker 是服务器-客户端架构。终端运行 docker 命令的时候，需要本机有 Docker 服务。如果这项服务没有启动，可以使用 systemctl 系列命令来进行控制。否则可能会出现报错信息。

	$ systemctl start docker
	$ systemctl status docker
	$ systemctl stop docker

## Docker image 及 image 文件

Docker 把应用程序及其依赖，打包在 image 文件里面。只有通过这个文件，才能生成 Docker 容器。image 文件可以看作是容器的模板。Docker 根据 image 文件生成容器的实例。同一个 image 文件，可以生成多个同时运行的容器实例。

image 是二进制文件。实际开发中，一个 image 文件往往通过继承另一个 image 文件，加上一些个性化设置而生成。举例来说，你可以在 Ubuntu 的 image 基础上，往里面加入 Apache 服务器，形成你的 image。


	# 列出本机的所有 image 文件。
	$ docker image ls

	# 删除 image 文件
	$ docker image rm [imageName]

image 文件是通用的，一台机器的 image 文件拷贝到另一台机器，照样可以使用。一般来说，为了节省时间，我们应该尽量使用别人制作好的 image 文件，而不是自己制作。即使要定制，也应该基于别人的 image 文件进行加工，而不是从零开始制作。

为了方便共享，image 文件制作完成后，可以上传到网上的仓库。Docker 的官方仓库 [Docker Hub](https://hub.docker.com/) 是最重要、最常用的 image 仓库。此外，出售自己制作的 image 文件也是可以的。

## Docker image 基本操作

运行下面的命令，将 image 文件从仓库抓取到本地。

	$ docker image pull library/hello-world

关于上述命令行解释：
`docker image pull` 是抓取 image 文件的命令。library/hello-world 是 image 文件在仓库里面的位置，其中 library 是 image 文件所在的组，hello-world是 image 文件的名字。

由于 Docker 官方提供的 image 文件，都放在library组里面，所以它的是默认组，可以省略。因此，上面的命令可以写成下面这样。
	
	$ docker image pull hello-world

此时使用前述查看 image 命令即可查看当前从远端获取的 image 文件。

## Docker container 及容器文件

image 文件生成的容器实例，本身也是一个文件，称为容器文件。也就是说，一旦容器生成，就会同时存在两个文件： image 文件和容器文件。而且关闭容器并不会删除容器文件，只是容器停止运行而已。

	$ docker container run hello-world 

`docker container run` 命令会从 image 文件生成一个正在运行的容器实例。

	$ docker container run -i -t ubuntu bash # 生成一个container
	$ docker container ls 
	$ docker container ls -all # 查看所有的容器
	$ docker container kill [containerID] # 停止一个容器
	$ docker container start/stop/stats [containerID] # 开启/停止/查看状态/一个容器
	$ docker container rm [containerID] # 删除一个容器
	$ docker container exec -it [containerID] /bin/bash # 进入正在运行的容器
	$ docker container update --restart=always [containerName] # 设置开机自动启动容器

### 容器压缩与解压

	保存镜像
	$ docker save ID > xxx.tar
	$ docker load < xxx.tar

	保存容器及解压运行容器
	$ docker export ID >xxx.tar
	$ docker import xxx.tar containr:v1
	$ docker run -it containr:v1 bash

## 容器如何主动执行 crontab 计划
