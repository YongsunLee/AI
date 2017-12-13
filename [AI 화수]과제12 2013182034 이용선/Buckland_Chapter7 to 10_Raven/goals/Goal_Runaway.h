#pragma once

#include "Goals/Goal_Composite.h"
#include "Raven_Goal_Types.h"

class Raven_Bot;

class Goal_Runaway : public Goal_Composite<Raven_Bot>
{
public:
	Goal_Runaway(Raven_Bot* pOwner) : Goal_Composite<Raven_Bot>(pOwner, goal_Runaway) {};

	void Activate();

	int Process();

	void Terminate() { m_iStatus = completed; }
};
