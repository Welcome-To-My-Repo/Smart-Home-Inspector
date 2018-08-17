#ifndef WINDOW
#define WINDOW

#include <gtk/gtk.h>
#include <unistd.h>

struct splashscreen

{

	GtkWidget *y, *z;

};

void splash (splashscreen a);
void quitsplash (splashscreen a);
void mainwindow ();

#endif
