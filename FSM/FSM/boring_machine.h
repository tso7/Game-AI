#include "boring_machine_state.h"
#include <iostream>

namespace AbstractFSM
{
	namespace Boring
	{
		class BoringMachine : public StateMachine
		{
		private:
			BoringMachineState * m_state_;
		public:
			BoringMachine()
			{
				m_state_ = new BoringMachineState;
			}
			State * CurrentState() const;
			vector<string> PossibleTransitions();
			bool Advance(string);
			bool IsComplete();
		};
	}
}