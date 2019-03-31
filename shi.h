#ifndef SHI
#define SHI

#include <gtk/gtk.h>

#include <boost/regex.hpp>

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
static std::vector <LOG_FILE_DATA> log_files;

#define default_text "There are no log files currently loaded."
//global application
static GtkApplication *MainWindow;
//made these global, not sure why anymore
static char *filename, *Log_File;
//vector of text buffer for future implementation of loading multiple log files
static std::vector <GtkTextBuffer*> Text_Files;


//GUI functions
//"front end" stuff. These are all the primary functions that control
//SHIs behavior. They call all the secondary functions (in the backend
//that perform the underlying processes

//produces main window
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
void read_time_segment ();
//wrapper on the remove page function for gtk notebooks
void remove_page (void *page);

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

//parses the log files and populates the device classes
//it also calls the gtk parsing dialogue
void set_regular_expressions (int *pos);
//creates the parsing dialogue window
void set_regex_window (void *_);
//adds new expression entry box to the parse log file window
void add_entry_box (GtkWidget *container);
//removes an entry box from the parse log file window
void remove_expression (GtkWidget *entry);
//adds new "custom" tab to the parse log file window
void add_custom_page (GtkWidget *notebook);
//add entry boxes for syntax types:
void add_entry_box_regex (void *_);

//remove entries from deleted entry boxes:
void remove_entry_regex (void *a);

//functions to highlight text buffers:
//creates a giant list of all events correlated to the time across all log files
void initialize_log_file_stats ();
//sorts all the times in chronological order
void sort_times();
//moves iterator to next time and adjusts UI accordingly
void move_time_forward ();
//moves iterator to previous time and adjusts UI accordingly
void move_time_backward ();

//creates error window
void error_window (char *error_string);

#endif
