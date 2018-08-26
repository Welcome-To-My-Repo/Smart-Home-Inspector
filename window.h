#ifndef WINDOW
#define WINDOW

#include <gtk/gtk.h>

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

#endif
