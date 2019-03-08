#include "shi.h"

//main function to parse the log file
void Parse_Log_Files ()
{
	//initialize and activate parse log file dialogue window
	GtkApplication *dialogue = gtk_application_new ("app.shi.syntax_dialogue", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (dialogue, "activate", G_CALLBACK (Parse_Log_Files_window), dialogue);
	g_application_run (G_APPLICATION (dialogue), 0, NULL);
	g_object_unref (dialogue);
	//parse_time ();
	initialize_log_file_stats ();
}

void parse_time ()
{
//make a vector of regex patterns
	std::vector<std::regex> patterns;
	std::regex *tmp;	//temporary regex to initialize using the gtk buffers
//add each of the user's regex patterns into the vector of regex's
	for (int i = 0; i < log_file_syntax.Time_Regex.size (); i ++)
	{
		tmp = new std::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Time_Regex.at (i))));
		patterns.push_back (*tmp);
		delete tmp;
	}

	for (int i = 0; i < Text_Files.size (); i ++)
	{

	}

}

void add_entry_box_time_regex (GtkWidget *container)
{
	GtkWidget *sidebox, *closebutton, *Entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Format.push_back (gtk_entry_buffer_new (NULL, -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Format.back ());

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), Entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, TRUE, 0);
	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (remove_entry_time_regex), Entry);
	gtk_widget_show_all (container);
}

void add_entry_box_device_regex (GtkWidget *container)
{
	GtkWidget *sidebox, *closebutton, *Entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Format.push_back (gtk_entry_buffer_new (NULL, -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Format.back ());

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), Entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, TRUE, 0);
	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (remove_entry_device_regex), Entry);
	gtk_widget_show_all (container);
}
void add_entry_box_event_regex (GtkWidget *container)
{
	GtkWidget *sidebox, *closebutton, *Entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Format.push_back (gtk_entry_buffer_new (NULL, -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Format.back ());

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), Entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, TRUE, 0);
	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (remove_entry_event_regex), Entry);
	gtk_widget_show_all (container);
}

void add_entry_box_state_regex (GtkWidget *container)
{
	GtkWidget *sidebox, *closebutton, *Entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Format.push_back (gtk_entry_buffer_new (NULL, -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Format.back ());

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), Entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, TRUE, 0);
	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (remove_entry_state_regex), Entry);
	gtk_widget_show_all (container);
}

void remove_entry_time_regex (GtkWidget *entry)
{
	log_file_syntax.time_remove_ex (gtk_entry_get_buffer (GTK_ENTRY (entry)));
	gtk_widget_destroy (gtk_widget_get_parent (entry));
}

void remove_entry_device_regex (GtkWidget *entry)
{
	log_file_syntax.device_remove_ex (gtk_entry_get_buffer (GTK_ENTRY (entry)));
	gtk_widget_destroy (gtk_widget_get_parent (entry));
}

void remove_entry_state_regex (GtkWidget *entry)
{
	log_file_syntax.state_remove_ex (gtk_entry_get_buffer (GTK_ENTRY (entry)));
	gtk_widget_destroy (gtk_widget_get_parent (entry));
}

void remove_entry_event_regex (GtkWidget *entry)
{
	log_file_syntax.event_remove_ex (gtk_entry_get_buffer (GTK_ENTRY (entry)));
	gtk_widget_destroy (gtk_widget_get_parent (entry));
}

void add_custom_page (GtkWidget *notebook)
{
	//add new custom page to notebook
}

void Parse_Log_Files_window (GtkApplication *dialogue)
{
	GtkWidget	*Window = gtk_application_window_new (dialogue),
			*BigBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*Notebook = gtk_notebook_new (),
			*NotebookEndAction = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*AddCustomTabButton = gtk_button_new_with_label ("Add Custom"),
			*DeleteCustomTabButton = gtk_button_new_with_label ("Erase Custom"),
			*Apply_button = gtk_button_new_from_icon_name ("gtk-apply", GTK_ICON_SIZE_SMALL_TOOLBAR),
			*NotebookTabBox,
			*AddExpressionButton,
			*EntryScrolledBox,
			*EntryViewport,
			*EntryViewportBox,
			*EntryContainer,
			*DeleteEntryButton,
			*Entry,
			*SecondEntry,
			*Close_image,
			*Radio_is_Device,
			*Radio_is_Event,
			*Radio_is_State;

	Radio_is_Device = gtk_radio_button_new_with_label (NULL, "Device Syntax");
	Radio_is_Event = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (Radio_is_Device), "Event Syntax");
	Radio_is_State = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (Radio_is_Device), "State Syntax");

	gtk_container_add (GTK_CONTAINER (Window), BigBox);
	gtk_box_pack_start (GTK_BOX (NotebookEndAction), AddCustomTabButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookEndAction), DeleteCustomTabButton, FALSE, FALSE, 0);
	gtk_notebook_set_action_widget (GTK_NOTEBOOK (Notebook), NotebookEndAction, GTK_PACK_END);
	gtk_box_pack_start (GTK_BOX (BigBox), Notebook, TRUE, TRUE, 0);
	gtk_box_pack_end (GTK_BOX (BigBox), Apply_button, FALSE, FALSE, 0);
	g_signal_connect_swapped (Apply_button, "clicked", G_CALLBACK (gtk_widget_destroy), Window);

	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Time Notation");

