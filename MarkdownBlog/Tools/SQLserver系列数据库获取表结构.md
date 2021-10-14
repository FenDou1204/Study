# SQLserver 数据库获取表结构

## 参考链接
(https://www.cnblogs.com/xiaotiannet/p/3838150.html)[https://www.cnblogs.com/xiaotiannet/p/3838150.html]

## SQLserver2000

```sql
SELECT
    d.name N'TableName',
    d.xtype N'TableType',
    a.colorder N'ColumnIndex',
    a.name N'ColumnName',
    (case when COLUMNPROPERTY( a.id,a.name,'IsIdentity')=1 then '1'else '0' end) N'IdnetityFG',
    (case when (SELECT count(*)  FROM sysobjects  WHERE 
               (name in (SELECT name FROM sysindexes WHERE (id = a.id) AND 
                        (indid in (SELECT indid FROM sysindexkeys WHERE (id = a.id) AND 
                                  (colid in (SELECT colid FROM syscolumns WHERE (id = a.id) AND (name = a.name)))
                                  )
                        )
                        )
                ) AND (xtype = 'PK')
                )>0 then '1' else '0' end
    ) N'IsPK',
    b.name N'DataType',
    COLUMNPROPERTY(a.id,a.name,'PRECISION') as N'Length',
    (case when a.isnullable=1 then '1'else '0' end) N'IsNullable',
    isnull(e.text,'') N'Default',
    g.value N'Description'    
FROM   syscolumns   a 
    left join systypes b on   a.xtype=b.xusertype
    inner join sysobjects d on a.id=d.id   and   d.xtype in ('U','V') and   d.name<>'dtproperties'
    left join syscomments e on a.cdefault=e.id
    left join sysproperties g on a.id=g.id and a.colid=g.smallid 
WHERE a.xusertype = b.xusertype
	AND a.id = object_id('test1')
```


## SQLserver2005

```sql
SELECT
    d.name N'TableName',
    d.xtype N'TableType',
    a.colorder N'ColumnIndex',
    a.name N'ColumnName',
    (case when COLUMNPROPERTY( a.id,a.name,'IsIdentity')=1 then '1'else '0' end) N'IdnetityFG',
    (case when
        (SELECT count(*)  FROM sysobjects  WHERE 
            (name in
                (SELECT name FROM sysindexes WHERE (id = a.id) AND 
                    (indid in 
                        (SELECT indid FROM sysindexkeys WHERE (id = a.id) AND 
                            (
                                colid in (SELECT colid FROM syscolumns WHERE (id = a.id) AND (name = a.name))
                            )
                        )
                    )
                )
            ) AND (xtype = 'PK')
        )>0 then '1' else '0' end
    ) N'IsPK',
    b.name N'DataType',
    COLUMNPROPERTY(a.id,a.name,'PRECISION') as N'Length',
    (case when a.isnullable=1 then '1'else '0' end) N'IsNullable',
    isnull(e.text,'') N'Default',
    g.value N'Description'    
FROM   syscolumns   a 
    left join systypes b on   a.xtype=b.xusertype
    inner join sysobjects d on a.id=d.id   and   d.xtype in ('U','V') and   d.name<>'dtproperties'
    left join syscomments e on a.cdefault=e.id
    LEFT OUTER JOIN sys.extended_properties AS g ON a.id = g.major_id AND a.colid = g.minor_id
WHERE a.xusertype = b.xusertype
	AND a.id = object_id('test1')
```



