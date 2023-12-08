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
	// ����ȭ. �� ������ ���������̹Ƿ� �����Ҷ� �����ڰ� ȣ��Ǿ�
	// Lock�� �ɾ��ְ� �� �Լ��� ����ɶ� �� ��ü�� ���ŵǾ� �Ҹ��ڰ� ȣ��ǰ�
	// �Ҹ��ڿ��� �ڵ����� Unlock�� ���ְ� �ȴ�.
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
