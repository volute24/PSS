#ifndef _DEFINE_H
#define _DEFINE_H

// Define.h
// 这里定义所有服务器用到的通用的东西，在这里加载一些ace的头和通用的一些数据方法
// add by freeeyes
// 2008-12-22

#include "ace/SString.h"
#include "ace/Malloc.h"
#include "ace/Malloc_T.h"
#include "ace/Task_T.h"
#include "ace/Local_Memory_Pool.h"
#include "ace/Time_Value.h"
#include "ace/OS_main.h"
#include "ace/OS_NS_sys_stat.h"
#include "ace/OS_NS_sys_socket.h"
#include "ace/OS_NS_unistd.h"
#include "ace/OS_NS_string.h"
#include "ace/High_Res_Timer.h"
#include "ace/INET_Addr.h"
#include "ace/Hash_Map_Manager.h"
#include "ace/Date_Time.h"
#include <math.h>
#include <type_traits>
#include <fstream>

#ifndef WIN32
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#endif

#include <memory>
#include <vector>

using namespace std;

#define NAMESPACE PSS
#define BEGIN_NAMESPACE namespace NAMESPACE{
#define END_NAMESPACE }
#define USING_NAMESPACE using namespace NAMESPACE;

BEGIN_NAMESPACE

//自动判定操作系统
#define PLATFORM_WIN     0
#define PLATFORM_UNIX    1
#define PLATFORM_APPLE   2

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) || defined(WIN64) || defined(_WIN64)
#  define PSS_PLATFORM PLATFORM_WIN
#elif defined(__APPLE_CC__)
#  define PSS_PLATFORM PLATFORM_APPLE
#else
#  define PSS_PLATFORM PLATFORM_UNIX
#endif

#ifndef NULL
#define NULL 0
#endif

#define MAINCONFIG            "main.xml"
#define ALERTCONFIG           "alert.xml"
#define FORBIDDENIP_FILE      "forbiddenIP.xml"
#define CONSOLECONFIG         "ConsoleCommand.xml"

#define MAX_BUFF_9    9
#define MAX_BUFF_20   20
#define MAX_BUFF_50   50
#define MAX_BUFF_100  100
#define MAX_BUFF_200  200
#define MAX_BUFF_300  300
#define MAX_BUFF_500  500
#define MAX_BUFF_1000 1000
#define MAX_BUFF_1024 1024
#define MAX_BUFF_10240 10240

#define INT32 int32_t

#define THREAD_PARAM THR_NEW_LWP | THR_BOUND | THR_DETACHED

/*
//计算当前版本号是否与制定版本好一致
static bool Convert_Version(int nTagVserion)
{
    int nCurrVserion = 0;
    nCurrVserion += (int)ACE::major_version() * 1000;
    nCurrVserion += (int)ACE::minor_version() * 100;
    nCurrVserion += (int)ACE::beta_version();

    if(nTagVserion >= nCurrVserion)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#define CONVERT_ACE_VERSION Convert_Version(6200)
*/
#define CONSOLE_PACKET_MAX_SIZE  200 //声明console的数据包大小

//根据不同的操作系统，定义不同的recv接收参数类型
#if PSS_PLATFORM == PLATFORM_WIN
#define MSG_NOSIGNAL          0            //信号量参数（WINDOWS）
#endif

#define SERVER_ACTOR_REACTOR  0
#define SERVER_ACTOR_PROACTOR 1

#define SERVER_ACTOR_TYPE     SERVER_ACTOR_PROACTOR         //当前服务器所用的架构类型，可以是Proactor，也可以是Reactor

#define MAX_DEV_POLL_COUNT    5000         //Devpoll处理链接的最大个数

#define CONSOLE_ENABLE        1            //打开后台端口
#define CONSOLE_DISABLE       0            //关闭后台端口

#define CONNECT_CLOSE_TIME    2            //链接缓冲关闭时间延迟

#define MAX_MSG_THREADCOUNT   1            //默认的逻辑线程处理数
#define MAX_MSG_THREADQUEUE   60000        //处理线程的消息队列数
#define MAX_MSG_TIMEDELAYTIME 60           //逻辑线程自检时间间隔
#define MAX_MSG_STARTTIME     1            //逻辑线程处理开始时间
#define MAX_MSG_MASK          64000        //逻辑Mark的线程数
#define MAX_MSG_PUTTIMEOUT    100          //放入逻辑的延迟
#define MAX_MSG_SENDPACKET    10           //最多缓冲发送包的个数,多于这个数字报警并丢弃下一个发送数据包
#define MAX_MSG_SNEDTHRESHOLD 10           //发送阀值(消息包的个数)
#define MAX_MSG_SENDCHECKTIME 100          //每隔多少毫秒进行一次发送的阀值
#define MAX_MSG_THREADTIMEOUT 30           //线程判定超时
#define MAX_MSG_PACKETTIMEOUT 5            //处理数据包超时时间
#define MAX_MSG_SOCKETBUFF    50*1024      //接收数据缓存大小
#define MAX_MSG_SENDTIMEOUT   5            //发送超时时间
#define MAX_MSG_HANDLETIME    120          //统计当前连接数的间隔
#define MAX_MSG_SENDALIVETIME 60           //发送存活包的时间间隔
#define MAX_MSG_SENDALCOUNT   5            //判定链接是否存活的极限
#define MAX_MSG_PACKETLENGTH  20*1024      //最大单一数据包长度限制 
#define MAX_MP_POOL           5000         //_MakePacket交换池里面的大小
#define MAX_HANDLE_POOL       1000         //默认Handler对象池的大小
#define MAX_ASYNCH_BACKLOG    100          //默认设置的BACKLOG数量
#define MAX_LOADMODEL_CLOSE   5            //默认等待模块关闭时间
#define MAX_CONNECT_COUNT     10000        //默认单位时间最大链接重连次数
#define MAX_BLOCK_SIZE        2048         //默认阻塞缓冲数据块的大小
#define MAX_BLOCK_COUNT       3            //默认最大的Block次数
#define MAX_BLOCK_TIME        1            //默认等待重发时间（单位是秒）
#define MAX_QUEUE_TIMEOUT     20           //默认队列超时处理时间
#define MAX_RECV_UDP_TIMEOUT  3            //最大接收超时时间(UDP) 

#define PACKET_PARSE          1            //消息处理包标志
#define PACKET_CONNECT        2            //链接建立事件消息标志
#define PACKET_CDISCONNECT    3            //客户端断开事件消息标志
#define PACKET_SDISCONNECT    4            //服务器断开事件消息标志
#define PACKET_SEND_ERROR     5            //数据发送失败事件 
#define PACKET_SEND_TIMEOUT   6            //服务器发送时间超过阀值的标志
#define PACKET_CHEK_TIMEOUT   7            //服务器心跳检测超时事件
#define PACKET_SEND_OK        8            //发送成功回执
#define PACKET_TTY_CONNECT    9            //TTy设备连接
#define PACKET_TTY_DISCONNECT 10           //TTy设备断开连接
#define PACKET_SERVER_TCP_CONNECT 11       //服务器间通讯Tcp连接建立
#define PACKET_SERVER_TCP_DISCONNECT 12    //服务器间通讯Tcp连接断开
#define PACKET_SERVER_UDP_CONNECT 13       //服务器间通讯Tcp连接建立
#define PACKET_SERVER_UDP_DISCONNECT 14    //服务器间通讯Tcp连接断开

#define MAX_PACKET_PARSE      5000         //PACKETPARSE对象池个数
#define MAX_MESSAGE_POOL      5000         //Message对象池个数

#define BUFFPACKET_MAX_COUNT  5000         //初始化BuffPacket包缓冲池的个数
#define SENDQUEUECOUNT        1            //默认发送线程队列的数量

#define MAX_POSTMESSAGE_SIZE  65536        //最大的PostMessage循环

#define MAX_TIMERMANAGER_THREADCOUNT      1   //Timer管理器的最大线程数

