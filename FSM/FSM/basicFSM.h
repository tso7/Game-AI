#pragma once
#ifndef BASICFSM_STATEMACHINE_H_

#include <string>
#include <cstdlib>
#include <map>
using namespace std;


namespace BasicFSM
{
	class StateMachine
	{
	#pragma region Members
	public:
		enum State
		{
			Routing,
			Sentrying,
			Attacking,
			Ending
		};
	private:
		State mState = State::Routing;
		map <State, string> StateNameMap;
	#pragma endregion
	public:	
		StateMachine()
		{
			InitMap();
		}	
		string GetStateName();
		string UpdateState();
		void InitMap();		
		void NextState();
		bool IsDone();
	};
}
#endif // !BASICFSM_STATEMACHINE_H_

