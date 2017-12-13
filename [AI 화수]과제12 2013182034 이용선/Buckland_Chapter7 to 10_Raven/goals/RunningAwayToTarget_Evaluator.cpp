#include "RunningAwayToTarget_Evaluator.h"
#include "Goal_Think.h"
#include "Raven_Goal_Types.h"
#include "../Raven_WeaponSystem.h"
#include "../Raven_ObjectEnumerations.h"
#include "misc/cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include "Raven_Feature.h"


#include "debug/DebugConsole.h"

double RunningAwayToTarget_Evaluator::CalculateDesirability(Raven_Bot * pBot)
{
	double Desirability = 0.0;

	//only do the calculation if there is a target present
	if (pBot->GetTargetSys()->isTargetPresent())
	{
		//const double Tweaker = 5.0;

		// HP가 줄어들면 줄어들수록 값이 커져서 점수가 높게 나온다.
		Desirability = 1- Raven_Feature::Health(pBot);

		//bias the value according to the personality of the bot
		//Desirability *= m_dCharacterBias;
	}

	return Desirability;
}

void RunningAwayToTarget_Evaluator::SetGoal(Raven_Bot * pBot)
{
	pBot->GetBrain()->AddGoal_RunAway();
}

void RunningAwayToTarget_Evaluator::RenderInfo(Vector2D Position, Raven_Bot * pBot)
{
	gdi->TextAtPos(Position, "RA: " + ttos(CalculateDesirability(pBot), 2));
	return;
}
