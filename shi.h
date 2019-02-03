#ifndef SHI
#define SHI

#include <gtk/gtk.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

//GUI functions
//"front end" stuff. These are all the primary functions that control
//SHIs behavior. They call all the secondary functions (in the backend
//that perform the underlying processes

void mainwindow ();	//function to start the shi window
void mainwindowactivate (GtkApplication *app);	//actual code to run the shi window
void drawing_area (GtkWidget *area);	//function to run the drawing area
void open_project ();	//open file dialogue for project files
void open_file ();	//open file dialogue for log files
void save_project ();	//save file dialogue for project files
void add_text_view ();	//add a new log file to the view

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

char *Parse_Log_File (char *filename);
const char mfin[] = "abc";

#endif
