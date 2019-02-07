#include "shi.h"

//main function to parse the log file
void Parse_Log_Files ()
{
	//initialize and activate parse log file dialogue window
	GtkApplication *dialogue = gtk_application_new ("app.shi.syntax_dialogue", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (dialogue, "activate", G_CALLBACK (Parse_Log_Files_window), dialogue);
	g_application_run (G_APPLICATION (dialogue), 0, NULL);
	g_object_unref (dialogue);
}

void read_time_segment (shi::smart_dev devlist)
{

}

void add_entry_box (GtkWidget *container)
{
	GtkWidget *sidebox, *closebutton, *entry;
	sidebox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	closebutton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));

	gtk_box_pack_start (GTK_BOX (sidebox), closebutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (sidebox), entry, TRUE, TRUE, 0);

	gtk_box_pack_start (GTK_BOX (container), sidebox, TRUE, FALSE, 0);

	g_signal_connect_swapped (closebutton, "clicked", G_CALLBACK (gtk_widget_destroy), sidebox);
	g_signal_connect (entry, "destroy", G_CALLBACK (remove_expression), entry);

	gtk_widget_show_all (container);
}

void remove_expression (GtkWidget *entry)
{
	std::string expression = "";
	expression.append (gtk_entry_buffer_get_text (GTK_ENTRY_BUFFER (gtk_entry_get_buffer (GTK_ENTRY (entry)))));
	//std::cout << "Remove Expression Called!" << std::endl;
	//std::cout << expression << std::endl;
	log_file_syntax.remove_expression (expression);
}

void add_custom_page (GtkWidget *notebook)
{
	//add new custom page to notebook
}

void Parse_Log_Files_window (GtkApplication *dialogue)
{
	GtkWidget	*Window = gtk_application_window_new (dialogue),
			*BigBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*Notebook = gtk_notebook_new (),
			*NotebookEndAction = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0),
			*AddCustomTabButton = gtk_button_new_with_label ("Add Custom"),
			*DeleteCustomTabButton = gtk_button_new_with_label ("Erase Custom"),
			*Apply_button = gtk_button_new_from_icon_name ("gtk-apply", GTK_ICON_SIZE_SMALL_TOOLBAR),
			*NotebookTabBox,
			*SectionBox,
			*AddExpressionButton,
			*EntryScrolledBox,
			*EntryViewport,
			*EntryViewportBox,
			*EntryContainer,
			*DeleteEntryButton,
			*Entry,
			*SecondEntry,
			*Close_image,
			*Radio_is_Device,
			*Radio_is_Event,
			*Radio_is_State;

	Radio_is_Device = gtk_radio_button_new_with_label (NULL, "Device Syntax");
	Radio_is_Event = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (Radio_is_Device), "Event Syntax");
	Radio_is_State = gtk_radio_button_new_with_label_from_widget (GTK_RADIO_BUTTON (Radio_is_Device), "State Syntax");

	gtk_container_add (GTK_CONTAINER (Window), BigBox);
	gtk_box_pack_start (GTK_BOX (NotebookEndAction), AddCustomTabButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookEndAction), DeleteCustomTabButton, FALSE, FALSE, 0);
	gtk_notebook_set_action_widget (GTK_NOTEBOOK (Notebook), NotebookEndAction, GTK_PACK_END);
	gtk_box_pack_start (GTK_BOX (BigBox), Notebook, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (BigBox), Apply_button, TRUE, FALSE, 0);
	g_signal_connect_swapped (Apply_button, "clicked", G_CALLBACK (gtk_widget_destroy), Window);

//make Time Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Time Notation");

//Add Date/Time Format section
	AddExpressionButton = gtk_button_new_with_label ("Add Date/Time Format");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Bounding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Preceding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Following Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//make Device Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Notation");

//Add Declarative Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Declarative Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Keywords section
	AddExpressionButton = gtk_button_new_with_label ("Add Keywords");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Bounding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Preceding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Preceding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Following Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Following Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//make Event Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Notation");

//Add Declarative Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Declarative Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Keywords section
	AddExpressionButton = gtk_button_new_with_label ("Add Keywords");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Bounding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Preceding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Preceding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Following Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Following Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//make State Notation tab
	NotebookTabBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (Notebook), NotebookTabBox, NULL);
	gtk_notebook_set_tab_label_text (GTK_NOTEBOOK (Notebook), NotebookTabBox, "Device Notation");

//Add Declarative Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Declarative Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Keywords section
	AddExpressionButton = gtk_button_new_with_label ("Add Keywords");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Bounding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Bounding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Preceding Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Preceding Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

//Add Following Expression section
	AddExpressionButton = gtk_button_new_with_label ("Add Following Expression");
	SectionBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), AddExpressionButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (NotebookTabBox), SectionBox, TRUE, FALSE, 0);
	EntryScrolledBox = gtk_scrolled_window_new (NULL, NULL);
	EntryViewport = gtk_viewport_new (NULL, NULL);
	EntryViewportBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_box_pack_start (GTK_BOX (SectionBox), EntryScrolledBox, TRUE, TRUE, 0);
	gtk_container_add (GTK_CONTAINER (EntryScrolledBox), EntryViewport);
	gtk_container_add (GTK_CONTAINER (EntryViewport), EntryViewportBox);
	EntryContainer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	DeleteEntryButton = gtk_button_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_SMALL_TOOLBAR);
	Entry = gtk_entry_new_with_buffer (gtk_entry_buffer_new (NULL, -1));
	gtk_box_pack_start (GTK_BOX (EntryViewportBox), EntryContainer, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), DeleteEntryButton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (EntryContainer), Entry, TRUE, TRUE, 0);
	g_signal_connect_swapped (AddExpressionButton, "clicked", G_CALLBACK (add_entry_box), EntryViewportBox);
	g_signal_connect_swapped (DeleteEntryButton, "clicked", G_CALLBACK (gtk_widget_destroy), EntryContainer);
	g_signal_connect (Entry, "destroy", G_CALLBACK (remove_expression), Entry);

	gtk_widget_show_all (Window);
}
