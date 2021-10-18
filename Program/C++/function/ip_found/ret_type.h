#ifndef RET_TYPE_H
#define RET_TYPE_H

typedef  enum
{
    RET_OK                  = 0,
    RET_FAILED              = -1,

    RET_MALLOC_ERR          = -11

} RET_TYPE;

typedef enum
{
  IP_TYPE_IPv4 = 4,
  IP_TYPE_IPv6 = 6,
  IP_TYPE_OTHER = 99

} IP_TYPE;

#endif // RET_TYPE_H
