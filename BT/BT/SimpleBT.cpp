/*
 *	- The most basic implementation of a Behavior Tree.
 *	- The code will model a dog who is trying to pick up a stick thrown some
 *	distance away.
 *               
 *
 *						Root
 *						 |
 *						 |
 *			Selector (Wait for one to succeed)  
 *				   /				\
 *				  /					 \
 *				 /					  \
 *			Stick picked up?		Sequence (All to succeed)
 *			(Complete when                /           \
 *			 stick is picked up)         /             \
 *			                            /               \
 *							   Approach stick      Pick up the stick
 *							  (Move closer until
 *								in range of stick)
 */

#include <iostream>
#include <list>

using namespace std;

// This class will represent each node in the BT
class Node
{
public:
	virtual bool run() = 0;
};

// List of nodes created using Composite Pattern
class CompositeNode : public Node
{
private:
	list<Node *> children_;
	
public:
	const list<Node *>& GetChildren() const
	{
		return children_;
	}

	void AddChild (Node *child)
	{
		children_.emplace_back(child);
	}
};

// Selector type node - Requires just one child to succeed
class Selector : public CompositeNode
{
public:
	virtual bool run() override
	{
		// Generic selector implementation
		for (Node *child : GetChildren())
		{
			// If one child succeeds, then the entire operation succeeds
			if (child->run())
				return true;
		}
		// Failure case when all children fail
		return false;
	}
};

// Sequence type node - Requires all children to succeed
class Sequence : public CompositeNode
{
public:
	virtual bool run() override
	{
		// Generic sequence implementation
		for (Node *child : GetChildren())
		{
			// If one child fails, then the entire operation fails
			if (!child->run())
				return false;
		}
		// Success case when all children have succeeded
		return true;
	}
};

// Stick details
struct StickStatus
{
	bool is_picked_up;	
	int distance;		// in meters
};

/* ############################ TASK DEFINITIONS ############################ */ 

class CheckIfStickPickedUpTask : public Node
{
private:
	StickStatus *status_;
	
public:
	CheckIfStickPickedUpTask(StickStatus *status) : status_(status) {}
	
	virtual bool run() override
	{
		if (status_->is_picked_up)
			cout << "The stick has been picked up!" << endl;
		else
			cout << "The stick has not been picked up." << endl;

		// Return status
		return status_->is_picked_up;
	}
};

class ApproachStickTask : public Node
{
private:
	StickStatus *status_;
	bool is_obstructed_;

public:
	ApproachStickTask(StickStatus *status, bool is_obstructed) 
		: status_(status)
		, is_obstructed_(is_obstructed)
	{}

	virtual bool run() override
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
};

class PickUpStickTask : public Node
{
private:
	StickStatus *status_;

public:
	PickUpStickTask (StickStatus *status) : status_(status) {}
	
	virtual bool run() override
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
};

/* Main function with one test scenario */
int main(void)
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

	while (!root->run())
	{
		cout << "-----------------------------------------------------" << endl;
	}
	cout << "BT simulation complete!" << endl;
}