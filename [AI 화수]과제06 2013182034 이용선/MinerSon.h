#pragma once

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "MinerSonOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

class MinerSon : public BaseGameEntity
{
private :
	StateMachine<MinerSon>* m_pStateMachine;

	location_type			m_Location;

public:
	MinerSon(int id) : BaseGameEntity(id), m_Location(shack)
	{
		m_pStateMachine = new StateMachine<MinerSon>(this);

		m_pStateMachine->SetCurrentState(GoToPlaygraund::Instance());

		m_pStateMachine->SetGlobalState(SonGlobalState::Instance());

	}
	~MinerSon() { delete m_pStateMachine; }

	void Update();

	virtual bool  HandleMessage(const Telegram& msg);

	StateMachine<MinerSon>* GetFSM() const { return m_pStateMachine; }

	location_type Location() const { return m_Location; }
	void		  ChangeLocation(const location_type loc) { m_Location = loc; }
};

