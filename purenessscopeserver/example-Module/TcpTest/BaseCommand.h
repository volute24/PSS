#pragma once

#include "IBuffPacket.h"
#include "ClientCommand.h"
#include "IObject.h"
#include "Trace.h"

#include <string>

//定义客户端信令(TCP)
//默认命令ID必须是CLIENT_LINK_USER以后的数字，之前的命令ID是保留字
#define COMMAND_BASE            0x1000
#define COMMAND_RETURN_ALIVE    0xf000
#define NET_VERSION				0x6800			//版本
#define COMMAND_HEARTBEAT		0x2100			//心跳
#define COMMAND_TESTREPLY		0x2101			//测试回复

#define SIGNALING_KEY									"R3CadminLUBOcomPuterWybNUsdkIPS"
#define SIGNALING_IV									"ADMINLUBOCOMr3c"

#define MESSAGE_FUNCTION_BEGIN(x) switch(x) {
#define MESSAGE_FUNCTION(x,y,z) case x: { y(z); break; }
#define MESSAGE_FUNCTION_END }

using namespace std;

class CBaseCommand : public CClientCommand
{
public:
    CBaseCommand(void);
    ~CBaseCommand(void);

    int DoMessage(IMessage* pMessage, bool& bDeleteFlag);
    void SetServerObject(CServerObject* pServerObject);

    void ReadIniFile(const char* pIniFileName);

private:
    int Do_Connect(IMessage* pMessage);
    int Do_DisConnect(IMessage* pMessage);
    int Do_ClientSendTimeout(IMessage* pMessage);
    int Do_Base(IMessage* pMessage);
    int Do_ClientSendOk(IMessage* pMessage);
    int Do_ReplyTest(IMessage* pMessage);
    int SendClient(string pData, short nCommand, uint32 nConnectId, char* pKey, char* pIv, bool nEncrypt);
    int SendData(char* SendBuffer, int nSendLen, short nCommand, uint32 nConnectId);

private:
    CServerObject* m_pServerObject;
    int            m_nCount;
};
