#include "boring_machine_state.h"

namespace AbstractFSM
{
	namespace Boring
	{
#pragma region State overrides
		std::string BoringMachineState::GetName()
		{
			return state_name_map_[m_state_];
		}

		void BoringMachineState::Run()
		{
			// Game logic goes here.
		}
#pragma endregion

#pragma region Helper functions
		// Initialze enum <-> string mapping
		void BoringMachineState::InitMap()
		{
			state_name_map_[SameOldStates::Enter] = "Enter";
			state_name_map_[SameOldStates::DoStuff] = "DoStuff";
			state_name_map_[SameOldStates::Exiting] = "Exiting";
			state_name_map_[SameOldStates::Done] = "Done";
		}
		// Check if machine has reached exit node
		bool BoringMachineState::IsComplete()
		{
			return (m_state_ == SameOldStates::Done);
		}
		// List all possible transitions from the current machine state
		std::vector<std::string> BoringMachineState::ListTransitions()
		{
			std::vector<std::string> result;
			switch ( m_state_ )
			{
			case SameOldStates::Enter:
				result.push_back("DoStuff");
				break;
			case SameOldStates::DoStuff:
				result.push_back("Exiting");
				break;
			case SameOldStates::Exiting:
				result.push_back("Done");
				break;
			case SameOldStates::Done:
				result.push_back("Done");
				break;
			}
			return result;
		}
		// Advance to the next machine state
		bool BoringMachineState::Advance()
		{
			switch ( m_state_ )
			{
			case SameOldStates::Enter:
				m_state_ = SameOldStates::DoStuff;
				break;
			case SameOldStates::DoStuff:
				m_state_ = SameOldStates::Exiting;
				break;
			case SameOldStates::Exiting:
				m_state_ = SameOldStates::Done;
				break;
			case SameOldStates::Done:
				// Do nothing.
				break;
			}
			return true;
		}
#pragma endregion
	}
}