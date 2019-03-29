class LOG_FILE_DATA
{
public:
	LOG_FILE_DATA ();
	LOG_FILE_DATA (GtkTextBuffer *_);
	~LOG_FILE_DATA ();
	void add_text_file (GtkTextBuffer *_);
	GtkTextBuffer *get_text_file ();

	GtkEntryBuffer *add_year_regex ();
	GtkEntryBuffer *add_month_regex ();
	GtkEntryBuffer *add_day_regex ();
	GtkEntryBuffer *add_hour_regex ();
	GtkEntryBuffer *add_minute_regex ();
	GtkEntryBuffer *add_second_regex ();
	void year_remove_ex (GtkEntryBuffer *expression);
	void month_remove_ex (GtkEntryBuffer *expression);
	void day_remove_ex (GtkEntryBuffer *expression);
	void hour_remove_ex (GtkEntryBuffer *expression);
	void minute_remove_ex (GtkEntryBuffer *expression);
	void second_remove_ex (GtkEntryBuffer *expression);
	void device_remove_ex (GtkEntryBuffer *expression);
	void event_remove_ex (GtkEntryBuffer *expression);
	void state_remove_ex (GtkEntryBuffer *expression);

private:

	struct SYNTAX
	{
		std::vector <GtkEntryBuffer *> 	Year_Regex,
						Month_Regex,
						Day_Regex,
						Hour_Regex,
						Minute_Regex,
						Second_Regex,
						Device_Regex,
						Event_Regex,
						State_Regex;
	};
	struct DATA
	{
		long int start, end;
		struct event
		{
			std::string 	device_name,
					event_name,
					state;
		};
		std::vector <event> events;
	};
	GtkTextBuffer *Text_File = gtk_text_buffer_new (NULL);
	long int current_data = -1;
	std::vector <DATA> data;
	SYNTAX syntax;
};
