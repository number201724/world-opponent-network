#include "LobbyContainer.h"

#include "LobbyTypes.h"
#include "LoginScreen.h"
#include "RootScreen.h"

#include "WONGUI/GUIConfig.h"
#include "WONGUI/HTMLDisplayGen.h"

using namespace WONAPI;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyContainer::LobbyContainer()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyContainer::~LobbyContainer()
{
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyContainer::InitComponent(ComponentInit &theInit)
{
	ScreenContainer::InitComponent(theInit);
	if(theInit.mType==ComponentInitType_ComponentConfig)
	{
		ComponentConfigInit &anInit = (ComponentConfigInit&)theInit;
		ComponentConfig *aConfig = anInit.mConfig;

		Font *aFont = GetDefaultFont();
		HTMLDisplayGen::SetGlobalDefaultFontFace(aFont->GetFace());

		WONComponentConfig_Get(aConfig,mLoginScreen,"LoginScreen");
		WONComponentConfig_Get(aConfig,mInternetScreen,"InternetScreen");
		WONComponentConfig_Get(aConfig,mLanScreen,"LanScreen");

		AddScreen(mLoginScreen);
		AddScreen(mInternetScreen);
		AddScreen(mLanScreen);
		ShowScreen(mLoginScreen);	
	}
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyContainer::ShowInternetScreen()
{
	ShowScreen(mInternetScreen);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyContainer::ShowLanScreen()
{
	ShowScreen(mLanScreen);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
void LobbyContainer::ShowLoginScreen()
{
	ShowScreen(mLoginScreen);
	mLoginScreen->ShowMOTD();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyContainer::OnInternetScreen()
{
	return GetCurScreen()==mInternetScreen.get();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyContainer::OnLanScreen()
{
	return GetCurScreen()==mLanScreen.get();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
bool LobbyContainer::OnLoginScreen()
{
	return GetCurScreen()==mLoginScreen.get();
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
LobbyGameType LobbyContainer::GetGameScreenType()
{
	if(OnInternetScreen())
		return LobbyGameType_Internet;
	else if(OnLanScreen())
	{
		if(mLanScreen->OnLanTab())
			return LobbyGameType_Lan; 
		else if(mLanScreen->OnDirectConnectTab())
			return LobbyGameType_DirectConnect;
	}
	
	return LobbyGameType_None;
}

