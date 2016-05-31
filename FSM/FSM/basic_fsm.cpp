#include "basic_fsm.h"
#include <iostream>
using namespace BasicFSM;

void StateMachine::InitMap()
{
	state_name_map_[State::Routing] = "Routing";
	state_name_map_[State::Sentrying] = "Sentrying";
	state_name_map_[State::Attacking] = "Attacking";
	state_name_map_[State::Ending] = "Ending";
}

std:: string StateMachine::GetStateName()
{
	return state_name_map_[m_state_];
}

std::string StateMachine::UpdateState()
{
	return "\nRunning state " + GetStateName();
}

void StateMachine::NextState()
{
	switch ( m_state_ )
	{
	case State::Routing:
		m_state_ = State::Sentrying;
		break;
	case State::Sentrying:
		m_state_ = State::Attacking;
		break;
	case State::Attacking:
		// Ideally this should be determined by game logic. Currently using RNG
		if ( rand() % 100 < 75 )
		{
			std::cout << "\nRandom generator says NPC has survived.";
			m_state_ = State::Routing;
		}
		else
		{
			std::cout << "\nRandom generator says NPC did not survive.";
			m_state_ = State::Ending;
		}
		break;

	case State::Ending:
		// Nothing to do.
		break;
	}
}

bool StateMachine::IsDone()
{
	return m_state_ == State::Ending;
}