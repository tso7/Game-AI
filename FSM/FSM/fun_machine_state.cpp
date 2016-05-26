#include "fun_machine_state.h"
#include <iostream>
using namespace AbstractFSM::Fun;

vector<FunMachineState*>& FunMachineState::Neighbors()
{
	return m_neighbors_;
}

/// <summary>
/// Initializes a new instance of the FunnerState class.
/// </summary>
/// <param name="mName">Name to display for this state</param>
/// <param name="mDescription">Text to display for this state</param>
FunMachineState::FunMachineState(string name, string desc)
{
	this->m_name_ = name;
	this->m_description_ = desc;
}

string FunMachineState::GetName()
{
	return m_name_;
}

void FunMachineState::Run()
{
	// We don't do any fancy stuff, just print out where we are
	std::cout << "\n" + m_description_;
}