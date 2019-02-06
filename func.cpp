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
	Parse_Log_File_window ();
	return Log_file;
}

void read_time_segment (smart_dev devlist)
{

}

void add_entry_box (GtkWidget *container)
{
	GtkWidget	*Box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*SecondBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
			*Entry = gtk_new,
			*Close = gtk_image_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
}

void remove_expression (GtkWidget *container, std::string expression)
{
	//search syntax class for expression
	//delete the main box widget
}

void add_custom_page (GtkWidget *notebook)
{
	//add new custom page to notebook
}

void Parse_Log_File_window ()
{
	GSList *radiobuttons;
	GtkWidget	*Window = gtk_window_new (GTK_WINDOW_TOPLEVEL),
			*BigBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*Notebook = gtk_notebook_new (),
			*TabBox,
			*SectionBox,
			*SectionScrollBox,
			*Viewport,
			*EntryButtonBox,
			*AddCustomTab = gtk_button_new_with_label ("Add Custom"),
			*EraseCustomTab = gtk_button_new_with_label ("Erase Custom"),
			*Add_buttons,
			*Close_buttons,
			*Close_image = gtk_image_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR),
			*Apply_button = gtk_button_new_from_icon_name ("gtk-apply", GTK_ICON_SIZE_SMALL_TOOLBAR);
			*EntryFieldBox,
			*Radio_is_Device = gtk_radio_button_new_with_label (radiobuttons, "Device Syntax"),
			*Radio_is_Event = gtk_radio_button_new_with_label (radiobuttons, "Event Syntax"),
			*Radio_is_State = gtk_radio_button_new_with_label (radiobuttons, "State Syntax");

	gtk_box_pack_start (GTK_BOX (BigBox), Notebook, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (BigBox), Apply_button, TRUE, FALSE, 0);

	TabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	SectionScrollBox = gtk_scrolled_window_new ();
	Viewport = gtk_viewport_new ();
	EntryButtonBox = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	EntryFieldBox = gtk_new_entry_new_with_buffer (NULL);
	Add_buttons = gtk_button_new_with_label ("Add Date/Time Format");

}
