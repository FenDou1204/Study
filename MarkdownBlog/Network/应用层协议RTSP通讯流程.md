# RTSP协议简要

RTSP协议:Real Time Strwaming Protocol是一个应用层协议，主要解决在IP网络如何传输流媒体数据的应用层协议。RTSP对流媒体提供了暂停、快进等功能，但是**不传输数据**，相当于流媒体的远程控制。

## 参考博客
[https://blog.csdn.net/yihuanyihuan/article/details/86485369](https://blog.csdn.net/yihuanyihuan/article/details/86485369)

## RTSP请求消息和应答消息的格式
请求消息格式

	REQUEST 方法 URI RTSP版本\r\n(\r\n在wireshark中无法显示)
	

## RTSP方法
RTSP中有下列几种方法，根据现场抓包情况，将遇到的数据包进行分析。

### DESCRIBE

	Real Time Streaming Protocol
    Request: DESCRIBE rtsp://10.69.91.52:554/pag://10.69.91.52:7302:001159:0:MAIN:TCP?cnid=1&pnid=1&token=ST-3-YEESYfhaGwpuphxmcUPp-cas&auth=50 RTSP/1.0\r\n
    Method: DESCRIBE
    URL: rtsp://10.69.91.52:554/pag://10.69.91.52:7302:001159:0:MAIN:TCP?cnid=1&pnid=1&token=ST-3-YEESYfhaGwpuphxmcUPp-cas&auth=50
    CSeq: 0\r\n
    Accept: application/sdp\r\n
    Authorization: Basic YWRtaW4xOmFkbWluMTIz\r\n
    User-Agent: StreamClient\r\n
    \r\n


应用层数据包含请求的URL。

DESCRIBE请求RTSP URL（rtsp://）以及可以处理的回复数据类型。

### REDIRECT
REDIRECT是一个重定向关键字。根据目前已知的现场环境，海康威视客户端从流服务器获取数据有两种情况，一种为服务器从各摄像头获取数据后，客户端查看视频直接从流媒体服务器获取即可；另外一种是客户端访问服务器，服务器会将相应摄像头的数据返回，客户端去访问摄像头的地址。两种访问方式还是有不同的区别的。