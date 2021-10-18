# 基于Boost的CLI共享内存使用简介
本文主要介绍Boost库中，有关共享内存部分的一些使用方法。以及如何将这些应用在CLI子模块中，使子模块保存的数据能够在多进程中使用
## Boost简介
Boost是一个C++的第三方库，里面提供了大量轮子，能够实现一些现有C++没有的特性以及一些复杂功能的封装接口。

## 名词解释
- 共享内存：通过将同一块物理内存加载到不同程序中，使多个程序可以共同访问这块内存的方法。
- 容器：C++中一类用于存储数据的结构的统称，他们具有基本相同的操作接口。容器会自动管理使用到的内存，因此无法直接用到共享内存中。
- 分配器：Allocator，用于分配内存的接口，通过替换容器使用的分配器，可以使容器中自动分配的内存分配于共享内存空间
- 句柄：Handle，由于每个程序的都运行在自己的虚拟地址环境中，因此同一块物理内存在不通程序间的地址可能不同，这导致两程序间无法使用同样的指针访问同样的内容。但在共享内存中分配的空间指针，相对与共享内存的基址的偏移是固定的，因此可以使用这个偏移在不通程序间表示同一个共享内存地址。这个偏移被称为句柄。
## Boost共享内存接口
Boost库中与共享内存相关的头文件位于 bootst/interprocess 目录下，重点文件包括：
- managed_shared_memory.hpp， 用于对共享内存的申请释放等进行管理
- allocators/allocator.hpp， 提供基于共享内存的分配器模板
- containers/map.hpp等，提供可用于共享内存的std容器模板

在使用时，基本过程如下：
1. 修改或创建结构，使之能在共享内存中使用，包括：
 - 如过共享结构中有容器，则需要在结构的构造函数中增加内存分配器参数，并在初始化时将分配器通过构造参数传给容器
 - 如过共享结构中有指针，则该指针的空间需要在共享内存区域进行分配，并且需要将指针替换为handle_t类型。(因为各程序的内存地址空间不同，同一个指针在不同程序间会指向不同的地方。handle则代表该指针相对与共享内存起始地址的偏移，这个值是固定的)
4. 定义对要共享结构的内存分配器
5. 创建共享内存
6. 实例化共享内存分配器
7. 使用分配器作为参数为初始化共享结构

## Boost共享内存例子
```
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

int main ()
{
   using namespace boost::interprocess;
   //定义分配器
   typedef allocator<char, managed_shared_memory::segment_manager> 
      CharAllocator;
   //定义可在共享内存中使用的string
   typedef basic_string<char, std::char_traits<char>, CharAllocator>
      MyShmString;
   //定义可在共享内存使用的vector的分配器
   typedef allocator<MyShmString, managed_shared_memory::segment_manager>
      StringAllocator;      
   //定义可在共享内存使用的vector
   typedef vector<MyShmString, StringAllocator>
      MyShmStringVector;

   //通过变量的构造和析构函数，在程序启动或退出时自动清楚已有的同名共享内存
   struct shm_remove
   {
      shm_remove() { shared_memory_object::remove("MySharedMemory"); }
      ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
   } remover;

   //创建共享内存
   managed_shared_memory shm(create_only, "MySharedMemory", 10000);

   //实例化分配器
   CharAllocator     charallocator  (shm.get_segment_manager());
   StringAllocator   stringallocator(shm.get_segment_manager());

   //This string is in only in this process (the pointer pointing to the
   //buffer that will hold the text is not in shared memory). 
   //But the buffer that will hold "this is my text" is allocated from 
   //shared memory
   //使用分配器作为参数初始化可在共享内存中使用的string
   MyShmString mystring(charallocator);
   mystring = "this is my text";

   //This vector is only in this process (the pointer pointing to the
   //buffer that will hold the MyShmString-s is not in shared memory). 
   //But the buffer that will hold 10 MyShmString-s is allocated from 
   //shared memory using StringAllocator. Since strings use a shared 
   //memory allocator (CharAllocator) the 10 buffers that hold 
   //"this is my text" text are also in shared memory.
   //使用分配器初始化一个vector，该vector本身是本地变量，但vector中的string是在共享内存中的
   MyShmStringVector myvector(stringallocator);
   myvector.insert(myvector.begin(), 10, mystring);

   //This vector is fully constructed in shared memory. All pointers
   //buffers are constructed in the same shared memory segment
   //This vector can be safely accessed from other processes.
   //从共享内存中主动分配一个vector类型，该vector本身就存在于共享内存空间
   MyShmStringVector *myshmvector = 
      shm.construct<MyShmStringVector>("myshmvector")(stringallocator);
   myshmvector->insert(myshmvector->begin(), 10, mystring);

   //Destroy vector. This will free all strings that the vector contains
   shm.destroy_ptr(myshmvector);
   return 0;
}
```
## CLI共享内存接口
在CLI中，对共享内存的访问做了一层封装，以便简化及统一操作接口，如下：
- cli_shared.h
	- CLISharedAlloc： 从CLI的共享内存空间申请一块内存
	- CLISharedFree： 释放一块共享内存区域的内存
	- CLISharedGetData： 通过handle得到该共享内存在本地的指针
	- CLISharedGetHandle： 通过共享内存指针获得对应的handle
	- CLISharedGetBase： 获得CLI共享内存的内存管理器，必要时可通过该管理器分配或查找一个具有名称的共享内存空间
	- CLISharedGetAllocator： 获得CLI共享的分配器

