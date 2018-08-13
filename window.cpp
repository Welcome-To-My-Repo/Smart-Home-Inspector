#include "window.h"

void SplashScreen (int a, char **b)

{

	GtkWidget *display, *spash;
	window - gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (window, width, height);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

	image = gtk_image_new_from_file ("logo.png");
	gtk_container_add (GTK_CONTAINER (window), image);
	gtk_widget_show_all (window);
	g_timeout_add (3, kill_splash, window);
	gtk_main ();


}

gboolean kill_splash (gpointer a)

{

	gtk_widget_destroy ((GtkWidget*) data);
	gtk_main_quit ();
	return (FALSE);

}

void MainWindow ()

{

}
