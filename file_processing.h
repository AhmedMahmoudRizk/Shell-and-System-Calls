#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_

//FILE *fptr;
/*
	history file basic functions' prototypes
*/
void open_history_file();
//FILE* get_history_file();
void close_history_file();
void print_history_file();
/*
	log file basic functions' prototypes
*/
void open_log_file();
void log_command();
//FILE* get_log_file();
void close_log_file();

/*
	CommandsBatch file basic functions' prototypes
*/
//void open_commands_batch_file(char *file_name_path);
//FILE* get_commands_batch_file();
void commands_batch_file(char * file_path);
//void close_commands_batch_file();


#endif // FILE_PROCESSING_H_
