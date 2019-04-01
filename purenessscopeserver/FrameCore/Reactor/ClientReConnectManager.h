#ifndef _CLIENTCONNECTMANAGER_H
#define _CLIENTCONNECTMANAGER_H

#include "ace/Connector.h"
#include "ace/SOCK_Connector.h"

#include "TimerManager.h"
#include "BaseClientConnectManager.h"
#include "ReactorUDPClient.h"
#include "HashTable.h"
#include "XmlConfig.h"

#define RE_CONNECT_SERVER_TIMEOUT 100*1000
#define WAIT_FOR_RECONNECT_FINISH 5000

typedef ACE_Connector<CConnectClient, ACE_SOCK_CONNECTOR> CConnectClientConnector;

class CReactorClientInfo
{
public:
    CReactorClientInfo();
    ~CReactorClientInfo();

    CReactorClientInfo(const CReactorClientInfo& ar);

    CReactorClientInfo& operator = (const CReactorClientInfo& ar)
    {
        if (this != &ar)
        {
            ACE_UNUSED_ARG(ar);
        }

        return *this;
    }

    bool Init(int nServerID, const char* pIP, int nPort, uint8 u1IPType, CConnectClientConnector* pReactorConnect, IClientMessage* pClientMessage, ACE_Reactor* pReactor);  //初始化链接地址和端口
    void SetLocalAddr(const char* pIP, int nPort, uint8 u1IPType);                         //绑定本地的IP和端口
    bool Run(bool blIsReady, EM_Server_Connect_State emState = SERVER_CONNECT_RECONNECT);  //开始链接
    bool SendData(ACE_Message_Block* pmblk);                                               //发送数据
    int  GetServerID();                                                                    //得到服务器ID
    bool Close();                                                                          //关闭服务器链接
    void SetConnectClient(CConnectClient* pConnectClient);                                 //设置链接状态
    CConnectClient* GetConnectClient();                                                    //得到ProConnectClient指针
    IClientMessage* GetClientMessage();                                                    //获得当前的消息处理指针
    ACE_INET_Addr GetServerAddr();                                                         //获得服务器的地址
    EM_Server_Connect_State GetServerConnectState();                                       //得到当前连接状态
    void SetServerConnectState(EM_Server_Connect_State objState);                          //设置当前连接状态

private:
    ACE_INET_Addr              m_AddrLocal;              //本地的连接地址（可以指定）
    ACE_INET_Addr              m_AddrServer;             //远程服务器的地址
    CConnectClient*            m_pConnectClient;         //当前链接对象
    CConnectClientConnector*   m_pReactorConnect;        //Connector链接对象
    IClientMessage*            m_pClientMessage;         //回调函数类，回调返回错误和返回数据方法
    ACE_Reactor*               m_pReactor;               //记录使用的反应器
    bool                       m_blIsLocal;              //是否需要制定本地端口
    int                        m_nServerID;              //远程服务器的ID
    EM_Server_Connect_State    m_emConnectState;         //连接状态
};

class CClientReConnectManager : public ACE_Event_Handler, public IClientManager
{
public:
    CClientReConnectManager(void);
    virtual ~CClientReConnectManager(void);

    CClientReConnectManager& operator = (const CClientReConnectManager& ar)
    {
        if (this != &ar)
        {
            ACE_UNUSED_ARG(ar);
        }

        return *this;
    }

    bool Init(ACE_Reactor* pReactor);
    virtual bool Connect(int nServerID, const char* pIP, int nPort, uint8 u1IPType, IClientMessage* pClientMessage);                                                             //链接服务器(TCP)
    virtual bool Connect(int nServerID, const char* pIP, int nPort, uint8 u1IPType, const char* pLocalIP, int nLocalPort, uint8 u1LocalIPType, IClientMessage* pClientMessage);  //连接服务器(TCP)，指定本地地址
    virtual bool ConnectUDP(int nServerID, const char* pIP, int nPort, uint8 u1IPType, EM_UDP_TYPE emType, IClientUDPMessage* pClientUDPMessage);                                //建立一个指向UDP的链接（UDP）
    bool ReConnect(int nServerID);                                                                                             //重新连接一个指定的服务器(TCP)
    bool CloseByClient(int nServerID);                                                                                         //远程被动关闭(TCP)
    virtual bool Close(int nServerID);                                                                                                 //关闭连接
    virtual bool CloseUDP(int nServerID);                                                                                              //关闭链接（UDP）
    bool ConnectErrorClose(int nServerID);                                                                                     //由内部错误引起的失败，由ProConnectClient调用
    virtual bool SendData(int nServerID, char*& pData, int nSize, bool blIsDelete = true);                                              //发送数据
    virtual bool SendDataUDP(int nServerID, const char* pIP, int nPort, char*& pMessage, uint32 u4Len, bool blIsDelete = true);   //发送数据（UDP）
    bool SetHandler(int nServerID, CConnectClient* pConnectClient);                                                            //将指定的CProConnectClient*绑定给nServerID
    virtual IClientMessage* GetClientMessage(int nServerID);                                                                           //获得ClientMessage对象
    virtual bool StartConnectTask(int nIntervalTime = CONNECT_LIMIT_RETRY);                                                            //设置自动重连的定时器
    virtual void CancelConnectTask();                                                                                                  //关闭重连定时器
    virtual void Close();                                                                                                              //关闭所有连接
    ACE_INET_Addr GetServerAddr(int nServerID);                                                                                //得到指定服务器的远程地址连接信息
    bool SetServerConnectState(int nServerID, EM_Server_Connect_State objState);                                               //设置指定连接的连接状态
    virtual bool GetServerIPInfo(int nServerID, _ClientIPInfo& objServerIPInfo);                                                       //得到一个nServerID对应的ServerIP信息
    virtual bool DeleteIClientMessage(IClientMessage* pClientMessage);                                                                 //删除一个生命周期结束的IClientMessage

    void GetConnectInfo(vecClientConnectInfo& VecClientConnectInfo);      //返回当前存活链接的信息（TCP）
    void GetUDPConnectInfo(vecClientConnectInfo& VecClientConnectInfo);   //返回当前存活链接的信息（UDP）
    virtual EM_Server_Connect_State GetConnectState(int nServerID);               //得到一个当前连接状态

    virtual int handle_timeout(const ACE_Time_Value& current_time, const void* act = 0);               //定时器执行

private:
    bool ConnectTcpInit(int nServerID, const char* pIP, int nPort, uint8 u1IPType, const char* pLocalIP, int nLocalPort, uint8 u1LocalIPType, IClientMessage* pClientMessage, CReactorClientInfo*& pClientInfo);
    bool ConnectUdpInit(int nServerID, CReactorUDPClient*& pReactorUDPClient);

public:
    CHashTable<CReactorClientInfo> m_objClientTCPList;            //TCP客户端链接
    CHashTable<CReactorUDPClient>  m_objClientUDPList;            //UDP客户端链接
    CConnectClientConnector        m_ReactorConnect;              //Reactor连接客户端对象
    ACE_Recursive_Thread_Mutex     m_ThreadWritrLock;             //线程锁
    int                            m_nTaskID;                     //定时检测工具
    ACE_Reactor*                   m_pReactor;                    //当前的反应器
    bool                           m_blReactorFinish;             //Reactor是否已经注册
    uint32                         m_u4ConnectServerTimeout;      //连接间隔时间
    int32                          m_u4MaxPoolCount;              //连接池的上限
};

typedef ACE_Singleton<CClientReConnectManager, ACE_Recursive_Thread_Mutex> App_ClientReConnectManager;
#endif
