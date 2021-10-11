#include <stdio.h>
#include "common.h"

int main(void)
{
//    IP_TYPE enIpType;
//    char cIp[] = "192.168.109.10";
//    char cIp6[] = "ABCD::1";
//    char cIpErr[] = "asdfasf";
//    char cMac[] = "00:98:09:19:10:11";
//    char cMacE[] = "pp:11:12:13:14:15";

//    enIpType = IsValuedIpAddr(cIp);
//    printf("ip类型:%d\n", enIpType);
//    enIpType = IsValuedIpAddr(cIp6);
//    printf("ip类型:%d\n", enIpType);
//    enIpType = IsValuedIpAddr(cIpErr);
//    printf("ip类型:%d\n", enIpType);
//    printf("是否为合法mac:%d\n", IsValuedMacAddr(cMac));
//    printf("是否为合法mac:%d\n", IsValuedMacAddr(cMacE));

//    NIC_INFO_VECTOR vNicInfo;
//    GetAllNicInfo(vNicInfo);
    int a=0;
    int i = IPv4_NetmaskToLen("255.255.255.128", &a);
    if (i)
    {
        printf("a=%d\n", a);
    }
//    IsValuedSubnetmaskAddr("255.255.255.247");
char cIp[IP_MAX_LEN];
IPv4_LenToNetmask(25, cIp, IP_MAX_LEN);
printf("%s\n", cIp);
    return 0;
}
