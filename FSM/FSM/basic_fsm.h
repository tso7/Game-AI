// Basic State Machine implemented using switch/case
#pragma once
#ifndef BASICFSM_STATEMACHINE_H_

#include <string>
#include <cstdlib>
#include <unordered_map>

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
		// The current machine state
		State m_state_;
		// Mapping enum values to their names as strings
		std::unordered_map <State, std::string> state_name_map_;
#pragma endregion
#pragma region Methods
	public:	
		// Default constructor
		StateMachine()
		{
			m_state_ = State::Routing;
			InitMap();
		}
		std::string GetStateName();
		// Get current running machine state
		std::string UpdateState();
		// Initialze enum <-> string mapping
		void InitMap();
		// Logic to advance to next state
		void NextState();
		// Check if machine has reached exit node
		bool IsDone();
	};
#pragma endregion
}
#endif // !BASICFSM_STATEMACHINE_H_

