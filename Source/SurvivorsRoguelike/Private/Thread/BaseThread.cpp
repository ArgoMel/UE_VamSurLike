#include "Thread/BaseThread.h"

CBaseThread::CBaseThread()
	: m_Loop(true)
{
}

CBaseThread::~CBaseThread()
{
}

bool CBaseThread::Init()
{
	return true;
}
