# SSH 常用操作

## 生成多份公钥私钥

### 背景
假如有多个 git 账号， 一个 gitee 用于工作，一个 github 用于个人活动，如何配置 SSH-Key 呢？

### 解决办法

1. 生成工作用 SSH-Key
    ```bash
    $ ssh-keygen -t rsa -C 'xxxxx@company.com' -f ~/.ssh/gitee_id_rsa
    ```
2. 生成个人用 SSH-Key
    ```bash
    $ ssh-keygen -t rsa -C 'xxxxx@qq.com' -f ~/.ssh/github_id_rsa`
    ```
3. 在 `~/.ssh` 目录下新建一个config文件，添加如下内容（其中Host和HostName填写git服务器的域名，IdentityFile指定私钥的路径）
    ```bash
    # gitee
    Host gitee.com
    HostName gitee.com
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/gitee_id_rsa
    # github
    Host github.com
    HostName github.com
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/github_id_rsa
    ```
4. 分别用以下命令测试配置是否成功
    ```bash
    $ ssh -T git@gitee.com
    $ ssh -T git@github.com
    ```

## SSH 免密登陆

1. 使用前述类似办法生成 SSH-Key
    ```
    $ ssh-keygen -t rsa -C 'xxxxx@company.com' -f ~/.ssh/gitee_id_rsa
    ```
2. 将公钥传输到远程服务器
    ```
    ssh-copy-id -i ~/.ssh/gitee_id_rsa.pub root@82.*.*.*
    ```
3. 登陆远程服务器
    ```
    ssh root@82.*.*.*
    ```

