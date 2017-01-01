#pragma once
#ifndef BT_SIMPLEBT_H_
#define BT_SIMPLEBT_H_
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

#include <list>
using namespace std;

namespace Simple
{
#pragma region Nodes
	// This class will represent each node in the BT
	class Node
	{
	public:
		virtual bool Run() = 0;
	};

	// List of nodes created using Composite Pattern
	class CompositeNode : public Node
	{
	private:
		list<Node *> children_;

	public:
		const list<Node *>& GetChildren() const { return children_; }
		void AddChild(Node *child) { children_.emplace_back(child); }
	};

	// Selector type node - Requires just one child to succeed
	class Selector : public CompositeNode
	{
	public:
		virtual bool Run() override;
	};

	// Sequence type node - Requires all children to succeed
	class Sequence : public CompositeNode
	{
	public:
		virtual bool Run() override;
	};

	// Stick details
	struct StickStatus
	{
		bool is_picked_up;
		int distance;		// in meters
	};
#pragma endregion

#pragma region Tasks
	class CheckIfStickPickedUpTask : public Node
	{
	private:
		StickStatus *status_;

	public:
		CheckIfStickPickedUpTask(StickStatus *status) : status_(status) {}
		virtual bool Run() override;
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
		virtual bool Run() override;
	};

	class PickUpStickTask : public Node
	{
	private:
		StickStatus *status_;

	public:
		PickUpStickTask(StickStatus *status) : status_(status) {}
		virtual bool Run() override;
	};
#pragma endregion

	// Test scenario for this implementation
	int main(void);
}
#endif	// !BT_SIMPLEBT_H_