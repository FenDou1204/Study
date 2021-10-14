# git常用的各种操作

git是一个开源的分布式版本控制系统，可以有效、高速地处理从很小到非常大的项目版本管理。目前比较流行的github、gitlab等基于git的控制系统，都是通用的用法。

## 本地代码仓库和远程仓库的关联

### 通用部分

#### 初始化git配置

git 的配置登记分为三级，其中 *local > global > system*。 

- git config --global user.name "你的名字"
- git config --global user.email "你的邮箱"

- mkdir git #创建一个git本地仓库文件夹
- cd git
- git init #这步会生成一个.git目录，会记录相关的信息
- 到此相关的git信息设置以及目录初始化结束

#### 获取ssh秘钥
- ssh-keygen -t rsa -C "你的邮箱"
- 默认一路回车
- 会生成一个相应的秘钥

![](https://i.imgur.com/OJEUjca.jpg)
- 需要拷贝id_rsa.pub的内容到github服务器相应的ssh配置
- 使用ssh -T git@github.com来测试是否配置成功

### 第一种方法:本地仓库与远程关联
1. 我在github创建的新仓库地址为:git@github.com:ExcellentVoyage/Markdown.git
2. 使用git commit将本地仓库中所有文件进行提交
3. 本地仓库和服务器指定仓库进行关联：git remote add origin git@github.com:ExcellentVoyage/Markdown.git
4. git push -u origin master #推送本地代码到服务器
**注意:第4步大部分人肯定会出现问题，导致出现问题的原因是:github新建仓库会默认生成README或者LICENSE文件，但是本地仓库没有这些文件，导致本地和远程出现差异,正确做法是先执行步骤5,然后执行步骤4**
5. git pull --rebase origin master
6. 执行成功

### 第二种方法:直接从服务器pull一份空仓库（推荐）
1. 在github创建一个新的仓库
2. git clone git@github.com:ExcellentVoyage/Markdown.git
3. 在相应目录下添加需要上传的文件目录
4. 直接git push 上传即可

## git常用指令
- `git status` #查看本地文件状态
- `git branch -a` #查看当前分支

- `git push origin 本地分支名:本地分支名` #推送本地分支到master分支并且创建合并请求
- `git rebase master` #从master分支合并到当前分支
- `git checkout -f` #删除本地所有的修改

## git status等中文显示数字乱码
- git config --global core.quotepath false

## git commit提交提示书写错误处理方式

可以参考[https://www.cnblogs.com/lfxiao/p/9378763.html](https://www.cnblogs.com/lfxiao/p/9378763.html).

- `git reset --soft HEAD^` 撤销上一次commit内容，不丢失相应的代码修改