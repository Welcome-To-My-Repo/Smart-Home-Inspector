#include "shi.h"
std::vector <LOG_FILE_DATA> log_files;
long  int current_time = 0;
bool Playing = false;
int main (int argc, char **argv)

{
	GtkApplication *MainWindow = gtk_application_new ("app.shi", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (MainWindow, "activate", G_CALLBACK (mainwindowactivate), MainWindow);
	g_application_run (G_APPLICATION (MainWindow), 0, NULL);
	g_object_unref (MainWindow);

	return 0;
}
