#ifndef SHI
#define SHI

#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <regex>
#include <filesystem>
#include "classes.h"

//all global classes initialized here
static shi::smart_network log_file_devices;
static shi::SYNTAX log_file_syntax;
static shi::TIME log_file_time;

#define default_text "There are no log files currently loaded."
static GtkApplication *MainWindow;
static char *filename, *Log_File;
//vector of text buffer for future implementation of loading multiple log files
static std::vector <GtkTextBuffer*> Text_Files;

//GUI functions
//"front end" stuff. These are all the primary functions that control
//SHIs behavior. They call all the secondary functions (in the backend
//that perform the underlying processes

//function to start the main shi window
void mainwindow ();
//actual code to produce the main shi window
void mainwindowactivate (GtkApplication *app);
//function to run the drawing area
void drawing_area (GtkWidget *area);
//open file dialogue for project files
void open_project ();
//open file dialogue for log files
void open_file (GtkWidget *tabs);
//save file dialogue for project files
void save_project ();
//add a new log file to the view
void add_text_view (char *filename, GtkWidget *tabs);
//updates the text view with new log files
void update_text_view (char *filename, GtkWidget *notepad);
//reads the events from the next smallest time segment in the log file
void read_time_segment (shi::smart_dev devlist);
//wrapper on the remove page function for gtk notebooks
void remove_page (int *page);

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

//parses the log files and populates the device classes
//it also calls the gtk parsing dialogue
void Parse_Log_Files ();
//creates the parsing dialogue window
void Parse_Log_Files_window (GtkApplication *dialogue);
//adds new expression entry box to the parse log file window
void add_entry_box (GtkWidget *container);
//removes an entry box from the parse log file window
void remove_expression (GtkWidget *container);
//adds new "custom" tab to the parse log file window
void add_custom_page (GtkWidget *notebook);

#endif
