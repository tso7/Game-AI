#include "DetailedBT.h"
#include <iostream>
#include <time.h>

using namespace Detailed;

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

bool Action::Run()
{
	if (rand() % 100 < success_rate_)
	{
		cout << name_ << " succeeded." << endl;
		return true;
	}
	else
	{
		cout << name_ << " failed." << endl;
		return false;
	}
}

/* Main function with test scenario */
int Detailed::main(void)
{
	srand(time(nullptr));
	BehaviorTree behavior_tree;
	BehaviorTree::Selector selector[3];
	BehaviorTree::Sequence sequence[4];

	Action
		// Melee sequence actions
		move_to_target("Move to target", 99),
		walk_over("Stomp target", 15),
		focus_target("Target focus", 25),
		melee_attack("Melee attack", 90),
		sword_attack("Sword attack", 75),
		melee_kill("Confirm melee kill", 60),
		report_melee("Update player about melee kill", 100),

		// Weapon sequence actions
		move_to_attack_range("Move into attack range", 99),
		machine_gun("Attack with machine gun", 60),
		acquire_lock("Acquire lock on target", 65),
		fire_missiles("Fire missiles", 85),
		core_attack("Special core attack", 95),
		weapon_kill("Confirm weapon kill", 85),
		report_weapon("Update player about weapon kill", 100);

	// Adding nodes as per tree described in the header file
	// Root node
	behavior_tree.SetRootChild(&selector[0]);
	selector[0].AddChildren({&sequence[0], &sequence[2]});
	
	// Melee sequence
	sequence[0].AddChildren({&move_to_target, &selector[1], &melee_kill, &report_melee});
	selector[1].AddChildren({&walk_over, &sequence[1], &sword_attack});
	sequence[1].AddChildren({&focus_target, &melee_attack});

	// Weapon sequence
	sequence[2].AddChildren({&move_to_attack_range, &selector[2], &weapon_kill, &report_weapon});
	selector[2].AddChildren({&machine_gun, &sequence[3], &core_attack});
	sequence[3].AddChildren({&acquire_lock, &fire_missiles});

	if (behavior_tree.Run())
		cout << "Target eliminated!" << endl;
	else
		cout << "Target not eliminated. Initiating self destruct sequence..." 
		<< endl;

	return 0;
}