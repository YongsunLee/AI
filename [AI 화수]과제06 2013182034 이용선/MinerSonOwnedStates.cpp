#include "MinerSonOwnedStates.h"
#include "MinerSon.h"
#include "Locations.h"
#include "EntityNames.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

SonGlobalState* SonGlobalState::Instance()
{
	static SonGlobalState instance;

	return &instance;
}

void SonGlobalState::Execute(MinerSon * son)
{
	if (RandFloat() < 0.2)
	{
		son->GetFSM()->ChangeState(GoHouseAndSleep::Instance());
	}
	else if (RandFloat() < 0.1)
	{
		son->GetFSM()->ChangeState(GoToSupermarket::Instance());
	}
}

bool SonGlobalState::OnMessage(MinerSon * son, const Telegram & msg)
{
	return false;
}

//----------------------------------------------------------------------------

GoToPlaygraund* GoToPlaygraund::Instance()
{
	static GoToPlaygraund instance;

	return &instance;
}

void GoToPlaygraund::Enter(MinerSon * son)
{
	if (son->Location() != playground) son->ChangeLocation(playground);
}

void GoToPlaygraund::Execute(MinerSon * son)
{
	switch (RandInt(0, 2))
	{
	case 0:

		cout << "\n" << GetNameOfEntity(son->ID()) << ": ¼ú·¡Àâ±â";

		break;

	case 1:

		cout << "\n" << GetNameOfEntity(son->ID()) << ": ¾óÀ½¶¯";

		break;

	case 2:

		cout << "\n" << GetNameOfEntity(son->ID()) << ": °æÂû°ú µµµÏ";

		break;
	}
}

void GoToPlaygraund::Exit(MinerSon * son)
{
}

bool GoToPlaygraund::OnMessage(MinerSon * son, const Telegram & msg)
{
	return false;
}

//----------------------------------------------------------------------------

GoHouseAndSleep* GoHouseAndSleep::Instance()
{
	static GoHouseAndSleep instance;

	return &instance;
}

void GoHouseAndSleep::Enter(MinerSon * son)
{
	if (son->Location() != shack)
	{
		cout << "\n" << GetNameOfEntity(son->ID()) << ": Bye, I'm going home.";
		son->ChangeLocation(shack);

		//let the wife know I'm home
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
			son->ID(),        //ID of sender
			ent_Elsa,            //ID of recipient
			Msg_MomImHome,   //the message
			NO_ADDITIONAL_INFO);
	}
}

void GoHouseAndSleep::Execute(MinerSon * son)
{


	cout << "\n" << GetNameOfEntity(son->ID()) << ": ZZZ....";

	son->GetFSM()->RevertToPreviousState();


}

void GoHouseAndSleep::Exit(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": Awake from one¢¥s sleep";
}

bool GoHouseAndSleep::OnMessage(MinerSon * son, const Telegram & msg)
{
	SetTextColor(BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	switch (msg.Msg)
	{
	case Msg_FrenchFriesReady:

		cout << "\nMessage handled by " << GetNameOfEntity(son->ID())
			<< " at time: " << Clock->GetCurrentTime();

		SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

		cout << "\n" << GetNameOfEntity(son->ID())
			<< ": Okay Hun, ahm a comin'!";

		son->GetFSM()->ChangeState(EatFrenchFries::Instance());

		return true;

	}//end switch

	return false;
}

//----------------------------------------------------------------------------

GoToSupermarket * GoToSupermarket::Instance()
{
	static GoToSupermarket instance;

	return &instance;
}

void GoToSupermarket::Enter(MinerSon * son)
{
	if (son->Location() != supermarket)
	{
		cout << "\n" << GetNameOfEntity(son->ID()) << ": I'm Thirst. Let's Go Supermarket";
		son->ChangeLocation(supermarket);
	}
}

void GoToSupermarket::Execute(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": Drinking COKE";

	son->GetFSM()->RevertToPreviousState();
}

void GoToSupermarket::Exit(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": Let's Go PlayGround";
}

bool GoToSupermarket::OnMessage(MinerSon * son, const Telegram & msg)
{
	return false;
}


//----------------------------------------------------------------------------

EatFrenchFries * EatFrenchFries::Instance()
{
	static EatFrenchFries instace;

	return &instace;
}

void EatFrenchFries::Enter(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": " << "Smells Reaaal goood";
}

void EatFrenchFries::Execute(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": " << "This FranchFries really Crunch";

	son->GetFSM()->RevertToPreviousState();
}

void EatFrenchFries::Exit(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": " << "Thank's Mom '";
}

bool EatFrenchFries::OnMessage(MinerSon * son, const Telegram & msg)
{
	return false;
}
