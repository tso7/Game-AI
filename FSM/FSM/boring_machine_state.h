// Boring State Machine that just advances from one state to the next.
// States do not have much meaning and user input is ignored.
#include "abstract_fsm.h"
#include <unordered_map>

namespace AbstractFSM
{
	namespace Boring
	{
		class BoringMachineState : public State
		{
#pragma region Members
		public:
			enum SameOldStates
			{
				Enter,
				DoStuff,
				Exiting,
				Done
			};
		private:
			// The current machine state
			SameOldStates m_state_;
			// Mapping enum values to their names as strings
			std::unordered_map <SameOldStates, std::string> state_name_map_;
		public:
			// Default constructor
			BoringMachineState()
			{
				SameOldStates m_state_ = SameOldStates::Enter;
				InitMap();
			}
#pragma endregion

#pragma region State overrides
			std::string GetName() override;
			void Run() override;
#pragma endregion

#pragma region Helper functions
			// Initialze enum <-> string mapping
			void InitMap();
			// Check if machine has reached exit node
			bool IsComplete();
			// List all possible transitions from the current machine state
			std::vector<std::string> ListTransitions();
			// Advance to the next machine state
			bool Advance();
#pragma endregion
		};
	}
}