#include "shi.h"
LOG_FILE_DATA::LOG_FILE_DATA ()
{

}
LOG_FILE_DATA::~LOG_FILE_DATA ()
{

}
LOG_FILE_DATA::LOG_FILE_DATA (GtkTextBuffer *_)
{
	Text_File = _;
}
void LOG_FILE_DATA::add_text_file (Gtk_Text_Buffer *_)
{
	Text_File = _;
}
GtkTextBuffer *LOG_FILE_DATA::get_text_file ()
{
	return Text_File;
}
GtkEntryBuffer *LOG_FILE_DATA::add_year_regex ()
{
	syntax.Year_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
	return syntax.Year_Regex.back ();
}
GtkEntryBuffer *LOG_FILE_DATA::add_month_regex ()
{
	syntax.Month_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
	return syntax.Month_Regex.back ();
}
GtkEntryBuffer *LOG_FILE_DATA::add_day_regex ()
{
	syntax.Day_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
	return syntax.Day_Regex.back ();
}
GtkEntryBuffer *LOG_FILE_DATA::add_hour_regex ()
{
	syntax.Hour_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
	return syntax.Hour_Regex.back ();
}
GtkEntryBuffer *LOG_FILE_DATA::add_minute_regex ()
{
	syntax.Minute_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
	return syntax.Minute_Regex.back ();
}
GtkEntryBuffer *LOG_FILE_DATA::add_second_regex ()
{
	syntax.Second_Regex.push_back (gtk_entry_buffer_new(NULL, -1));
	return syntax.Second_Regex.back ();
}
void LOG_FILE_DATA::year_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Year_Regex.size (); i++)
	{
		if (syntax.Year_Regex.at (i) == expression)
		{
			syntax.Year_Regex.erase (Year_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::month_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Month_Regex.size (); i ++)
	{
		if (syntax.Month_Regex.at (i) == expression)
		{
			syntax.Month_Regex.erase (Month_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::day_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Day_Regex.size (); i ++)
	{
		if (syntax.Day_Regex.at (i) == expression)
		{
			syntax.Day_Regex.erase (Day_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::hour_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Hour_Regex.size (); i ++)
	{
		if (syntax.Hour_Regex.at (i) == expression)
		{
			syntax.Hour_Regex.erase (Hour_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::minute_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Minute_Regex.size (); i ++)
	{
		if (syntax.Minute_Regex.at (i) == expression)
		{
			syntax.Minute_Regex.erase (Minute_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::second_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Second_Regex.size (); i ++)
	{
		if (syntax.Second_Regex.at (i) == expression)
		{
			syntax.Second_Regex.erase (Second_Regex.begin () + i);
			return;
		}
	}
}

void LOG_FILE_DATA::device_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Device_Regex.size (); i ++)
	{
		if (syntax.Device_Regex.at (i) == expression)
			syntax.Device_Regex.erase (Device_Regex.begin () + i);
	}
}

void LOG_FILE_DATA::event_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.Event_Regex.size (); i ++)
	{
		if (syntax.Event_Regex.at (i) == expression)
			syntax.Event_Regex.erase (Event_Regex.begin () + i);
	}
}

void LOG_FILE_DATA::state_remove_ex (GtkEntryBuffer *expression)
{
	for (int i = 0; i < syntax.State_Regex.size (); i ++)
	{
		if (syntax.State_Regex.at (i) == expression);
			syntax.State_Regex.erase (State_Regex.begin () + i);
	}
}