#define PARM_CONNECTHANDLE_CHECK          2   //定时器发送包检测
#define PARM_HANDLE_CLOSE                 1   //定时器句柄关闭

#define HANDLE_ISCLOSE_NO                 0      //连接已经关闭
#define HANDLE_ISCLOSE_YES                1      //连接目前正常

#define TYPE_IPV4                         1      //IPv4标准
#define TYPE_IPV6                         2      //IPv6标准

#define MAX_UDP_PACKET_LEN                1024   //UDP数据包的最大大小
#define UDP_HANDER_ID                     0      //默认UDP的ConnectID

#define COMMAND_TYPE_IN                   0      //进入服务器命令包状态（用于CommandData，统计命令信息类）
#define COMMAND_TYPE_OUT                  1      //出服务器的命令包状态（用于CommandData，统计命令信息类）

#define PACKET_WITHSTREAM                 0      //不带包头的数据流模式
#define PACKET_WITHHEAD                   1      //带包头的数据包模式

#define PACKET_GET_ENOUGH                 0      //得到完整的数据包，需要继续接收
#define PACKET_GET_NO_ENOUGH             1      //得到的数据包不完整
#define PACKET_GET_ERROR                  2      //数据包格式错误

#define MAX_PACKET_SIZE     1024*1024            //最大允许的包尺寸

#define PACKET_IS_FRAMEWORK_RECYC         true   //框架回收（数据包回收机制）
#define PACKET_IS_SELF_RECYC              false  //由逻辑自己回收（数据包回收机制）

#define CONNECT_LIMIT_RETRY 30                   //初始化中间服务器链接后定期检查，单位是秒

#define TCP_NODELAY_ON      0                    //TCP Nagle算法开关开关打开
#define TCP_NODELAY_OFF     1                    //TCP Nagle算法开关开关关闭

//输出json的内容
#define OUTPUT_CHART_JSON_X "{\"type\": \"category\",\"data\": [%s]}\n"
#define OUTPUT_CHART_JSON_Y "{\"name\":\"%d\",\"type\": \"line\",\"smooth\": \"true\",\"data\": [%s]}\n"
#define OUTPUT_CHART_JSON "{\"title\": {\"text\": \"%s\"},\"tooltip\" : {}, \
\"legend\" : {\"data\":[\"time\"]},\"xAxis\" : %s,\"yAxis\" : {\"type\":\"value\"}, \"series\": [%s]}"

//数据来源
enum class EM_PACKET_RESOURCE
{
    PACKET_RESOURCE_FROM_CLIENT = 0,      //客户端数据包
    PACKET_RESOURCE_FROM_SERVER,          //服务器间数据包
};

//连接的性质类型
enum class EM_CONNECT_IO_TYPE
{
    CONNECT_IO_TCP = 0,      //IO是TCP
    CONNECT_IO_UDP,          //IO是UDP
    CONNECT_IO_TTY,          //IO是TTY
    CONNECT_IO_SERVER_TCP,   //IO是服务期间连接TCP
    CONNECT_IO_SERVER_UDP    //IO是服务期间连接UDP
};

//服务器间通讯和TTy通讯的处理模式，可以选择是框架处理还是业务处理
enum class EM_CONNECT_IO_DISPOSE
{
    CONNECT_IO_FRAME = 0,     //框架PacketParse处理
    CONNECT_IO_PLUGIN         //插件自己处理
};

//UDP的播放模式
enum class EM_UDP_TYPE
{
    UDP_SINGLE = 0,        //UDP单独连接
    UDP_BROADCAST,         //UDP广播
};

//对Handler接收数据入口类型的定义
enum class EM_IO_TYPE
{
    NET_INPUT = 0,      //网络入口
    FILE_INPUT,         //文件入口
};

//对应当前框架支持的网络模式
enum class NETWORKMODE
{
    NETWORKMODE_PRO_IOCP    = 1,    //IOCP模式
    NETWORKMODE_RE_SELECT   = 10,   //Select模式
    NETWORKMODE_RE_TPSELECT = 11,   //TPSelect模式
    NETWORKMODE_RE_EPOLL    = 12,   //epolllt模式(水平触发)
    NETWORKMODE_RE_EPOLL_ET = 13,   //epollet模式(边沿触发)
};

//对应链接的状态，用于设置链接时候的状态
enum class CONNECTSTATE
{
    CONNECT_INIT         = 0,
    CONNECT_OPEN         = 1,
    CONNECT_RECVGEGIN    = 2,
    CONNECT_RECVGEND     = 3,
    CONNECT_SENDBEGIN    = 4,
    CONNECT_SENDEND      = 5,
    CONNECT_SERVER_CLOSE = 6,
    CONNECT_CLIENT_CLOSE = 7,
    CONNECT_RECVERROR    = 8,
    CONNECT_SENDERROR    = 9,
    CONNECT_SENDBUFF     = 10,
    CONNECT_SENDNON      = 11,
};

//服务器间通讯，是否需要回调的枚举
enum class EM_s2s
{
    S2S_NEED_CALLBACK = 0,    //需要回调
    S2S_INNEED_CALLBACK,      //不需要回调
};

//对应处理线程的状态
enum class THREADSTATE
{
    THREAD_INIT      = 0,   //线程初始化
    THREAD_RUNBEGIN  = 1,   //开始处理线程
    THREAD_RUNEND    = 2,   //处理数据结束
    THREAD_BLOCK     = 3,   //线程阻塞
};

//对应服务器间通讯的传输状态
enum class EM_Server_Connect_State
{
    SERVER_CONNECT_READY = 0,
    SERVER_CONNECT_FIRST,
    SERVER_CONNECT_OK,
    SERVER_CONNECT_FAIL,
    SERVER_CONNECT_RECONNECT,
};

//服务器间通讯数据接收状态
#define SERVER_RECV_TIMEOUT    20   //服务器间接收数据超时时间
enum class EM_Server_Recv_State
{
    SERVER_RECV_INIT = 0,     //未接收数据
    SERVER_RECV_BEGIN,        //接收数据完成
    SERVER_RECV_END,          //处理数据完成
};

//启动文件测试结果的定义
enum class FILE_TEST_RESULT
{
	RESULT_ERR_UNKOWN = -1,   //未知错误
	RESULT_OK = 0,            //启动成功
	RESULT_ERR_TESTING,       //正在测试
	RESULT_ERR_CFGFILE,       //配置文件错误
	RESULT_ERR_PROFILE,       //协议文件错误
};

enum class EM_SEND_PACKET_PARSE
{
    EM_SENDMESSAGE_NOMAL = 0,      //默认发送数据包模式(走PacketPrase端口)
    EM_SENDMESSAGE_JAMPNOMAL,      //发送数据包模式(不走PacketPrase端口)
};

//日志编号声明
const int LOG_SYSTEM                  = 1000;
const int LOG_SYSTEM_ERROR            = 1001;
const int LOG_SYSTEM_CONNECT          = 1002;
const int LOG_SYSTEM_WORKTHREAD       = 1003;
const int LOG_SYSTEM_POSTTHREAD       = 1004;
const int LOG_SYSTEM_UDPTHREAD        = 1005;
const int LOG_SYSTEM_POSTCONNECT      = 1006;
const int LOG_SYSTEM_PACKETTIME       = 1007;
const int LOG_SYSTEM_PACKETTHREAD     = 1008;
const int LOG_SYSTEM_CONNECTABNORMAL  = 1009;
const int LOG_SYSTEM_RECVQUEUEERROR   = 1010;
const int LOG_SYSTEM_SENDQUEUEERROR   = 1011;
const int LOG_SYSTEM_COMMANDDATA      = 1012;
const int LOG_SYSTEM_CONSOLEDATA      = 1013;
const int LOG_SYSTEM_DEBUG_CLIENTRECV = 1014;
const int LOG_SYSTEM_DEBUG_CLIENTSEND = 1015;
const int LOG_SYSTEM_DEBUG_SERVERRECV = 1016;
const int LOG_SYSTEM_DEBUG_SERVERSEND = 1017;
const int LOG_SYSTEM_MONITOR          = 1018;

