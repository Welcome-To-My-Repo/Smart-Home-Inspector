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
	GtkWidget	*Window = gtk_application_window_new (app),
			*BigBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*OpenSaveBox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
			*OpenJSON = gtk_button_new_from_icon_name ("gtk-open", GTK_ICON_SIZE_SMALL_TOOLBAR),
			*SaveJSON = gtk_button_new_from_icon_name ("gtk-save", GTK_ICON_SIZE_SMALL_TOOLBAR),
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
	gtk_box_pack_start (GTK_BOX (OpenSaveBox), OpenJSON, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (OpenSaveBox), SaveJSON, TRUE, TRUE, 0);
	g_signal_connect_swapped (OpenJSON, "clicked", G_CALLBACK (load_from_json), pos);
	g_signal_connect_swapped (SaveJSON, "clicked", G_CALLBACK (save_to_json), pos);
	gtk_box_pack_start (GTK_BOX (BigBox), OpenSaveBox, TRUE, TRUE, 0);
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

//day regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Day Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*day) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*day));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", day);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*day); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*day, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", day);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", day);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//hour regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Hour Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*hour) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*hour));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", hour);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*hour); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*hour, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", hour);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", hour);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//minute regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Minute Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*minute) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*minute));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", minute);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*minute); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*minute, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", minute);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", minute);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//second regex entry
	AddExpressionButton = gtk_button_new_with_label ("Add Second Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (subbox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (subbox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*second) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*second));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", second);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*second); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*second, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", second);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", second);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//make device regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Regex");

	AddExpressionButton = gtk_button_new_with_label ("Add Device Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*device) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*device));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", device);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*device); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*device, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", device);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", device);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//make event regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Event Regex");

	AddExpressionButton = gtk_button_new_with_label ("Add Event Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*event) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*event));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", event);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*event); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*event, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", event);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", event);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

//make state regex tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "State Regex");

	AddExpressionButton = gtk_button_new_with_label ("Add State Regex");
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (EntryScrolledBox), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	if (log_files.at (*pos).get_regex_list_size (*state) == 0)
	{
		EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
		DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
		Entry = gtk_entry_new_with_buffer (log_files.at (*pos).add_regex (*state));
		gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
		gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
		g_object_set_data (G_OBJECT (Entry), "char", state);
		g_object_set_data (G_OBJECT (Entry), "position", pos);
		g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
	}
	else
	{
		for (int i = 0; i < log_files.at (*pos).get_regex_list_size (*state); i ++)
		{
			EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
			DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
			Entry = gtk_entry_new_with_buffer (log_files.at (*pos).get_regex (*state, i));
			gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, TRUE, TRUE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
			gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
			g_object_set_data (G_OBJECT (Entry), "char", state);
			g_object_set_data (G_OBJECT (Entry), "position", pos);
			g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (remove_expression), Entry);
		}
	}
	g_object_set_data (G_OBJECT (EntryViewportBox), "char", state);
	g_object_set_data (G_OBJECT (EntryViewportBox), "position", pos);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box_regex), EntryViewportBox);

	gtk_widget_show_all (Window);
}

void initialize_log_file_stats ()
{
	std::vector <boost::regex>	year,
					month,
					day,
					hour,
					minute,
					second,
					device,
					event,
					state;
	boost::regex *tmp;
	boost::smatch	YearP,
			MonthP,
			DayP,
			HourP,
			MinuteP,
			SecondP,
			DeviceP,
			EventP,
			StateP;
	std::string contents, line;
	std::stringstream buffer;
	GtkTextIter start, end;
	GtkTextBuffer *TextBuffer;
	DATA *check;
	EVENT *E;
	for (int i = 0; i < log_files.size (); i ++)
	{
//copy text from text buffer into string stream
		TextBuffer = log_files.at (i).get_text_file ();
		gtk_text_buffer_get_start_iter (TextBuffer, &start);
		gtk_text_buffer_get_end_iter (TextBuffer, &end);
		contents = gtk_text_buffer_get_text (TextBuffer, &start, &end, TRUE);
		buffer.str (contents);
//create regex expressions
		for (int i = 0; i < log_files.at (i).Year_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Year_Regex.at (i))));
			year.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Month_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Month_Regex.at (i))));
			month.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Day_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Day_Regex.at (i))));
			day.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Hour_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Hour_Regex.at (i))));
			hour.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Minute_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Minute_Regex.at (i))));
			minute.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Second_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Second_Regex.at (i))));
			second.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Device_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Device_Regex.at (i))));
			device.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).Event_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).Event_Regex.at (i))));
			event.push_back (*tmp);
			delete tmp;
		}
		for (int i = 0; i < log_files.at (i).State_Regex.size (); i ++)
		{
			tmp = new boost::regex (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (log_files.at (i).State_Regex.at (i))));
			state.push_back (*tmp);
			delete tmp;
		}
