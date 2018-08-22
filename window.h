#ifndef WINDOW
#define WINDOW

#include <gtk/gtk.h>

void mainwindow (int argc, char **argv);
void mainwindowactivate (GtkApplication *app, gpointer user_data);
void print_hello (GtkWidget *widget, gpointer data);
void splashscreen (int argc, char **argv);
void startsplash (GtkApplication *app, gpointer user_data);
void stopsplash ();
void splash_choose_file ();
void set_recent_files_menu (GtkMenu *menu);

#endif
