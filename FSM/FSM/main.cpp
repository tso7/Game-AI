#include "basic_fsm.h"
#include "boring_machine.h"
#include "fun_machine.h"
#include "saved_machine.h"
using namespace std;

AbstractFSM::StateMachine* GetMachine()
{
	AbstractFSM::StateMachine* machine = NULL;
	while ( !machine )
	{
		cout << " 1 - Boring state machine" << endl;
		cout << " 2 - Fun state machine" << endl;
		cout << " 3 - Saved state machine" << endl;
		cout << "\nChoose your state machine: ";
		int key;
		cin >> key;
		switch ( key )
		{
		case 1:
			machine = new AbstractFSM::Boring::BoringMachine;
			break;
		case 2:
			machine = new AbstractFSM::Fun::FunMachine;
			break;
		case 3:
			machine = new AbstractFSM::DataDriven::SavedMachine;
			break;
		default:
			cout << "\nUnknown State Machine!\n";
			break;
		}
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	}
	return machine;
}

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

#pragma region BoringFSM
	//// First we need to create the state machine.
	//// Note that I'm using the abstract IStateMachine instead of a concrete class.
	//AbstractFSM::Boring::BoringMachine machine;

	//// We have a machine, now run it.
	//while ( !machine.IsComplete() )
	//{
	//	// Print out our current state
	//	cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//	machine.CurrentState()->Run();

	//	// Print out our possible transitions
	//	cout<< "\nAvailable choices are:";
	//	vector<string> transitions = machine.PossibleTransitions();
	//	for(size_t i=0, len = transitions.size(); i < len; ++i)
	//	{
	//		cout << " " + transitions[i];
	//	}

	//	// Request a transition from the user
	//	cout << "\nWhat do you want to do?\n";
	//	string next_state;
	//	cin >> next_state;
	//	machine.Advance(next_state);
	//}

	//// And we're done!
	//// Run our final node as a special case since the above loop won't do it.
	//cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//machine.CurrentState()->Run();
#pragma endregion

#pragma region FunFSM
	//// First we need to create the state machine.
	//// Note that I'm using the abstract IStateMachine instead of a concrete class.
	//AbstractFSM::Fun::FunMachine machine;

	//// We have a machine, now run it.
	//while ( !machine.IsComplete() )
	//{
	//	// Print out our current state
	//	cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//	machine.CurrentState()->Run();

	//	// Print out our possible transitions
	//	cout << "\nAvailable choices are:";
	//	vector<string> transitions = machine.PossibleTransitions();
	//	for ( size_t i = 0, len = transitions.size(); i < len; ++i )
	//	{
	//		cout << "\n" + transitions[i];
	//	}

	//	// Request a transition from the user
	//	cout << "\nWhat do you want to do?\n";
	//	string next_state;
	//	getline(cin,next_state);
	//	machine.Advance(next_state);
	//}

	//// And we're done!
	//// Run our final node as a special case since the above loop won't do it.
	//cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//machine.CurrentState()->Run();
#pragma endregion

#pragma region SavedFSM
	//// First we need to create the state machine.
	//// Note that I'm using the abstract IStateMachine instead of a concrete class.
	//AbstractFSM::DataDriven::SavedMachine machine;

	//// We have a machine, now run it.
	//while ( !machine.IsComplete() )
	//{
	//	// Print out our current state
	//	cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//	machine.CurrentState()->Run();

	//	// Print out our possible transitions
	//	cout << "\nAvailable choices are:";
	//	vector<string> transitions = machine.PossibleTransitions();
	//	for ( size_t i = 0, len = transitions.size(); i < len; ++i )
	//	{
	//		cout << "\n" + transitions[i];
	//	}

	//	// Request a transition from the user
	//	cout << "\nWhat do you want to do?\n";
	//	string next_state;
	//	getline(cin, next_state);
	//	machine.Advance(next_state);
	//}

	//// And we're done!
	//// Run our final node as a special case since the above loop won't do it.
	//cout << "\nCurrently in " + machine.CurrentState()->GetName();
	//machine.CurrentState()->Run();
#pragma endregion

#pragma region AbstractFSM
	// First we need to create the state machine.
	// Note that I'm using the abstract IStateMachine instead of a concrete class.
	AbstractFSM::StateMachine* machine = GetMachine();

	// We have a machine, now run it.
	while ( !machine->IsComplete() )
	{
		// Print out our current state
		cout << "\nCurrently in " + machine->CurrentState()->GetName();
		machine->CurrentState()->Run();

		// Print out our possible transitions
		cout << "\nAvailable choices are:";
		vector<string> transitions = machine->PossibleTransitions();
		for ( size_t i = 0, len = transitions.size(); i < len; ++i )
		{
			cout << "\n" + transitions[i];
		}

		// Request a transition from the user
		cout << "\nWhat do you want to do?\n";
		string next_state;
		getline(cin, next_state);
		machine->Advance(next_state);
	}

	// And we're done!
	// Run our final node as a special case since the above loop won't do it.
	cout << "\nCurrently in " + machine->CurrentState()->GetName();
	machine->CurrentState()->Run();	
	delete machine;
#pragma endregion
}