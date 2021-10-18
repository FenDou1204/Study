#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include <asm/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include <arpa/inet.h>
#include <errno.h>

#include <net/if.h>

#include "netlink_socket.h"

/// 初始化一个netlink套接字,通过此套接字进行数据收发
int InitSocket(void)
{
	struct sockaddr_nl stSrcAddrnl;
	memset(&stSrcAddrnl, 0, sizeof(struct sockaddr_nl));
	//必要参数,必须设置为AF_NETLINK
	stSrcAddrnl.nl_family = AF_NETLINK;
	//剩余参数不设置也能正常工作
	//stSrcAddrnl.nl_groups = RTMGRP_IPV4_ROUTE;
	//stSrcAddrnl.nl_pad = 0;
	//stSrcAddrnl.nl_pid = 0;

	int fd = socket(AF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE);
	if (fd == -1)
	{
		printf("创建套接字失败,错误原因:%s\n", strerror(errno));
		return -1;
	}
	if (bind(fd, (struct sockaddr *)&stSrcAddrnl, sizeof(struct sockaddr_nl)) == -1)
	{
		printf("绑定本地地址失败,错误原因:%s\n", strerror(errno));
		return -1;
	}
	printf("初始化套接字成功\n");
	return fd;
}

/// 传入参数:fd 获取数据socket
///			 pcBuf 存储数据内存
///			 pcBufLen 存储数据内存长度
/// 返回值: 收到数据的实际长度
int GetKernalNeigh(const int fd, char *pcBuf, int pcBufLen)
{
	int nRecvSize = 0;

	// 目的信息
	struct sockaddr_nl stDstAddrnl;
//	stDstSrcAddrnl.nl_family = AF_NETLINK;
//	stDstSrcAddrnl.nl_groups = RTMGRP_IPV4_ROUTE;
//	stDstSrcAddrnl.nl_pad = 0;
	//必要参数,sendto发送的目的必须pid为0,否则数据无法获取
	stDstAddrnl.nl_pid = 0;
	// 构造netlink socket请求头部
	struct
	{
		struct nlmsghdr nlh; //固定头部
		struct ndmsg msg; //根据需求选择不同结构体,route是rtmsg,neigh是ndmsg,其他情况看man手册
	} stReqHead;
	memset(&stReqHead, 0, sizeof(stReqHead));

	// 填充各字段的长度,这个需要具体问题具体解决,而且需要查找很多资料判断填充字段是否正确
	stReqHead.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct ndmsg));
	//必要参数,获取数据类型,并且与请求头部相对应
	stReqHead.nlh.nlmsg_type = RTM_GETNEIGH; //获取的数据类型,是获取路由信息或者MAC信息,具体情况参照man手册
	//必要参数,设置数据包为请求数据包或者是否一次性返回所有数据等参数
	stReqHead.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT | NLM_F_MATCH;
//	stReqHead.nlh.nlmsg_pid = 0;
//	stReqHead.nlh.nlmsg_seq = 1;
	
//	stReqHead.msg.rtm_family = AF_INET;
//	stReqHead.msg.rtm_table = RT_TABLE_MAIN;

	// 向内核发送请求信息
	if (sendto(fd, (void*)&stReqHead, sizeof(stReqHead), 0,
		(struct sockaddr *)&stDstAddrnl, sizeof(struct sockaddr)) == -1)
	{
		printf("向内核发送请求数据失败:%s\n", strerror(errno));
		return -1;
	}
	printf("向内核发送请求数据成功\n");

	nRecvSize = recvfrom(fd, pcBuf, pcBufLen, 0, NULL, NULL);
	if (nRecvSize == -1)
	{
		printf("从内核接收数据失败:%s\n", strerror(errno));
		return -1;
	}
	if (nRecvSize > pcBufLen)
	{
		printf("获取的数据长度超出了存储范围\n");
		return -1;
	}
	printf("从内核接收数据成功\n");

	return nRecvSize;
}

int GetKernalRoute(const int fd, char *pcBuf, int pcBufLen)
{
	int nRecvSize = 0;

	// 目的信息
	struct sockaddr_nl stDstSrcAddrnl;
//	stDstSrcAddrnl.nl_family = AF_NETLINK;
//	stDstSrcAddrnl.nl_groups = RTMGRP_IPV4_ROUTE;
//	stDstSrcAddrnl.nl_pad = 0;
	stDstSrcAddrnl.nl_pid = 0; //bi yao can shu 
	// 构造netlink socket请求头部
	struct
	{
		struct nlmsghdr nlh; //固定头部
		struct rtmsg msg; //具体请求数据头部
	} stReqHead;
	memset(&stReqHead, 0, sizeof(stReqHead));

	// 填充各字段的长度,这个需要具体问题具体解决,而且需要查找很多资料判断填充字段是否正确
	stReqHead.nlh.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
	stReqHead.nlh.nlmsg_type = RTM_GETROUTE; //bi yao can shu
	stReqHead.nlh.nlmsg_flags = NLM_F_REQUEST | NLM_F_ROOT | NLM_F_MATCH; //bi yao can shu
//	stReqHead.nlh.nlmsg_pid = 0;
//	stReqHead.nlh.nlmsg_seq = 1;
	
//	stReqHead.msg.rtm_family = AF_INET;
//	stReqHead.msg.rtm_table = RT_TABLE_MAIN;

	// 向内核发送请求信息
	if (sendto(fd, (void*)&stReqHead, sizeof(stReqHead), 0,
		(struct sockaddr *)&stDstSrcAddrnl, sizeof(struct sockaddr)) == -1)
	{
		printf("向内核发送请求数据失败:%s\n", strerror(errno));
		return -1;
	}
	printf("向内核发送请求数据成功\n");

	nRecvSize = recvfrom(fd, pcBuf, pcBufLen, 0, NULL, NULL);
	if (nRecvSize == -1)
	{
		printf("从内核接收数据失败:%s\n", strerror(errno));
		return -1;
	}
	if (nRecvSize > pcBufLen)
	{
		printf("获取的数据长度超出了存储范围\n");
		return -1;
	}
	printf("从内核接收数据成功\n");

	return nRecvSize;
}

