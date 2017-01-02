#include "DecoratedBT.h"
#include <iostream>
#include <time.h>

using namespace Decorated;

void BehaviorTree::CompositeNode::AddChildren(initializer_list<BehaviorTree::Node *>
	&& new_children)
{
	for (Node *new_child : new_children)
		AddChild(new_child);
}

template <typename CONTAINER>
void BehaviorTree::CompositeNode::AddChildren(const CONTAINER& newChildren)
{
	for (Node *new_child : new_children)
		AddChild(new_child);
}

vector<BehaviorTree::Node *> BehaviorTree::CompositeNode::ChildrenShuffled() const
{
	vector<Node *> temp = children_;
	random_shuffle(temp.begin(), temp.end());
	return temp;
}

bool BehaviorTree::Selector::Run()
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

bool BehaviorTree::RandomSelector::Run()
{
	// Shuffled order
	for (Node *child : ChildrenShuffled())
	{
		// If one child succeeds, then the entire operation succeeds
		if (child->Run())
			return true;
	}
	// Failure case when all children fail
	return false;
}

bool BehaviorTree::Sequence::Run()
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

bool BehaviorTree::Root::Run()
{
	return GetChild()->Run();
}

bool BehaviorTree::Inverter::Run()
{
	return !GetChild()->Run();
}

bool BehaviorTree::Succeeder::Run()
{
	GetChild()->Run();
	return true;
}

bool BehaviorTree::Failer::Run()
{
	GetChild()->Run();
	return false;
}

bool BehaviorTree::Repeater::Run()
{
	if (num_repeats_ == NOT_FOUND)
	{
		while (true)
			GetChild()->Run();
	}
	else
	{
		for (int i = 0; i < num_repeats_ - 1; i++)
			GetChild()->Run();

		return GetChild()->Run();
	}
}

bool BehaviorTree::RepeatUntilFail::Run()
{
	while (GetChild()->Run());

	return true;
}

template <typename T>
bool BehaviorTree::PushToStack<T>::Run()
{
	this->stack.push(item);
	return true;
}

template <typename T>
bool BehaviorTree::GetStack<T>::Run()
{
	this->stack_ = obtained_stack_;
	if (object_)
		this->stack_.push(object_);
	return true;
}

template <typename T>
bool BehaviorTree::PopFromStack<T>::Run()
{
	if (this->stack_.empty())
		return false;
	item_ = this->stack_.top();
	// template specialization with T = Door needed for this line
	std::cout << "Trying to get through door #" << item_->door_number << "." 
		<< std::endl; 
	this->stack_.pop();
	return true;
}

template <typename T>
bool BehaviorTree::StackIsEmpty<T>::Run()
{
	return this->stack_.empty();
}

template <typename T>
bool BehaviorTree::SetVariable<T>::Run()
{
	variable_ = object_;
	// template specialization with T = Door needed for this line
	std::cout << "The door that was used to get in is door #" <<
		variable_->door_number << "." << std::endl;  
	
	return true;
};

template <typename T>
bool BehaviorTree::IsNull<T>::Run()
{
	return !object_;
}

Building::Building(int num_doors)
{
	Init(num_doors);
}

void Building::Init(int num_doors)
{
	for (int i = 0; i < num_doors; i++)
		doors_.push(new Door{num_doors - i});
}

bool DoorAction::Run()
{
	if (rand() % 100 < success_rate_)
	{
		std::cout << name_ << " succeeded." << endl;
		return true;
	}
	else
	{
		std::cout << name_ << " failed." << endl;
		return false;
	}
}

int Decorated::main(void)
{
	srand(time(nullptr));

	BehaviorTree behavior_tree;
	DataContext data;
	// Building with 5 doors to get in
	Building building(5);

	// Nodes + decorators
	BehaviorTree::Sequence sequence[3];
	BehaviorTree::Selector selector;
	BehaviorTree::Inverter inverter[2];
	BehaviorTree::Succeeder succeeder;
	BehaviorTree::RepeatUntilFail until_fail;

	// Stack related nodes
	BehaviorTree::GetStack<Door> GetDoorStackFromBuilding(data.doors, building.GetDoors());
	BehaviorTree::PopFromStack<Door> PopFromStack(data.current_door, data.doors);
	BehaviorTree::SetVariable<Door> SetVariable(data.used_door, data.current_door);
	BehaviorTree::IsNull<Door> IsNull(data.used_door);

	// Model the action
	DoorAction
		walk_to_door("Walk to door", 99), 
		open_door("Open door", 15), 
		unlock_door("Unlock door", 25), 
		smash_door("Smash door", 50), 
		walk_through_door("Walk through door", 60),
		close_door("Close door", 100);

	behavior_tree.SetRootChild(&sequence[0]);
	sequence[0].AddChildren({&GetDoorStackFromBuilding, &until_fail, &inverter[0]});
	until_fail.SetChild(&sequence[1]);
	inverter[0].SetChild(&IsNull);
	sequence[1].AddChildren({&PopFromStack, &inverter[1]});
	inverter[1].SetChild(&sequence[2]);
	sequence[2].AddChildren({&walk_to_door, &selector, &walk_through_door, &succeeder, &SetVariable});
	selector.AddChildren({&open_door, &unlock_door, &smash_door});
	succeeder.SetChild(&close_door);

	if (behavior_tree.Run())
		std::cout << "Congratulations!  You made it into the building!" << std::endl;
	else
		std::cout << "Sorry.  You have failed to enter the building." << std::endl;
	
	return 0;
}