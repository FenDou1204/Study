# C++ OpenSSL 开源接口使用

## OpenSSL 介绍

## tcp socket多路复用select方法


## openssl提供接口
OPENSSL [官方API文档](https://wiki.openssl.org/index.php/API)提供了不同编程语言接口；不同语言可能需要不同的组件来支持，这里先暂时不讲解如何讲解各种库的安装,有需求可以查看下API文档，也许会有介绍。在C/C++中，需要安装openssl-devel(REDHAT)或者libssl-dev(debian,ubuntu),安装内容主要包括头文件和动态库。

### 头文件以及动态库
- openssl/ssl.h
- openssl/err.h

编译链接时需要两个动态库libssl.so和libcrypto.so。

### 创建openssl的使用环境
在使用opsnssl加密之前，需要预先加载需要的一些协议
int SSL_library_int(void);

### 选择进行加密的协议
openssl相关提供了多种加密协议。主要包括TSL，SSL和TSL加密套件。具体方法可参考:[SSL加密方法](https://www.openssl.org/docs/man1.0.2/man3/SSLv23_client_method.html)。需要注意的是，client端和server端需要选择不同的方法，否则会导致在SSL握手过程中出错。

1. 客户端调用SSLv23_client_method()方法
2. 服务器端调用SSLv23_server_method()方法

具体选择什么方法还需要根据客户端采用什么方法来兼容。server端目前无法同时启用多种加密方法，具体配置需要进行选择。

### 创建会话环境以及证书等内容
1. SSL_CTX* SSL_CTX_new(SSL_METHOD* method) //通过采用的加密协议方法创建SSL会话
2. int SSL_CTX_set_verify(SSL_CTX \*ctx,int mode,int(*verify_callback),int(X509_STORE_CTX *)) //设置SSL会话
3. SSL_CTX_load_verify_location(SSL_CTX *ctx,const char *Cafile,const char *Capath) //加载CA证书
4. SSL_CTX_use_certificate_file(SSL_CTX *ctx, const char *file,int type) //加载用户证书
5. SSL_CTX_use_PrivateKey_file(SSL_CTX \*ctx,const char* file,int type) //加载用户私钥
6. int SSL_CTX_check_private_key(SSL_CTX *ctx) //验证私钥和证书是否符合

### 创建SSL套接字进行数据的收发
1. SSL\* SSL_new(SSL_CTX *ctx) //创建SSL套接字
2. SSL_set_fd(ssl,fd) //将SSL套接字与socket套接字进行绑定(读写套接字)，类似的还有SSL_set_rfd和SSL_set_wfd
3. int SSL_connect(SSL* ssl) //客户端在connect()之后调用此函数进行SSL握手
4. int SSL_accept(SSL* ssl) //服务器端在accept()之后调用此函数进行SSL握手
5. int SSL_read(SSL* ssl) //从ssl socket接收数据
6. int SSL_write(SSL* ssl) //往ssl socket发送数据

### 断开连接以及销毁操作句柄及ssl环境
1. int SSL_shutdown(SSL *ssl) //断开SSL连接
2. void SSl_free(SSL *ssl) //释放ssl套接字
3. void SSL_CTX_free(SSL_CTX *ctx) //释放ssl句柄
4. 还有释放初始化ssl环境

## client和server端的处理流程
|-|-|-|
|操作|CLIENT|SERVER|
||socket()|socket()|
||bind()|bind()|
||connect()|listen()|
|||accept()|
||SSLv23_client_method()|SSLv23_client_method()|
||SSL_CTX_new|SSL_CTX_new()|
||SSL_new()|SSL_new()|
||SSL_set_fd()|SSL_set_fd()|
||SSL_connect()|SSL_accept()|
||SSL_read()&SSL_write()|SSL_read()&SSL_write()|
||SSL_shutdown()|SSL_shutdown()|
||SSL_free()|SSL_free()|
||SSL_CTX_free()|SSL_CTX_free()|

## SSL_read函数和read(recv)特殊处理区别
处理从每个连接接收数据时，采用的是select多路复用，每次从socket读取一字节数据。在recv()/read()情况下，如果socket中还有数据，那么每次select能够判断出有数据可读；模拟此种方法，将recv/read替换为SSL_read，但是每次都只能读到一个字节数据，后续的数据都无法触发select判断是否有数据可读。造成这种情况的原因是，在调用SSL_read（）函数时，此函数会将所有的数据都会接受处理存放于缓存中，导致后续调用此函数无法继续接受函数；那么如何解决此办法呢？在select之前，通过SSL_pending()函数来判断某个SSL套接字中是否有数据可以读取，如果返回值不为0，那么通过SSL_read()函数将其中所有的数据都进行读取。