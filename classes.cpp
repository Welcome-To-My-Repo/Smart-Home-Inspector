#include "shi.h"
using namespace shi;
//member functions for smart_dev class
LOG_FILE_STATS::LOG_FILE_STATS ()
{

}
LOG_FILE_STATS::~LOG_FILE_STATS ()
{

}
void LOG_FILE_STATS::set_time_pattern (std::string _)
{

}
std::string LOG_FILE_STATS::get_time_pattern ()
{
	return 0;
}
void LOG_FILE_STATS::add_device_stats_node (DEVICE_STATS _)
{
	device_stats.push_back (_);
}
void LOG_FILE_STATS::add_segment_pos (SEGMENT_POS _)
{
	segment_pos.push_back (_);
}
void LOG_FILE_STATS::add_text_buffer_link (GtkTextBuffer *_)
{
	log_files.push_back (_);
}
LOG_FILES::LOG_FILES ()
{

}
LOG_FILES::~LOG_FILES ()
{

}
void LOG_FILES::add_log_file_stats (LOG_FILE_STATS _)
{
	log_file_stats.push_back (_);
}
void LOG_FILES::remove_log_file_stats (int a)
{
	log_file_stats.erase (log_file_stats.begin () + a);
}
void LOG_FILES::set_it_begin ()
{
	it = log_file_stats.begin ();
}
void LOG_FILES::set_it_end ()
{
	it = log_file_stats.end ();
}
void LOG_FILES::move_it_forward ()
{
	it ++;
}
void LOG_FILES::move_it_backward ()
{
	it --;
}
long int LOG_FILES::get_number_of_elements ()
{
	return log_file_stats.size ();
}
void LOG_FILES::move_to (long int pos)
{
	it = log_file_stats.begin ();
	for (int i = 0; i < pos; i ++)
	{
		it ++;
	}
}
bool LOG_FILES::is_time_pattern (std::string y, std::string m, std::string d, std::string h, std::string i, std::string s)
{
	std::vector <LOG_FILE_STATS>::iterator it;
	for (it = log_file_stats.begin (); it < log_file_stats.end () + 1; it ++)
	{
		if (it->year == y)
			if (it->month == m)
				if (it->day == d)
					if (it->hour == h)
						if (it->minute == i)
							if (it->second == s)
								return true;
	}
	return false;
}
long int LOG_FILES::find (std::string y, std::string m, std::string d, std::string h, std::string i, std::string s)
{
	for (long int j = 0; j < log_file_stats.size (); j ++)
	{
		if (log_file_stats.at (j).year == y)
			if (log_file_stats.at (j).month == m)
				if (log_file_stats.at (j).day == d)
					if (log_file_stats.at (j).hour == h)
						if (log_file_stats.at (j).minute == i)
							if (log_file_stats.at (j).second == s)
								return j;
	}
	return -1;
}
LOG_FILE_STATS LOG_FILES::at (long int pos)
{
	return log_file_stats.back ();
}
SYNTAX::SYNTAX ()
{

}

SYNTAX::~SYNTAX ()
{

}

void SYNTAX::year_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Year_Regex.size (); i++)
	{
		if (Year_Regex.at (i) == expression)
		{
			Year_Regex.erase (Year_Regex.begin () + i);
			return;
		}
	}
}

void SYNTAX::month_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Month_Regex.size (); i ++)
	{
		if (Month_Regex.at (i) == expression)
		{
			Month_Regex.erase (Month_Regex.begin () + i);
			return;
		}
	}
}

void SYNTAX::day_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Day_Regex.size (); i ++)
	{
		if (Day_Regex.at (i) == expression)
		{
			Day_Regex.erase (Day_Regex.begin () + i);
			return;
		}
	}
}

void SYNTAX::hour_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Hour_Regex.size (); i ++)
	{
		if (Hour_Regex.at (i) == expression)
		{
			Hour_Regex.erase (Hour_Regex.begin () + i);
			return;
		}
	}
}

void SYNTAX::minute_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Minute_Regex.size (); i ++)
	{
		if (Minute_Regex.at (i) == expression)
		{
			Minute_Regex.erase (Minute_Regex.begin () + i);
			return;
		}
	}
}

void SYNTAX::second_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Second_Regex.size (); i ++)
	{
		if (Second_Regex.at (i) == expression)
		{
			Second_Regex.erase (Second_Regex.begin () + i);
			return;
		}
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
