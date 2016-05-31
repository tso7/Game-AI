#include "boring_machine.h"

namespace AbstractFSM
{
	namespace Boring
	{
#pragma region StateMachine overrides
		// Accessor to look at the current state
		State * BoringMachine::CurrentState() const
		{
			State * ptr = m_state_;
			return ptr;
		}
		// List of all possible transitions we can make from this current state
		std::vector<std::string> BoringMachine::PossibleTransitions()
		{
			// For this simple example, forward it on to the state method
			return m_state_->ListTransitions();
		}
		// Advance to the specified machine state
		bool BoringMachine::Advance(std::string nextState)
		{
			std::cout << "I'm a boring state machine.  I don't care what you entered.  Advancing state.";
			return m_state_->Advance();
		}
		// Check if machine has reached exit node
		bool BoringMachine::IsComplete()
		{
			// For the simple example, forward it on to the state method
			return m_state_->IsComplete();
		}
#pragma endregion
	}
}
