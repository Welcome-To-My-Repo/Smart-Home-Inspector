#ifndef SHI
#define SHI

#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>

//GUI functions
//"front end" stuff. These are all the primary functions that control
//SHIs behavior. They call all the secondary functions (in the backend
//that perform the underlying processes

void mainwindow (char *filename);
void mainwindowactivate (GtkApplication *app, gchar *filename);
void print_hello (GtkWidget *widget, gpointer data);
void splashscreen ();
void startsplash (GtkApplication *app);
void stopsplash ();
void splash_choose_file ();
void drawing_area (GtkWidget *area);
void open_project ();
void open_file ();
void save_project ();

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

char *Parse_Log_File (char *filename);
const char mfin[] = "abc";

#endif