const int DEBUG_ON  = 1;
const int DEBUG_OFF = 0;

/**
* Format a message to the thread-safe ACE logging mechanism.  Valid
* options (prefixed by '%', as in printf format strings) include:
*  - 'A': print an ACE_timer_t value (which could be either double
*         or ACE_UINT32.)
*  - 'a': abort the program at this point abruptly.
*  - 'b': print a ssize_t value
*  - 'B': print a size_t value
*  - 'c': print a character
*  - 'C': print a char* character string (also see s and W)
*  - 'i', 'd': print a decimal number
*  - 'I': indent according to nesting depth (obtained from
*         ACE_Trace::get_nesting_indent()).
*  - 'e', 'E', 'f', 'F', 'g', 'G': print a double
*  - 'l': print line number where an error occurred.
*  - 'M': print the name of the priority of the message.
*  - 'm': return the message corresponding to errno value, e.g., as
*         done by strerror()
*  - 'N': print file name where the error occurred.
*  - 'n': print the name of the program (or "<unknown>" if not set)
*  - 'o': print as an octal number
*  - 'P': print out the current process id
*  - 'p': print out the appropriate errno message from sys_errlist,
*         e.g., as done by perror()
*  - 'Q': print out the uint64 number
*  - 'q': print out the int64 number
*  - '@': print a void* pointer (in hexadecimal)
*  - 'r': call the function pointed to by the corresponding argument
*  - 'R': print return status
*  - 'S': print out the appropriate signal message corresponding
*         to var-argument, e.g., as done by strsignal()
*  - 's': prints a ACE_TCHAR* character string (also see C and W)
*  - 'T': print timestamp in hour:minute:sec:usec format (plain option,
*         i.e. without any flags, prints system supplied timestamp;
*         with '#' flag added expects ACE_Time_Value* in argument list)
*  - 'D': print timestamp as Weekday Month day year hour:minute:sec.usec
*         (plain option, i.e. without any flags, prints system supplied
*         timestamp; with '#' flag added expects ACE_Time_Value* in
*         argument list)
*  - 't': print thread id (1 if single-threaded)
*  - 'u': print as unsigned int
*  - 'w': prints a wide character
*  - 'W': prints a wchar_t* character string (also see C and s)
*  - 'x': print as a hex number
*  - 'X': print as a hex number
*  - 'z': print an ACE_OS::WChar character
*  - 'Z': print an ACE_OS::WChar character string
*  - ':': print a time_t value as an integral number
*  - '%': print out a single percent sign, '%'
*  - '?': print out stack trace (see Stack_Trace.h header comments)
*/
#define OUR_DEBUG(X) { ACE_DEBUG((LM_INFO, "[%D %P|%t][%N,%l]")); ACE_DEBUG(X); }

//*****************************************************************
//增加两个特殊的命令头，一个是链接建立，一个是链接退出
#define CLIENT_LINK_CONNECT        0x0001      //用户链接
#define CLIENT_LINK_CDISCONNET     0x0002      //客户端退出
#define CLIENT_LINK_SDISCONNET     0x0003      //服务器退出
#define CLINET_LINK_SENDTIMEOUT    0x0004      //服务器发送客户端时间超过阀值
#define CLINET_LINK_SENDERROR      0x0005      //客户端发送失败消息 
#define CLINET_LINK_CHECKTIMEOUT   0x0006      //服务器心跳检测超时消息  
#define CLIENT_LINK_SENDOK         0x0007      //服务器发送成功回执
#define CLINET_LINK_TTY_CONNECT    0x0008      //tty建立连接
#define CLINET_LINK_TTY_DISCONNECT 0x0009      //tty断开建立连接
#define CLINET_LINK_ST_CONNECT     0x000a      //服务器间TCP连接
#define CLINET_LINK_ST_DISCONNECT  0x000b      //服务器间TCP连接断开
#define CLINET_LINK_SU_CONNECT     0x000c      //服务器间UDP连接
#define CLINET_LINK_SU_DISCONNECT  0x000d      //服务器间UDP连接断开
#define CLINET_LINK_HANDLER_CLOSE  0x000e      //发送服务器断开指令 
#define CLIENT_LINK_USER           0x0100      //用户信令开始序列头部
//*****************************************************************

//*****************************************************************
//位操作运算符
#define BIT_SET(a,b) if((int)(sizeof(a)) * 8 > b && b >= 0) { ((a) |= ((long long)1<<(b))); }
#define BIT_CLEAR(a,b) if((int)(sizeof(a)) * 8 > b && b >= 0) { ((a) &= ~((long long)1<<(b))); }
#define BIT_FLIP(a,b) if((int)(sizeof(a)) * 8 > b && b >= 0) { ((a) ^= ((long long)1<<(b))); }
#define BIT_CHECK(a,b)  if((int)(sizeof(a)) * 8 > b && b >= 0) { ((a) & ((long long)1<<(b))); }
//*****************************************************************

//*****************************************************************

//定义一个内存管理分配器
typedef  ACE_Malloc<ACE_LOCAL_MEMORY_POOL, ACE_SYNCH_MUTEX> MUTEX_MALLOC;
typedef ACE_Allocator_Adapter<MUTEX_MALLOC> Mutex_Allocator;

#ifndef uint8
typedef ACE_UINT8 uint8;
#endif

#ifndef uint16
typedef ACE_UINT16 uint16;
#endif

#ifndef uint32
typedef ACE_UINT32 uint32;
#endif

#ifndef uint64
typedef ACE_UINT64 uint64;
#endif

#ifndef int8
typedef char int8;
#endif

#ifndef int16
typedef short int16;
#endif

#ifndef int32
typedef INT32 int32;
#endif

#ifndef int64
typedef ACE_INT64 int64;
#endif

#ifndef float32
typedef float float32;
#endif

#ifndef float64
typedef double float64;
#endif

#ifdef UNICODE
typedef wofstream _tofstream;
typedef wifstream _tifstream;
typedef std::wstring _tstring;
#else
typedef ofstream _tofstream;
typedef ifstream _tifstream;
typedef std::string _tstring;
#endif // UNICODE

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) if( (x) != NULL ) {delete (x); (x) = NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x) if( (x) != NULL ) {delete[] (x); (x) = NULL; }
#endif

template<typename T>
struct item_return
{
    using type = T && ;
};

template<typename T>
inline typename item_return<T>::type convert(T&& arg)
{
    return static_cast<T&&>(arg);
}

//定义一个函数，可以支持内存越界检查
inline void sprintf_safe(char* szText, int nLen, const char* fmt ...)
{
    if(szText == NULL)
    {
        return;
    }

    va_list ap;
    va_start(ap, fmt);

    ACE_OS::vsnprintf(szText, nLen, fmt, ap);
    szText[nLen - 1] = '\0';

    va_end(ap);
};

//支持memcpy的边界检查
inline bool memcpy_safe(const char* pSrc, uint32 u4SrcLen, char* pDes, uint32 u4DesLen, bool blIsString = false)
{
    if(u4SrcLen > u4DesLen)
    {
        return false;
    }
    else
    {
        ACE_OS::memcpy((void* )pDes, (void* )pSrc, (size_t)u4SrcLen);

        if (u4DesLen > u4SrcLen && true == blIsString)
        {
            //如果是文本，拷贝后末尾补\0结尾
            pDes[u4SrcLen] = '\0';
        }

        return true;
    }
}

//支持strcpy边界检查
inline bool strcpy_safe(const char* pSrc, char* pDes, int nDesLen)
{
    int nSrcLen = (int)ACE_OS::strlen(pSrc);

    if(nSrcLen <= 0 || nDesLen <= 0 || nSrcLen > nDesLen)
    {
        return false;
    }
    else
    {
        ACE_OS::strcpy(pDes, (const char* )pSrc);
        return true;
    }
}

