#include "basicFSM.h"
#include <iostream>
using namespace BasicFSM;

void StateMachine::InitMap()
{
	StateNameMap[State::Routing] = "Routing";
	StateNameMap[State::Sentrying] = "Sentrying";
	StateNameMap[State::Attacking] = "Attacking";
	StateNameMap[State::Ending] = "Ending";
}

string StateMachine::GetStateName()
{
	return StateNameMap[mState];
}

string StateMachine::UpdateState()
{
	return "\nRunning state " + GetStateName();
}

void StateMachine::NextState()
{
	switch ( mState )
	{
	case State::Routing:
		mState = State::Sentrying;
		break;
	case State::Sentrying:
		mState = State::Attacking;
		break;
	case State::Attacking:
		// Ideally this should be determined by game logic. Currently using RNG
		if ( rand() % 100 < 75 )
		{
			std::cout << "\nRandom generator says NPC has survived.";
			mState = State::Routing;
		}
		else
		{
			std::cout << "\nRandom generator says NPC did not survive.";
			mState = State::Ending;
		}
		break;

	case State::Ending:
		// Nothing to do.
		break;
	}
}

bool StateMachine::IsDone()
{
	return mState == State::Ending;
}