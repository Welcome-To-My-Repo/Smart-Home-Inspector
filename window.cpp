#include "shi.h"
#include <fstream>

GtkApplication *MainWindow, *splashwindow;
char *filename, *Log_File;

void splashscreen ()

{

	splashwindow = gtk_application_new ("temp.splash", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (splashwindow, "activate", G_CALLBACK (startsplash), NULL);
	g_application_run (G_APPLICATION (splashwindow), 0, NULL);
	g_object_unref (splashwindow);

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
			*RecentFiles [8],
			*New;

	Window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (Window), "Smart Home Inspector");
	gtk_window_set_decorated (GTK_WINDOW (Window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (Window), 512, 512);
	gtk_window_set_position (GTK_WINDOW (Window), GTK_WIN_POS_CENTER);
	gtk_window_set_resizable (GTK_WINDOW (Window), FALSE);
	gtk_window_set_deletable (GTK_WINDOW (Window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (Window), TRUE);

	Box = 		gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	Image = 	gtk_image_new_from_file ("logo.png");
	Menu = 		gtk_menu_new ();
	MenuButtonCon =	gtk_menu_item_new ();
	MenuButton = 	gtk_button_new_with_label ("Menu");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Recent = 	gtk_menu_item_new_with_label ("Open Project");
	New = 		gtk_menu_item_new_with_label ("New Project");
	QuitButton =	gtk_button_new_with_label ("Quit");

	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), Recent);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), MenuButtonCon);

	gtk_box_pack_start (GTK_BOX (Box), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), Image, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), QuitButton, FALSE, FALSE, 0);

	gtk_container_add (GTK_CONTAINER (Window), Box);
	gtk_container_add (GTK_CONTAINER (MenuButtonCon), MenuButton);

	gtk_box_set_child_packing (GTK_BOX (Box), QuitButton, TRUE, FALSE, 0, GTK_PACK_END);
	gtk_box_set_child_packing (GTK_BOX (Box), MenuBar, TRUE, FALSE, 0, GTK_PACK_START);
	gtk_box_set_child_packing (GTK_BOX (Box), Image, TRUE, FALSE, 0, GTK_PACK_START);

	gtk_box_set_center_widget (GTK_BOX (Box), Image);

	gtk_widget_set_halign (GTK_WIDGET (Menu), GTK_ALIGN_CENTER);
	gtk_widget_set_halign (GTK_WIDGET (MenuBar), GTK_ALIGN_CENTER);
	gtk_widget_set_halign (GTK_WIDGET (QuitButton), GTK_ALIGN_CENTER);

	gtk_box_set_baseline_position (GTK_BOX (MenuBox), GTK_BASELINE_POSITION_CENTER);

	gtk_menu_item_set_submenu (GTK_MENU_ITEM (MenuButtonCon), Menu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (Menu), MenuBox);

	g_signal_connect_swapped (New, "activate", G_CALLBACK (open_file), NULL);
	g_signal_connect_swapped (Recent, "activate", G_CALLBACK (open_project), NULL);
	g_signal_connect_swapped (QuitButton, "clicked", G_CALLBACK (gtk_widget_destroy), Window);


	gtk_widget_show_all (Window);

}

void stopsplash ()

{

	g_application_quit (G_APPLICATION (splashwindow));

}

void mainwindow (char *filename)

{

	MainWindow = gtk_application_new ("org.app.shi", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), NULL);
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);
	g_object_unref (MainWindow);

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

	Window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (Window), "window");
	gtk_window_set_default_size (GTK_WINDOW (Window), 768, 512);

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

	gtk_container_add (GTK_CONTAINER (Window), MainBox);

	gtk_menu_item_set_submenu (GTK_MENU_ITEM (FileButton), FileMenu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (FileMenu), MenuBox);

	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Save);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), SaveAs);
	gtk_menu_shell_append (GTK_MENU_SHELL (FileMenu), Quit);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), FileButton);

	gtk_box_pack_start (GTK_BOX (MenuBox), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), MenuBox, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (MainBox), SecondBox, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), TextDisplay, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (SecondBox), DrawDisplay, TRUE, FALSE, 0);

	gtk_widget_show_all (Window);

	g_signal_connect_swapped (Quit, "activate", G_CALLBACK (gtk_widget_destroy), Window);


}

void drawing_area (GtkWidget *area)

{



}

void open_project ()

{



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

	File_Chooser = gtk_file_chooser_dialog_new ("	Open A Log File",
							GTK_WINDOW (Window),
							GTK_FILE_CHOOSER_ACTION_OPEN,
							("_Cancel"),
							GTK_RESPONSE_CANCEL,
							("Open"),
							GTK_RESPONSE_ACCEPT,
							NULL);

	x = gtk_dialog_run (GTK_DIALOG (File_Chooser));
	if (x == GTK_RESPONSE_ACCEPT)

	{

		char *File_Name;
		GtkFileChooser *Choose = GTK_FILE_CHOOSER (File_Chooser);
		File_Name = gtk_file_chooser_get_filename (Choose);

	}

	gtk_widget_destroy (File_Chooser);
	mainwindow (File_Name);
	g_free (File_Name);

}
