#include "abstract_fsm.h"
#include <map>

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
			SameOldStates m_state_ = SameOldStates::Enter;
			std::map <SameOldStates, string> state_name_map_;
#pragma endregion

#pragma region State overrides
		public:
			BoringMachineState()
			{
				InitMap();
			}
			string GetName() override;
			void Run() override;
#pragma endregion

#pragma region Helper functions
			void InitMap();
			bool IsComplete();
			vector<string> ListTransitions();
			bool Advance();
#pragma endregion
		};

	}
}