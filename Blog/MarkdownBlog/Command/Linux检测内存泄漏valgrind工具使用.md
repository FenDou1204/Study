# valgrind 内存泄漏检测工具

[TOC]

在中大型项目日常运行中，某些时候我们能够发现可能存在内存泄露的情况。对于普通的运行错误，我们可以添加部分日志输出来进行定位；如果是内存泄露情况，那么如何能快速定位出现问题的函数位置？valgrind 工具能够帮助定位出现问题的地方。

## 基本执行命令
`valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --undef-value-errors=no --log-file=log 可执行文件以及参数`


## 结果分析

通过