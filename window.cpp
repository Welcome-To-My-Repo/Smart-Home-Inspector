#include "shi.h"
#include <fstream>
//all the GUI functions are defined in this file
GtkApplication *MainWindow, *splashwindow;		//the global widgets to hold the splash and main windows
char *filename, *Log_File;				//global strings to hold the path and the contents of the inspected logfile
//the main function that starts the GUI. everything else is called
//from this
void splashscreen ()
{
	splashwindow = gtk_application_new ("temp.splash", G_APPLICATION_FLAGS_NONE);	//assign a new wintow to splashscreen
	g_signal_connect (splashwindow, "activate", G_CALLBACK (startsplash), NULL);	//assign signal handler to the "activate" signal
	g_application_run (G_APPLICATION (splashwindow), 0, NULL);			//give the "activate" signal
	g_object_unref (splashwindow);							//de references splashwindow
}

void startsplash (GtkApplication *app)
{
	GtkWidget	*Window,
	 		*Box,
			*Image,
			*QuitButton,
			*Menu,
			*MenuButtonCon,
			*MenuButton,
			*MenuBox,
			*MenuBar,
			*Recent,
			*RecentMenu,
			*RecentBox,
			*RecentFiles [7],
			*New;
//assign new window to Window
	Window = gtk_application_window_new (app);
//set Window properties
	gtk_window_set_title (GTK_WINDOW (Window), "Smart Home Inspector");
	gtk_window_set_decorated (GTK_WINDOW (Window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (Window), 512, 512);
	gtk_window_set_position (GTK_WINDOW (Window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW (Window), FALSE);
	gtk_window_set_deletable (GTK_WINDOW (Window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (Window), TRUE);
//assign elements to other widgets
	Box = 		gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	Image = 	gtk_image_new_from_file ("logo.png");
	Menu = 		gtk_menu_new ();
	MenuButtonCon =	gtk_menu_item_new ();
	MenuButton = 	gtk_button_new_with_label ("Menu");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Recent = 	gtk_menu_item_new_with_label ("Recent Projects");
	New = 		gtk_menu_item_new_with_label ("New Project");
	QuitButton =	gtk_button_new_with_label ("Quit");
//add buttons to menu container
	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), Recent);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), MenuButtonCon);
//add the elements vertically into the window
	gtk_box_pack_start (GTK_BOX (Box), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), Image, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), QuitButton, FALSE, FALSE, 0);
//add menu elements to the window
	gtk_container_add (GTK_CONTAINER (Window), Box);
	gtk_container_add (GTK_CONTAINER (MenuButtonCon), MenuButton);
//set orientation of the areas in the window
	gtk_box_set_child_packing (GTK_BOX (Box), QuitButton, TRUE, FALSE, 0, GTK_PACK_END);
	gtk_box_set_child_packing (GTK_BOX (Box), MenuBar, TRUE, FALSE, 0, GTK_PACK_START);
	gtk_box_set_child_packing (GTK_BOX (Box), Image, TRUE, FALSE, 0, GTK_PACK_START);
//set the element that goes in the center (possibly unnecessary)
	gtk_box_set_center_widget (GTK_BOX (Box), Image);
//center the three main elements in the window
	gtk_widget_set_halign (GTK_WIDGET (Menu), GTK_ALIGN_CENTER);
	gtk_widget_set_halign (GTK_WIDGET (MenuBar), GTK_ALIGN_CENTER);
	gtk_widget_set_halign (GTK_WIDGET (QuitButton), GTK_ALIGN_CENTER);
//center the primary container in the window (possibly unnecessary)
	gtk_box_set_baseline_position (GTK_BOX (MenuBox), GTK_BASELINE_POSITION_CENTER);
//set menu items to show on selection
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (MenuButtonCon), Menu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (Menu), MenuBox);
//create signal handlers to call other functions on button press events
//also set signal handlers to open file chooser dialogues
	g_signal_connect_swapped (New, "activate", G_CALLBACK (open_file), NULL);
	g_signal_connect_swapped (Recent, "activate", G_CALLBACK (open_project), NULL);
	g_signal_connect_swapped (QuitButton, "clicked", G_CALLBACK (gtk_widget_destroy), Window);
//display the elements on the window
	gtk_widget_show_all (Window);
}

void stopsplash ()
{
	g_application_quit (G_APPLICATION (splashwindow));	//destroy the splash window
}

void mainwindow (char *filename)
{
	MainWindow = gtk_application_new ("org.app.shi", G_APPLICATION_FLAGS_NONE);		//creates main window
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), NULL);	//creates signal handler for activating the window
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);				//runs the window
	g_object_unref (MainWindow);								//de references the window
}

void mainwindowactivate (GtkApplication *app, char *filename)
{
	GtkWidget 	*Window,
			*MainBox,
			*SecondBox,
			*TextDisplay,
			*DrawDisplay,
			*FileMenu,
			*FileButton,
			*MenuBox,
			*MenuBar,
			*Open,
			*Save,
			*SaveAs,
			*Quit;
//assign new window to Window
	Window = gtk_application_window_new (app);
//set Window parameters
	gtk_window_set_title (GTK_WINDOW (Window), "window");
	gtk_window_set_default_size (GTK_WINDOW (Window), 768, 512);
//assign elements to other widgets
	MainBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	SecondBox = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	TextDisplay = 	gtk_text_view_new ();
	DrawDisplay = 	gtk_drawing_area_new ();
	FileMenu = 	gtk_menu_new ();
	FileButton = 	gtk_menu_item_new_with_label ("File");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Open = 		gtk_menu_item_new_with_label ("Open Log File");
	Save = 		gtk_menu_item_new_with_label ("Save Project");
	SaveAs = 	gtk_menu_item_new_with_label ("Save Project As");
	Quit = 		gtk_menu_item_new_with_label ("Quit");
//add primary container element to window
	gtk_container_add (GTK_CONTAINER (Window), MainBox);
//add menu elements to menu bar container
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (FileButton), FileMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (FileMenu), MenuBox);
//add menu items to drop down menu
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Save);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), SaveAs);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Quit);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), FileButton);
//add elements to primary container element
	gtk_box_pack_start (GTK_BOX (MenuBox), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), MenuBox, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), SecondBox, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), TextDisplay, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), DrawDisplay, TRUE, FALSE, 0);
//display all elements in window
	gtk_widget_show_all (Window);
//create signal handlers for button press events
	g_signal_connect_swapped (Quit, "activate", G_CALLBACK (gtk_widget_destroy), Window);
	g_signal_connect_swapped (Open, "activate", G_CALLBACK (open_file), NULL);
	g_signal_connect_swapped (SaveAs, "activate", G_CALLBACK (save_project), NULL);
}

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
	mainwindow (filename);
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
	gint x;
	char *File_Name;
	GtkWidget	*Window,
			*File_Chooser;
	Window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (Window), "Open A Log File");
	gtk_window_set_default_size (GTK_WINDOW (Window), 512, 256);
	File_Chooser = gtk_file_chooser_dialog_new (	"Open A Log File",
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
		File_Name = gtk_file_chooser_get_filename (Choose);
	}
	gtk_widget_destroy (File_Chooser);
	mainwindow (File_Name);
	g_free (File_Name);
}
