#include "shi.h"

//main function to parse the log file
void set_regular_expressions (to_regex *_)
{
	GtkApplication *dialogue = gtk_application_new ("app.shi.syntax_dialogue", G_APPLICATION_FLAGS_NONE);
	g_object_set_data (G_OBJECT (dialogue), "position", _);
	g_signal_connect (dialogue, "activate", G_CALLBACK (set_regex_window), dialogue);
	g_application_run (G_APPLICATION (dialogue), 0, NULL);
	g_object_unref (dialogue);
}
void add_entry_box_regex (GtkWidget *container)
{
	char type = *(char*)g_object_get_data (G_OBJECT (container), "char");
	int position = *(int*)g_object_get_data (G_OBJECT (container), "position");
	std::cout << "add ad\t" << type << " " << position << std::endl;
	std::cout << position << std::endl;
	GtkWidget *sidebox, *closebutton, *Entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (log_files.at(position).add_regex (type));

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), Entry, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, TRUE, 0);
	g_object_set_data (G_OBJECT (Entry), "char", g_object_get_data (G_OBJECT (container), "char"));
	g_object_set_data (G_OBJECT (Entry), "position", g_object_get_data (G_OBJECT (container), "position"));
	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (remove_expression), Entry);
	gtk_widget_show_all (container);
}
void remove_expression (GtkEntry *Entry)
{
	char type = *(char*)g_object_get_data (G_OBJECT (Entry), "char");
	int position = *(int*)g_object_get_data (G_OBJECT (Entry), "position");
	std::cout << "remove at\t" << type << " " << position << std::endl;
	std::cout << position << std::endl;
	log_files.at (position).remove_ex (type, gtk_entry_get_buffer (Entry));
	gtk_widget_destroy (gtk_widget_get_parent (GTK_WIDGET (Entry)));
}

void set_regex_window (GtkApplication *app)
{
	to_regex *params = (to_regex*)g_object_get_data (G_OBJECT (app), "position");
	int *pos = new int;
	*pos = params->pos;
	std::cout << "vector position set_regex_window\t" << pos << std::endl;
	GtkWidget	*Window = gtk_application_window_new (app),
			*BigBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*Notebook = gtk_notebook_new (),
			*NotebookEndAction = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*AddCustomTabButton = gtk_button_new_with_label ("Add Custom"),
			*DeleteCustomTabButton = gtk_button_new_with_label ("Erase Custom"),
			*Apply_button = gtk_button_new_from_icon_name ("gtk-apply", GTK_ICON_SIZE_SMALL_TOOLBAR),
			*ChooseTextFile = gtk_combo_box_new (),
			*NotebookTabBox,
			*AddExpressionButton,
			*EntryScrolledBox,
			*EntryViewport,
			*EntryViewportBox,
			*EntryContainer,
			*DeleteEntryButton,
			*Entry,
			*SecondEntry,
			*Close_image;
	char	*year = new char {'y'},
		*month = new char {'M'},
		*day = new char {'d'},
		*hour = new char {'h'},
		*minute = new char {'m'},
		*second = new char {'s'},
		*device = new char {'D'},
		*event = new char {'e'},
		*state = new char {'S'};

	gtk_container_add (GTK_CONTAINER (Window), BigBox);
	gtk_box_pack_start (GTK_BOX (BigBox), Notebook, TRUE, TRUE, 0);
	gtk_box_pack_end (GTK_BOX (BigBox), Apply_button, FALSE, FALSE, 0);
	g_signal_connect_swapped (Apply_button, "clicked", G_CALLBACK (gtk_widget_destroy), Window);

//make time regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Time Regex");
	GtkWidget *subbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), subbox, TRUE, TRUE, 0);
//year regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Year Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*year) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*year));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", year);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*year); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*year, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", year);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", year);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//month regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Month Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*month) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*month));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", month);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*month); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*month, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", month);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", month);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//make device regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Regex");

//make event regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Event Regex");

