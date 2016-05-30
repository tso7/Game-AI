#include "abstract_fsm.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>
#include <algorithm>
#include <unordered_map>
using namespace rapidxml;

namespace AbstractFSM
{
	namespace DataDriven
	{
		class SavedMachineState : public State
		{
#pragma region Members
		public:
			enum StateFlags
			{
				None = 0,
				Enter = 1,
				Exit = 2,
			};
			char* flag_names_[3] =
			{
				"None",
				"Enter",
				"Exit"
			};
			std::unordered_map <string, StateFlags> flag_name_map_;
		private:
			StateFlags m_flags_;
			string m_name_;
			string m_description_;			
		public:
			string m_key_;
			vector<string> m_neighbors_;
			vector<string>& Neighbors();
#pragma	endregion

#pragma region Constructors
			SavedMachineState::SavedMachineState(string key, StateFlags flags, string name, string description, string neighbors);
			SavedMachineState(xml_node<> *);
#pragma	endregion

#pragma region Helper Functions
			void InitMap();
			bool IsStartState() const { return (m_flags_ & StateFlags::Enter) == StateFlags::Enter; }
			bool IsExitState() const { return (m_flags_ & StateFlags::Exit) == StateFlags::Exit; }
			string Key() const { return m_key_; }
			string ToLower(string);
			bool IsMyName(string);
#pragma endregion

#pragma region State Overrides
			string GetName();
			void Run();
#pragma endregion

#pragma region XML Members
		    void ReadXml(xml_node<> *);
			void WriteXml(xml_document<> &doc);
#pragma endregion
		};
	}
}