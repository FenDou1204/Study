#ifndef _NETLINK_SOCKET_H
#define _NETLINK_SOCKET_H


int InitSocket(void);

int GetKernalNeigh(const int fd, char *pcBuf, int pcBufLen);
int GetKernalRoute(const int fd, char *pcBuf, int pcBufLen);

int ParseNeighData(char *cBuf, int nRecvLen);
int ParseRouteData(char *cBuf, int nRecvLen);
#endif
