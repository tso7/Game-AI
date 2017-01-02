#pragma once
#ifndef BT_DECORATEDBT_H_
#define BT_DECORATEDBT_H_

/*
 *	Credit: http://www.gamasutra.com/blogs/ChrisSimpson/20140717/221339/Behavior_trees_for_AI_How_they_work.php
 *	
 *	- A Behavior Tree implementation with the use of decorators.
 *	1. Until Fail = Repeats until a fail condition is encountered.
 *	2. Inverter = Inverts the result of the child.
 *	3. Succeeder = Always returns true, irrespective of child result.
 *	
 *	- Utility nodes:
 *	1. SetVariable(var_name, object)
 *	2. IsNull(object)
 *
 *						   Root
 *							|
 *							|
 *						Sequence
 *							|
 *		    ---------------------------------
 *		  /				    |				  \
 *		 /					|				   \
 *	Get door stack		UNTIL FAIL			INVERTER
 *	from building			|					|
 *							|					|
 *						Sequence			IsNull(used_door)
 *						/		\
 *					   /		 \
 *				Pop door		INVERTER
 *				from stack			|
 *									|
 *								Sequence
 *									|
 *			   ------------------------------------------------
 *			 /			|				|			\			\
 *			/			|				|			 \			 \
 *		Walk to		 Selector		Walk through	SUCCEEDER	SetVariable
 *		(door)	  /		|	  \			door			|		(door, used_door)
 *				 /		|	   \						|
 *			Open	 Unlock		Smash				Close door
 *			door	 door		door
 *
 *	- This code tries to emulate a character entering a building:
 *	1.	First, it retrieves a stack containing every doorway into the building. 
 *	2.	Then it calls the Until Fail repeater node which will continue to 
 *		reprocess its child until its child returns a failure.
 *	3.	That child, a sequence, will first pop a door from the stack, storing it
 *		in the door variable.
 *	4.	If the stack is empty because there are no doors, then this node will fail
 *		and break out of the Until Fail repeater with a success (Until Fail always
 *		succeeds), to continue the parent sequence, where we have an inverted
 *		IsNull check on ‘usedDoor’. This will fail if the usedDoor is null
 *		(which it will be, since it never got chance to set that variable), and
 *		this will cause the entire Behavior to fail.
 *	5.	If the stack does manage to grab a door, it then calls another sequence 
 *		(with an inverter) which will attempt to walk to the door, open it and 
 *		walk through it.
 *	6.	If the NPC fails to get through the door by any means available to him 
 *		(the door is locked, and the NPC is too weak to break it down), then the
 *		selector will fail, and will return fail to the parent, which is the
 *		Inverter, which inverts the failure into a success, which means it
 *		doesn't escape the Until Fail repeater, which in turn repeats and freshly
 *		re-calls its child sequence to pop the next door from the stack and the
 *		NPC will try the next door.
 *	7.	If the NPC succeeds in getting through a door, then it will set that door
 *		in the ‘usedDoor’ variable, at which point the sequence will return success.
 *		This success will be inverted into a failure so we can escape the
 *		Until Fail repeater.
 *	8.	In this circumstance, we then fail in the IsNull check on usedDoor,
 *		since it’s not null. This is inverted into a success, which causes the
 *		entire Behavior to succeed. The parent knows the NPC successfully found
 *		a door and got through it into the building.
 */

#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

namespace Decorated
{
	// Base class to encapsulate the implementation of our behavior tree
	class BehaviorTree
	{
	public:
#pragma region Basic BT Nodes
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
#pragma endregion

#pragma region Decorator nodes
		// Decorator Node - Function is either to transform the result it receives
		// from its child node's status, to terminate the child, or repeat 
		// processing of the child, depending on the type of decorator node.
		class DecoratorNode : public Node
		{
		private:
			// Single child maintained
			Node* child_;
		protected:
			Node* GetChild() const { return child_; }
		public:
			void SetChild(Node* new_child) { child_ = new_child; }
		};

		// Root node - parent that triggers the behavior
		class Root : public DecoratorNode
		{
		public:
			virtual bool Run() override;
			virtual Root* Clone() const override { return new Root(*this); }
		};

		// Inverter node - Inverts the result of the child. A child fails and
		// it will return success to its parent, or a child succeeds and it will
		// return failure to the parent.
		class Inverter : public DecoratorNode
		{
		public:
			virtual bool Run() override;
			virtual Inverter* Clone() const override { return new Inverter(*this); }
		};

		// Succeeder node - A succeeder will always return success, irrespective
		// of what the child node actually returned. These are useful in cases where
		// you want to process a branch of a tree where a failure is expected or
		// anticipated, but you don’t want to abandon processing of a sequence 
		// that branch sits on.
		class Succeeder : public DecoratorNode
		{
		public:
			virtual bool Run() override;
			virtual Succeeder* Clone() const override { return new Succeeder(*this); }
		};

