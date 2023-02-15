#include "shi.h"

void mainwindowactivate (GtkApplication *app)
{
//assign new window to Window
	GtkWidget *Window = gtk_application_window_new (app);
//set Window parameters
	gtk_window_set_title (GTK_WINDOW (Window), "window");
	gtk_window_set_default_size (GTK_WINDOW (Window), 1536, 1024);
//assign elements to other widgets
	GtkWidget
	*MainBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
	*SecondBox = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
	*TextTabs = 	gtk_notebook_new (),
	*Tabs = 	gtk_notebook_new (),
	*EventsPlayBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
	*DrawDisplay = 	gtk_drawing_area_new (),
	*DevList = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
	*DevListScroll = gtk_scrolled_window_new (NULL, NULL),
	*FileMenu = 	gtk_menu_new (),
	*FileButton = 	gtk_menu_item_new_with_label ("File"),
	*ActionsMenu = 	gtk_menu_new (),
	*ActionsButton = gtk_menu_item_new_with_label ("Actions"),
	*ActionsBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
	*MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
	*MenuBar = 	gtk_menu_bar_new (),
	*Open = 	gtk_menu_item_new_with_label ("Open Log File"),
	*OpenProject = 	gtk_menu_item_new_with_label ("Open Project"),
	*Save = 	gtk_menu_item_new_with_label ("Save Project"),
	*SaveAs = 	gtk_menu_item_new_with_label ("Save Project As"),
	*MenuSeparator =	gtk_separator_menu_item_new (),
	*Quit = 		gtk_menu_item_new_with_label ("Quit"),
	*Inspect = 	gtk_menu_item_new_with_label ("Analyze"),
	*Playbar = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
	*PlayScrubber,
	*PlayButton = 	gtk_button_new_from_icon_name ("gtk-media-play", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*StopButton = 	gtk_button_new_from_icon_name ("gtk-media-stop", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipLeft = 	gtk_button_new_from_icon_name ("gtk-media-rewind", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipRight = 	gtk_button_new_from_icon_name ("gtk-media-forward", GTK_ICON_SIZE_SMALL_TOOLBAR);
	GtkAdjustment *ScrubberAdjustment = gtk_adjustment_new (0, 0, 100, 1, 1, 1);
	PlayScrubber = gtk_scale_new (GTK_ORIENTATION_HORIZONTAL, ScrubberAdjustment);

	g_object_set_data (G_OBJECT (ScrubberAdjustment), "dev_list_scroll", DevListScroll);
	g_object_set_data (G_OBJECT (ScrubberAdjustment), "dev_list", DevList);
	g_object_set_data (G_OBJECT (ScrubberAdjustment), "events", EventsPlayBox);
	g_object_set_data (G_OBJECT (ScrubberAdjustment), "tabs", Tabs);
	g_signal_connect ( G_OBJECT (DrawDisplay), "draw", G_CALLBACK (generate_device_map), NULL);

//set default text display
	GtkWidget *tmp;
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (TextTabs), TRUE);
	gtk_notebook_append_page (GTK_NOTEBOOK (TextTabs), tmp = gtk_scrolled_window_new (NULL, NULL), NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (TextTabs), tmp, "Blank");
	GtkTextBuffer *a = gtk_text_buffer_new (NULL);
	gtk_text_buffer_set_text (a, default_text, -1);
	gtk_container_add (GTK_CONTAINER (tmp), gtk_text_view_new_with_buffer (a));
//create tab display
	gtk_notebook_append_page (GTK_NOTEBOOK (Tabs), EventsPlayBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Tabs), EventsPlayBox, "Device Map");
	gtk_notebook_append_page (GTK_NOTEBOOK (Tabs), DevListScroll, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Tabs), DevListScroll, "Device List");
//create the playbar with scrubber
	gtk_box_pack_start (GTK_BOX (Playbar), SkipLeft, FALSE, FALSE, 0);
	g_signal_connect_swapped (SkipLeft, "clicked", G_CALLBACK (skip_backward), ScrubberAdjustment);
	gtk_box_pack_start (GTK_BOX (Playbar), PlayButton, FALSE, FALSE, 0);
	g_signal_connect_swapped (PlayButton, "clicked", G_CALLBACK (play), ScrubberAdjustment);
	gtk_box_pack_start (GTK_BOX (Playbar), StopButton, FALSE, FALSE, 0);
	g_signal_connect_swapped (StopButton, "clicked", G_CALLBACK (stop), NULL);
	gtk_box_pack_start (GTK_BOX (Playbar), SkipRight, FALSE, FALSE, 0);
	g_signal_connect_swapped (SkipRight, "clicked", G_CALLBACK (skip_forward), ScrubberAdjustment);
	gtk_box_pack_start (GTK_BOX (Playbar), PlayScrubber, TRUE, TRUE, 0);
	g_signal_connect_swapped (ScrubberAdjustment, "value-changed", G_CALLBACK (scrubber_change_time), ScrubberAdjustment);

//add primary container element to window
	gtk_container_add (GTK_CONTAINER (Window), MainBox);
	gtk_container_add (GTK_CONTAINER (DevListScroll), DevList);
//add menu elements to menu bar container
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (FileButton), FileMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (FileMenu), MenuBox);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (ActionsButton), ActionsMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (ActionsMenu), ActionsBox);

//add menu items to drop down menu
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), OpenProject);
	//gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Save);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), SaveAs);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), MenuSeparator);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Quit);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), FileButton);

	gtk_menu_shell_append (GTK_MENU_SHELL (ActionsMenu), Inspect);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), ActionsButton);
