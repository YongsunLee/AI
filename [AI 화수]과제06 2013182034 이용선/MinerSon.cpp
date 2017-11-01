#include "MinerSon.h"

void MinerSon::Update()
{
	//set text color to green
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	m_pStateMachine->Update();
}

bool MinerSon::HandleMessage(const Telegram & msg)
{
	return m_pStateMachine->HandleMessage(msg);
}
