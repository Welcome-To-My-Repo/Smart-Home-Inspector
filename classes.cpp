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
GtkEntryBuffer *LOG_FILE_DATA::add_regex (char type)
{
	switch (type)
	{
		case 'y':
		{
			syntax.Year_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Year_Regex.back ();
		}
		case 'M':
		{
			syntax.Month_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Month_Regex.back ();
		}
		case 'd':
		{
			syntax.Day_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Day_Regex.back ();
		}
		case 'h':
		{
			syntax.Hour_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Hour_Regex.back ();
		}
		case 'm':
		{
			syntax.Minute_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Minute_Regex.back ();
		}
		case 's':
		{
			syntax.Second_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Second_Regex.back ();
		}
		case 'D':
		{
			syntax.Device_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Device_Regex.back ();
		}
		case 'e':
		{
			syntax.Event_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.Event_Regex.back ();
		}
		case 'S':
		{
			syntax.State_Regex.push_back (gtk_entry_buffer_new (NULL, -1));
			return syntax.State_Regex.back ();
		}
	};
}
void LOG_FILE_DATA::remove_ex (char type, GtkEntryBuffer *expression)
{
	switch (type)
	{
		case 'y':
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
		case 'M':
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
		case 'd':
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
		case 'h':
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
		case 'm':
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
		case 's':
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
		case 'D':
		{
			for (int i = 0; i < syntax.Device_Regex.size (); i ++)
			{
				if (syntax.Device_Regex.at (i) == expression)
				{
					syntax.Device_Regex.erase (Device_Regex.begin () + i);
					return;
				}
			}
		}
		case 'e':
		{
			for (int i = 0; i < syntax.Event_Regex.size (); i ++)
			{
				if (syntax.Event_Regex.at (i) == expression)
				{
					syntax.Event_Regex.erase (Event_Regex.begin () + i);
					return;
				}
			}
		}
		case 'S':
		{
			for (int i = 0; i < syntax.State_Regex.size (); i ++)
			{
				if (syntax.State_Regex.at (i) == expression)
				{
					syntax.State_Regex.erase (State_Regex.begin () + i);
					return;
				}
			}
		}
	};
}
