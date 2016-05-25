#include "basic_fsm.h"
#include "boring_machine.h"
#include <iostream>
#include <vector>
using namespace std;

int main (void)
{
#pragma region BasicFSM
	//cout << "\nCreating basic state machine";
	//BasicFSM::StateMachine *machine = new BasicFSM::StateMachine();

	//cout << "\nRunning state machine!";

	//while ( machine->IsDone() == false )
	//{
	//	cout << "\nCurrently in " + machine->GetStateName();
	//	cout << machine->UpdateState();
	//	machine->NextState();
	//	cout << "\nAdvanced to " + machine->GetStateName();
	//}
#pragma endregion

#pragma region AbstractFSM
	// First we need to create the state machine.
	// Note that I'm using the abstract IStateMachine instead of a concrete class.
	AbstractFSM::Boring::BoringMachine machine;

	// We have a machine, now run it.
	while ( !machine.IsComplete() )
	{
		// Print out our current state
		cout << "\nCurrently in " + machine.CurrentState()->GetName();
		machine.CurrentState()->Run();

		// Print out our possible transitions
		cout<< "\nAvailable choices are:";
		vector<string> transitions = machine.PossibleTransitions();
		for(size_t i=0, len = transitions.size(); i < len; ++i)
		{
			cout << " " + transitions[i];
		}

		// Request a transition from the user
		cout << "\nWhat do you want to do?\n";
		string next_state;
		cin >> next_state;
		machine.Advance(next_state);
	}

	// And we're done!
	// Run our final node as a special case since the above loop won't do it.
	cout << "\nCurrently in " + machine.CurrentState()->GetName();
	machine.CurrentState()->Run();
#pragma endregion
}