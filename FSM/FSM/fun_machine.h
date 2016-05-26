#include "fun_machine_state.h"

namespace AbstractFSM
{
	namespace Fun
	{
		class FunMachine : public StateMachine
		{
		private:
			vector<FunMachineState*> m_states_;
			FunMachineState *m_current_;
			FunMachineState *m_exit_;
		public:
			FunMachine();
#pragma region StateMachine Overrides
			State* CurrentState() const;
			vector<string> PossibleTransitions();
			bool Advance(string nextState);		
			bool IsComplete();
#pragma endregion
		};
	}
}