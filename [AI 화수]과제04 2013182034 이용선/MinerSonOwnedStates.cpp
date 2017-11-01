#include "MinerSonOwnedStates.h"
#include "MinerSon.h"
#include "Locations.h"
#include "EntityNames.h"

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
	else if ( RandFloat() < 0.1 )
	{
		son->GetFSM()->ChangeState(GoToSupermarket::Instance());
	}
}

//----------------------------------------------------------------------------

GoToPlaygraund* GoToPlaygraund::Instance()
{
	static GoToPlaygraund instance;

	return &instance;
}

void GoToPlaygraund::Enter(MinerSon * son)
{
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

//----------------------------------------------------------------------------

GoHouseAndSleep* GoHouseAndSleep::Instance()
{
	static GoHouseAndSleep instance;

	return &instance;
}

void GoHouseAndSleep::Enter(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": Bye, I'm going home.";
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

//----------------------------------------------------------------------------

GoToSupermarket * GoToSupermarket::Instance()
{
	static GoToSupermarket instance;

	return &instance;
}

void GoToSupermarket::Enter(MinerSon * son)
{
	cout << "\n" << GetNameOfEntity(son->ID()) << ": I'm Thirst. Let's Go Supermarket";
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
