#include "basicFSM.h"
#include <iostream>
using namespace std;

int main (void)
{
	cout << "\nCreating basic state machine";
	BasicFSM::StateMachine *machine = new BasicFSM::StateMachine();

	cout << "\nRunning state machine!";

	while ( machine->IsDone() == false )
	{
		cout << "\nCurrently in " + machine->GetStateName();
		cout << machine->UpdateState();
		machine->NextState();
		cout << "\nAdvanced to " + machine->GetStateName();
	}
}