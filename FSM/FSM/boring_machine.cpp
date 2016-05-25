#include "boring_machine.h"

namespace AbstractFSM
{
	namespace Boring
	{
		State * BoringMachine::CurrentState() const
		{
			State * ptr = m_state_;
			return ptr;
		}
		vector<string> BoringMachine::PossibleTransitions()
		{
			// For this simple example, forward it on to the state
			return m_state_->ListTransitions();
		}
		bool BoringMachine::Advance(string nextState)
		{
			std::cout << "I'm a boring state machine.  I don't care what you entered.  Advancing state.";
			return m_state_->Advance();
		}
		bool BoringMachine::IsComplete()
		{
			// For the simple example, forward it on to the state
			return m_state_->IsComplete();
		}
	}
}