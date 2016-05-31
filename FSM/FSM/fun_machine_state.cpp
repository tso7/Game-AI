#include "fun_machine_state.h"
#include <iostream>

namespace AbstractFSM
{
	namespace Fun
	{
#pragma region Members
		// Fetch the list of neighbors
		std::vector<FunMachineState*>& FunMachineState::Neighbors()
		{
			return m_neighbors_;
		}
		/// <summary>
		/// Initializes a new instance of the Fun Machine State class.
		/// </summary>
		/// <param name="mName">Name to display for this state</param>
		/// <param name="mDescription">Text to display for this state</param>
		FunMachineState::FunMachineState(std::string name, std::string desc)
		{
			this->m_name_ = name;
			this->m_description_ = desc;
		}
#pragma endregion

#pragma region State overrides
		std::string FunMachineState::GetName()
		{
			return m_name_;
		}

		void FunMachineState::Run()
		{
			// We don't do any fancy stuff, just print out where we are
			std::cout << "\n" + m_description_;
		}
#pragma endregion
	}
}