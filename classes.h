//avoid namespace collisions
namespace shi
{

	struct DEVICE_STATS
	{
		std::string
			device_name,
			device_event_name,
			device_state;
	};

	struct SEGMENT_POS
	{
		long int start, end;
	};

	class LOG_FILE_STATS
	{
	public:
		LOG_FILE_STATS ();
		~LOG_FILE_STATS ();
		void set_time (std::string _);
		void add_device_stats_node (DEVICE_STATS _);
		void add_segment_pos (SEGMENT_POS _);

	private:
		std::string time;
		std::vector <DEVICE_STATS> device_stats;
		std::vector <SEGMENT_POS> segment_pos;
		std::vector <GtkTextBuffer> log_files;
	};

	class LOG_FILES
	{
		friend class LOG_FILE_STATS;
	public:
		LOG_FILES ();
		~LOG_FILES ();
		void add_log_file_stats (LOG_FILE_STATS _);
		void remove_log_file_stats (int a);
	private:
		std::vector <LOG_FILE_STATS> log_file_stats;

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