//支持strcat边界检查
inline bool strcat_safe(const char* pSrc, char* pDes, int nDesLen)
{
    int nCurrSrcLen = (int)ACE_OS::strlen(pSrc);
    int nCurrDesLen = (int)ACE_OS::strlen(pDes);

    if(nDesLen <= 0 || nDesLen <= nCurrSrcLen + nCurrDesLen)
    {
        return false;
    }
    else
    {
        ACE_OS::strcat(pDes, (const char* )pSrc);
        return true;
    }
}

//支持memmove边界检查
inline bool memmove_safe(char* pSrc, uint32 u4SrcLen, char* pDes, uint32 u4DesLen)
{
    if(u4SrcLen > u4DesLen)
    {
        return false;
    }
    else
    {
        ACE_OS::memmove((void* )pDes, (void* )pSrc, (size_t)u4SrcLen);
        return true;
    }
}

//打印指定的Messahe_Block中的信息到屏幕
inline void Print_Binary(ACE_Message_Block* pMessageBlock)
{
    if(NULL != pMessageBlock)
    {
        char* pData = pMessageBlock->rd_ptr();
        int32 nLen = (int32)pMessageBlock->length();
        OUR_DEBUG((LM_INFO, "[Print_Binary]"));

        for(int32 i = 0; i < nLen; i++)
        {
            OUR_DEBUG((LM_INFO, " %02x", (unsigned char)pData[i]));
        }

        OUR_DEBUG((LM_INFO, "\n"));
    }
    else
    {
        OUR_DEBUG((LM_INFO, "[Print_Binary]pMessageBlock is NULL.\n"));
    }
}

//打印指定的Messahe_Block中的信息到屏幕
inline void Print_Binary(const char* pData, int nLen)
{
    if(NULL != pData)
    {
        OUR_DEBUG((LM_INFO, "[Print_Binary]"));

        for(int32 i = 0; i < nLen; i++)
        {
            OUR_DEBUG((LM_INFO, " %02x", (unsigned char)pData[i]));
        }

        OUR_DEBUG((LM_INFO, "\n"));
    }
    else
    {
        OUR_DEBUG((LM_INFO, "[Print_Binary]pData is NULL.\n"));
    }
}

//用于整合获取整数2次幂的函数(内存池应用)
static inline uint32 is_pow_of_2(uint32 x)
{
    return !(x & (x-1));
}

static inline uint32 next_pow_of_2(uint32 x)
{
    if ( is_pow_of_2(x) )
    {
        return x;
    }

    x |= x>>1;
    x |= x>>2;
    x |= x>>4;
    x |= x>>8;
    x |= x>>16;
    return x+1;
}

typedef struct FILETESTRESULTINFO
{
    FILE_TEST_RESULT n4Result = FILE_TEST_RESULT::RESULT_OK; //启动测试结果信息
    int32 n4TimeInterval      = 0;                           //启动测试时间间隔
    int32 n4ProNum            = 0;                           //启动测试协议条数
    int32 n4ConnectNum        = 0;                           //模拟连接数
    vector<string> vecProFileDesc;                           //协议文件描述

    FILETESTRESULTINFO(const FILETESTRESULTINFO& ar)
    {
        vecProFileDesc.clear();
        this->n4Result = ar.n4Result;
        this->n4TimeInterval = ar.n4TimeInterval;
        this->n4ProNum = ar.n4ProNum;
        this->n4ConnectNum = ar.n4ConnectNum;
        this->vecProFileDesc.assign(ar.vecProFileDesc.begin(), ar.vecProFileDesc.end());
    }

    FILETESTRESULTINFO()
    {
    }

    ~FILETESTRESULTINFO()
    {
        n4Result = FILE_TEST_RESULT::RESULT_OK;
        n4TimeInterval = 0;
        n4ProNum = 0;
        n4ConnectNum = 0;
        vecProFileDesc.clear();
    }

    FILETESTRESULTINFO& operator= (const FILETESTRESULTINFO& ar)
    {
        this->n4Result = ar.n4Result;
        this->n4TimeInterval = ar.n4TimeInterval;
        this->n4ProNum = ar.n4ProNum;
        this->n4ConnectNum = ar.n4ConnectNum;
        this->vecProFileDesc.assign(ar.vecProFileDesc.begin(), ar.vecProFileDesc.end());
        return *this;
    }
} FileTestResultInfoSt;

//对象创建信息
struct _Object_Create_Info
{
    char   m_szCreateFileName[MAX_BUFF_100] = {'\0'};   //声明文件
    uint32 m_u4Line                         = 0;        //声明行数位置
    uint32 m_u4Count                        = 0;        //对象个数

    _Object_Create_Info()
    {
    }
};

//客户端连接活跃信息
struct _Connect_Chart_Info
{
    uint32 m_n4ConnectCount       = 0;        //当前活跃连接数
    uint32 m_u4LastConnectCount   = 0;    //之前一分钟的连接建立数
    ACE_Time_Value m_tvConnectTime; //收集数据的时间

    _Connect_Chart_Info()
    {
    }
};

//指定命令信息
struct _Command_Chart_Info
{
    uint16 m_u2CommandID    = 0;            //命令ID
    uint32 m_u4CommandCount = 0;            //单位时间数
    ACE_Time_Value m_tvCommandTime;         //手机数据的时间

    _Command_Chart_Info()
    {
    }
};

//文件测试数据信息
typedef struct FILETESTDATAINFO
{
    char                    m_szData[MAX_BUFF_10240] = {'\0'};        //当前缓冲中数据的长度
    uint32                  m_u4DataLength           = 0;             //当前缓冲块中的数据长度

    FILETESTDATAINFO()
    {
    }

    FILETESTDATAINFO(const FILETESTDATAINFO& ar)
    {
        ACE_OS::memset(m_szData, 0, MAX_BUFF_10240);

        if (false == memcpy_safe(const_cast<char*>(ar.m_szData), MAX_BUFF_10240, const_cast<char*>(this->m_szData), MAX_BUFF_10240))
        {
            OUR_DEBUG((LM_INFO, "[FILETESTDATAINFO::FILETESTDATAINFO]memcpy_safe error.\n"));
        }

        this->m_u4DataLength = ar.m_u4DataLength;
    }

    void Close()
    {
        ACE_OS::memset(m_szData, 0, MAX_BUFF_10240);
        m_u4DataLength     = 0;
    }

    ~FILETESTDATAINFO()
    {
        Close();
    }

    FILETESTDATAINFO& operator= (const FILETESTDATAINFO& ar)
    {
        if (false == memcpy_safe(const_cast<char*>(ar.m_szData), MAX_BUFF_10240, const_cast<char*>(this->m_szData), MAX_BUFF_10240))
        {
            OUR_DEBUG((LM_INFO, "[FILETESTDATAINFO::FILETESTDATAINFO]operator= error.\n"));
        }

        this->m_u4DataLength = ar.m_u4DataLength;
        return *this;
    }
} FileTestDataInfoSt;

//标记VCHARS_TYPE的模式
enum class VCHARS_TYPE
{
    VCHARS_TYPE_TEXT = 0,      //文本模式
    VCHARS_TYPE_BINARY,        //二进制模式
};

