#pragma once
#include "../GameInfo.h"

constexpr int QueMaxSize = 201;

struct FPacketInfo
{
	int32			Header;
	int32			Size;
	uint8			Packet[1016];
};


class SURVIVORSROGUELIKE_API CPacketQueue
{
public:
	CPacketQueue();
	~CPacketQueue();

private:
	FCriticalSection	m_Crt;
	FPacketInfo			m_Queue[QueMaxSize];
	int32				m_Head;
	int32				m_Tail;
	int32				m_Size;

public:
	void Push(int32 header, int32 length, uint8* packet);
	void Pop(int32& header, int32& length, uint8* packet);
	bool Empty();
	int32 Size();
	void Clear();
};
