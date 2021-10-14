# Linux 设置终端显示

## 配置文件

bash 的配置文件路径 `~/.bashrc`，通常位于家目录下，为隐藏文件。

## 配置流程

1. 打开 bash 的配置文件，移到配置文件的最尾部。
2. 写入下列内容

		find_git_branch ()
		{
			local dir=. head
			until [ "$dir" -ef / ]; do
			if [ -f "$dir/.git/HEAD" ]; then
			head=$(< "$dir/.git/HEAD")
			if [[ $head = ref:\ refs/heads/* ]]; then
			git_branch=" → ${head#*/*/}"
			elif [[ $head != '' ]]; then
			git_branch=" → (detached)"
			else
			git_branch=" → (unknow)"
			fi
			return
			fi
			dir="../$dir"
			done
			git_branch=''
		}

		PROMPT_COMMAND="find_git_branch; $PROMPT_COMMAND"

		# Here is bash color codes you can use
		black=$'\[\e[1;30m\]'
		red=$'\[\e[1;31m\]'
		green=$'\[\e[1;32m\]'
		yellow=$'\[\e[1;33m\]'
		blue=$'\[\e[1;34m\]'
		magenta=$'\[\e[1;35m\]'
		cyan=$'\[\e[1;36m\]'
		white=$'\[\e[1;37m\]'
		normal=$'\[\e[m\]'
		# 重新定义一个PS1,这里的“\u表示root,\h表示host，颜色什么的完全可以自定义”
		PS1="$white[$magenta\u$white@$green\h$white:$cyan\w$yellow\$git_branch$white]\$ $normal"
		export PS1

3. 执行 `source ~/.bashrc` 使配置生效。
4. 上述配置也可以写入 `~/.profile` 或者 `/etc/profile` 目录中，但是 profile 文件和 bashrc 文件是由区别的，部分情况可能会造成错误问题。