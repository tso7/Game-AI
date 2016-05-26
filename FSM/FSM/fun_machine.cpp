#include "fun_machine.h"
#include <iostream>

namespace AbstractFSM
{
	namespace Fun
	{
		/// <summary>
		/// Initializes a new instance of the FunnerMachine class.
		/// </summary>
		State* FunMachine::CurrentState() const
		{
			State *ptr = m_current_;
			return ptr;
		}

		FunMachine::FunMachine()
		{
			// Create all the fun states in our mini-world
			FunMachineState *entry_hall = new FunMachineState("Grand Entrance", "You are standing in a grand entrance of a castle.\nThere are tables and chairs, but nothing you can interact with.");
			FunMachineState *staircase = new FunMachineState("Grand Staircase", "The staircase is made from beautiful granite.");
			FunMachineState *east_wing = new FunMachineState("East Wing", "This wing is devoted to bedrooms.");
			FunMachineState *west_wing = new FunMachineState("West Wing", "This wing is devoted to business.");
			FunMachineState *bedroom_A = new FunMachineState("Master Suite", "This is the master suite.  What a fancy room!");
			FunMachineState *bedroom_B = new FunMachineState("Prince Bob's Room", "The prince has an extensive library on his wall.\nHe also has more clothes than most males know what to do with.");
			FunMachineState *bedroom_C = new FunMachineState("Princess Alice's Room", "The princess has filled her room with a small computer lab.\nShe spends her days playing games and writing code.");
			FunMachineState *workroom_A = new FunMachineState("Study", "This is the study. It has many books.");
			FunMachineState *workroom_B = new FunMachineState("Bathroom", "Every home needs one.");
			FunMachineState *workroom_C = new FunMachineState("Do Not Enter", "I warned you not to enter.\nYou are in a maze of twisty little passages, all alike.");
			FunMachineState *passage = new FunMachineState("Twisty Passage", "You are in a maze of twisty little passages, all alike");

			// Special case.
			m_exit_ = new FunMachineState("Outside", "You have successfully exited the castle.");

			// Hook up doors.
			entry_hall->Neighbors().push_back(staircase);
			entry_hall->Neighbors().push_back(m_exit_);

			staircase->Neighbors().push_back(east_wing);
			staircase->Neighbors().push_back(west_wing);
			staircase->Neighbors().push_back(entry_hall);

			east_wing->Neighbors().push_back(bedroom_A);
			east_wing->Neighbors().push_back(bedroom_B);
			east_wing->Neighbors().push_back(bedroom_C);
			east_wing->Neighbors().push_back(staircase);

			bedroom_A->Neighbors().push_back(east_wing);
			bedroom_B->Neighbors().push_back(east_wing);
			bedroom_C->Neighbors().push_back(east_wing);

			west_wing->Neighbors().push_back(workroom_A);
			west_wing->Neighbors().push_back(workroom_B);
			west_wing->Neighbors().push_back(workroom_C);

			workroom_A->Neighbors().push_back(west_wing);
			workroom_B->Neighbors().push_back(west_wing);

			// Trap of doom.
			workroom_C->Neighbors().push_back(passage);
			passage->Neighbors().push_back(passage);

			// Add them to the collection
			m_states_.push_back(entry_hall);
			m_states_.push_back(staircase);
			m_states_.push_back(east_wing);
			m_states_.push_back(west_wing);
			m_states_.push_back(bedroom_A);
			m_states_.push_back(bedroom_B);
			m_states_.push_back(bedroom_C);
			m_states_.push_back(workroom_A);
			m_states_.push_back(workroom_B);
			m_states_.push_back(workroom_C);
			m_states_.push_back(passage);
			m_states_.push_back(m_exit_);

			// Finally set the starting point
			m_current_ = entry_hall;
		}
#pragma region StateMachine Overrides
		vector<string> FunMachine::PossibleTransitions()
		{
			vector<string> result;
			for (size_t i = 0, len = m_current_->Neighbors().size(); i < len; ++i)
			{
				result.push_back(m_current_->Neighbors()[i]->GetName());
			}
			return result;
		}
		
		bool FunMachine::Advance(string next_state)
		{
			for ( size_t i = 0, len = m_current_->Neighbors().size(); i < len; ++i )
			{
				if ( next_state == m_current_->Neighbors()[i]->GetName() )
				{
					m_current_ = m_current_->Neighbors()[i];
					return true;
				}
			}
			std::cout << "Invalid state.";
			return false;
		}

		bool FunMachine::IsComplete()
		{
			return m_current_ == m_exit_;
		}
#pragma endregion
	}
}