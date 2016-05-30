#include "saved_machine_state.h"
#include <iostream>
#include <sstream>
#include <cstring>
using namespace AbstractFSM::DataDriven;

void SavedMachineState::InitMap()
{
	flag_name_map_["None"] = StateFlags::None;
	flag_name_map_["Enter"] = StateFlags::Enter;
	flag_name_map_["Exit"] = StateFlags::Exit;
}

vector<string>& SavedMachineState::Neighbors()
{
	return m_neighbors_;
}

/// <summary>
/// Manual constructor for default maze
/// </summary>
/// <param name="uniqueKey">unique name for the stateFlags</param>
/// <param name="flags">flags to indicate enter nodes and exit nodes</param>
/// <param name="name">name to show to the user</param>
/// <param name="description">text to show for the description</param>
/// <param name="neighbors">unique keys for neighboring rooms, seperated by commas and not spaces</param>
SavedMachineState::SavedMachineState(std::string unique_key, StateFlags flags, std::string name, std::string description, std::string neighbors)
{
	InitMap();
	m_key_ = unique_key;
	m_flags_ = flags;
	m_name_ = name;
	m_description_ = description;
	stringstream string_stream (neighbors);
	std::string sub_string;
	while (getline(string_stream, sub_string, ',')) 
	{
		m_neighbors_.push_back(sub_string);
	}
}
/// <summary>
/// Constructor to create an object from a save file
/// </summary>
/// <param name="reader">xml stream to read from</param>
SavedMachineState::SavedMachineState(xml_node<> * room_node)
{
	InitMap();
	ReadXml(room_node);
}

std::string SavedMachineState::ToLower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

bool SavedMachineState::IsMyName(string name_to_test)
{
	//TODO: Add shortcuts to names.  For example, allow "Great Hall", "Hall", etc.
	if ( ToLower(name_to_test) == ToLower(m_name_) )
		return true;
	if ( ToLower(name_to_test) == ToLower(m_key_) )
		return true;
	return false;
}
string SavedMachineState::GetName()
{
	return m_name_;
}

void SavedMachineState::Run()
{
	// We don't do any fancy stuff, just print out where we are
	std::cout << "\n" + m_description_;
}

void SavedMachineState::ReadXml(xml_node<> * room_node)
{
	m_key_ = room_node->first_node("UniqueName")->value();
	m_flags_ = flag_name_map_[room_node->first_node("Flags")->value()];
	m_name_ = room_node->first_node("VisibleName")->value();
	m_description_ = room_node->first_node("Description")->value();
	stringstream neighbors_stream (room_node->first_node("Neighbors")->value());
	string sub_string;
	while ( getline(neighbors_stream, sub_string, ',') )
	{
		m_neighbors_.push_back(sub_string);
	}
}

void SavedMachineState::WriteXml(xml_document<> &doc)
{
	xml_node<> *root = doc.first_node("SavedMachine");
	xml_node<> *room_node = doc.allocate_node(node_element, "Room");
	xml_node<> *child_node = doc.allocate_node(node_element, "UniqueName", m_key_.c_str());
	room_node->append_node(child_node);
	child_node = doc.allocate_node(node_element, "Flags", flag_names_[m_flags_]);
	room_node->append_node(child_node);
	child_node = doc.allocate_node(node_element, "VisibleName", m_name_.c_str());
	room_node->append_node(child_node);
	child_node = doc.allocate_node(node_element, "Description", m_description_.c_str());
	room_node->append_node(child_node);
	std::string neighbor_str;
	for ( std::vector<std::string>::const_iterator i = m_neighbors_.begin(); i != m_neighbors_.end(); ++i )
	{
		neighbor_str += *i;
		if ( i !=  m_neighbors_.end() - 1)
			neighbor_str += ',';
	}
	char *node_name = doc.allocate_string(neighbor_str.c_str());
	child_node = doc.allocate_node(node_element, "Neighbors", node_name);
	room_node->append_node(child_node);
	root->append_node(room_node);
}