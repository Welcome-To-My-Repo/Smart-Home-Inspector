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

void SYNTAX::time_remove_ex (std::string expression)
{
	for (int i = 0; i < T.Time_Fomat.size (); i ++)
	{
		if (0 == strcmp (
				gtk_entry_buffer_get_text(
				GTK_ENTRY_BUFFER (T.Time_Format.at (i))),
				expression.c_str ()))
		{
			T.Time_Format.erase (T.Time_Format.begin () + i);
			return;
		}
	}
	for (int i = 0; i < T.Bounding_Ex.size (); i ++)
	{
		if (0 == strcmp (
				gtk_entry_buffer_get_text(
				GTK_ENTRY_BUFFER (T.Bounding_Ex.at (i))),
				expression.c_str ()))
		{
			T.Bounding_Ex.erase (T.Bounding_Ex.begin () + i);
			return;
		}
	}
	for (int i = 0; i < T.Preceding_Ex.size (); i ++)
	{
		if (0 == strcmp (
				gtk_entry_buffer_get_text(
				GTK_ENTRY_BUFFER (T.Preceding_Ex.at (i))),
				expression.c_str ()))
		{
			T.Preceding_Ex.erase (T.Preceding_Ex.begin () + i);
			return;
		}
	}
	for (int i = 0; i < T.Following_Ex.size (); i ++)
	{
		if (0 == strcmp (
				gtk_entry_buffer_get_text(
				GTK_ENTRY_BUFFER (T.Following_Ex.at (i))),
				expression.c_str ()))
		{
			T.Following_Ex.erase (T.Following_Ex.begin () + i);
			return;
		}
	}
}

void SYNTAX::device_remove_ex (std::string expression)
{
	for (int i = 0; i < D.Declarative_Ex.size (); i++)
	{
		
	}
}
