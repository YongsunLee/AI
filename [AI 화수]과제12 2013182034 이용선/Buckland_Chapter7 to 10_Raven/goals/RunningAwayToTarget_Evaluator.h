#pragma once

#include "Goal_Evaluator.h"
#include "../Raven_Bot.h"

class RunningAwayToTarget_Evaluator : public Goal_Evaluator
{
public:
	RunningAwayToTarget_Evaluator(double bias) : Goal_Evaluator(bias) {};

	double CalculateDesirability(Raven_Bot* pBot);

	void  SetGoal(Raven_Bot* pBot);

	void RenderInfo(Vector2D Position, Raven_Bot* pBot);

private:

};