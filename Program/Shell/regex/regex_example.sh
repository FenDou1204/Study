#!/bin/bash

# 数字比较运算符
function NumCompare
{
	# 等于
	if [ 5 -eq 5 ];then
		echo 等于
	fi
	# 不等于
	if [ 5 -ne 6 ];then
		echo 不等于 
	fi
	# 大于
	if [ 6 -gt 5 ];then
		echo 大于
	fi
	# 小于
	if [ 6 -lt 5 ];then
		echo 小于
	fi
	# 大于等于
	if [ 6 ge 5 ];then
		echo 大于等于
	fi
	# 小于等于
	if [ 6 le 5 ];then
		echo 小于等于
	fi
}


#作用：将掩码长度（0-32）转换为点分十进制格式。
#24->255.255.255.0 32->255.255.255.255
function MaskToIP
{
	if [ $1 -lt 1 ] || [ $1 -gt 31 ]; then
		echo 不符合规则
		return
	fi

	declare -i FULL_MASK_INT=4294967295
	declare -i MASK_LEN=$1
	declare -i LEFT_MOVE="32 - ${MASK_LEN}"
	declare -i N="${FULL_MASK_INT} << ${LEFT_MOVE}"
	declare -i H1="$N & 0x000000ff"
	declare -i H2="($N & 0x0000ff00) >> 8"
	declare -i L1="($N & 0x00ff0000) >> 16"
	declare -i L2="($N & 0xff000000) >> 24"

	echo "$L2.$L1.$H2.$H1"
}

# 将某一个目录中所有文件进行md5计算，并且将结果写入文件
function CalculateDirFileMd5
{
	`find ./ -type f -print0 | xargs -0 md5sum > ./my.md5`
}
