# Git 配置多个 SSH-Key

## 需求

a. gitee 使用公司邮箱注册进行开发活动。
b. github 使用个人邮箱注册进行个人活动。

## 操作流程

### 生成两个 SSH-Key
1. 使用公司邮箱生成一个 Key。
`ssh-keygen -t rsa -C 'xxxxx@company.com' -f ~/.ssh/gitee_id_rsa`
2. 使用个人邮箱生成一个 Key。
`ssh-keygen -t rsa -C 'xxxxx@company.com' -f ~/.ssh/github_id_rsa`

### 生成 SSH 读取的配置文件

1. 执行`touch ~/.ssh/config`。
2. 打开上述配置文件，写入:

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

3. 分别将生成的 `~/.ssh/` 目录下的 `.pub` 文件添加到不同平台的配置中。

## 验证配置

通过 `ssh -T git@github.com` 及 `ssh -T git@gitee.com` 验证配置的正确性。 