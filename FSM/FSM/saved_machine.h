// The actual machine that handles the different saved machine state
#include "saved_machine_state.h"

namespace AbstractFSM
{
	namespace DataDriven
	{
		class SavedMachine : public StateMachine
		{
		private:
#pragma region Members
			// List of states that exist within the machine
			std::vector<SavedMachineState*> m_states_;
			// The current machine state
			SavedMachineState *m_current_;
			// Create map if XML does not exist
			void GenerateDefaultMap();
		public:
			// Default constructor
			SavedMachine();
#pragma endregion

#pragma region Helper Functions
			// Write into the XML file
			void ExportToXML();
			// Read the XML file
			void ImportFromXML();
			// Populate the states based on the DOM tree
			void ReadXml(xml_document<> &doc);
			// Convert the existing state data into a DOM tree
			void WriteXml(xml_document<> &doc);
#pragma region Helper Functions

#pragma region StateMachine Overrides
			// Accessor to look at the current state
			State* CurrentState() const;
			// List of all possible transitions we can make from this current state
			std::vector<std::string> PossibleTransitions();
			// Advance to the specified machine state
			bool Advance(std::string);
			// Check if machine has reached exit node
			bool IsComplete();
#pragma endregion
		};
	}
}