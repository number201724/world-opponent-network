#include "SocketThread.h"
using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SocketThread::SocketThread()
{
	mSingleThreaded = false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
SocketThread::~SocketThread()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SocketThread::PurgeOps()
{
}

/*
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SocketThread::Init(bool doThread, SocketThread *theThread)
{
	if(mSocketThread!=NULL)
		Destroy();

	mSocketThread = theThread;	
	mSocketThread->SetSingleThreaded(!doThread);
	if(doThread && mSocketThread->NeedThreadPrv())
		mSocketThread->Start();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void SocketThread::Destroy()
{
	SocketThread *aThread = mSocketThread;
	mSocketThread = NULL;

	if(aThread!=NULL)
	{
		if(aThread->NeedThreadPrv())
			aThread->Stop();

		delete aThread;
	}
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::Pump(DWORD theWaitTime)
{
	mSocketThread->PumpPrv(theWaitTime);
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::PumpPrv(DWORD theWaitTime)
{
	mSignalEvent.WaitFor(theWaitTime);
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::AddSocketOp(SocketOp *theOp)
{
	if(mSocketThread!=NULL)
		mSocketThread->AddSocketOpPrv(theOp);
	else
		theOp->Kill();
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::RemoveSocketOp(SocketOp *theOp)
{
	if(mSocketThread!=NULL)
		mSocketThread->RemoveSocketOpPrv(theOp);
}
*/

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::AddSocketOp(SocketOp *)
{
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::RemoveSocketOp(SocketOp *)
{
}
	
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::Pump(DWORD theWaitTime)
{
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SocketThread::ThreadFunc()
{
	while(!mStopped)
		Pump(1000);
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool SocketThread::DoOp(SocketOp *theOp)
{
	if(theOp->Pending())
	{
		WONStatus aStatus = theOp->Continue();
		if(aStatus!=WS_TimedOut)
		{
			theOp->mInSocketThread = false;
			theOp->Finish(aStatus);
		}
	}
	
	if(!theOp->Pending())
	{
		theOp->mInSocketThread = false;
		return true;
	}

	return false;
}

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

