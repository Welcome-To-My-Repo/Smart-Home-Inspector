#include "window.h"
#include <fstream>

GtkApplication *MainWindow, *splashwindow;

void splashscreen (int argc, char **argv)

{

	splashwindow = gtk_application_new ("temp.splash", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (splashwindow, "activate", G_CALLBACK (startsplash), NULL);
	g_application_run (G_APPLICATION (splashwindow), argc, argv);
	g_object_unref (splashwindow);

}

void startsplash (GtkApplication *app, gpointer user_data)

{
	GtkWidget	*Window,
	 		*Box,
			*Image,
			*QuitButton,
			*Menu,
			*MenuButton,
			*MenuBox,
			*MenuBar,
			*Open,
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
	MenuButton = 	gtk_menu_item_new_with_label ("Menu");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Recent = 	gtk_menu_item_new_with_label ("Recent Projects");
	New = 		gtk_menu_item_new_with_label ("New");
	Open = 		gtk_menu_item_new_with_label ("Open");
	QuitButton =	gtk_button_new_with_label ("Quit");

	gtk_container_add (GTK_CONTAINER (Window), Box);

	gtk_menu_item_set_submenu (GTK_MENU_ITEM (MenuButton), Menu);
	gtk_menu_button_set_popup (GTK_MENU_BUTTON (Menu), MenuBox);

	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), New);
	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), Open);
	gtk_menu_shell_append (GTK_MENU_SHELL (Menu), Recent);
	gtk_menu_shell_append (GTK_MENU_SHELL (MenuBar), MenuButton);

	gtk_box_pack_start (GTK_BOX (Box), MenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), Image, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (Box), QuitButton, FALSE, FALSE, 0);

	g_signal_connect_swapped (New, "activate", G_CALLBACK (mainwindow), NULL);
	g_signal_connect_swapped (QuitButton, "clicked", G_CALLBACK (gtk_widget_destroy), Window);


	gtk_widget_show_all (Window);

}

void stopsplash ()

{

	g_application_quit (G_APPLICATION (splashwindow));

}

void set_recent_files_menu (GtkMenu *menu)

{

	/*
	(GtkWidget *recentfiles [7];
	for (int i = 0; i < 7; i ++)

	{

		recentfiles [i] = gtk_menu_item_new_with_label ("Hello World!");
		gtk_menu_attach (menu, recentfiles [i], -1, -1, -1, -1);

	}
	*/
	GtkWidget *recentfile;
	recentfile = gtk_menu_item_new_with_label ("recent file");
	gtk_menu_attach (menu, recentfile, 1, 1, 1, 1);

}

void mainwindow (int argc, char **argv)

{

	MainWindow = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), NULL);
	g_application_run (G_APPLICATION (MainWindow), argc, argv);
	g_object_unref (MainWindow);

}

void mainwindowactivate (GtkApplication *app, gpointer user_data)

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
	gtk_window_set_default_size (GTK_WINDOW (Window), 700, 500);

	MainBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	SecondBox = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	TextDisplay = 	gtk_text_view_new ();
	DrawDisplay = 	gtk_drawing_area_new ();
	FileMenu = 	gtk_menu_new ();
	FileButton = 	gtk_menu_item_new_with_label ("File");
	MenuBox = 	gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	MenuBar = 	gtk_menu_bar_new ();
	Open = 		gtk_menu_item_new_with_label ("Open");
	Save = 		gtk_menu_item_new_with_label ("Save");
	SaveAs = 	gtk_menu_item_new_with_label ("Save As");
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
