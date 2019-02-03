#include "shi.h"
#include <fstream>
/*
GtkApplication *MainWindow;
char *filename, *Log_File;
std::vector <GtkTextBuffer*> Text_Files;	//a vecotr of buffers so that in the
						//future multiple text files can be
						//chosen
GtkTextBuffer *TextBuffer;	//default text buffer until multiple log files
				//has been implemented
*/
void mainwindow ()
{
	MainWindow = gtk_application_new ("org.app.shi", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), NULL);
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);
	g_object_unref (MainWindow);
}

void mainwindowactivate (GtkApplication *app)
{
	GtkWidget 	*Window,
			*MainBox,
			*SecondBox,
			*Scrollbox,
			*TextDisplay,
			*Tabs,
			*DrawDisplay,
			*DevList,
			*FileMenu,
			*FileButton,
			*MenuBox,
			*MenuBar,
			*Open,
			*Save,
			*SaveAs,
			*MenuSeparator,
			*Quit;
//assign new window to Window
	Window = gtk_application_window_new (app);
//set Window parameters
	gtk_window_set_title (GTK_WINDOW (Window), "window");
	gtk_window_set_default_size (GTK_WINDOW (Window), 1536, 1024);
//assign elements to other widgets
	MainBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	SecondBox = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	TextDisplay = 	gtk_text_view_new_with_buffer (GTK_TEXT_BUFFER (TextBuffer));
	Scrollbox = 	gtk_scrolled_window_new (NULL, NULL);
	DrawDisplay = 	gtk_drawing_area_new ();
	FileMenu = 	gtk_menu_new ();
	FileButton = 	gtk_menu_item_new_with_label ("File");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Open = 		gtk_menu_item_new_with_label ("Open Log File");
	Save = 		gtk_menu_item_new_with_label ("Save Project");
	SaveAs = 	gtk_menu_item_new_with_label ("Save Project As");
	MenuSeparator =	gtk_separator_menu_item_new ();
	Quit = 		gtk_menu_item_new_with_label ("Quit");
//set text view properties
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (TextDisplay), false);
	gtk_text_view_set_editable (GTK_TEXT_VIEW (TextDisplay), false);
	gtk_text_view_set_accepts_tab (GTK_TEXT_VIEW (TextDisplay), false);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (TextDisplay), GTK_WRAP_NONE);
	gtk_text_view_set_monospace (GTK_TEXT_VIEW (TextDisplay), GTK_WRAP_NONE);
	gtk_text_view_set_justification (GTK_TEXT_VIEW (TextDisplay), GTK_JUSTIFY_LEFT);
	gtk_scrollable_set_vscroll_policy (GTK_SCROLLABLE (TextDisplay), GTK_SCROLL_NATURAL);
	gtk_scrollable_set_hscroll_policy (GTK_SCROLLABLE (TextDisplay), GTK_SCROLL_NATURAL);
	TextBuffer = gtk_text_buffer_new (NULL);
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER (TextBuffer),
					"There are no log files currently loaded",
					-1);
	gtk_text_view_set_buffer (GTK_TEXT_VIEW (TextDisplay), GTK_TEXT_BUFFER (TextBuffer));
//add primary container element to window
	gtk_container_add (GTK_CONTAINER (Window), MainBox);
	gtk_container_add (GTK_CONTAINER (Scrollbox), TextDisplay);
//add menu elements to menu bar container
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (FileButton), FileMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (FileMenu), MenuBox);
//add menu items to drop down menu
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Save);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), SaveAs);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), MenuSeparator);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Quit);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), FileButton);
//add elements to primary container element
	gtk_box_pack_start (GTK_BOX (MenuBox), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), MenuBox, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), SecondBox, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), Scrollbox, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), gtk_separator_new (GTK_ORIENTATION_VERTICAL), false, false, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), DrawDisplay, TRUE, TRUE, 0);
//box child packing settings
	gtk_box_set_child_packing (GTK_BOX (MainBox), SecondBox, true, true, 0, GTK_PACK_START);
	gtk_box_set_child_packing (GTK_BOX (SecondBox), Scrollbox, TRUE, TRUE, 0, GTK_PACK_START);
	//gtk_box_set_child_packing (GTK_BOX (SecondBox), TextDisplay, true, true, 5, GTK_PACK_START);
	//gtk_box_set_child_packing (GTK_BOX (SecondBox), DrawDisplay, true, true, 5, GTK_PACK_START);
//create signal handlers for button press events
	g_signal_connect_swapped (Quit, "activate", G_CALLBACK (gtk_widget_destroy), Window);
	g_signal_connect_swapped (Open, "activate", G_CALLBACK (open_file), NULL);
	g_signal_connect_swapped (SaveAs, "activate", G_CALLBACK (save_project), NULL);
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

void open_file ()
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
		update_text_view (filename);
		g_free (filename);
	}
	gtk_widget_destroy (file_chooser);
}

void update_text_view (char *filename)
{
	std::ifstream in;
	std::string contents = "";
	std::stringstream buffer;
	in.open (filename);
	if (in.is_open ())
	{
		buffer << in.rdbuf ();	//copy contents of ifstream buffer to stringstream
		contents = buffer.str ();	//copy contents of stringstream to string
		gtk_text_buffer_set_text (GTK_TEXT_BUFFER (TextBuffer),
					contents.c_str (),
					-1);
	}
}
