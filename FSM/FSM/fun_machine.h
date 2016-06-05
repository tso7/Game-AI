// The actual machine that handles the different fun machine state
#include "fun_machine_state.h"
#include <algorithm>

namespace AbstractFSM
{
	namespace Fun
	{
		class FunMachine : public StateMachine
		{
#pragma region Members	
		private:
			// List of states that exist within the machine
			std::vector<FunMachineState*> m_states_;
			// The current machine state
			FunMachineState *m_current_;
			// The exit state
			FunMachineState *m_exit_;
		public:
			// Default constructor
			FunMachine();
			// Dtor
			~FunMachine()
			{
				for (size_t i = 0, len = m_states_.size(); i < len; ++i)
				{
					delete m_states_[i];
				}
			}
#pragma endregion

#pragma region StateMachine Overrides
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