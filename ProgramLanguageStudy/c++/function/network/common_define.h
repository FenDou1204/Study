#ifndef COMMON_H_
#define COMMON_H_

#include <vector>

#ifdef IN
#undef IN
#endif
#define IN

#ifdef OUT
#undef OUT
#endif
#define OUT

#ifdef INOUT
#undef INOUT
#endif
#define INOUT

#ifdef version
#undef version
#endif
#define version "0.0.0.0"
/// v0.0.0.0	1. 添加判断IP是否为合规以及IP类型的函数
///		2. 添加判断MAC是否合规

#define FILE_NAME_MAX_LEN 		128
#define IP_MAX_LEN			64
#define NIC_NAME_MAX_LEN		16

typedef enum
{
	IP_TYPE_IPv4 = 0,
	IP_TYPE_IPv6,
	
	IP_TYPE_OTHER
} IP_TYPE;

typedef struct
{
    char			cNicName[NIC_NAME_MAX_LEN];		//网卡名称
    char			cIp[IP_MAX_LEN];			//IP地址
    char			cMask[IP_MAX_LEN];
    unsigned int		uiNicIndex;
    unsigned int		uiMaskLen;				//24->255.255.255.0
    IP_TYPE			enIpType;

} NIC_INFO;

/// 存放所有网卡信息的数组
typedef std::vector<NIC_INFO> NIC_INFO_VECTOR;


#endif
