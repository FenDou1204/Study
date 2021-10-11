#include <stdio.h>
#include <string.h>
#include "netlink_socket.h"

int main(void)
{
	int iSock, iDataLen;
	char cBuf[128*1024] = {0};
	iSock = InitSocket();
	
	iDataLen = GetKernalNeigh(iSock, cBuf, sizeof(cBuf));
	ParseNeighData(cBuf, iDataLen);
	
	memset(cBuf, 0, sizeof(cBuf));
	iSock = InitSocket();
	iDataLen = GetKernalRoute(iSock, cBuf, sizeof(cBuf));
	ParseRouteData(cBuf, iDataLen);
}
