#include "Goal_Runaway.h"
#include "../Raven_Bot.h"
#include "../navigation/Raven_PathPlanner.h"
#include "../Raven_Game.h"
#include "../Raven_Map.h"
#include "Messaging/Telegram.h"
#include "../Raven_SensoryMemory.h"
#include "..\Raven_Messages.h"
#include "Goal_FollowPath.h"
#include "Goal_HuntTarget.h"
#include "Goal_Explore.h"
#include "Goal_GetItem.h"
#include "Goal_DodgeSideToSide.h"
#include "Goal_SeekToPosition.h"


void Goal_Runaway::Activate()
{
	//m_iStatus = active;

	// 이 목표가 다시 활성화되면 일부 기존의 하위 범주가 있을 수 있습니다.
	// 반드시 제거해야 한다.
	RemoveAllSubgoals();

	/*
		HP가 부족하면 실행될 확률이 올라간다.
		무엇을 하는가

		DodgeSideToSide를 통해 피하면서
		
		현재 조준된 상대방과의 거리를 계산해서
		
		거리를 벌린다.
	*/

	// 이 목표가 활성화되는 동안에는 로봇의 표적이 죽는 것이 가능하다.
	// 테스트 대상이 활성 대상인지 확인
	if (!m_pOwner->GetTargetSys()->isTargetPresent())
	{
		m_iStatus = completed;
		return;
	}

	// 만약 로봇이 표적을 쏠 수 있다면(공작물과 표적 사이에)
	// 총을 쏘는 동안 따르는 전술을 선택하라.
	if (m_pOwner->GetTargetSys()->isTargetShootable())
	{
		/*Vector2D dummy;
		if (m_pOwner->canStepBackward(dummy) || m_pOwner->canStepForward(dummy))
		{
			AddSubgoal(new Goal_DodgeSideToSide(m_pOwner));
		}*/

		// 타겟 Bot과의 거리
		double dist = Vec2DDistanceSq(m_pOwner->GetTargetSys()->GetTarget()->Pos(), m_pOwner->Pos());

		// 거리가 
		if (dist < MaxDouble)
		{
			AddSubgoal(new Goal_Explore(m_pOwner));
		}
	}
	
	// 적을 공격할 수 없는 상태가되면 바로 HP를 먹으러간다.
	else
	{
		AddSubgoal(new Goal_GetItem(m_pOwner, type_health));
	}
}

int Goal_Runaway::Process()
{
	//if status is inactive, call Activate()
	ActivateIfInactive();

	//process the subgoals
	m_iStatus = ProcessSubgoals();

	//ReactivateIfFailed();

	return m_iStatus;
}
