#include "LobbyMisc.h"

#include "ChatCommandParser.h"
#include "InitLogic.h"
#include "LanLogic.h"
#include "LobbyClient.h"
#include "LobbyConfig.h"
#include "LobbyContainer.h"
#include "LobbyEvent.h"
#include "LobbyPersistentData.h"
#include "LoginScreen.h"
#include "LobbyStaging.h"
#include "PingLogic.h"
#include "RoutingLogic.h"
#include "WONLobbyPrv.h"


#include "WONAuth/AuthContext.h"
#include "WONGUI/Sound.h"
#include "WONSocket/UDPManager.h"

using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetAccountServers()
{
	return gLobbyData.get()?gLobbyData->mAccountServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetAuthServers()
{
	return gLobbyData.get()?gLobbyData->mAuthServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetDirServers()
{
	return gLobbyData.get()?gLobbyData->mDirServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetRoomDirServers()
{
	return gLobbyData.get()?gLobbyData->mRoomDirServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetFirewallDetectServers()
{
	return gLobbyData.get()?gLobbyData->mFirewallDetectServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ServerContext* LobbyMisc::GetPatchServers()
{
	return gLobbyData.get()?gLobbyData->mPatchServers:NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::SetRoomDirServersToDirServers()
{
	if(gLobbyData.get())
		gLobbyData->mRoomDirServers = gLobbyData->mDirServers;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
AuthContext* LobbyMisc::GetAuthContext()
{
	if(gLobbyData.get()==NULL)
		return NULL;

	if(gLobbyData->mLobbyConfig->mIsCRCCheck && !gLobbyData->mHasSetHashFileList)
	{
		gLobbyData->mHasSetHashFileList = true;
		if(gLobbyData->mHashFileList.empty())
			gLobbyData->mAuthContext->SetHashFile(gLobbyData->mLoginCommunity);
		else
			gLobbyData->mAuthContext->SetHashFileList(gLobbyData->mLoginCommunity, gLobbyData->mHashFileList);
	}

	return gLobbyData->mAuthContext;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::SetVersionStatus(WONStatus theStatus)
{
	if(gLobbyData.get()!=NULL)
		gLobbyData->mVersionStatus = theStatus;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
WONStatus LobbyMisc::GetVersionStatus()
{
	return gLobbyData.get()?gLobbyData->mVersionStatus:WS_None;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyMisc::GetCDKey(CDKey &theKey)
{
	if(gLobbyData.get()==NULL)
		return false;
	else
	{
		theKey = gLobbyData->mCDKey;
		return theKey.IsValid();
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyMisc::DoCDKeyCheck()
{	
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mLobbyConfig->mIsCDKeyCheck;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyMisc::IsCDKeyValid()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mCDKey.IsValid();
	else
		return false;	
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
unsigned short LobbyMisc::GetProductId()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mProductId;
	else
		return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
unsigned short LobbyMisc::GetLanProductId()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mLanProductId;
	else
		return 0;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int LobbyMisc::GetDefaultTimeout()
{
	return 60000;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::RunOp(AsyncOp *theOp, DWORD theTime)
{
	if(theTime==0)
		theTime = GetDefaultTimeout();

	theOp->RunAsync(theTime);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::SetTOUTimes(time_t theSysTime, time_t theGameTime)
{
	if(gLobbyData.get())
	{
		gLobbyData->mSysTOUTime = theSysTime;
		gLobbyData->mGameTOUTime = theGameTime;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::GetTOUTimes(time_t &theSysTime, time_t &theGameTime)
{
	if(gLobbyData.get())
	{
		theSysTime = gLobbyData->mSysTOUTime;
		theGameTime = gLobbyData->mGameTOUTime;
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
const std::string& LobbyMisc::GetSysTOUPath()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mSysTOUPath;
	else
		return GetEmptyStr();
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
const std::string& LobbyMisc::GetGameTOUPath()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mGameTOUPath;
	else
		return GetEmptyStr();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyMisc::CheckDoTOU(time_t theSysTime, time_t theGameTime)
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mSysTOUTime>theSysTime || gLobbyData->mGameTOUTime>theGameTime;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyServerList* LobbyMisc::GetLobbyServerList()
{
	if(gLobbyData.get())
		return gLobbyData->mRoutingLogic->GetServerList();
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyGroup* LobbyMisc::GetChatGroup()
{
	if(gLobbyData.get())
		return gLobbyData->mRoutingLogic->GetChatGroup();
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyServer* LobbyMisc::GetChatServer()
{
	if(gLobbyData.get())
		return gLobbyData->mRoutingLogic->GetServer();
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ChatCommandParser* LobbyMisc::GetChatCommandParser()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mChatCommandParser;
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
ChatCommandParser* LobbyMisc::GetChatCommandParser(int theRoomSpecFlags)
{
	if(gLobbyData.get()==NULL)
		return NULL;
	
	ChatCommandParser *aParser = gLobbyData->mChatCommandParser;
	LobbyClientList *aClientList = NULL;

	if(gLobbyData->mLobbyContainer->OnInternetScreen())
		aClientList = gLobbyData->mRoutingLogic->GetClientList();
	else if(gLobbyData->mLobbyContainer->OnLanScreen())
		aClientList = gLobbyData->mLanLogic->GetClientList();

	aParser->SetRoomContext(aClientList,theRoomSpecFlags);
	return aParser;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::SetIgnored(LobbyClient *theClient, bool ignored, int theRoomSpecFlags)
{
	if(gLobbyData.get()==NULL)
		return;

	if(theClient->IsIgnored()==ignored)
		return;

	theClient->SetIsIgnored(ignored);
	gLobbyData->mPersistentData->SetIgnore(theClient->GetName(),ignored);
	LobbyEvent::BroadcastEvent(new ClientChangedEvent(theClient,theRoomSpecFlags,LobbyChangeType_Modify));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::SetBlocked(LobbyClient *theClient, bool blocked, int theRoomSpecFlags)
{
	if(gLobbyData.get()==NULL)
		return;

	if (!gLobbyData->mLobbyConfig->mIsCDKeyCheck)
		return;

	if(theClient->IsBlocked()==blocked)
		return;

	theClient->SetIsBlocked(blocked);
	LobbyEvent::BroadcastEvent(new ClientChangedEvent(theClient,theRoomSpecFlags,LobbyChangeType_Modify));
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
UDPManager* LobbyMisc::GetUDPManager()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mUDPManager;
	else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::QueuePing(LobbyGame *theGame, bool force)
{
	if(gLobbyData.get()!=NULL)
		gLobbyData->mPingLogic->QueuePing(theGame,false,force);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::QueueDetailQuery(LobbyGame *theGame)
{
	if(gLobbyData.get()!=NULL)
		gLobbyData->mPingLogic->QueuePing(theGame,true,true);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
int LobbyMisc::GetNumPingsToDo()
{
	if(gLobbyData.get()!=NULL)
		return gLobbyData->mPingLogic->GetNumPingsToDo();
	else
		return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::KillPings(bool resetValues)
{
	if(gLobbyData.get()!=NULL)
		gLobbyData->mPingLogic->KillPings(resetValues);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::KillFirewallDetectOps()
{
	if(gLobbyData.get()!=NULL)
		gLobbyData->mInitLogic->KillFirewallDetectOps();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::PlaySound(Sound *theSound)
{
	if(gLobbyData.get()!=NULL && !gLobbyData->mSuspended && theSound!=NULL)
		theSound->Play();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::CheckSetNetworkAdapter(long theHost)
{
	bool needRestartUDPManager = false;
	if(IPAddr::GetLocalHost()!=theHost)
	{
		needRestartUDPManager = true;
		if(!IPAddr::SetLocalHost(theHost,true))
			return;
	}


	if(IPAddr::GetLocalHost()!=LobbyPersistentData::GetNetworkAdapter())
		LobbyPersistentData::SetNetworkAdapter();

	if(needRestartUDPManager)
		RestartUDPManager();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyMisc::RestartUDPManager()
{
	// Init UDP Manager
	LobbyConfig *aConfig = LobbyConfig::GetLobbyConfig();
	unsigned short aPort = aConfig?aConfig->mLobbyPort:8888;
	LobbyStaging::SetLobbyPort(aPort);
	UDPManager *aMgr = LobbyMisc::GetUDPManager();
	if(aMgr!=NULL)
	{
		WONStatus aStatus = aMgr->Bind(aPort,true);
		if(aStatus!=WS_Success)
		{
			srand(time(NULL));
			aPort = rand()%10000 + 10000; // FIXME
			aStatus = aMgr->Bind(aPort);
			LobbyStaging::SetLobbyPort(aPort);
		}

		if(aStatus==WS_Success)
			aMgr->SetAutoRecv(true);
	}

}
