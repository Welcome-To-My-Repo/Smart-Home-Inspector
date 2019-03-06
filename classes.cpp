#include "shi.h"
using namespace shi;
//member functions for smart_dev class
LOG_FILE_STATS::LOG_FILE_STATS ()
{

}
LOG_FILE_STATS::~LOG_FILE_STATS
{

}
void LOG_FILE_STATS::set_time (std::string _)
{

}
void LOG_FILE_STATS::add_device_stats_node (DEVICE_STATS _)
{

}
void LOG_FILE_STATS::add_segment_pos (SEGMENT_POS _)
{

}
void LOG_FILE_STATS::add_text_buffer_link (GtkTextBuffer _)
{

}
LOG_FILES::LOG_FILES ()
{

}
LOG_FILES::~LOG_FILES ()
{

}
void LOG_FILES::add_log_file_stats (LOG_FILE_STATS _)
{

}
void LOG_FILES::remove_log_file_stats (int a)
{

}
void LOG_FILES::set_it_begin ()
{

}
void LOG_FILES::set_it_end ()
{

}
void LOG_FILES::move_it_forward ()
{

}
void LOG_FILES::move_it_backward ()
{

}
long int LOG_FILES::get_number_of_elements ()
{

}
void LOG_FILES::move_to (long int pos)
{

}
bool LOG_FILES::is_time_pattern (std::string pattern)
{

}
long int LOG_FILES::find (std::string pattern)
{

}
LOG_FILE_STATS LOG_FILE_STATS::at (long int pos)
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

TIME::TIME ()
{

}

TIME::~TIME ()
{

}


bool TIME::operator = (TIME a)
{
	return true;
}

void TIME::operator ++ (int)
{

}
void TIME::operator -- (int)
{

}
