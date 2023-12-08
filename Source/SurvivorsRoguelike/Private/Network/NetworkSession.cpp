#include "Network/NetworkSession.h"

CNetworkSession::CNetworkSession()
	: m_Socket(nullptr)
	, m_ReceivePacket{}
	, m_SendPacket{}
	, m_Connect(false)
{
}

CNetworkSession::~CNetworkSession()
{
	Close();
}

bool CNetworkSession::Connect(const FString& IPAddr, int32 port)
{
	// 소켓을 생성한다.
	m_Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(
		NAME_Stream, TEXT("Default"), false);
	// 문자열로 들어온 IP와 Port를 이용해서 주소를 만들어준다.
	FIPv4Address	ip;
	FIPv4Address::Parse(IPAddr, ip);
	TSharedRef<FInternetAddr>	addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);
	m_Connect = m_Socket->Connect(*addr);
	return m_Connect;
}

void CNetworkSession::Close()
{
	if (m_Connect)
	{
		m_Socket->Close();
		delete m_Socket;
		m_Socket = nullptr;
		m_Connect = false;
	}
}

bool CNetworkSession::Receive(int32& packetHeader, int32& length, uint8* packet)
{
	if (!m_Connect)
	{
		return false;
	}
	bool result = m_Socket->Recv(m_ReceivePacket, 1024, length);
	if (!result || length == 0)
	{
		return false;
	}
	FMemory::Memcpy(&packetHeader, m_ReceivePacket, 4);
	FMemory::Memcpy(&length, m_ReceivePacket + 4, 4);
	FMemory::Memcpy(packet, m_ReceivePacket + 8, length);
	return true;
}

bool CNetworkSession::Send(int32 packetHeader, int32 length, uint8* packet)
{
	if (!m_Connect)
	{
		return false;
	}
	FMemory::Memcpy(m_SendPacket, &packetHeader, 4);
	FMemory::Memcpy(m_SendPacket + 4, &length, 4);
	FMemory::Memcpy(m_SendPacket + 8, packet, length);
	return m_Socket->Send(m_SendPacket, length + 8, length);
}