//add elements to primary container element
	gtk_box_pack_start (GTK_BOX (MenuBox), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), MenuBox, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), SecondBox, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), TextTabs, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox),
		gtk_separator_new (GTK_ORIENTATION_VERTICAL),
		false, false, 7);
	gtk_box_pack_start (GTK_BOX (SecondBox), Tabs, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EventsPlayBox), DrawDisplay, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (EventsPlayBox),
		gtk_separator_new (GTK_ORIENTATION_HORIZONTAL),
		false, false, 7);
	gtk_box_pack_start (GTK_BOX (MainBox), Playbar, FALSE, FALSE, 0);
//box child packing settings
	gtk_box_set_child_packing (GTK_BOX (MainBox), SecondBox, true, true, 0, GTK_PACK_START);
	gtk_box_set_child_packing (GTK_BOX (SecondBox), TextTabs, TRUE, TRUE, 0, GTK_PACK_START);
//create signal handlers for button press events
	g_signal_connect_swapped (Quit, "activate", G_CALLBACK (gtk_widget_destroy), Window);
	open_file_params *j = new open_file_params;
	j->tabs = TextTabs;
	g_signal_connect_swapped (Open, "activate", G_CALLBACK (open_file), j);
	g_signal_connect_swapped (SaveAs, "activate", G_CALLBACK (save_project), NULL);
	g_signal_connect_swapped (OpenProject, "activate", G_CALLBACK (open_project), TextTabs);
	g_signal_connect_swapped (Inspect, "activate", G_CALLBACK (initialize_log_file_stats), ScrubberAdjustment);
//display all elements in window
	gtk_widget_show_all (Window);
}

//everything to do with the drawing area happens in this function
void drawing_area (GtkWidget *area)
{

}

void open_file (open_file_params *_)
{
	GtkWidget *file_chooser, *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Open a log file");
	gint i;
	file_chooser = gtk_file_chooser_dialog_new (	"Open a log file",
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
		char *filename;
		GtkFileChooser *a = GTK_FILE_CHOOSER (file_chooser);
		filename = gtk_file_chooser_get_filename (a);
		add_text_view (filename, _->tabs);
		g_free (filename);
	}
	gtk_widget_destroy (file_chooser);

}

void add_text_view (char *filename, GtkWidget *tabs)
{
	GtkWidget 	*scroll = gtk_scrolled_window_new (NULL, NULL),
			*text,
			*box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*set_regex = gtk_button_new_with_label ("Set Regular Expressions"),
			*close = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	int page;
	std::string str = filename, sub = "";
	sub = str.substr (str.rfind ("/", std::string::npos) + 1, std::string::npos);
	std::ifstream in;
	std::string contents = "";
	std::stringstream buffer;

	if (strcmp ("Blank", gtk_notebook_get_tab_label_text (GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page (GTK_NOTEBOOK (tabs), 0))) == 0)
	{
		gtk_notebook_remove_page (GTK_NOTEBOOK (tabs), 0);
	}
	in.open (filename);
	if (in.is_open ())
	{
		buffer << in.rdbuf ();	//copy contents of ifstream buffer to stringstream
		contents = buffer.str ();	//copy contents of stringstream to string
		LOG_FILE_DATA tmp;
		tmp.filename.append (filename);
		gtk_text_buffer_set_text (tmp.get_text_file (), contents.c_str (), -1);
		log_files.push_back (tmp);
	}
	gtk_box_pack_start (GTK_BOX (box), set_regex, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (box), scroll, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), close, FALSE, TRUE, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (tabs), box, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (tabs), box, sub.c_str());

	text = gtk_text_view_new_with_buffer (GTK_TEXT_BUFFER (log_files.back ().get_text_file()));
	page = gtk_notebook_get_n_pages (GTK_NOTEBOOK (tabs));

	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (text), false);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (text), false);
	gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW (text), false);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (text), GTK_WRAP_NONE);
	gtk_text_view_set_monospace (GTK_TEXT_VIEW (text), GTK_WRAP_NONE);
	gtk_text_view_set_justification (GTK_TEXT_VIEW (text), GTK_JUSTIFY_LEFT);
	gtk_scrollable_set_vscroll_policy (GTK_SCROLLABLE (text), GTK_SCROLL_NATURAL);
	gtk_scrollable_set_hscroll_policy (GTK_SCROLLABLE (text), GTK_SCROLL_NATURAL);
	gtk_container_add (GTK_CONTAINER (scroll), text);
	gtk_widget_show_all (tabs);

	struct _ {GtkWidget *y; int z;};
	_*to_remove = new _;
	to_remove->y = tabs; to_remove->z = page - 1;
	g_signal_connect_swapped (close, "clicked", G_CALLBACK (remove_page), to_remove);

	to_regex *i = new to_regex;
	i->pos = page -1;
	g_signal_connect_swapped (set_regex, "clicked", G_CALLBACK (set_regular_expressions), i);
}

void remove_page (void *page)
{
	struct tmp {GtkWidget *y; int z;};
	tmp *a = (tmp*)page;
	if (gtk_notebook_get_n_pages (GTK_NOTEBOOK (a->y)) > 1)
		gtk_notebook_remove_page (GTK_NOTEBOOK (a->y), a->z);
}

void set_regex_window (GtkApplication *app)
{
	to_regex *params = (to_regex*)g_object_get_data (G_OBJECT (app), "position");
	g_object_steal_data (G_OBJECT(app), "position");
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
	g_object_set_data (G_OBJECT (BigBox), "position", pos);
	g_signal_connect_swapped (OpenJSON, "clicked", G_CALLBACK (load_from_json), BigBox);
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