#ifndef VCHARS_STR
typedef  struct _VCHARS_STR
{
    char*       text    = NULL;             //数据指针
    bool        blCopy  = true;             //是否拷贝数据块，True是拷贝，默认是拷贝
    bool        blNew   = false;            //是否是new出来的数据
    uint8       u1Len   = 0;                //数据长度
    VCHARS_TYPE type    = VCHARS_TYPE::VCHARS_TYPE_TEXT; //类型，类型定义见VCHARS_TYPE

    _VCHARS_STR(bool blIsCopy = true, VCHARS_TYPE ntype = VCHARS_TYPE::VCHARS_TYPE_TEXT)
    {
		blCopy = blIsCopy;
		type = ntype;
    }

    ~_VCHARS_STR()
    {
        if(blNew == true)
        {
            delete text;
        }
    }

    void SetData(const char* pData, uint8& u1Length)
    {
        if(blCopy == true)
        {
            //如果是需要构建新内存，则在这里申请
            if(blNew == true)
            {
                SAFE_DELETE(text);
            }

            if(type == VCHARS_TYPE::VCHARS_TYPE_TEXT)
            {
                //文本模式
                uint8 u1targetLen = u1Length + 1;
                text = new char[u1targetLen];

                if (false == memcpy_safe((char*)pData, u1Length, text, u1Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARS_STR::SetData]memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                text[u1Length] = '\0';
                u1Len = u1Length + 1;
            }
            else
            {
                //二进制模式
                text = new char[u1Length];

                if (false == memcpy_safe((char*)pData, u1Length, text, u1Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARS_STR::SetData]binary memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                u1Len = u1Length;
            }

            blNew = true;
        }
        else
        {
            text  = (char* )pData;
            u1Len = u1Length;
        }
    }

} VCHARS_STR;
#endif

#ifndef VCHARM_STR
typedef  struct _VCHARM_STR
{
    char*       text   = NULL;             //数据指针
    uint16      u2Len  = 0;                //数据长度
    bool        blCopy = true;             //是否拷贝数据块，True是拷贝，默认是拷贝
    bool        blNew  = false;            //是否是new出来的数据
    VCHARS_TYPE type   = VCHARS_TYPE::VCHARS_TYPE_TEXT; //类型，类型定义见VCHARS_TYPE

    _VCHARM_STR(bool blIsCopy = true, VCHARS_TYPE ntype = VCHARS_TYPE::VCHARS_TYPE_TEXT)
    {
        blCopy = blIsCopy;
        type   = ntype;
    }

    ~_VCHARM_STR()
    {
        if(blNew == true)
        {
            delete text;
        }
    }

    void SetData(const char* pData, uint16& u2Length)
    {
        if(blCopy == true)
        {
            //如果是需要构建新内存，则在这里申请
            if(blNew == true)
            {
                SAFE_DELETE(text);
            }

            if(type == VCHARS_TYPE::VCHARS_TYPE_TEXT)
            {
                //文本模式
                uint16 u2targetLen = u2Length + 1;
                text = new char[u2targetLen];

                if (false == memcpy_safe((char*)pData, u2Length, text, u2Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARM_STR::SetData]memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                text[u2Length] = '\0';
                u2Len = u2Length + 1;
            }
            else
            {
                //二进制模式
                text = new char[u2Length];

                if (false == memcpy_safe((char*)pData, u2Length, text, u2Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARM_STR::SetData]binary memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                u2Len = u2Length;
            }

            blNew = true;
        }
        else
        {
            text  = (char* )pData;
            u2Len = u2Length;
        }
    }

} VCHARM_STR;
#endif

#ifndef VCHARB_STR
typedef  struct _VCHARB_STR
{
    char*       text   = NULL;               //数据指针
    uint32      u4Len  = 0;                  //数据长度
    bool        blCopy = true;               //是否拷贝数据块，True是拷贝，默认是拷贝
    bool        blNew  = false;              //是否是new出来的数据
    VCHARS_TYPE type   = VCHARS_TYPE::VCHARS_TYPE_TEXT;   //类型，类型定义见VCHARS_TYPE

    _VCHARB_STR(bool blIsCopy = true, VCHARS_TYPE ntype = VCHARS_TYPE::VCHARS_TYPE_TEXT)
    {
        blCopy = blIsCopy;
        type   = ntype;
    }

    ~_VCHARB_STR()
    {
        if(blNew == true)
        {
            delete text;
        }
    }

    void SetData(const char* pData, uint32& u4Length)
    {
        //如果长度是0，后面不再做解析
        if (u4Length == 0)
        {
            return;
        }

        if(blCopy == true)
        {
            //如果是需要构建新内存，则在这里申请
            if(blNew == true)
            {
                SAFE_DELETE(text);
            }

            if(type == VCHARS_TYPE::VCHARS_TYPE_TEXT)
            {
                //文本模式
                uint32 u4targetLen = u4Length + 1;
                text = new char[u4targetLen];

                if (false == memcpy_safe((char*)pData, u4Length, text, u4Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARB_STR::SetData]memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                text[u4Length] = '\0';
                u4Len = u4Length + 1;
            }
            else
            {
                //二进制模式
                text = new char[u4Length];

                if (false == memcpy_safe((char*)pData, u4Length, text, u4Length))
                {
                    OUR_DEBUG((LM_INFO, "[_VCHARB_STR::SetData]binary memcpy_safe error.\n"));
                    SAFE_DELETE(text);
                    return;
                }

                u4Len = u4Length;
            }

            blNew = true;
        }
        else
        {
            text  = (char* )pData;
            u4Len = u4Length;
        }
    }

} VCHARB_STR;
#endif

//定义PacketParse的相关消息体
//数据包头结构
struct _Head_Info
{
    uint32             m_u4HeadSrcLen      = 0;       //原始数据包头长（解析前）
    uint32             m_u4HeadCurrLen     = 0;       //当前数据包长 （解析后）
    uint32             m_u4BodySrcLen      = 0;       //当前包体长度（解析前）
    uint16             m_u2PacketCommandID = 0;       //CommandID
    ACE_Message_Block* m_pmbHead           = NULL;    //包头消息体

    _Head_Info()
    {
    }
};

//数据包体结构
struct _Body_Info
{
    uint32             m_u4BodySrcLen      = 0;       //原始数据包体长（解析前）
    uint32             m_u4BodyCurrLen     = 0;       //当前数据包长 （解析后）
    uint16             m_u2PacketCommandID = 0;       //CommandID(如果有，则直接赋值，如果没有，则保持初始值不变)
    ACE_Message_Block* m_pmbBody           = NULL;    //包头消息体

    _Body_Info()
    {
    }
};

//数据包完整结构
struct _Packet_Info
{
    uint32             m_u4HeadSrcLen      = 0;       //原始数据包头长（解析前）
    uint32             m_u4HeadCurrLen     = 0;       //当前数据包长 （解析后）
    uint32             m_u4BodySrcLen      = 0;       //原始数据包头长（解析前）
    uint32             m_u4BodyCurrLen     = 0;       //当前数据包长 （解析后）
    uint16             m_u2PacketCommandID = 0;       //CommandID
    ACE_Message_Block* m_pmbHead           = NULL;    //包头消息体
    ACE_Message_Block* m_pmbBody           = NULL;    //包头消息体

    _Packet_Info()
    {
    }
};

//定时监控数据包和流量的数据信息，用于链接有效性的逻辑判定
struct _TimeConnectInfo
{
    uint32 m_u4RecvPacketCount      = 0;         //当前接收包数量
    uint32 m_u4RecvSize             = 0;         //当前接收数据量
    uint32 m_u4SendPacketCount      = 0;         //当前发送包数量
    uint32 m_u4SendSize             = 0;         //当前发送数据量
    uint32 m_u4ValidRecvPacketCount = 0;         //单位时间可允许接收数据包的上限
    uint32 m_u4ValidRecvSize        = 0;         //单位时间可允许的数据接收量
    uint32 m_u4ValidSendPacketCount = 0;         //单位时间可允许数据数据包的上限
    uint32 m_u4ValidSendSize        = 0;         //单位时间可允许的数据发送量
    uint8  m_u1Minutes              = 0;         //当前的分钟数

    _TimeConnectInfo()
    {
    }

    void Init(uint32 u4RecvPacketCount, uint32 u4RecvSize, uint32 u4SendPacketCount, uint32 u4ValidSendSize)
    {
        m_u1Minutes              = 0;
        m_u4RecvPacketCount      = 0;
        m_u4RecvSize             = 0;
        m_u4SendPacketCount      = 0;
        m_u4SendSize             = 0;

        m_u4ValidRecvPacketCount = u4RecvPacketCount;
        m_u4ValidRecvSize        = u4RecvSize;
        m_u4ValidSendPacketCount = u4SendPacketCount;
        m_u4ValidSendSize        = u4ValidSendSize;
    }

    bool RecvCheck(uint8 u1Minutes, uint16 u2PacketCount, uint32 u4RecvSize)
    {
        if(m_u1Minutes != u1Minutes)
        {
            m_u1Minutes         = u1Minutes;
            m_u4RecvPacketCount = u2PacketCount;
            m_u4RecvSize        = u4RecvSize;
        }
        else
        {
            m_u4RecvPacketCount += u2PacketCount;
            m_u4RecvSize        += u4RecvSize;
        }

        if(m_u4ValidRecvPacketCount > 0)
        {
            //需要比较
            if(m_u4RecvPacketCount > m_u4ValidRecvPacketCount)
            {
                return false;
            }
        }

        if(m_u4ValidRecvSize > 0)
        {
            //需要比较
            if(u4RecvSize > m_u4ValidRecvSize)
            {
                return false;
            }
        }

        return true;
    }

    bool SendCheck(uint8 u1Minutes, uint16 u2PacketCount, uint32 u4SendSize)
    {
        if(m_u1Minutes != u1Minutes)
        {
            m_u1Minutes         = u1Minutes;
            m_u4SendPacketCount = u2PacketCount;
            m_u4RecvSize        = u4SendSize;
        }
        else
        {
            m_u4SendPacketCount += u2PacketCount;
            m_u4RecvSize        += u4SendSize;
        }

        if(m_u4ValidSendPacketCount > 0)
        {
            //需要比较
            if(m_u4SendPacketCount > m_u4ValidSendPacketCount)
            {
                return false;
            }
        }

        if(m_u4ValidSendSize > 0)
        {
            //需要比较
            if(u4SendSize > m_u4ValidSendSize)
            {
                return false;
            }
        }

        return true;
    }
};

//定时器参数的设置结构
struct _TimerCheckID
{
    uint16 m_u2TimerCheckID = 0;

    _TimerCheckID()
    {
    }
};

//Message里面数据块结构体
struct _PacketInfo
{
    char*   m_pData    = NULL;       //解析后的数据头指针
    int32   m_nDataLen = 0;          //解析后的数据长度

    _PacketInfo()
    {
    }
};

//客户端链接信息数据结构
struct _ClientConnectInfo
{
    uint64        m_u8RecvQueueTimeCost = 0;     //接受逻辑处理包总时间消耗
    uint64        m_u8SendQueueTimeCost = 0;     //发送数据总时间消耗
    uint32        m_u4ConnectID         = 0;     //链接ID
    uint32        m_u4RecvCount         = 0;     //接收包数量
    uint32        m_u4SendCount         = 0;     //发送包数量
    uint32        m_u4AllRecvSize       = 0;     //接收字节数
    uint32        m_u4AllSendSize       = 0;     //发送字节数
    uint32        m_u4BeginTime         = 0;     //链接建立时间
    uint32        m_u4AliveTime         = 0;     //存活时间秒数
    uint32        m_u4RecvQueueCount    = 0;     //接受逻辑处理包的个数
    bool          m_blValid             = false; //当前链接是否有效
    ACE_INET_Addr m_addrRemote;                  //远程链接地址

    _ClientConnectInfo()
    {
    }

    //拷贝构造函数
    _ClientConnectInfo(const _ClientConnectInfo& ar)
    {
        this->m_blValid = ar.m_blValid;
        this->m_u4ConnectID = ar.m_u4ConnectID;
        this->m_addrRemote = ar.m_addrRemote;
        this->m_u4RecvCount = ar.m_u4RecvCount;
        this->m_u4SendCount = ar.m_u4SendCount;
        this->m_u4AllRecvSize = ar.m_u4AllRecvSize;
        this->m_u4AllSendSize = ar.m_u4AllSendSize;
        this->m_u4BeginTime = ar.m_u4BeginTime;
        this->m_u4AliveTime = ar.m_u4AliveTime;
        this->m_u4RecvQueueCount = ar.m_u4RecvQueueCount;
        this->m_u8RecvQueueTimeCost = ar.m_u8RecvQueueTimeCost;
        this->m_u8SendQueueTimeCost = ar.m_u8SendQueueTimeCost;
    }

    _ClientConnectInfo& operator = (const _ClientConnectInfo& ar)
    {
        this->m_blValid             = ar.m_blValid;
        this->m_u4ConnectID         = ar.m_u4ConnectID;
        this->m_addrRemote          = ar.m_addrRemote;
        this->m_u4RecvCount         = ar.m_u4RecvCount;
        this->m_u4SendCount         = ar.m_u4SendCount;
        this->m_u4AllRecvSize       = ar.m_u4AllRecvSize;
        this->m_u4AllSendSize       = ar.m_u4AllSendSize;
        this->m_u4BeginTime         = ar.m_u4BeginTime;
        this->m_u4AliveTime         = ar.m_u4AliveTime;
        this->m_u4RecvQueueCount    = ar.m_u4RecvQueueCount;
        this->m_u8RecvQueueTimeCost = ar.m_u8RecvQueueTimeCost;
        this->m_u8SendQueueTimeCost = ar.m_u8SendQueueTimeCost;
        return *this;
    }
};
typedef vector<_ClientConnectInfo> vecClientConnectInfo;

//要连接的服务器信息
struct _ServerConnectInfo
{
    uint32      m_u4ServerID   = 0;     //服务器的ID
    uint32      m_u4ServerPort = 0;     //服务器的端口
    uint32      m_u4MaxConn    = 0;     //服务器的最大线程连接数
    uint32      m_u4TimeOut    = 0;     //服务器的链接超时时间
    ACE_TString m_strServerName;        //服务器的名称
    ACE_TString m_strServerIP;          //服务器的IP

    _ServerConnectInfo()
    {
    }
};

//为逻辑块提供一个Try catch的保护宏，用于调试，具体使用方法请参看TestTcp用例
//目前最多支持一条2K的日志
//************************************************************************
#define ASSERT_LOG_PATH  "./Log/assert.log"   //如果路径想自己要，请修改这里。

inline void __show__( const char* szTemp)
{
#if PSS_PLATFORM == PLATFORM_WIN
    printf_s("[__show__]%s.\n", szTemp);
#else
    printf("[__show__]%s.\n", szTemp);
#endif

    FILE* f = ACE_OS::fopen(ASSERT_LOG_PATH, "a") ;
    ACE_OS::fwrite( szTemp, strlen(szTemp), sizeof(char), f) ;
    ACE_OS::fwrite( "\r\n", 1, 2*sizeof(char), f);
    fclose(f);
};

inline void __assertspecial__(const char* file, int32 line, const char* func, const char* expr, const char* msg)
{
    char szTemp[2*MAX_BUFF_1024] = {0};

    sprintf_safe( szTemp, 2*MAX_BUFF_1024, "Alert[%s][%d][%s][%s][%s]", file, line, func, expr,msg) ;
    __show__(szTemp) ;
};

#if defined(WIN32)
#define AssertSpecial(expr,msg) ((void)((expr)?0:(__assertspecial__(__FILE__, __LINE__, __FUNCTION__, #expr, msg),0)))
#else
#define AssertSpecial(expr,msg) {if(!(expr)){__assertspecial__(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr, msg);}}
#endif

#if defined(WIN32)
#define __ENTER_FUNCTION() {try{
#define __THROW_FUNCTION(msg) throw(msg)
#define __LEAVE_FUNCTION() }catch(char* msg){AssertSpecial(false,msg); }}
#define __LEAVE_FUNCTION_WITHRETURN(ret) }catch(char* msg){AssertSpecial(false,msg); return ret; }}
#else   //linux
#define __ENTER_FUNCTION() {try{
#define __THROW_FUNCTION(msg) throw(msg)
#define __LEAVE_FUNCTION() }catch(char* msg){AssertSpecial(false,msg);}}
#define __LEAVE_FUNCTION_WITHRETURN(ret) }catch(char* msg){AssertSpecial(false,msg); return ret; }}
#endif

//************************************************************************

//增加一个统计函数处理时间的宏，这个宏可以直接统计当前函数执行时间
//使用例子 __TIMECOST(100); 100为毫秒，超过100毫秒就会计入日志
//************************************************************************
#define ASSERT_TIME_PATH  "./Log/FuncTimeout.log"   //如果路径想自己要，请修改这里。
class CTimeCost
{
public:
    CTimeCost(unsigned int nMillionSecond, const char* pFunctionName, const char* pFileName, int32 nLine)
    {
        m_nMillionSecond = nMillionSecond;
        sprintf_safe(m_szFunctionName, MAX_BUFF_100, "%s", pFunctionName);
        sprintf_safe(m_szFileName, MAX_BUFF_300, "%s", pFileName);
        m_nFileLine = nLine;
        TimeBegin();
    }

    ~CTimeCost()
    {
        TimeEnd();
    }

    void TimeBegin()
    {
        m_lBegin = GetSystemTickCount();
    }

    void TimeEnd()
    {
        m_lEnd = GetSystemTickCount();
        uint64 lTimeInterval = m_lEnd - m_lBegin;  //转换成毫秒

        if(lTimeInterval >= (long)m_nMillionSecond)
        {
            //记录日志
            FILE* pFile = ACE_OS::fopen(ASSERT_TIME_PATH, "a+");

            if(pFile != NULL)
            {
                char szLog[MAX_BUFF_1024] = { '\0' };

                char szTimeNow[MAX_BUFF_50];
                time_t tNow = time(NULL);
                struct tm* tmNow = ACE_OS::localtime(&tNow);
                sprintf_safe(szTimeNow, MAX_BUFF_50, "%04d-%02d-%02d %02d:%02d:%02d", tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday, tmNow->tm_hour, tmNow->tm_min, tmNow->tm_sec);
                sprintf_safe(szLog, MAX_BUFF_1024, "[%s]dbTimeInterval more than (%d) < (%d), File(%s):FunName(%s):Line(%d).\n", szTimeNow, m_nMillionSecond, lTimeInterval, m_szFileName, m_szFunctionName, m_nFileLine);
                ACE_OS::fwrite(szLog, strlen(szLog), sizeof(char), pFile);
                ACE_OS::fclose(pFile);
            }
        }
    }

private:
    int64 GetSystemTickCount()
    {
#if PSS_PLATFORM == PLATFORM_WIN
        //return (unsigned long)GetTickCount();
        static LARGE_INTEGER TicksPerSecond = { 0 };
        LARGE_INTEGER Tick;

        if (!TicksPerSecond.QuadPart)
        {
            QueryPerformanceFrequency(&TicksPerSecond);
        }

        QueryPerformanceCounter(&Tick);

        int64 Seconds = Tick.QuadPart / TicksPerSecond.QuadPart;
        int64 LeftPart = Tick.QuadPart - (TicksPerSecond.QuadPart * Seconds);
        int64 MillSeconds = LeftPart * 1000 / TicksPerSecond.QuadPart;
        int64 Ret = Seconds * 1000 + MillSeconds;
        _ASSERT(Ret > 0);
        return Ret;
#else
        struct timespec ts;

        clock_gettime(CLOCK_MONOTONIC, &ts);

        return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
#endif
    }

private:
    int64        m_lBegin                       = 0;
    int64        m_lEnd                         = 0;
    int32        m_nFileLine                    = 0;
    uint32       m_nMillionSecond               = 0;
    char         m_szFunctionName[MAX_BUFF_100] = {'\0'};
    char         m_szFileName[MAX_BUFF_300]     = { '\0' };
};

#define __TIMECOST(cost) CTimeCost timecost(cost, __FUNCTION__, __FILE__, __LINE__);

//************************************************************************
//add by freeeyes
//获得对自己大小端的自我判定
//添加在mainConfig中，是因为没必要在define.h中判定
//在框架里自己判定是否转换大小端
enum class ENUM_CHAR_ORDER
{
    SYSTEM_LITTLE_ORDER = 0,   //小端字序
    SYSTEM_BIG_ORDER,          //大端字序
};

const unsigned int O32_LITTLE_ENDIAN = 0x03020100ul;
const unsigned int O32_BIG_ENDIAN    = 0x00010203ul;
const unsigned int O32_PDP_ENDIAN    = 0x01000302ul;

static const union
{
    unsigned char bytes[4];
    uint32 value;
} o32_host_order =
{ { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

//定义一个对64位长整形的网络字节序的转换
inline uint64 hl64ton(uint64 u8Data)
{
    if(O32_HOST_ORDER == O32_LITTLE_ENDIAN)
    {
        union
        {
            uint32 lv[2];
            uint64 llv;
        } u;
        u.lv[0] = htonl(u8Data >> 32);
        u.lv[1] = htonl(u8Data & 0xFFFFFFFFULL);
        return u.llv;
    }
    else
    {
        //如果本身是大端就不理
        return u8Data;
    }

}

//定义一个队64位长整形的主机字节序的转换
inline uint64 ntohl64(uint64 u8Data)
{
    if(O32_HOST_ORDER == O32_LITTLE_ENDIAN)
    {
        union
        {
            uint32 lv[2];
            uint64 llv;
        } u;
        u.llv = u8Data;
        return ((uint64)ntohl(u.lv[0]) << 32) | (uint64)ntohl(u.lv[1]);
    }
    else
    {
        //如果本身是大端就不理
        return u8Data;
    }
}

//定义一个函数，可支持字符串替换，目前先不考虑支持中文
inline bool Replace_String(char* pText, uint32 u4Len, const char* pOld, const char* pNew)
{
    char* pTempSrc = new char[u4Len];

    if (false == memcpy_safe(pText, u4Len, pTempSrc, u4Len))
    {
        return false;
    }

    pTempSrc[u4Len - 1] = '\0';

    uint16 u2NewLen = (uint16)ACE_OS::strlen(pNew);

    char* pPos = ACE_OS::strstr(pTempSrc, pOld);

    while(pPos)
    {
        //计算出需要覆盖的字符串长度
        uint32 u4PosLen = (uint32)(pPos - pTempSrc);

        //黏贴最前面的
        if (false == memcpy_safe(pText, u4PosLen, pTempSrc, u4PosLen))
        {
            return false;
        }

        pText[u4PosLen] = '\0';

        if(u4PosLen + u2NewLen >= (uint32)u4Len)
        {
            //清理中间变量
            delete[] pTempSrc;
            return false;
        }
        else
        {
            //黏贴新字符
            if (false == memcpy_safe(pText, u2NewLen, &pText[u4PosLen], u2NewLen))
            {
                return false;
            }

            pText[u4PosLen + u2NewLen] = '\0';

            //指针向后移动
            pTempSrc =  pTempSrc + u4PosLen;

            //寻找下一个相同的字符串
            pPos = ACE_OS::strstr(pTempSrc, pOld);
        }

    }

    //清理中间变量
    delete[] pTempSrc;
    return true;
}

//写独占文件锁
inline int32 AcquireWriteLock(int32 fd, int32 start, int32 len)
{
#ifndef WIN32
    struct flock arg;
    arg.l_type = F_WRLCK; // 加写锁
    arg.l_whence = SEEK_SET;
    arg.l_start = start;
    arg.l_len = len;
    arg.l_pid = getpid();

    return fcntl(fd, F_SETLKW, &arg);
#else
    return -1;
#endif
}

//释放独占文件锁
inline int32 ReleaseLock(int32 fd, int32 start, int32 len)
{
#ifndef WIN32
    struct flock arg;
    arg.l_type = F_UNLCK; //  解锁
    arg.l_whence = SEEK_SET;
    arg.l_start = start;
    arg.l_len = len;
    arg.l_pid = getpid();

    return fcntl(fd, F_SETLKW, &arg);
#else
    return -1;
#endif
}

//查看写锁
inline int32 SeeLock(int32 fd, int32 start, int32 len)
{
#ifndef WIN32
    struct flock arg;
    arg.l_type = F_WRLCK;
    arg.l_whence = SEEK_SET;
    arg.l_start = start;
    arg.l_len = len;
    arg.l_pid = getpid();

    if (fcntl(fd, F_GETLK, &arg) != 0) // 获取锁
    {
        return -1; // 测试失败
    }

    if (arg.l_type == F_UNLCK)
    {
        return 0; // 无锁
    }
    else if (arg.l_type == F_RDLCK)
    {
        return 1; // 读锁
    }
    else if (arg.l_type == F_WRLCK)
    {
        return 2; // 写所
    }

    return 0;
#else
    return -1;
#endif
}

//客户端IP信息
struct _ClientIPInfo
{
    string  m_strClientIP;      //客户端的IP地址
    int16 m_u2Port  = 0;        //客户端的端口
};

//链接别名映射信息(用于PSS_ClientManager管理)
struct _ClientNameInfo
{
    int16  m_u2Port                  = 0;           //客户端的端口
    int32  m_nConnectID              = 0;           //连接ID
    int32  m_nLog                    = 0;           //是否记录日志
    char   m_szName[MAX_BUFF_100]    = {'\0'};      //连接别名
    char   m_szClientIP[MAX_BUFF_50] = {'\0'};      //客户端的IP地址

    _ClientNameInfo()
    {
    }

    //拷贝构造函数
    _ClientNameInfo(const _ClientNameInfo& ar)
    {
        sprintf_safe(this->m_szName, MAX_BUFF_100, "%s", ar.m_szName);
        sprintf_safe(this->m_szClientIP, MAX_BUFF_50, "%s", ar.m_szClientIP);
        this->m_u2Port = ar.m_u2Port;
        this->m_nConnectID = ar.m_nConnectID;
        this->m_nLog = ar.m_nLog;
    }

    _ClientNameInfo& operator = (const _ClientNameInfo& ar)
    {
        sprintf_safe(this->m_szName, MAX_BUFF_100, "%s", ar.m_szName);
        sprintf_safe(this->m_szClientIP, MAX_BUFF_50, "%s", ar.m_szClientIP);
        this->m_u2Port      = ar.m_u2Port;
        this->m_nConnectID = ar.m_nConnectID;
        this->m_nLog       = ar.m_nLog;
        return *this;
    }
};
typedef vector<_ClientNameInfo> vecClientNameInfo;

//格式化一个ACE Hash类
template<class EXT_ID, class INT_ID>
class ACE_Hash_Map :
    public ACE_Hash_Map_Manager_Ex<EXT_ID, INT_ID,
    ACE_Hash<EXT_ID>, ACE_Equal_To<EXT_ID>, ACE_Null_Mutex>
{};


inline void Set_Output_To_File(int nTrunOn, ofstream*& pLogoStream, const char* pLogPath, const char* pLogName, int nMaxLogSize)
{
    //如果不需要输出到日志
    if (nTrunOn == 0)
    {
        return;
    }

    char szDebugFileName[MAX_BUFF_200] = { '\0' };
    sprintf_safe(szDebugFileName, MAX_BUFF_200, "%s/%s.log", pLogPath, pLogName);

    if (pLogoStream == NULL)
    {
        //这个是新建的文件
        pLogoStream = new ofstream(szDebugFileName, std::ofstream::out | std::ofstream::trunc);
        ACE_LOG_MSG->msg_ostream(pLogoStream);
    }
    else
    {
        //获得当前的对象是否已经超过了max的数值
        if ((size_t)nMaxLogSize <= (size_t)pLogoStream->tellp())
        {
            ACE_LOG_MSG->acquire();
            //需要重启一个日志文件
            ofstream* pOldLogoStream = (ofstream*)ACE_LOG_MSG->msg_ostream();
            if (NULL != pOldLogoStream)
            {
				ACE_Date_Time  dt;
				//转移日志文件
				char szHistoryLogFile[MAX_BUFF_200] = { '\0' };
				sprintf_safe(szHistoryLogFile, MAX_BUFF_200, "%s/%s_%04d%02d%02d_%02d%02d%02d.log", pLogPath, pLogName,
					dt.year(), dt.month(), dt.day(), dt.hour(), dt.minute(), dt.second());
				ACE_OS::rename(szDebugFileName, szHistoryLogFile);

				pOldLogoStream->close();

				ACE_OS::unlink(szDebugFileName);

				pOldLogoStream->open(szDebugFileName, std::ofstream::out | std::ofstream::trunc);
            }

            ACE_LOG_MSG->release();
        }
    }

    ACE_LOG_MSG->set_flags(ACE_Log_Msg::STDERR | ACE_Log_Msg::OSTREAM);
}

#ifndef WIN32

//获得当前文件打开数
inline int Checkfilelimit(int nMaxOpenFile)
{
    //获得当前文件打开数
    struct rlimit rfilelimit;

    if (getrlimit(RLIMIT_NOFILE, &rfilelimit) != 0)
    {
        OUR_DEBUG((LM_INFO, "[Checkfilelimit]failed to getrlimit number of files.\n"));
        return -1;
    }
    else
    {
        OUR_DEBUG((LM_INFO, "[Checkfilelimit]rfilelimit.rlim_cur=%d,nMaxOpenFile=%d.\n", rfilelimit.rlim_cur, nMaxOpenFile));

        //提示同时文件打开数不足，需要设置。
        if ((int)rfilelimit.rlim_cur < nMaxOpenFile)
        {
            OUR_DEBUG((LM_INFO, "[Checkfilelimit]** WARNING!WARNING!WARNING!WARNING! **.\n"));
            OUR_DEBUG((LM_INFO, "[Checkfilelimit]** PSS WILL AUTO UP FILE OPEN LIMIT **.\n"));
            OUR_DEBUG((LM_INFO, "[Checkfilelimit]** WARNING!WARNING!WARNING!WARNING! **.\n"));
            //这段自动提升的功能暂时注释，运维人员必须知道这个问题并自己设置，这是上选。
            //尝试临时提高并行文件数
            rfilelimit.rlim_cur = (rlim_t)nMaxOpenFile;
            rfilelimit.rlim_max = (rlim_t)nMaxOpenFile;

            if (setrlimit(RLIMIT_NOFILE, &rfilelimit) != 0)
            {
                OUR_DEBUG((LM_INFO, "[Checkfilelimit]failed to setrlimit number of files(error=%s).\n", strerror(errno)));
                return -1;
            }

            //如果修改成功，再次检查一下
            if (getrlimit(RLIMIT_NOFILE, &rfilelimit) != 0)
            {
                OUR_DEBUG((LM_INFO, "[Checkfilelimit]failed to getrlimit number of files.\n"));
                return -1;
            }

            //再次检查修改后的文件句柄数
            if ((int)rfilelimit.rlim_cur < nMaxOpenFile)
            {
                OUR_DEBUG((LM_INFO, "[Checkfilelimit]rlim.rlim_cur=%d, nMaxOpenFile=%d, openfile is not enougth， please check [ulimit -a].\n", (int)rfilelimit.rlim_cur, nMaxOpenFile));
                return -1;
            }

            return 0;
        }
    }

    return 0;
}

inline void Gdaemon()
{
    pid_t pid;

    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    if (setpgrp() == -1)
    {
        perror("setpgrp failure");
    }

    signal(SIGHUP, SIG_IGN);

    if ((pid = fork()) < 0)
    {
        perror("fork failure");
        exit(1);
    }
    else if (pid > 0)
    {
        exit(0);
    }

    setsid();
    umask(0);

    signal(SIGCLD, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
}
#endif
END_NAMESPACE
USING_NAMESPACE

#endif
