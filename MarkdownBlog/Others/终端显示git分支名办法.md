# 如何在终端显示 git 分支名

## 办法

1. 打开 `vim ~/.bashrc` 文件或者 `/etc/profile`，将下述内容粘贴到文件末尾。

```bash
function git_branch
{
    branch="`git branch 2>/dev/null | grep "^\*" | sed -e "s/^\*\ //"`"
    if [ "${branch}" != "" ]
    then
        if [ "${branch}" = "(no branch)" ]
        then
            branch="(`git rev-parse --short HEAD`...)"
    fi
    echo "$branch"
    fi
}
export PS1='[\u@\h \[\033[01;36m\]\W\[\033[01;32m\]$(git_branch)\[\033[00m\]] '
```

2. 对应使用 `source ~/.bashrc` 或者 `source /etcprofile` 生效上述操作