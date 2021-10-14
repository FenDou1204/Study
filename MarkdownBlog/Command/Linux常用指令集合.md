# 大文件拆分与合并

## 拆分

- `cat file.tar | split -C 20M - file.tar.` #将file.tar分解为多个20M大小的文件，最终各分块名为file.tar.aa file.tar.ab等等类似

## 合并
- `cat file.tar.a* > file.tar` #将所有的小文件合并为最初的文件

注:使用md5sum来验证前后操作文件的唯一性