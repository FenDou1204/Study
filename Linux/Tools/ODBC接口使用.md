# unixODBC安装及接口使用

ODBC是什么？ODBC是一个开放规范，旨在为应用程序开发人员提供可预测的API，以使用其访问数据源。数据源包括SQL Server和任何带有ODBC驱动程序的数据源。

## unixODBC安装包下载

unixODBC是一个开源项目，其官方网址为[http://www.unixodbc.org/](http://www.unixodbc.org/)。
截止2020年10月27日，当前的版本为2.3.9，安装包路径为[http://www.unixodbc.org/unixODBC-2.3.9.tar.gz](http://www.unixodbc.org/unixODBC-2.3.9.tar.gz)。

### linux环境安装unixODBC
1. 选取指定的目录作为存放安装包的基本路径。
1. 执行`wget http://www.unixodbc.org/unixODBC-2.3.9.tar.gz`获取到软件安装包。
2. 执行`./configure --prefix=/usr/local/unixODBC`来设置安装路径以及检查安装所需要的各环境变量。
3. 执行`make && make install`来编译相应程序以及将生成的动态库以及将动态库配置文件置于相应的系统目录中。
4. 查看`/usr/local/unixODBC`路径下，已经编译好的动态库，二进制程序以及配置文件等内容。

## 使用ODBC进行C++编码

### 不同数据库ODBC驱动下载
网站[https://www.easysoft.com/products/data_access/index.html?advert=odbc&referring_page=ODBC%20from%20C%20Tutorial%20Part%201&location=header](https://www.easysoft.com/products/data_access/index.html?advert=odbc&referring_page=ODBC%20from%20C%20Tutorial%20Part%201&location=header)中列举了多种常见的数据库(不包含国产数据库)的ODBC驱动，供大家下载，目测大概有20种。

### 头文件选取


### 简单的编码流程