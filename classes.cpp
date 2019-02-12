#include "shi.h"
using namespace shi;
//member functions for smart_dev class
smart_dev::smart_dev ()
{
}

smart_dev::~smart_dev ()
{
}

void smart_dev::add_event (std::string name)
{
	event_types ++;
	events.push_back (event (name));
}

int smart_dev::get_event_types ()
{
	return event_types;
}

void smart_dev::remove_event (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	events.erase (it);
}
void smart_dev::remove_event (int event_type)
{

}

bool smart_dev::is_active (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	return it->event_active;
}

float smart_dev::get_event_value (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	return it->event_value;
}

smart_network::smart_network ()
{

}

smart_network::~smart_network ()
{

}

SYNTAX::SYNTAX ()
{

}

SYNTAX::~SYNTAX ()
{

}

void SYNTAX::time_remove_format (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Time_Format.size (); i ++)
	{
		if (Time_Format.at (i) == expression)
			Time_Format.erase (Time_Format.begin () + i);
	}
}

void SYNTAX::time_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Time_Regex.size (); i ++)
	{
		if (Time_Regex.at (i) == expression)
			Time_Regex.erase (Time_Regex.begin () + i);
	}
}

void SYNTAX::device_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Device_Regex.size (); i ++)
	{
		if (Device_Regex.at (i) == expression)
			Device_Regex.erase (Device_Regex.begin () + i);
	}
}

void SYNTAX::event_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Event_Regex.size (); i ++)
	{
		if (Event_Regex.at (i) == expression)
			Event_Regex.erase (Event_Regex.begin () + i);
	}
}

void SYNTAX::state_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < State_Regex.size (); i ++)
	{
		if (State_Regex.at (i) == expression);
			State_Regex.erase (State_Regex.begin () + i);
	}
}
