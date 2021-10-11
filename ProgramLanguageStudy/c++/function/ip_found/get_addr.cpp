#include <stdio.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <string>

#include "get_addr.h"
#include "ret_type.h"

using namespace std;

///获取网卡名称
static string GetNicName(IN const struct ifaddrs *pstMsg)
{
    return (*pstMsg).ifa_name;
}

///获取掩码长度
static string GetNicNetmask(IN const struct ifaddrs *pstMsg)
{
    return "";
}


static string GetNicIp(IN const struct ifaddrs *pstMsg)
{

    return "";
}


///获取IPv4地址信息
static string DealIPv4Msg(IN const struct ifaddrs *pstMsg)
{
    string strNicNameAndIp;
    strNicNameAndIp = GetNicName(pstMsg);
    char cIp[64] = "";
    inet_ntop(AF_INET,
              &(((struct sockaddr_in *)((*pstMsg).ifa_addr))->sin_addr),
              cIp, 64);

    strNicNameAndIp = strNicNameAndIp + ':' + '\t' + cIp;
    printf("%s\n", strNicNameAndIp.c_str());

    return strNicNameAndIp;
}

///获取IPv6地址信息
static string DealIPv6Msg(IN const struct ifaddrs *pstMsg)
{
    string strNicNameAndIp;
    strNicNameAndIp = GetNicName(pstMsg);
    char cIp[64] = "";
    inet_ntop(AF_INET6,
              &(((struct sockaddr_in6 *)((*pstMsg).ifa_addr))->sin6_addr),
              cIp, 64);

    strNicNameAndIp = strNicNameAndIp + ':' + '\t' + cIp;
    printf("%s\n", strNicNameAndIp.c_str());

    return strNicNameAndIp;
}
///判断获取的IP类型（只处理IPv4和IPv6）
static int JudegIpType(IN const struct ifaddrs *pstMsg)
{
    if(NULL == pstMsg)
    {
        return RET_FAILED;
    }
    if(pstMsg->ifa_addr->sa_family == AF_INET)
    {
        return IP_TYPE_IPv4;
    }
    if(pstMsg->ifa_addr->sa_family == AF_INET6)
    {
        return IP_TYPE_IPv6;
    }

    return  IP_TYPE_OTHER;
}

///
/// \brief GetAllIpAddr 获取所有的
/// \param strStorge
/// \return

bool GetAllIpAddr(INOUT string strStorge)
{
    int iRet = 0;
    int iIpType = 0;
    string strIp;
    struct ifaddrs *pstIf,*pstIfHead;

    iRet = getifaddrs(&pstIf);
    if(-1 == iRet)
    {
        perror("无法获取网卡信息:");
        return false;
    }
    pstIfHead = pstIf;
    for( ; NULL != pstIf; pstIf=(*pstIf).ifa_next)
    {
        if(NULL != (*pstIf).ifa_addr)
        {
            //判断IP地址类型
            iIpType = JudegIpType(pstIf);
            switch(iIpType)
            {
                case IP_TYPE_IPv4:
                    strIp = DealIPv4Msg(pstIf);
                    break;
                case IP_TYPE_IPv6:
                    strIp = DealIPv6Msg(pstIf);
                    break;
                default:
                    break;
            }
        }
    }
    freeifaddrs(pstIfHead);

    return true;
}


