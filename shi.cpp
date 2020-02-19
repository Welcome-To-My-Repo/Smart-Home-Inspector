#include "shi.h"
//define all the global shit from shi.h...
//wheeee!
GtkApplication *MainWindow;
std::vector <LOG_FILE_DATA> log_files;
//long  int current_time = 0;
bool Playing = false;
GtkAdjustment *current_time;
//look how small and pathetic the main function is. laugh at it with me!
int main (int argc, char **argv)

{
	current_time = gtk_adjustment_new (0, 0, 0, 1, 1, 1);
	gtk_adjustment_set_value (current_time, 0);
//create the application (don't ask me ask the GTK project...)
	MainWindow = gtk_application_new ("app.shi", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), MainWindow);
//start the main app window
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);
	g_object_unref (MainWindow);

//if you don't know this one, go back to school
	return 0;
}
