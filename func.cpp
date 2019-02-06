#include "shi.h"
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

void smart_dev::remove_event (int event_type)
{
	events.erase (events.begin () + event_type);
}

void smart_dev::remove_event (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	events.erase (it);
}

bool smart_dev::is_active (int event_type)
{
	return events.at (event_type).event_active;
}

bool smart_dev::is_active (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	return it->event_active;
}

float smart_dev::get_event_value (int event_type)
{
	return events.at (event_type).event_value;
}

float smart_dev::get_event_value (std::string name)
{
	std::vector<event>::iterator it = events.begin ();
	while (it->event_name != name)
		it ++;
	return it->event_value;
}

//main function to parse the log file
char *Parse_Log_File (std::string log)

{

	std::cout << "Parsing " << filename << std::endl;

	char *Log_file;



	return Log_file;

}

void read_time_segment (smart_dev devlist)