## CLI共享内存例子
以改造后的deamo为例，在CLI中实现一个可共享数据的子模块的方法如下：
### 结构定义
```
typedef struct _item_data
{
    // char_string是可在共享内存中使用的string类型封装
    char_string strDesc;
    uint32_t uValue;

#ifdef _SHARED_MEM
    // 定义具有分配器的构造函数，以初始化结构中需要分配器分配的C++容器
    _item_data(const void_allocator &void_alloc)
    	// 所有容器均需要在构造函数中传入分配器
        :strDesc(void_alloc)
    {}
#else
#endif
} ITEM_DATA;

typedef struct _item
{
    ITEM_DATA   stData;
    char_string strName;
    uint64_t    uID;
#ifdef _SHARED_MEM
    _item(const void_allocator &void_alloc)
        :stData(void_alloc), strName(void_alloc)
    {}
#else
#endif
} ITEM;

#ifdef _SHARED_MEM
//	 使用boost的容器替换标准std容器，并定义对应的分配器
typedef boost::interprocess::allocator<ITEM, segment_manager_t> ITEM_ALLOCATOR;
typedef boost::interprocess::vector<ITEM, ITEM_ALLOCATOR> ITEM_VECTOR;
#else
typedef std::vector<ITEM> ITEM_VECTOR;
#endif
```
### 结构申请
可以用如下两种方式申请可共享结构：
```cpp
//	直接定义或使用new都可以分配可共享结构，构造时均需要传入分配器
ITEM item(*CLISharedGetAllocator());
pItem = new ITEM(*CLISharedGetAllocator());
```

### 结构赋值
结构创建后可以按正常方法使用，唯一要注意的是共享内存中的容器和std容器不能直接使用=赋值。
```cpp
    pItem->stData.strDesc = "";
    pItem->strName = "";
    pItem->uID = (uint32_t)-1;
    pItem->stData.uValue = 0;
    
    
    std::string strTmp = "asd";
    // 不能这么操作
    // pItem->strName = strTmp;
    // 应该这么操作
    pItem->strName = strTmp.c_str();
```
### 结构释放
new出来的共享结构，直接使用delete删除即可

## CLI共享内存注意事项
- 命名空间。由于boost提供的可在共享内存中的容器与std容器同名，因此如果在使用时用了 using namespace std::string或者 using std::string 这类语句，可能会导致容器冲突或产生预料之外的问题。因此在使用时请直接不要using命名空间，直接使用std::string表示普通容器，boost::interprocess::string表示共享内存容器
- 指针转成handle保存。对于容器，boost的容器已经封装好可以直接在共享内存中使用，但是指针还需要自己处理。在共享结构中，指针应当保存为handle，否则无法在两程序间使用。例：

```cpp
// 结构定义
struct _test
{
    // 使用handle保存要传输的指针
    CLI_SHARED_HANDLE Data;
}a;
// 分配共享内存空间
char *pTmp = CLISharedAlloc(3);
sprintf(pTmp, "12");
// 转换为handle存储及传输
a.Data = CLISharedGetHandle(pTmp);
// 通过handle得到数据指针
printf("%s\n", CLISharedGetData(a.Data))
// 释放共享内存
CLISharedFree(CLISharedGetData(a.Data))
```
- 对于不需要共享的程序，不用修改仍然能继续使用。
