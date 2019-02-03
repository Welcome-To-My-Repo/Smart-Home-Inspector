#include "shi.h"
#include <fstream>

GtkApplication *MainWindow;
char *filename, *Log_File;
std::vector <GtkTextBuffer> Text_Files;	//a vecotr of buffers so that in the
					//future multiple text files can be
					//chosen
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
	g_free (File_Name);
}
