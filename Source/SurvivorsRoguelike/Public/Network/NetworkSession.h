#pragma once
#include "../GameInfo.h"

class SURVIVORSROGUELIKE_API CNetworkSession
{
public:
	CNetworkSession();
	~CNetworkSession();

private:
	FSocket*	m_Socket;
	FString		m_Name;
	uint8		m_ReceivePacket[1024];
	uint8		m_SendPacket[1024];
	bool		m_Connect;

public:
	bool IsConnect()	const
	{
		return m_Connect;
	}
	const FString& GetName()	const
	{
		return m_Name;
	}
	void SetName(const FString& name)
	{
		m_Name = name;
	}

	bool Connect(const FString& IPAddr, int32 port);
	void Close();
	bool Receive(int32& packetHeader, int32& length, uint8* packet);
	bool Send(int32 packetHeader, int32 length, uint8* packet);
};