//create match patterns for applying the regexes
		while (!buffer.eof ())
		{
			check = new DATA;
			E = new EVENT;
			check->start = buffer.tellg ();
			std::getline (buffer, line);
			check->end = buffer.tellg ();
			int k = 0;
			for (int k = 0; k < year.size (); k ++)
				if (boost::regex_search (line, YearP, year.at (k)))
					break;
			for (int k = 0; k < month.size (); k ++)
				if (boost::regex_search (line, MonthP, month.at (k)))
					break;
			for (int k = 0; k < day.size (); k ++)
				if (boost::regex_search (line, DayP, day.at (k)))
					break;
			for (int k = 0; k < hour.size (); k ++)
				if (boost::regex_search (line, HourP, hour.at (k)))
					break;
			for (int k = 0; k < minute.size (); k ++)
				if (boost::regex_search (line, MinuteP, minute.at (k)))
					break;
			for (int k = 0; k < second.size (); k ++)
				if (boost::regex_search (line, SecondP, second.at (k)))
					break;
			for (int k = 0; k < device.size (); k ++)
				if (boost::regex_search (line, DeviceP, device.at (k)))
					break;
			for (int k = 0; k < event.size (); k ++)
				if (boost::regex_search (line, EventP, event.at (k)))
					break;
			for (int k = 0; k < state.size (); k ++)
				if (boost::regex_search (line, StateP, state.at (k)))
					break;
			if (!YearP.empty ())
				check->year = YearP[0];
			if (!MonthP.empty ())
				check->month = MonthP[0];
			if (!DayP.empty ())
				check->day = DayP[0];
			if (!HourP.empty ())
				check->hour = HourP[0];
			if (!MinuteP.empty ())
				check->minute = MinuteP[0];
			if  (!SecondP.empty ())
				check->second = SecondP[0];
			if (!DeviceP.empty ())
				E->device_name = DeviceP[0];
			if (!EventP.empty ())
				E->event_name = EventP[0];
			if (!StateP.empty ())
				E->state = StateP[0];
			check->events.push_back (*E);
			if (log_files.at (i).data.size () == 0)
			{
				log_files.at (i).data.push_back (*check);
			}
			else
			{
				long int CheckPos = log_files.at (i).is_same_data (*check);
				if (CheckPos != -1)
				{
					log_files.at (i).merge_data (CheckPos, *check);
				}
				else
				{
					log_files.at (i).data.push_back (*check);
				}
			}
			delete check;
			delete E;
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

void save_to_json (int *log_files_pos)
{
	GtkWidget	*file_chooser,
			*window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	int i;
	char *filename;
	file_chooser = gtk_file_chooser_dialog_new (	"Open a Regex Set",
							GTK_WINDOW (window),
							GTK_FILE_CHOOSER_ACTION_OPEN,
							("_Cancel"),
							GTK_RESPONSE_CANCEL,
							("_Open"),
							GTK_RESPONSE_ACCEPT,
							NULL);
	i = gtk_dialog_run (GTK_DIALOG (file_chooser));
	if (i == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *a = GTK_FILE_CHOOSER (file_chooser);
		filename = gtk_file_chooser_get_filename (a);
	}
	gtk_widget_destroy (file_chooser);
	if (filename != nullptr)
	{
		log_files.at (*log_files_pos).Year_Regex.clear ();
		log_files.at (*log_files_pos).Month_Regex.clear ();
		log_files.at (*log_files_pos).Day_Regex.clear ();
		log_files.at (*log_files_pos).Hour_Regex.clear ();
		log_files.at (*log_files_pos).Minute_Regex.clear ();
		log_files.at (*log_files_pos).Second_Regex.clear ();
		log_files.at (*log_files_pos).Device_Regex.clear ();
		log_files.at (*log_files_pos).Event_Regex.clear ();
		log_files.at (*log_files_pos).State_Regex.clear ();
		ifstream a;
		a.open (filename);
		if (a.is_open ())
		{
			std::string b;
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('y'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('M'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('d'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('h'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('m'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('s'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('D'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('e'),
					a.c_str (),
					-1)
			}
			while (true)
			{
				getline (b, a);
				if (a == "")
					break;
				gtk_entry_buffer_new (
					log_files.at (*log_files_pos).add_regex ('S'),
					a.c_str (),
					-1)
			}
		}
	}
}
void load_from_json (int *log_files_pos)
{

}
