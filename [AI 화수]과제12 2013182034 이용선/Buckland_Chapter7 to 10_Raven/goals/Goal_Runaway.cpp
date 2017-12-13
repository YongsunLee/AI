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

	// �� ��ǥ�� �ٽ� Ȱ��ȭ�Ǹ� �Ϻ� ������ ���� ���ְ� ���� �� �ֽ��ϴ�.
	// �ݵ�� �����ؾ� �Ѵ�.
	RemoveAllSubgoals();

	/*
		HP�� �����ϸ� ����� Ȯ���� �ö󰣴�.
		������ �ϴ°�

		DodgeSideToSide�� ���� ���ϸ鼭
		
		���� ���ص� ������� �Ÿ��� ����ؼ�
		
		�Ÿ��� ������.
	*/

	// �� ��ǥ�� Ȱ��ȭ�Ǵ� ���ȿ��� �κ��� ǥ���� �״� ���� �����ϴ�.
	// �׽�Ʈ ����� Ȱ�� ������� Ȯ��
	if (!m_pOwner->GetTargetSys()->isTargetPresent())
	{
		m_iStatus = completed;
		return;
	}

	// ���� �κ��� ǥ���� �� �� �ִٸ�(���۹��� ǥ�� ���̿�)
	// ���� ��� ���� ������ ������ �����϶�.
	if (m_pOwner->GetTargetSys()->isTargetShootable())
	{
		/*Vector2D dummy;
		if (m_pOwner->canStepBackward(dummy) || m_pOwner->canStepForward(dummy))
		{
			AddSubgoal(new Goal_DodgeSideToSide(m_pOwner));
		}*/

		// Ÿ�� Bot���� �Ÿ�
		double dist = Vec2DDistanceSq(m_pOwner->GetTargetSys()->GetTarget()->Pos(), m_pOwner->Pos());

		// �Ÿ��� 
		if (dist < MaxDouble)
		{
			AddSubgoal(new Goal_Explore(m_pOwner));
		}
	}
	
	// ���� ������ �� ���� ���°��Ǹ� �ٷ� HP�� ����������.
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
