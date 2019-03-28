#include "shi.h"
#include <fstream>
/*
GtkWidget 	*Window,
		*MainBox,
		*SecondBox,
		*Tabs,
		*TextTabs,
		*EventsPlayBox,
		*DrawDisplay,
		*DevList,
		*DevListScroll,
		*FileMenu,
		*FileButton,
		*ActionsMenu,
		*ActionsButton,
		*ActionsBox,
		*MenuBox,
		*MenuBar,
		*Open,
		*Save,
		*SaveAs,
		*MenuSeparator,
		*Quit,
		*Inspect,
		*Playbar,
		*PlayScrubber,
		*PlayButton,
		*StopButton,
		*SkipRight,
		*SkipLeft;
*/
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
	*Tabs = 		gtk_notebook_new (),
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
	*Open = 		gtk_menu_item_new_with_label ("Open Log File"),
	*Save = 		gtk_menu_item_new_with_label ("Save Project"),
	*SaveAs = 	gtk_menu_item_new_with_label ("Save Project As"),
	*MenuSeparator =	gtk_separator_menu_item_new (),
	*Quit = 		gtk_menu_item_new_with_label ("Quit"),
	*Inspect = 	gtk_menu_item_new_with_label ("Inspect Log Files"),
	*Playbar = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
	*PlayScrubber = 	gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1),
	*PlayButton = 	gtk_button_new_from_icon_name ("gtk-media-play", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*StopButton = 	gtk_button_new_from_icon_name ("gtk-media-stop", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipRight = 	gtk_button_new_from_icon_name ("gtk-media-rewind", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipLeft = 	gtk_button_new_from_icon_name ("gtk-media-forward", GTK_ICON_SIZE_SMALL_TOOLBAR);

//set default text display
	GtkWidget *tmp;
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (TextTabs), TRUE);
	gtk_notebook_append_page (GTK_NOTEBOOK (TextTabs), tmp = gtk_scrolled_window_new (NULL, NULL), NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (TextTabs), tmp, "Blank");
	Text_Files.resize (0);
	Text_Files.push_back (gtk_text_buffer_new (NULL));
	gtk_text_buffer_set_text (Text_Files.front (), "There are no log files currently loaded.", -1);
	gtk_container_add (GTK_CONTAINER (tmp), gtk_text_view_new_with_buffer (Text_Files.front ()));
//create tab display
	gtk_notebook_append_page (GTK_NOTEBOOK (Tabs), EventsPlayBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Tabs), EventsPlayBox, "Device Map");
	gtk_notebook_append_page (GTK_NOTEBOOK (Tabs), DevListScroll, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Tabs), DevListScroll, "Device List");
//create the playbar with scrubber
	gtk_box_pack_start (GTK_BOX (Playbar), SkipRight, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Playbar), PlayButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Playbar), StopButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Playbar), SkipLeft, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Playbar), PlayScrubber, TRUE, TRUE, 0);
//add primary container element to window
	gtk_container_add (GTK_CONTAINER (Window), MainBox);
	//gtk_container_add (GTK_CONTAINER (TextTabs), TextDisplay);
	gtk_container_add (GTK_CONTAINER (DevListScroll), DevList);
//add menu elements to menu bar container
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (FileButton), FileMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (FileMenu), MenuBox);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (ActionsButton), ActionsMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (ActionsMenu), ActionsBox);

//add menu items to drop down menu
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Save);
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
	//gtk_box_set_child_packing (GTK_BOX (SecondBox), TextDisplay, true, true, 5, GTK_PACK_START);
	//gtk_box_set_child_packing (GTK_BOX (SecondBox), DrawDisplay, true, true, 5, GTK_PACK_START);
//create signal handlers for button press events
	g_signal_connect_swapped (Quit, "activate", G_CALLBACK (gtk_widget_destroy), Window);
	g_signal_connect_swapped (Open, "activate", G_CALLBACK (open_file), TextTabs);
	g_signal_connect_swapped (SaveAs, "activate", G_CALLBACK (save_project), NULL);
	g_signal_connect_swapped (Inspect, "activate", G_CALLBACK (Parse_Log_Files), NULL);
//display all elements in window
	gtk_widget_show_all (Window);
	drawing_area (DrawDisplay);
}

//everything to do with the drawing area happens in this function
void drawing_area (GtkWidget *area)
{

}

