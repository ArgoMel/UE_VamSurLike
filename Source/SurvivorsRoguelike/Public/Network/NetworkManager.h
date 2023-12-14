#pragma once
#include "../GameInfo.h"
#include "Thread/BaseThread.h"

class CNetworkSession;
class CPacketQueue;

struct FThreadInfo
{
	CBaseThread* Worker;
	FRunnableThread* Thread;
};

class SURVIVORSROGUELIKE_API CNetworkManager
{
public:
	CNetworkManager();
	~CNetworkManager();

private:
	static CNetworkManager* m_Inst;

	TMap<FString, CNetworkSession*>	m_SessionMap;
	TMap<FString, CPacketQueue*>	m_PacketQueueMap;
	TMap<FString, FThreadInfo*>	m_ThreadMap;
	EServerType		m_CurrentServerType;

public:
	static CNetworkManager* GetInst()
	{
		if (!m_Inst)
		{
			m_Inst = new CNetworkManager;
		}
		return m_Inst;
	}
	static void DestroyInst()
	{
		if (m_Inst)
		{
			delete m_Inst;
			m_Inst = nullptr;
		}
	}

	void SetServerType(EServerType type)
	{
		m_CurrentServerType = type;
	}

	bool Init();
	bool CheckSession(const FString& name);
	bool Connect(const FString& name, const FString& IPAddr, int32 port);
	bool Close(const FString& name);
	CNetworkSession* FindSession(const FString& name);
	bool RemoveSession(const FString& name);
	bool Send(const FString& sessionName, int32 header, int32 length, uint8* packet);
	bool Receive(const FString& sessionName, int32& header, int32& length, uint8* packet);
	bool SendServerType(const FString& sessionName);
	bool CreatePacketQueue(const FString& name);
	CPacketQueue* FindPacketQueue(const FString& name);
	bool SuspendThread(const FString& name, bool pause);
	bool RemoveThread(const FString& name);

	template <typename T>
	FThreadInfo* CreateThread(const FString& name)
	{
		if (m_ThreadMap.Contains(name))
		{
			return nullptr;
		}
		FThreadInfo* info = new FThreadInfo;
		info->Worker = new T;
		info->Worker->SetName(name);
		info->Worker->Init();
		info->Thread = FRunnableThread::Create(info->Worker, *name);
		info->Thread->Suspend();
		m_ThreadMap.Emplace(name, info);
		return info;
	}
};
