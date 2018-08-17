#include "window.h"

void splash (splashscreen a)

{

	const char *image_name = "logo.png";
	int time = 3;
	int width = 500, height = 500;
	GtkWidget *image = a.y, *window = a.z;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  	gtk_widget_set_size_request (window, width, height);
  	gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
  	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
  	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  	image=gtk_image_new_from_file(image_name);
  	gtk_container_add(GTK_CONTAINER(window), image);
  	gtk_widget_show_all (window);
  	gtk_main ();


}

void quitsplash (splashscreen a)

{

	GtkWidget *window = a.z;
	gtk_widget_destroy (window);
	gtk_main_quit ();

}
