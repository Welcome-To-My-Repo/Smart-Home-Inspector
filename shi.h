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
//class to manage smart devices and associated events
class smart_dev
{
public:
	smart_dev ();
	~smart_dev ();
	void add_event (std::string name);
	int get_event_types ();
	void remove_event (std::string name);
	void remove_event (int event_type);
	bool is_active (std::string name);
	bool is_active (int event_type);
	float get_event_value (std::string name);
	float get_event_value (int event_type);
private:
//event_types holds the number of different events a smart device can have
	int event_types = 0;
//name of device
	std::string device_name;
//event structure with an event_type corresponding to the event number in
//event types, an event_active signal, and a value from the event if it exists
	struct event
	{
		event(std::string name) {event_name = name;}
		std::string event_name = "";
		bool event_active = false;
		float event_value = 0;
	};
//a vector of the diferent kinds of events.
	std::vector <event> events;
};

class smart_network
{
public:
	smart_network ();
	~smart_network ();
private:
	std::vector <smart_dev> devices;
}

struct TIME
{
	int	day = 0,
		month = 0,
		year = 0,
		hour = 0,
		minute = 0,
		second = 0;
}

class SYNTAX
{
public:
	SYNTAX ();
	~SYNTAX ();
private:
//vector of
}

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
void read_time_segment (smart_dev devlist);
//wrapper on the remove page function for gtk notebooks
void remove_page (int *page);

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

//parses the log files and populates the device classes
//it also calls the gtk parsing dialogue
void Parse_Log_File (std::string log);
//creates the parsing dialogue window
void Parse_Log_File_window ();


#endif