//Add Regex Section
/*
	AddExpressionButton = gtk_button_new_with_label ("Add Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Regex.push_back (gtk_entry_buffer_new ("Type a Regular Expression here", -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.back ());

	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);

	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_time_regex), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_time_regex), Entry);
	*/
	AddExpressionButton = gtk_button_new_with_label ("Add Regex");
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_time_regex), EntryViewportBox);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_file_syntax.Time_Regex.size () == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_time_regex), Entry);
		log_file_syntax.Time_Regex.push_back (gtk_entry_buffer_new ("Type a Regular Expression here", -1));
		Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.back ());
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);

	}
	else
	{
		for (int i = 0; i < log_file_syntax.Time_Regex.size (); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_time_regex), Entry);
			Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.at (i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		}
	}

//make Device Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Notation");

//make Regex Section
	AddExpressionButton = gtk_button_new_with_label ("Add Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Regex.push_back (gtk_entry_buffer_new ("Type a Regular Expression here", -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.back ());

	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);

	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_device_regex), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_device_regex), Entry);

//make Event Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Event Notation");

	AddExpressionButton = gtk_button_new_with_label ("Add Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Regex.push_back (gtk_entry_buffer_new ("Type a Regular Expression here", -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.back ());

	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);

	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_event_regex), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_event_regex), Entry);

//make State Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "State Notation");

	AddExpressionButton = gtk_button_new_with_label ("Add Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	log_file_syntax.Time_Regex.push_back (gtk_entry_buffer_new ("Type a Regular Expression here", -1));
	Entry = gtk_entry_new_with_buffer (log_file_syntax.Time_Regex.back ());

	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);

	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_state_regex), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_entry_state_regex), Entry);


	gtk_widget_show_all (Window);
}

void initialize_log_file_stats ()
{
//make the variables
	std::string contents, line;
	std::stringstream buffer;
	GtkTextIter *start, *end;
	shi::SEGMENT_POS *pos;
	shi::DEVICE_STATS *stats;
	std::vector <shi::DEVICE_STATS> all_stats;
	GtkTextBuffer *to_text;
	std::vector <std::regex> t, d, e, s;
	std::regex *tmp;
	std::smatch Tpatterns, Dpatterns, Epatterns, Spatterns;
	for (int i = 0; i < Text_Files.size (); i ++)
	{
		to_text = Text_Files.at (i);
//make the text buffer
		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (Text_Files.at (i)), start, 0);
		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (Text_Files.at (i)), end, -1);
		contents = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (Text_Files.at (i)), start, end, TRUE);
		buffer.str (contents);
//loop creating regex's from the parse log file dialogue
		for (int i = 0; i < log_file_syntax.Time_Regex.size (); i++)
		{
			tmp = new std::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Time_Regex.at (i))));
			t.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.Device_Regex.size (); i ++)
		{
			tmp = new std::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Device_Regex.at (i))));
			d.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.Event_Regex.size (); i ++)
		{
			tmp = new std::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Event_Regex.at (i))));
			d.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.State_Regex.size (); i ++)
		{
			tmp = new std::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.State_Regex.at (i))));
			d.push_back (*tmp);
			delete tmp;
		}
//create match patterns for applying the regexes
		while (!buffer.eof ())
		{
//create a new segment position
			pos = new shi::SEGMENT_POS;
//get starting position
			pos->start = buffer.tellg ();
//get a single line from the buffer
			std::getline (buffer, line);
//get ending position
			pos->end = buffer.tellg ();
			int i = 0;
//check all time regular expressions against the string until a hit
			while (!std::regex_match (line, Tpatterns, t.at (i)));
				i ++;
			i = 0;
//check all device regular expressions against the string until a hit
			while (!std::regex_match (line, Dpatterns, d.at (i)));
				i ++;
			i = 0;
//check all event regular expressions against the string until a hit
			while (!std::regex_match (line, Epatterns, e.at (i)));
				i ++;
			i = 0;
//check all state regular expressions against the string until a hit
			while (!std::regex_match (line, Spatterns, s.at (i)));
				i ++;
//if the time pattern already esists in the string, do stuff
			if (log_files.is_time_pattern (Tpatterns[0]))
			{
//find the identical time pattern
				long int a = log_files.find (Tpatterns[0]);
//add the pointer to the text buffer
				log_files.at (a).add_text_buffer_link (Text_Files.at (i));
//add the segment position to the vector
				log_files.at (a).add_segment_pos (*pos);

			}
//if the time pattern is new, do stuff
			else
			{

			}
		}

	}
}

void error_window_dialogue (char *error_warning);
void error_window (char *error_string)
{
	/*
	GtkApplication *warning = gtk_application_new ("app.shi.error", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (warning, "activate", G_CALLBACK (error_window_dialogue), warning);
	g_application_run (G_APPLICATION (warning), 0, NULL);
	g_object_unref (warning);
	*/

	GtkWidget	*window,
			*error_label,
			*ok_button;
	window = gtk_window_new (GTK_WINDOW_POPUP);
	error_label = gtk_label_new (error_string);
	ok_button = gtk_button_new_with_label ("Ok");

	gtk_container_add (GTK_CONTAINER (window), error_label);
	gtk_container_add (GTK_CONTAINER (window), ok_button);

	g_signal_connect_swapped (ok_button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	gtk_widget_show_all (window);
}

void error_window_dialogue (GtkApplication *app, char *error_warning)
{
	GtkWidget	*window,
			*error_label,
			*ok_button;

	window = gtk_application_window_new (app);
	error_label = gtk_label_new (error_warning);

}
