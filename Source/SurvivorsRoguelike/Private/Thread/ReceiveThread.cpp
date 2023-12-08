#include "Thread/ReceiveThread.h"
#include "Network/NetworkManager.h"
#include "Network/NetworkSession.h"
#include "Network/PacketQueue.h"

CReceiveThread::CReceiveThread()
	: m_Session(nullptr)
	, m_Queue(nullptr)
{
}

CReceiveThread::~CReceiveThread()
{
	m_Queue->Clear();
}

bool CReceiveThread::Init()
{
	CBaseThread::Init();
	FString queueName = m_Name + TEXT("_Queue");
	CNetworkManager::GetInst()->CreatePacketQueue(queueName);
	m_Queue = CNetworkManager::GetInst()->FindPacketQueue(queueName);
	return true;
}

uint32 CReceiveThread::Run()
{
	do
	{
		if (m_Session)
		{
			uint8   packet[1024] = {};
			int32   header = 0;
			int32	length = 0;
			if (!m_Session->Receive(header, length, packet))
			{
				return 0;
			}
			m_Queue->Push(header, length, packet);
		}
	} while (m_Loop);
	return 0;
}

void CReceiveThread::Stop()
{
	CBaseThread::Stop();
}

void CReceiveThread::Exit()
{
	CBaseThread::Exit();
	m_Loop = false;
}
