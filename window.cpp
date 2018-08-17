#include "window.h"

void mainwindowactivate (GtkApplication *app, gpointer user_data)

{

	GtkWidget *window;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);
	gtk_widget_show_all (window);

}

void mainwindow (int argc, char **argv)

{

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtkk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (mainwindowactivate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

}

void startsplashscreen (splash a)

{

	GtkWidget *window = a.splash, *image = a.image;
	const char *image_name = "logo.png";
	int width = 500, height = 500;

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_size_request (window, width, height);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);

	image = gtk_image_new_from_file (image_name);
	gtk_container_add (GTK_CONTAINER (window), image);

	gtk_widget_show_all (window);
	gtk_main ();

}

void quitsplashscreen (splash a)

{

	gtk_widget_destroy (a.splash);
	gtk_main_quit ();

}
