#pragma once
#include "Thread/BaseThread.h"

class CNetworkSession;
class CPacketQueue;

class SURVIVORSROGUELIKE_API CReceiveThread
	: public CBaseThread
{
public:
	CReceiveThread();
	~CReceiveThread();

private:
	CNetworkSession* m_Session;
	CPacketQueue* m_Queue;

public:
	void SetSession(CNetworkSession* session)
	{
		m_Session = session;
	}
	void SetQueue(CPacketQueue* queue)
	{
		m_Queue = queue;
	}

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();
};
