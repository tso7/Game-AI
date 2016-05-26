#include "abstract_fsm.h"
#include <map>
#include <vector>

namespace AbstractFSM
{
	namespace Fun
	{
		class FunMachineState : public State
		{
#pragma region Members
		private:
			string m_name_;
			string m_description_;
#pragma endregion
		public:
			vector<FunMachineState*> m_neighbors_;
			vector<FunMachineState*>& Neighbors();
			FunMachineState(string, string);

#pragma region State overrides
			string GetName() override;
			void Run() override;
#pragma endregion
		};
	}
}