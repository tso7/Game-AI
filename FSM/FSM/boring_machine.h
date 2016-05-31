// The actual machine that handles the different boring machine state
#include "boring_machine_state.h"
#include <iostream>

namespace AbstractFSM
{
	namespace Boring
	{
		class BoringMachine : public StateMachine
		{
#pragma region Members		
		private:
			// The current machine state
			BoringMachineState * m_state_;
		public:
			// Default constructor
			BoringMachine()
			{
				m_state_ = new BoringMachineState;
			}
#pragma endregion

#pragma region StateMachine overrides
			// Accessor to look at the current state
			State* CurrentState() const override;
			// List of all possible transitions we can make from this current state
			std::vector<std::string> PossibleTransitions() override;
			// Advance to the specified machine state
			bool Advance(std::string) override;
			// Check if machine has reached exit node
			bool IsComplete() override;
#pragma endregion
		};
	}
}