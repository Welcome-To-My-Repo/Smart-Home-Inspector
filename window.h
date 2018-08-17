#include <gtk/gtk.h>

void mainwindow (int argc, char **argv);
void mainwindowactivate (GtkApplication *app, gpointer user_data);

//compiles but segfaults don't use
struct splash { GtkWidget *splash, *image; };
void startsplashscreen (splash a);
void quitsplashscreen (splash a);
