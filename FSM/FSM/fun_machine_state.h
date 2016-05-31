// Fun State Machine that creates states for the layout of a house.
// User decides which room they want to enter based on the possible
// connections between the different sections of the house.
#include "abstract_fsm.h"

namespace AbstractFSM
{
	namespace Fun
	{
		class FunMachineState : public State
		{
#pragma region Members
		private:
			// Name of the machine state
			std::string m_name_;
			// Description of the state
			std::string m_description_;
			// List of possible neighbors
			std::vector<FunMachineState*> m_neighbors_;
		public:
			// Constructor to create state based on name and description
			FunMachineState(std::string, std::string);
			// Fetch the list of neighbors
			std::vector<FunMachineState*>& Neighbors();			
#pragma endregion

#pragma region State overrides
			std::string GetName() override;
			void Run() override;
#pragma endregion
		};
	}
}