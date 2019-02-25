//avoid namespace collisions
namespace shi
{

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
	//a std::vector of the diferent kinds of events.
		std::vector <event> events;
	};

	class smart_network
	{
	public:
		smart_network ();
		~smart_network ();
	private:
		std::vector <smart_dev> devices;
	};

	struct TIME
	{
		std::string current_time, earliest_time, latest_time;
		TIME ();
		~TIME ();
		bool operator > (TIME a);
		bool operator < (TIME a);
		bool operator = (TIME a);
		void operator ++ (int);
		void operator -- (int);


	};
	void TIMEsetvalue (int *a);

	class SYNTAX
	{
	public:
		SYNTAX ();
		~SYNTAX ();

		void time_remove_format (GtkEntryBuffer *expression);
		void time_remove_ex (GtkEntryBuffer *expression);
		void device_remove_ex (GtkEntryBuffer *expression);
		void event_remove_ex (GtkEntryBuffer *expression);
		void state_remove_ex (GtkEntryBuffer *expression);

		std::vector <GtkEntryBuffer *> 	Time_Format,
						Time_Regex,
						Device_Regex,
						Event_Regex,
						State_Regex;
	};

};
