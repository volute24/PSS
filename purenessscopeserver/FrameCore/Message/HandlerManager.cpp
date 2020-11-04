#include "HandlerManager.h"

bool CPSSHandlerManager::PostMessage(uint32 u4ConnectID, uint16 u2CommandID, IBuffPacket*& pBuffPacket, CSend_Param objSendParam)
{
	if (u4ConnectID > 0)
	{
		//�����TCP���ӣ��ҵ����Handler���ڵĴ����߳�
		CSendMessageInfo objSendMessageInfo;

		objSendMessageInfo.blDelete    = objSendParam.m_blDlete;
		objSendMessageInfo.nMessageID  = objSendParam.m_nMessageID;
		objSendMessageInfo.emSendType  = objSendParam.m_emSendType;
		objSendMessageInfo.emSendState = objSendParam.m_emSendState;
		objSendMessageInfo.pBuffPacket = pBuffPacket;
		objSendMessageInfo.u2CommandID = u2CommandID;
		objSendMessageInfo.u4ConnectID = u4ConnectID;

		return App_MessageServiceGroup::instance()->Send_Post_Message(objSendMessageInfo);
	}
	else
	{
		OUR_DEBUG((LM_INFO, "[CPSSHandlerManager::PostMessage]Cant't send connectid is 0.\n"));
		return true;
	}
}

bool CPSSHandlerManager::CloseConnect(uint32 u4ConnectID)
{
	CSendMessageInfo objSendMessageInfo;

	objSendMessageInfo.u2CommandID = CLIENT_LINK_SDISCONNET;
	objSendMessageInfo.u4ConnectID = u4ConnectID;

	return App_MessageServiceGroup::instance()->Send_Post_Message(objSendMessageInfo);
}

_ClientIPInfo CPSSHandlerManager::GetClientIPInfo(uint32 u4ConnectID)
{
	return App_MessageServiceGroup::instance()->GetClientIPInfo(u4ConnectID);
}

_ClientIPInfo CPSSHandlerManager::GetLocalIPInfo(uint32 u4ConnectID)
{
	return App_MessageServiceGroup::instance()->GetLocalIPInfo(u4ConnectID);
}

uint32 CPSSHandlerManager::GetCount()
{
	return App_MessageServiceGroup::instance()->GetHandlerCount();
}

bool CPSSHandlerManager::SetIsLog(uint32 u4ConnectID, bool blIsLog)
{
	//��ʵ��
	ACE_UNUSED_ARG(u4ConnectID);
	ACE_UNUSED_ARG(blIsLog);
	return true;
}

EM_Client_Connect_status CPSSHandlerManager::GetConnectState(uint32 u4ConnectID)
{
	//��ʵ��
	ACE_UNUSED_ARG(u4ConnectID);
	return EM_Client_Connect_status::CLIENT_CONNECT_EXIST;
}