#pragma once

#include "State.h"

class MinerSon;

class SonGlobalState : public State<MinerSon>
{
private:

	SonGlobalState() {}

	//copy ctor and assignment should be private
	SonGlobalState(const SonGlobalState&);
	SonGlobalState& operator=(const SonGlobalState&);

public:

	static SonGlobalState* Instance();

	virtual void Enter(MinerSon* son) {}

	virtual void Execute(MinerSon* son);

	virtual void Exit(MinerSon* son) {}
};

class GoToPlaygraund : public State<MinerSon>
{

private:

	GoToPlaygraund() {}

	//copy ctor and assignment should be private
	GoToPlaygraund(const GoToPlaygraund&);
	GoToPlaygraund& operator=(const GoToPlaygraund&);

public:

	static GoToPlaygraund* Instance();

	virtual void Enter(MinerSon* son);

	virtual void Execute(MinerSon* son);

	virtual void Exit(MinerSon* son);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class GoHouseAndSleep : public State<MinerSon>
{
private:

	GoHouseAndSleep() {}

	//copy ctor and assignment should be private
	GoHouseAndSleep(const GoHouseAndSleep&);
	GoHouseAndSleep& operator=(const GoHouseAndSleep&);

public:

	static GoHouseAndSleep* Instance();

	virtual void Enter(MinerSon* son);

	virtual void Execute(MinerSon* son);

	virtual void Exit(MinerSon* son);

};

class GoToSupermarket : public State<MinerSon>
{
private:

	GoToSupermarket() {}

	//copy ctor and assignment should be private
	GoToSupermarket(const GoToSupermarket&);
	GoToSupermarket& operator=(const GoToSupermarket&);

public:

	static GoToSupermarket* Instance();

	virtual void Enter(MinerSon* son);

	virtual void Execute(MinerSon* son);

	virtual void Exit(MinerSon* son);

};