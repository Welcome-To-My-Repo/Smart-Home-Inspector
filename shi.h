#ifndef SHI
#define SHI

#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>

//GUI functions

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

//Backend Functions

char *Parse_Log_File (char *filename);

#endif
