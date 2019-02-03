#ifndef SHI
#define SHI

#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

static GtkApplication *MainWindow;
static char *filename, *Log_File;
//vector of text buffer for future implementation of loading multiple log files
static std::vector <GtkTextBuffer*> Text_Files;
//default text buffer for loading single log files
static GtkTextBuffer *TextBuffer;

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
void update_text_view (char *filename);	//updates the text view with new log files

//Backend Functions
//none of these functions are used individually or called by
//themselves. these are all used to provide the information to display
//with the GUI functions

char *Parse_Log_File (std::string log);
class smart_dev
{
public:
	smart_dev ();
	~smart_dev ();
	void add_event ();
	int get_event_types ();
	void remove_event (int event_type);
	bool is_active (int event_type);
	float get_event_value (int event_type);
private:
//event_types holds the number of different events a smart device can have
	int event_types = 0;
//event structure with an event_type corresponding to the event number in
//event types, an event_active signal, and a value from the event if it exists
	struct event
	{
		event(int type) {event_type = type;}
		int event_type;
		bool event_active;
		float event_value;
	};
//a vector of the diferent kinds of events.
	std::vector <event> events;
};

#endif
