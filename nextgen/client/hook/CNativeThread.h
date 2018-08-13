#pragma once
#include "GtaClasses.h"

class CNativeThread: 
	protected GtaThread
{
private:
	GtaThread *m_pOriginalThread;
	int m_nThreadIndex;

protected:
	char ThreadName[24];

	ThreadStates Reset(unsigned int hash,int v2,int i3);
	ThreadStates Run(int i1);
	ThreadStates Tick(unsigned int msec);

public:
	CNativeThread();
	~CNativeThread();
	void Kill();

	void AttachGtaThread();
	void SetName(char *);
};
