// Template to be used for different implementations of States and State Machjines
#pragma once
#ifndef ABSTRACTFSM_STATEMACHINE_H_

#include <string>
#include <vector>

namespace AbstractFSM
{
	// Abstract classes for the base structure of the State Machine

	class State
	{
	public:
		// Utility function to display name.
		virtual std::string GetName() = 0;
		// Function to perform state related actions.
		virtual void Run() = 0;
		// To prevent memory leaks from abstract class.
		virtual ~State() {}
	};

	class StateMachine
	{
	public:
		// Accessor to look at the current state.
		virtual State* CurrentState() const = 0;
		// List of all possible transitions we can make from this current state.
		virtual std::vector<std::string> PossibleTransitions() = 0;
		// Advance to a named state, returning true on success.
		virtual bool Advance(std::string nextState) = 0;
		// Is this state a "completion" state.  Are we there yet?
		virtual bool IsComplete() = 0;
		// To prevent memory leaks from abstract class.
		virtual ~StateMachine() {}
	};
}
#endif // !ABSTRACTFSM_STATEMACHINE_H_