void open_project ()
{
	gint x;
	char *filename;
	GtkWidget *Window, *File_Chooser;
	Window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (Window), "Open A Project");
	gtk_window_set_default_size (GTK_WINDOW (Window), 512, 256);
	File_Chooser = gtk_file_chooser_dialog_new (	"Open A Project",
							GTK_WINDOW (Window),
							GTK_FILE_CHOOSER_ACTION_OPEN,
							("Cancel"),
							GTK_RESPONSE_CANCEL,
							("Open"),
							GTK_RESPONSE_ACCEPT,
							NULL);
	x = gtk_dialog_run (GTK_DIALOG (File_Chooser));
	if (x == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *Choose = GTK_FILE_CHOOSER (File_Chooser);
		filename = gtk_file_chooser_get_filename (Choose);
	}
	gtk_widget_destroy (File_Chooser);
	g_free (filename);
}

void save_project ()
{
	gint x;
	GtkWidget *Window, *File_Chooser;
	Window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (Window), "Save Project");
	gtk_window_set_default_size (GTK_WINDOW (Window), 512, 256);
	File_Chooser = gtk_file_chooser_dialog_new (	"Save Project",
							GTK_WINDOW (Window),
							GTK_FILE_CHOOSER_ACTION_SAVE,
							("Cancel"),
							GTK_RESPONSE_CANCEL,
							("Save"),
							GTK_RESPONSE_ACCEPT,
							NULL);
	gtk_widget_destroy (File_Chooser);
}

void open_file (GtkWidget *tabs)
{
	GtkWidget *file_chooser, *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "Open a log file");
	gint _;
	file_chooser = gtk_file_chooser_dialog_new (	"Open a log file",
							GTK_WINDOW (window),
							GTK_FILE_CHOOSER_ACTION_OPEN,
							("_Cancel"),
							GTK_RESPONSE_CANCEL,
							("_Open"),
							GTK_RESPONSE_ACCEPT,
							NULL);
	_ = gtk_dialog_run (GTK_DIALOG (file_chooser));
	if (_ == GTK_RESPONSE_ACCEPT)
	{
		char *filename;
		GtkFileChooser *a = GTK_FILE_CHOOSER (file_chooser);
		filename = gtk_file_chooser_get_filename (a);
		add_text_view (filename, tabs);
		g_free (filename);
	}
	gtk_widget_destroy (file_chooser);
	Parse_Log_Files ();
}

void add_text_view (char *filename, GtkWidget *tabs)
{
	GtkWidget 	*scroll = gtk_scrolled_window_new (NULL, NULL),
			*text,
			*box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*close = gtk_button_new ();
	int *page = new int;
	std::string str = filename, sub = "";
	sub = str.substr (str.rfind ("/", std::string::npos) + 1, std::string::npos);
	*page = gtk_notebook_get_n_pages (GTK_NOTEBOOK (tabs));
	std::ifstream in;
	std::string contents = "";
	std::stringstream buffer;

	if (strcmp ("Blank", gtk_notebook_get_tab_label_text (GTK_NOTEBOOK (tabs), gtk_notebook_get_nth_page (GTK_NOTEBOOK (tabs), 0))) == 0)
	{
		Text_Files.resize (0);
		gtk_notebook_remove_page (GTK_NOTEBOOK (tabs), 0);
	}
	in.open (filename);
	if (in.is_open ())
	{
		buffer << in.rdbuf ();	//copy contents of ifstream buffer to stringstream
		contents = buffer.str ();	//copy contents of stringstream to string
		Text_Files.push_back (gtk_text_buffer_new (NULL));
		gtk_text_buffer_set_text (Text_Files.back(),
					contents.c_str (),
					-1);
	}

	gtk_button_set_always_show_image (GTK_BUTTON (close), TRUE);
	gtk_button_set_image (GTK_BUTTON (close), gtk_image_new_from_icon_name ("window-close", GTK_ICON_SIZE_SMALL_TOOLBAR));
	gtk_box_pack_start (GTK_BOX (box), scroll, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), close, FALSE, TRUE, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (tabs), box, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (tabs), box, sub.c_str());

	text = gtk_text_view_new_with_buffer (GTK_TEXT_BUFFER (Text_Files.back ()));


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

	g_signal_connect_swapped (close, "clicked", G_CALLBACK (remove_page), page);

}

void remove_page (int *page)
{
	if (gtk_notebook_get_n_pages (GTK_NOTEBOOK (TextTabs)) > 1)
	{
		gtk_notebook_remove_page (GTK_NOTEBOOK (TextTabs), *page - 1);
		Text_Files.erase (Text_Files.begin () + *page - 1);
	}
}
