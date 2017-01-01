#include "SimpleBT.h"
#include <iostream>

using namespace Simple;

# pragma region NodeImplementation
// Selector type node - Requires just one child to succeed
bool Selector::Run()
{
	// Generic selector implementation
	for (Node *child : GetChildren())
	{
		// If one child succeeds, then the entire operation succeeds
		if (child->Run())
			return true;
	}
	// Failure case when all children fail
	return false;
}


// Sequence type node - Requires all children to succeed
bool Sequence::Run()
{
	// Generic sequence implementation
	for (Node *child : GetChildren())
	{
		// If one child fails, then the entire operation fails
		if (!child->Run())
			return false;
	}
	// Success case when all children have succeeded
	return true;
}

#pragma endregion

#pragma region TaskImplementation
bool CheckIfStickPickedUpTask::Run()
{
	if (status_->is_picked_up)
		cout << "The stick has been picked up!" << endl;
	else
		cout << "The stick has not been picked up." << endl;

	// Return status
	return status_->is_picked_up;
}

bool ApproachStickTask::Run()
{
	if (is_obstructed_)
		return false;

	if (status_->distance > 0)
	{
		cout << "The dog is approaching the stick..." << endl;
		status_->distance--;

		if (status_->distance > 1)
			cout << "The dog is now " << status_->distance << " meters away "
			"from the stick." << endl;
		else if (status_->distance == 1)
			cout << "The dog is nearly at the stick!" << endl;
		else
			cout << "The dog has reached the stick!" << endl;
	}

	// Succeeds after performing update
	return true;
}

bool PickUpStickTask::Run()
{
	if (status_->distance > 0)
	{
		cout << "The dog is too far away from the stick to pick it up"
			<< endl;
		return false;
	}

	status_->is_picked_up = true;
	cout << "The stick has been picked up!" << endl;
	return true;
}
#pragma endregion

/* Main function with one test scenario */
int Simple::main(void)
{
	Sequence *root = new Sequence, *sequence1 = new Sequence;
	Selector *selector1 = new Selector;

	// The stick is initially on the ground 5 meters away
	StickStatus *stick_status = new StickStatus{false, 5};

	CheckIfStickPickedUpTask *check_pickup =
		new CheckIfStickPickedUpTask(stick_status);
	ApproachStickTask *approach = new ApproachStickTask(stick_status, false);
	PickUpStickTask *pickup = new PickUpStickTask(stick_status);

	root->AddChild(selector1);

	selector1->AddChild(check_pickup);
	selector1->AddChild(sequence1);

	sequence1->AddChild(approach);
	sequence1->AddChild(pickup);

	while (!root->Run())
	{
		cout << "-----------------------------------------------------" << endl;
	}
	cout << "BT simulation complete!" << endl;

	return 0;
}