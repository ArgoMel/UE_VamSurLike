#include "Network/PacketQueue.h"

CPacketQueue::CPacketQueue()
	: m_Head(0)
	, m_Tail(0)
	, m_Size(0)
{
}

CPacketQueue::~CPacketQueue()
{
}

void CPacketQueue::Push(int32 header, int32 length, uint8* packet)
{
	// 동기화. 이 변수는 지역변수이므로 생성할때 생성자가 호출되어
	// Lock을 걸어주고 이 함수가 종료될때 이 객체도 제거되어 소멸자가 호출되고
	// 소멸자에서 자동으로 Unlock을 해주게 된다.
	FScopeLock	lock(&m_Crt);
	if (m_Size == QueMaxSize -1)
	{
		return;
	}
	m_Tail = (m_Tail + 1) % QueMaxSize;
	m_Queue[m_Tail].Header = header;
	m_Queue[m_Tail].Size = length;
	FMemory::Memcpy(m_Queue[m_Tail].Packet, packet, length);
	++m_Size;
}

void CPacketQueue::Pop(int32& header, int32& length, uint8* packet)
{
	FScopeLock	lock(&m_Crt);
	if (m_Size == 0)
	{
		return;
	}
	m_Head = (m_Head + 1) % QueMaxSize;
	header = m_Queue[m_Head].Header;
	length = m_Queue[m_Head].Size;
	FMemory::Memcpy(packet, m_Queue[m_Tail].Packet, length);
	--m_Size;
}

bool CPacketQueue::Empty()
{
	return m_Size == 0;
}

int32 CPacketQueue::Size()
{
	return m_Size;
}

void CPacketQueue::Clear()
{
	m_Size = 0;
	m_Head = 0;
	m_Tail = 0;
}
