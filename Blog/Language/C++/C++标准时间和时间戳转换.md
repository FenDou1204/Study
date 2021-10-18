# 标准时间和时间戳的转换

## 标准日期转换为时间戳	

```c++
time_t date_to_timestamp(char *date, char *pfmt)
{
    struct tm t;
    strptime(date, pfmt, &t);
    time_t tt = mktime(&t);
    return tt;
}
```

## 时间戳转换为标准时间 

```c++
string  timestamp_to_date(time_t tt)
{
    struct tm *t = localtime(&tt);
    char dateBuf[128];
    snprintf(dateBuf, sizeof(dateBuf),
    "%04d-%02d-%02d %02d:%02d:%02d",
    t->tm_year+1900,
    t->tm_mon+1,
    t->tm_mday,
    t->tm_hour,
    t->tm_min,
    t->tm_sec);

    string date(dateBuf);
    return date;
}
```