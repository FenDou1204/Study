#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <net/if.h>

#include <errno.h>

#include <regex.h>

#include <string>

#include "common.h"

/// 執行正则表达式
static bool ExcuteRegex(IN const char *pcPattern, IN const char *pcValue)
{
    if (nullptr == pcPattern || nullptr == pcValue)
    {
        return false;
    }
    int iValue = 0;
    int iFlag = REG_EXTENDED | REG_NEWLINE | REG_NOSUB;

    regmatch_t pm[1];
    const size_t nmatch = 100;
    regex_t reg;
    // 编译正則表達式
    iValue = regcomp(&reg, pcPattern, iFlag);
    if (iValue != 0)
    {
        regfree(&reg);
        return false;
    }
    // 执行正则表达式
    iValue = regexec(&reg, pcValue, nmatch, pm, 0);
    regfree(&reg);
    if (iValue != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/// 输出网卡的详细信息
static void PrintNicInfo(NIC_INFO *pstNicInfo)
{
    printf("============\n");
    printf("NicName:%s\n", pstNicInfo->cNicName);
    printf("Ip:%s\n", pstNicInfo->cIp);
    printf("IpMask:%s\n", pstNicInfo->cMask);
    printf("IpType:%d\n", pstNicInfo->enIpType);
    printf("NicIndex:%u\n", pstNicInfo->uiNicIndex);
    printf("============\n\n");
}

//////////////////////////////////////////////////////////////////////////////////////

/// 是否为合法的IP地址
IP_TYPE IsValuedIpAddr(IN const char *pcIpAddr)
{
    if (NULL == pcIpAddr)
        return IP_TYPE_OTHER;

    char cIPv4Buf[sizeof(struct in_addr)] = {0};
    char cIPv6Buf[sizeof(struct in6_addr)] = {0};

    if (1 == inet_pton(AF_INET, pcIpAddr, cIPv4Buf))
        return IP_TYPE_IPv4;
    else if (1 == inet_pton(AF_INET6, pcIpAddr, cIPv6Buf))
        return IP_TYPE_IPv6;
    else
        return IP_TYPE_OTHER;
}

/// 是否为合法的MAC地址(正则表达式实现)
bool IsValuedMacAddr(IN const char *pcMacAddr)
{
    if (NULL == pcMacAddr)
        return false;
    const char *pcMacRegex = "([a-fA-F0-9]{2}[-:]){5}[a-fA-F0-9]{2}";
    if (true == ExcuteRegex(pcMacRegex, pcMacAddr))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/// 是否为合法的子网掩码(连续都为1,0-32个)(其他办法:转为2进制字符串,查看是否有01存在)
bool IsValuedSubnetmaskAddr(IN const char *pcSubnetmaskAddr)
{
    if (NULL == pcSubnetmaskAddr ||
        IP_TYPE_IPv4 != IsValuedIpAddr(pcSubnetmaskAddr))
        return false;
    unsigned int n[4]={0}, iTmp=0;
    if (EOF == sscanf(pcSubnetmaskAddr, "%u.%u.%u.%u",
                      &n[3], &n[2], &n[1], &n[0]))
    {
        return false;
    }
    for (int i=0; i<4; ++i)
    {
        // 转为32位无符号整形
        iTmp += (n[i]<<(i*8));
    }
    //取反加1肯定为2^n
    iTmp = ~iTmp + 1;
    if((iTmp&(iTmp-1)) == 0)
    {
        return true;
    }
    return false;
}

/// 获取设备的所有网卡信息
bool GetAllNicInfo(INOUT NIC_INFO_VECTOR &vNicInfo)
{
    vNicInfo.clear();
    NIC_INFO stNicInfoTmp;
    int iRet = 0;

    struct ifaddrs* ifa = NULL;
    iRet = getifaddrs(&ifa);
    if (-1 == iRet)
    {
        //printf("执行getifaddrs错误:%s\n", strerror(errno));
        return false;
    }

    struct ifaddrs *ifp = ifa;
    for (; ifp != NULL; ifp = ifp->ifa_next)
    {
        memset(&stNicInfoTmp, 0, sizeof(NIC_INFO));
        if (ifp->ifa_addr && ifp->ifa_addr->sa_family == AF_INET)
        {
            // 网卡IP
            inet_ntop(AF_INET,
                      &(((struct sockaddr_in*)ifp->ifa_addr)->sin_addr),
                      stNicInfoTmp.cIp,
                      IP_MAX_LEN);
            // 掩码长度
            inet_ntop(AF_INET,
                      &(((struct sockaddr_in*)ifp->ifa_netmask)->sin_addr),
                      stNicInfoTmp.cMask,
                      IP_MAX_LEN);
            // 网卡索引
            stNicInfoTmp.uiNicIndex = if_nametoindex(ifp->ifa_name);
            // 网卡名称
            strncpy(stNicInfoTmp.cNicName, ifp->ifa_name, NIC_NAME_MAX_LEN);
            // IP类型
            stNicInfoTmp.enIpType = IP_TYPE_IPv4;
            vNicInfo.push_back(stNicInfoTmp);
        }
        else if (ifp->ifa_addr && ifp->ifa_addr->sa_family == AF_INET6)
        {
            inet_ntop(AF_INET6,
                      &(((struct sockaddr_in6*)ifp->ifa_addr)->sin6_addr),
                      stNicInfoTmp.cIp,
                      IP_MAX_LEN);
            inet_ntop(AF_INET6,
                      &(((struct sockaddr_in6*)ifp->ifa_netmask)->sin6_addr),
                      stNicInfoTmp.cMask,
                      IP_MAX_LEN);
            // 网卡索引
            stNicInfoTmp.uiNicIndex = if_nametoindex(ifp->ifa_name);
            // 网卡名称
            strncpy(stNicInfoTmp.cNicName, ifp->ifa_name, NIC_NAME_MAX_LEN);
            // IP类型
            stNicInfoTmp.enIpType = IP_TYPE_IPv6;
            vNicInfo.push_back(stNicInfoTmp);
        }
        else
        {
            continue;
        }
        PrintNicInfo(&stNicInfoTmp);
    }

    freeifaddrs(ifa);
    return true;
}

/// 获取指定网口的IP地址信息
bool GetIpFromSpecialIp(IN const char *pcNicName, NIC_INFO_VECTOR &vNicInfo)
{
    vNicInfo.clear();
    NIC_INFO stNicInfoTmp;
    if (NULL == pcNicName)
    {
        return false;
    }
    memset(&stNicInfoTmp, 0, sizeof(NIC_INFO));

    return true;
}

/// 掩码长度转换为IP格式
bool IPv4_LenToNetmask(IN const int iNetmaskLen, INOUT char *pcIp,
                       IN const int iIpLen)
{
    if (iNetmaskLen < 0 || iNetmaskLen > 32)
    {
        return false;
    }
    memset(pcIp, 0, iIpLen);
    unsigned int ip_num = 0;

    if (iNetmaskLen == 8)
    {
        strncpy(pcIp, "255.0.0.0", iIpLen);
        return true;
    }
    if (iNetmaskLen == 16)
    {
        strncpy(pcIp, "255.255.0.0", iIpLen);
        return true;
    }
    if (iNetmaskLen == 24)
    {
        strncpy(pcIp, "255.255.255.0", iIpLen);
        return true;
    }
    if (iNetmaskLen == 32)
    {
        strncpy(pcIp, "255.255.255.255", iIpLen);
        return true;
    }

    for (int i = iNetmaskLen, j = 31; i > 0; i--, j--)
    {
        ip_num += (1<<j);
    }
    snprintf(pcIp, iIpLen, "%hhu.%hhu.%hhu.%hhu", (ip_num>>24)&0xff,
             (ip_num>>16)&0xff, (ip_num>>8)&0xff, ip_num&0xff);

    return true;
}

std::string IPv4_LenToNetmask(IN const int iNetmaskLen)
{
    if (iNetmaskLen < 0 || iNetmaskLen > 32)
    {
        return NULL;
    }
    unsigned int ip_num = 0;
    char cIp[IP_MAX_LEN] = {0};

    for (int i = iNetmaskLen, j = 31; i > 0; i--, j--)
    {
        ip_num += (1<<j);
    }
    snprintf(cIp, IP_MAX_LEN, "%hhu.%hhu.%hhu.%hhu", (ip_num>>24)&0xff,
             (ip_num>>16)&0xff, (ip_num>>8)&0xff, ip_num&0xff);

    return cIp;
}

/// IP格式掩码转换为长度
bool IPv4_NetmaskToLen(IN const char *pcIp, INOUT int *piNetmaskLen)
{
    if (!IsValuedSubnetmaskAddr(pcIp))
    {
        return false;
    }
    if (NULL == pcIp)
    {
        return false;
    }

    unsigned int uiIpNum = 0;
    unsigned char c1,c2,c3,c4;
    int iNetMaskLen = 0;

    if (EOF == sscanf(pcIp, "%hhu.%hhu.%hhu.%hhu", &c1, &c2, &c3, &c4))
    {
        return false;
    }
    // IP地址转换为uint值
    uiIpNum = c1<<24 | c2<<16 | c3<<8 | c4;

    if (uiIpNum == 0xffffffff)
    {
       *piNetmaskLen = 32;
       return true;
    }
    else if (uiIpNum == 0xffffff00)
    {
       *piNetmaskLen = 24;
       return true;
    }
    else if (uiIpNum == 0xffff0000)
    {
       *piNetmaskLen = 16;
       return true;
    }
    else if (uiIpNum == 0xff000000)
    {
       *piNetmaskLen = 8;
       return true;
    }

    for (int i = 0; i < 32; i++)
    {
        if ((uiIpNum<<i) & 0x80000000)
            iNetMaskLen++;
        else
            break;
    }
    *piNetmaskLen = iNetMaskLen;
    return true;
}

int IPv4_NetmaskToLen(IN const char *pcIp)
{
    if (!IsValuedSubnetmaskAddr(pcIp))
    {
        return -1;
    }
    if (NULL == pcIp)
    {
        return -1;
    }

    unsigned int uiIpNum = 0;
    unsigned char c1,c2,c3,c4;
    int iNetMaskLen = 0;

    if (EOF == sscanf(pcIp, "%hhu.%hhu.%hhu.%hhu", &c1, &c2, &c3, &c4))
    {
        return -1;
    }
    // IP地址转换为uint值
    uiIpNum = c1<<24 | c2<<16 | c3<<8 | c4;

    for (int i = 0; i < 32; i++)
    {
        if ((uiIpNum<<i) & 0x80000000)
            iNetMaskLen++;
        else
            break;
    }
    return iNetMaskLen;
}