/// 传入参数： cBuf 解析的数据内容
///            nRecvLen 解析数据内容长度
int ParseNeighData(char *cBuf, int nRecvLen)
{
	struct nlmsghdr *nlh; // 消息头

	struct ndmsg *neigh_entry;	// 路由表信息,主要存储数据属于哪个表
	struct rtattr *neigh_attr;	// 各条路由项信息,这个结构体包含各key:value
	int neigh_attr_len;

	nlh = (struct nlmsghdr *)cBuf;
	// 重复获取每条表项的所有内容
	for (; NLMSG_OK(nlh, nRecvLen); nlh=NLMSG_NEXT(nlh, nRecvLen))
	{
		char cNicName[64] = {0};
		unsigned short usState = 0;
		char cDst[32] = {0};
		unsigned char *cBuf;
		char cMac[32] = {0};
		int len;
		// 
		neigh_entry = (struct ndmsg *)NLMSG_DATA(nlh);
		if_indextoname(neigh_entry->ndm_ifindex, cNicName);
		usState = neigh_entry->ndm_state;
		//每条路由项信息各参数信息
		neigh_attr = (struct rtattr *)RTM_RTA(neigh_entry);
		neigh_attr_len = RTM_PAYLOAD(nlh);
		//printf("neigh_attr_len:%d\n", neigh_attr_len);
		//获取每条表项中具体各字段内容 
		for (; RTA_OK(neigh_attr, neigh_attr_len);
			 neigh_attr = RTA_NEXT(neigh_attr, neigh_attr_len))
		{
			if (neigh_attr->rta_type == NDA_DST)
			{
				//RTA_PAYLOAD宏,获取到当前字段数据具体内容的长度,
				//例如当前获取的是IP,占4个字节,而下面NDA_LLADDR所代表的是MAC,占6个字节
				len = RTA_PAYLOAD(neigh_attr);
				inet_ntop(AF_INET, RTA_DATA(neigh_attr), cDst, 32);
			}
			else if (neigh_attr->rta_type == NDA_LLADDR)
			{	
				len = RTA_PAYLOAD(neigh_attr);
				cBuf = (unsigned char *)RTA_DATA(neigh_attr);
				sprintf(cMac, "%02X:%02X:%02X:%02X:%02X:%02X", cBuf[0], cBuf[1],
					    cBuf[2], cBuf[3], cBuf[4], cBuf[5]);
			}
			else
			{
			}
		}
		
		if (nlh->nlmsg_type == RTM_NEWNEIGH)
		{
			printf("neigh add  ");
			printf("Nic:%-10s", cNicName);
			printf("State:%-10x", usState);
			printf("IP:%-20s", cDst);
			printf("Mac:%-10s\n", cMac);
		}
		else if (nlh->nlmsg_type == RTM_DELROUTE)
		{
			printf("neigh del  ");
			printf("Nic:%-10s", cNicName);
			printf("State:%-10x", usState);
			printf("IP:%-20s", cDst);
			printf("Mac:%-10s\n", cMac);
		}
		else
		{
		}
	}
	
	return 0;
}

int ParseRouteData(char *cBuf, int nRecvLen)
{
	struct nlmsghdr *nlh; // 消息头

	struct rtmsg *route_entry;	// 路由表信息,主要存储数据属于哪个表
	struct rtattr *route_attr;	// 各条路由项信息,这个结构体包含各key:value
	int route_attr_len = 0;

	nlh = (struct nlmsghdr *)cBuf;
	for (; NLMSG_OK(nlh, nRecvLen); nlh=NLMSG_NEXT(nlh, nRecvLen))
	{
		char cDst[32] = {0};
		char cNextHop[32] = {0};
		// 路由表信息
		route_entry = (struct rtmsg *)NLMSG_DATA(nlh);
		//每条路由项信息各参数信息
		route_attr = (struct rtattr *)RTM_RTA(route_entry);
		route_attr_len = RTM_PAYLOAD(nlh);
		for (; RTA_OK(route_attr, route_attr_len);
			 route_attr = RTA_NEXT(route_attr, route_attr_len))
		{
			if (route_attr->rta_type == RTA_DST)
			{
				
				inet_ntop(AF_INET, RTA_DATA(route_attr), cDst, 32);
			}
			else if (route_attr->rta_type == RTA_GATEWAY)
			{	
				inet_ntop(AF_INET, RTA_DATA(route_attr), cNextHop, 32);
			}
			else
			{
			}
		}
		
		if (nlh->nlmsg_type == RTM_NEWROUTE)
		{
			printf("add\t");
			printf("目标地址:%-20s", cDst);
			printf("下一跳地址:%-20s\n", cNextHop);
		}
		else if (nlh->nlmsg_type == RTM_DELROUTE)
		{
			printf("del\t");
			printf("目标地址:%-20s", cDst);
			printf("下一跳地址:%-20s\n", cNextHop);
		}
		else
		{
		}
	}
	
	return 0;
}


