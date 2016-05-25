#pragma once
#ifndef ABSTRACTFSM_STATEMACHINE_H_

#include <string>
#include <vector>
using namespace std;

namespace AbstractFSM
{
	class State
	{
	public:
		// Utility function to help us display useful things
		virtual string GetName() = 0;
		// Do something
		virtual void Run() = 0;
	};

	class StateMachine
	{
	public:
		// Accessor to look at the current state.
		virtual State * CurrentState() const = 0;
		
		// List of all possible transitions we can make from this current state.
		virtual vector<string> PossibleTransitions() = 0;

		// Advance to a named state, returning true on success.
		virtual bool Advance(string nextState) = 0;

		// Is this state a "completion" state.  Are we there yet?
		virtual bool IsComplete() = 0;
		virtual ~StateMachine() {}
	};
}
#endif // !ABSTRACTFSM_STATEMACHINE_H_

