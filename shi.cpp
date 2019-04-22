#include "shi.h"
//define all the global shit from shi.h...
//wheeee!
std::vector <LOG_FILE_DATA> log_files;
//long  int current_time = 0;
gtk_adjustmetn_set_value (&current_time, 0);
bool Playing = false;
/*
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
	*Inspect = 	gtk_menu_item_new_with_label ("Inspect Log Files"),
	*Playbar = 	gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0),
	*PlayScrubber,
	*PlayButton = 	gtk_button_new_from_icon_name ("gtk-media-play", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*StopButton = 	gtk_button_new_from_icon_name ("gtk-media-stop", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipLeft = 	gtk_button_new_from_icon_name ("gtk-media-rewind", GTK_ICON_SIZE_SMALL_TOOLBAR),
	*SkipRight = 	gtk_button_new_from_icon_name ("gtk-media-forward", GTK_ICON_SIZE_SMALL_TOOLBAR);
GtkAdjustment *ScrubberAdjustment = gtk_adjustment_new (0, 0, 100, 1, 1, 1);
*/

//look how small and pathetic the main function is. laugh at it with me!
int main (int argc, char **argv)

{
//create the application (don't ask me ask the GTK project...)
	GtkApplication *MainWindow = gtk_application_new ("app.shi", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), MainWindow);
//start the main app window
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);
	g_object_unref (MainWindow);

//if you don't know this one, go back to school
	return 0;
}
