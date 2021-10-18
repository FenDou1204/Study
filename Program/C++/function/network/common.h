#include "common_define.h"

/// 判断是否为合法IP
IP_TYPE IsValuedIpAddr(IN const char *pcIpAddr);

/// 判断是否为合法MAC(正则表达式实现)
bool IsValuedMacAddr(IN const char *pcMacAddr);

/// 获取设备所有网口信息
bool GetAllNicInfo(INOUT NIC_INFO_VECTOR &vNicInfo);

/// 掩码长度转化为IP格式
bool IPv4_NetmaskToLen(IN const char *pcIp, INOUT int *piNetmaskLen);

/// IP格式掩码转换为长度
bool IPv4_LenToNetmask(IN const int iNetmaskLen, INOUT char *pcIp,
                       IN const int iIpLen);

/// 是否是合法的子网掩码地址
bool IsValuedSubnetmaskAddr(IN const char *pcSubnetmaskAddr);

////////////////////////////////////////////////////////////////////////////////////////////
//需要封装的另外一些函数
////////////////////////////////////////////////////////////////////////////////////////////

/// 判断一个IP地址是否为广播地址(最后一个字段是否为255，其他符合广播地址的情况IPv4 D类地址)
bool IsBroadcastIpAddr(IN const char *pcIpAddr)