		// Failer node - The opposite of a Succeeder, always returning fail. 
		// Note that this can be achieved also by using an Inverter and setting
		// its child to a Succeeder. Can be used to check selectors.
		class Failer : public DecoratorNode
		{
		public:
			virtual bool Run() override;
			virtual Failer* Clone() const override { return new Failer(*this); }
		};

		// Repeater node - A repeater will reprocess its child node each time 
		// its child returns a result. These are often used at the very base of 
		// the tree, to make the tree to run continuously. Repeaters may 
		// optionally run their children a set number of times before returning 
		// to their parent.
		class Repeater : public DecoratorNode
		{
		private:
			int num_repeats_;
			static const int NOT_FOUND = -1;
		public:
			// By default, never end
			Repeater(int num = NOT_FOUND) : num_repeats_(num) {}
			virtual bool Run() override;
			virtual Repeater* Clone() const override { return new Repeater(*this); }
		};

		// RepeatUntilFail node - Like a repeater, these decorators will continue
		// to reprocess their child. That is until the child finally returns a 
		// failure, at which point the repeater will return success to its parent.
		class RepeatUntilFail : public DecoratorNode
		{
		public:
			virtual bool Run() override;
			virtual RepeatUntilFail* Clone() const override { return new RepeatUntilFail(*this); }
		};
#pragma endregion

#pragma region Utility Nodes
		// Basic Stack node
		template <typename T>
		class StackNode : public Node 
		{
		protected:
			stack<T*>& stack_;  // Must be reference to a stack to work.
			StackNode(stack<T*>& s) : stack_(s) {}
		};

		// Specific type of leaf node (hence has no child).
		template <typename T>
		class PushToStack : public StackNode<T> 
		{  
		private:
			T*& item_;
		public:
			PushToStack(T*& t, stack<T*>& s) : StackNode<T>(s), item_(t) {}
		private:
			virtual bool Run() override;
			virtual PushToStack* Clone() const override { return new PushToStack(*this); }
		};

		// Leaf Node - Retrieve a stack
		template <typename T>
		class GetStack : public StackNode<T> 
		{
		private:
			const stack<T*>& obtained_stack_;
			T* object_;
		public:
			GetStack(stack<T*>& s, const stack<T*>& o, T* t = nullptr) : 
				StackNode<T>(s), 
				obtained_stack_(o),
				object_(t) {}
		private:
			virtual bool Run() override;
			virtual GetStack* Clone() const override { return new GetStack(*this); }
		};

		// Leaf Node - Pop an object from a stack
		template <typename T>
		class PopFromStack : public StackNode<T>
		{
		private:
			T*& item_;
		public:
			PopFromStack(T*& t, stack<T*>& s) : StackNode<T>(s), item_(t) {}
		private:
			virtual bool Run() override;
			virtual PopFromStack* Clone() const override { return new PopFromStack(*this); }
		};

		// Leaf node - Check if stack is empty
		template <typename T>
		class StackIsEmpty : public StackNode<T> 
		{ 
		public:
			StackIsEmpty(stack<T*>& s) : StackNode<T>(s) {}
		private:
			virtual bool Run() override;
			virtual StackIsEmpty* Clone() const override { return new StackIsEmpty(*this); }
		};

		// Set an object to given value
		template <typename T>
		class SetVariable : public BehaviorTree::Node 
		{  
		private:
			T *&variable_, *&object_;  // Must use reference to pointer to work correctly.
		public:
			SetVariable(T*& t, T*& obj) : variable_(t), object_(obj) {}
			virtual bool Run() override;
			virtual SetVariable* Clone() const override { return new SetVariable(*this); }
		};

		// Check if object is null/empty
		template <typename T>
		class IsNull : public BehaviorTree::Node
		{ 
		private:
			T*& object_;  // Must use reference to pointer to work correctly.
		public:
			IsNull(T*& t) : object_(t) {}
			virtual bool Run() override;
			virtual IsNull* Clone() const override { return new IsNull(*this); }
		};
#pragma endregion
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

#pragma region Example specific containers
	// Doors identified by door number
	struct Door
	{
		int door_number;
	};

	// Acts as a storage for arbitrary variables that are interpreted and altered by the nodes.
	struct DataContext 
	{ 
		stack<Door*> doors;
		Door* current_door;
		Door* used_door = nullptr;
	};

	// Building class that provides stack of available doors
	class Building
	{
	private:
		stack<Door *> doors_;
	public:
		Building(int num_doors);
		const stack<Door *>& GetDoors() const { return doors_; }
	private:
		void Init(int num_doors);
	};

	// Action to be performed
	class DoorAction : public BehaviorTree::Node 
	{
	private:
		string name_;
		int success_rate_;	// Probability of success (0-100%)
	public:
		DoorAction(const string name, int rate) : 
			name_(name), 
			success_rate_(rate) {}
	private:
		virtual bool Run() override;
		virtual DoorAction* Clone() const override { return new DoorAction(*this); }
	};
#pragma endregion

	// Test scenario for this implementation
	int main(void);
}

#endif // !BT_DECORATEDBT_H_