#include "Network/NetworkManager.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"

CNetworkManager* CNetworkManager::m_Inst = nullptr;

CNetworkManager::CNetworkManager()
{
}

CNetworkManager::~CNetworkManager()
{
	// 스레드를 종료시켜준다.
	for (auto& thread : m_ThreadMap)
	{
		thread.Value->Worker->Exit();
	}
	// 스레드가 종료되기 전에 먼저 소켓을 모두 종료시켜준다.
	// 만약 소켓이 Receive 상태라면 종료를 해줘야 이 함수를
	// 빠져나오기 때문에 반드시 소켓을 먼저 종료해준 후에
	// 스레드를 제거한다.
	for (auto& session : m_SessionMap)
	{
		session.Value->Close();
	}
	for (auto& thread : m_ThreadMap)
	{
		thread.Value->Thread->Kill();
		// 스레드 제거가 모두 끝날때까지 기다려준다.
		thread.Value->Thread->WaitForCompletion();
		delete thread.Value->Thread;
		delete thread.Value->Worker;
		delete thread.Value;
	}
	for (auto& session : m_SessionMap)
	{
		delete session.Value;
	}
	for (auto& queue : m_PacketQueueMap)
	{
		delete queue.Value;
	}
}

bool CNetworkManager::Init()
{
	return true;
}

bool CNetworkManager::CheckSession(const FString& name)
{
	return m_SessionMap.Contains(name);
}

bool CNetworkManager::Connect(const FString& name, const FString& IPAddr, int32 port)
{
	CNetworkSession* session = nullptr;
	if (!CheckSession(name))
	{
		session = new CNetworkSession;
		session->SetName(name);
		m_SessionMap.Emplace(name, session);
	}
	else
	{
		session = FindSession(name);
	}
	if (session->IsConnect())
	{
		return false;
	}
	return session->Connect(IPAddr, port);
}

bool CNetworkManager::Close(const FString& name)
{
	if (!CheckSession(name))
	{
		return false;
	}
	CNetworkSession* session = FindSession(name);
	if (!session->IsConnect())
	{
		return false;
	}
	session->Close();
	return true;
}

CNetworkSession* CNetworkManager::FindSession(const FString& name)
{
	if (!m_SessionMap.Contains(name))
	{
		return nullptr;
	}
	return m_SessionMap.FindRef(name);
}

bool CNetworkManager::RemoveSession(const FString& name)
{
	if (!CheckSession(name))
	{
		return false;
	}
	CNetworkSession* session = FindSession(name);
	delete session;
	m_SessionMap.Remove(name);
	return true;
}

bool CNetworkManager::Send(const FString& sessionName, int32 header, int32 length, uint8* packet)
{
	if (!CheckSession(sessionName))
	{
		return false;
	}
	CNetworkSession* session = FindSession(sessionName);
	if (!session->IsConnect())
	{
		return false;
	}
	return session->Send(header, length, packet);
}

bool CNetworkManager::Receive(const FString& sessionName, int32& header, int32& length, uint8* packet)
{
	if (!CheckSession(sessionName))
	{
		return false;
	}
	CNetworkSession* session = FindSession(sessionName);
	if (!session->IsConnect())
	{
		return false;
	}
	return session->Receive(header, length, packet);
}

bool CNetworkManager::SendServerType(const FString& sessionName)
{
	if (!CheckSession(sessionName))
	{
		return false;
	}
	CNetworkSession* session = FindSession(sessionName);
	if (!session->IsConnect())
	{
		return false;
	}
	uint8	packet[1016] = {};
	int32	serverType = (int32)m_CurrentServerType;
	FMemory::Memcpy(packet, &serverType, 4);
	return session->Send((int32)EPacketHeader::SessionType, 4, packet);
}

bool CNetworkManager::CreatePacketQueue(const FString& name)
{
	if (m_PacketQueueMap.Contains(name))
	{
		return false;
	}
	CPacketQueue* queue = new CPacketQueue;
	m_PacketQueueMap.Emplace(name, queue);
	return true;
}

CPacketQueue* CNetworkManager::FindPacketQueue(const FString& name)
{
	if (!m_PacketQueueMap.Contains(name))
	{
		return nullptr;
	}
	return m_PacketQueueMap.FindRef(name);
}

bool CNetworkManager::SuspendThread(const FString& name, bool pause)
{
	if (!m_ThreadMap.Contains(name))
	{
		return false;
	}
	m_ThreadMap.FindRef(name)->Thread->Suspend(pause);
	return true;
}

bool CNetworkManager::RemoveThread(const FString& name)
{
	if (!m_ThreadMap.Contains(name))
	{
		return false;
	}
	m_ThreadMap.FindRef(name)->Worker->Exit();
	m_ThreadMap.FindRef(name)->Thread->Kill();
	m_ThreadMap.FindRef(name)->Thread->WaitForCompletion();
	delete m_ThreadMap.FindRef(name)->Worker;
	delete m_ThreadMap.FindRef(name)->Thread;
	delete m_ThreadMap.FindRef(name);
	m_ThreadMap.Remove(name);
	return true;
}