//make device regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "State Regex");

	gtk_widget_show_all (Window);
}

void initialize_log_file_stats ()
{
	/*
	std::cout << "initializing" << std::endl;
//make the variables
	std::string contents, line;
	std::stringstream buffer;
	GtkTextIter *start, *end;
	shi::SEGMENT_POS *pos;
	shi::DEVICE_STATS *stats;
	std::vector <shi::DEVICE_STATS> all_stats;
	GtkTextBuffer *to_text;
	std::vector <boost::regex> 	year,
					month,
					day,
					hour,
					minute,
					second,
					d,
					e,
					s;
	boost::regex *tmp;
	boost::smatch 	YearPatterns,
			MonthPatterns,
			DayPatterns,
			HourPatterns,
			MinutePatterns,
			SecondPatterns,
			Dpatterns,
			Epatterns,
			Spatterns;
	for (int i = 0; i < Text_Files.size (); i ++)
	{
		to_text = Text_Files.at (i);
//make the text buffer
		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (Text_Files.at (i)), start, 0);
		gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (Text_Files.at (i)), end, -1);
		contents = gtk_text_buffer_get_text (GTK_TEXT_BUFFER (Text_Files.at (i)), start, end, TRUE);
		buffer.str (contents);
//loop creating regex's from the parse log file dialogue
		for (int i = 0; i < log_file_syntax.Year_Regex.size (); i++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Year_Regex.at (i))));
			year.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.Device_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Device_Regex.at (i))));
			d.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.Event_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.Event_Regex.at (i))));
			d.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_file_syntax.State_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_file_syntax.State_Regex.at (i))));
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
			try
			{while (!boost::regex_search (line, YearPatterns, year.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;

			try
			{while (!boost::regex_search (line, MonthPatterns, month.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;

			try
			{while (!boost::regex_search (line, DayPatterns, day.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;

			try
			{while (!boost::regex_search (line, HourPatterns, hour.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;

			try
			{while (!boost::regex_search (line, MinutePatterns, minute.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;

			try
			{while (!boost::regex_search (line, SecondPatterns, second.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;
//check all device regular expressions against the string until a hit
			try
			{while (!boost::regex_search (line, Dpatterns, d.at (i))); i++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;
//check all event regular expressions against the string until a hit
			try
			{while (!boost::regex_search (line, Epatterns, e.at (i))); i++;}
			catch (...)
			{error_window ("Regex Search Error!");}
			i = 0;
//check all state regular expressions against the string until a hit
			try
			{while (!boost::regex_search (line, Spatterns, s.at (i))); i ++;}
			catch (...)
			{error_window ("Regex Search Error!");}
//if the time pattern already esists in the string, do stuff
			if (log_files.is_time_pattern (YearPatterns[0], MonthPatterns[0], DayPatterns[0], HourPatterns[0], MinutePatterns[0], SecondPatterns[0]))
			{
//find the identical time pattern
				long int a = log_files.find (YearPatterns[0], MonthPatterns[0], DayPatterns[0], HourPatterns[0], MinutePatterns[0], SecondPatterns[0]);
//add the pointer to the text buffer
				log_files.at (a).add_text_buffer_link (Text_Files.at (i));
//add the segment position to the vector
				log_files.at (a).add_segment_pos (*pos);

			}
//if the time pattern is new, do stuff
			else
			{
				shi::LOG_FILE_STATS x;
				x.add_text_buffer_link (Text_Files.at (i));
				x.add_segment_pos (*pos);
				log_files.log_file_stats.push_back (x);
			}
		}

	}
*/
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
			*box,
			*error_label,
			*ok_button;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	error_label = gtk_label_new (error_string);
	ok_button = gtk_button_new_with_label ("Ok");

	gtk_container_add (GTK_CONTAINER (window), box);
	gtk_container_add (GTK_CONTAINER (box), error_label);
	gtk_container_add (GTK_CONTAINER (box), ok_button);

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
