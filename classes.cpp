#include "shi.h"
using namespace shi;
//member functions for smart_dev class
void LOG_FILE_DATA::year_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::month_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::day_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::hour_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::minute_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::second_remove_ex (GtkEntryBuffer *expression)
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

void LOG_FILE_DATA::device_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Device_Regex.size (); i ++)
	{
		if (Device_Regex.at (i) == expression)
			Device_Regex.erase (Device_Regex.begin () + i);
	}
}

void LOG_FILE_DATA::event_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < Event_Regex.size (); i ++)
	{
		if (Event_Regex.at (i) == expression)
			Event_Regex.erase (Event_Regex.begin () + i);
	}
}

void LOG_FILE_DATA::state_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < State_Regex.size (); i ++)
	{
		if (State_Regex.at (i) == expression);
			State_Regex.erase (State_Regex.begin () + i);
	}
}
