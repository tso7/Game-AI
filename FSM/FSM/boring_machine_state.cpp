#include "boring_machine_state.h"
#include <vector>
using namespace AbstractFSM::Boring;

void BoringMachineState::InitMap()
{
	state_name_map_[SameOldStates::Enter] = "Enter";
	state_name_map_[SameOldStates::DoStuff] = "DoStuff";
	state_name_map_[SameOldStates::Exiting] = "Exiting";
	state_name_map_[SameOldStates::Done] = "Done";
}
string BoringMachineState::GetName()
{
	return state_name_map_[m_state_];
}

void BoringMachineState::Run()
{
	// Game logic goes here.
}
bool BoringMachineState::IsComplete()
{
	return (m_state_ == SameOldStates::Done);
}

vector<string> BoringMachineState::ListTransitions()
{
	std::vector<string> result;
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