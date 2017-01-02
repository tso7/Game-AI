#pragma once
#ifndef BT_DETAILEDBT_H_
#define BT_DETAILEDBT_H_
/*
 *	- A more complex implementation of a Behavior Tree.
 *	- I just finished Titanfall 2, so this code will try to model a Titan in
 *	  auto mode, trying to destroy a target.
 *	- It first attempts to destroy the target by moving into melee range and
 *	  trying different melee attacks.
 *	- If those fail, it attempts to use weapons.
 *	- All tasks have been simplified to simple pass / fail scenarios.
 *
 *									Root
 *									 |
 *									 |
 *								  Selector
 *									 |
 *							 -----------------------------------------------
 *							|												|
 *						Sequence (Melee attack)								|
 *							|												|
 *		    -----------------------------------------------					|
 *		  /				    |				|				\				|
 *		 /					|				|				 \				|
 *		/					|				|				  \				|
 *	Move to				Selector		Confirm 		Update player		|
 *	 target					|			target kill							|
 *							|												|
 *			   ------------------------										|
 *			 /				|			\									|
 *			/				|			 \									|
 *		Walk over		Sequence		Sword attack						|
 *						/	   \											|
 *					   /		\											|
 *				Focus target	Melee smash									|
 *																			|
 *																			|
 *							 -----------------------------------------------
 *							|
 *						Sequence (Weapons)
 *							|
 *		    -----------------------------------------------
 *		  /				    |				|				\
 *		 /					|				|				 \
 *		/					|				|				  \
 *	Move to 			Selector		Confirm 		Update player
 *	attack range			|			target kill
 *							|
 *			   ------------------------
 *			 /				|			\
 *			/				|			 \
 *		Machine gun		Sequence		Special core attack
 *						/	   \
 *					   /		\
 *				Acquire lock	Fire missiles
 */

#include <vector>
#include <algorithm>
#include <string>
using namespace std;

namespace Detailed
{
#pragma region BT
	// Base class to encapsulate the implementation of our behavior tree
	class BehaviorTree
	{
	public:
		// Class to represent each node in the tree
		class Node
		{
		public:
			// Clone implmentation for deep copying
			virtual ~Node() {}
			virtual Node* Clone() const = 0;

			// The Run() method to be overriden
			virtual bool Run() = 0;
		};

		// Composite Pattern for the nodes
		class CompositeNode : public Node
		{
		private:
			vector<Node *> children_;

		public:
			const vector<Node *>& GetChildren() const { return children_; }
			void AddChild(Node *child) { children_.emplace_back(child); }

			void AddChildren(initializer_list<Node *>&& new_children);

			template <typename CONTAINER>
			void AddChildren(const CONTAINER& newChildren);

		protected:
			vector<Node *> ChildrenShuffled() const;
		};

		// Selector type node - Requires just one child to succeed
		class Selector : public CompositeNode
		{
		public:
			virtual bool Run() override;
			virtual Selector* Clone() const override { return new Selector(*this); }
		};

		// Selector type node - Variant where the child chosen is randomized
		class RandomSelector : public CompositeNode
		{
		public:
			virtual bool Run() override;
			virtual RandomSelector* Clone() const override { return new RandomSelector(*this); }
		};

		// Sequence type node - Requires all children to succeed
		class Sequence : public CompositeNode
		{
		public:
			virtual bool Run() override;
			virtual Sequence* Clone() const override { return new Sequence(*this); }
		};

		// Root node
		class Root : public Node
		{
		private:
			Node* child_;
		public:
			void SetChild(Node* new_child) { child_ = new_child; }
			virtual bool Run() override { return child_->Run(); }
			virtual Root* Clone() const override { return new Root(*this); }
		};

	private:
		Root *root_;

	public:
		BehaviorTree() : root_(new Root) {}
		BehaviorTree(const BehaviorTree& rhs) : root_(rhs.root_->Clone()) {}
		BehaviorTree& operator = (const BehaviorTree& rhs)
		{
			this->root_ = rhs.root_->Clone();
			return *this;
		}

		void SetRootChild(Node *root_child) const { root_->SetChild(root_child); }
		bool Run() const { return root_->Run(); }
	};
#pragma endregion

#pragma region Action
	// Template for the overall goal to be performed
	class Action : public BehaviorTree::Node
	{
	private:
		string name_;
		int success_rate_;		// Probability of success (0-100%)

	public:
		Action (const string name, int rate) :
			name_(name),
			success_rate_(rate)
		{}
		virtual Action* Clone() const override { return new Action(*this); }

	private:
		virtual bool Run() override;
	};
#pragma endregion

	// Test scenario for this implementation
	int main(void);
}
#endif // !BT_DETAILEDBT_H_