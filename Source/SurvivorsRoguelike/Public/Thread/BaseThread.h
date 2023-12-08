#pragma once
#include "../GameInfo.h"

class SURVIVORSROGUELIKE_API CBaseThread : public FRunnable
{
public:
	CBaseThread();
	virtual ~CBaseThread();

protected:
	FString	m_Name;
	bool	m_Loop;
	
public:
	void SetName(const FString& name)
	{
		m_Name = name;
	}
	void SetLoop(bool loop)
	{
		m_Loop = loop;
	}

	virtual bool Init();
	virtual uint32 Run() = 0;
	virtual void Stop() {};
	virtual void Exit() {};
};
