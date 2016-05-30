#include "saved_machine_state.h"


namespace AbstractFSM
{
	namespace DataDriven
	{
		class SavedMachine : public StateMachine
		{
		private:
#pragma region Members
			vector<SavedMachineState*> m_states_;
			SavedMachineState *m_current_;
			void GenerateDefaultMap();
#pragma endregion
		public:
			SavedMachine();
#pragma region Helper Functions
			void ExportToXML();
			void ImportFromXML();
			void ReadXml(xml_document<> &doc);
			void WriteXml(xml_document<> &doc);
#pragma region Helper Functions

#pragma region StateMachine Overrides
			State* CurrentState() const;
			vector<string> PossibleTransitions();
			bool Advance(string);		
			bool IsComplete();
#pragma endregion
		};
	}
}