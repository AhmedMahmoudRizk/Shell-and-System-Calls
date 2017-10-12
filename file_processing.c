#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_processing.h"

FILE * file_name_current;
FILE * file_name ;
FILE * fptr;
FILE * flog;
/*
	history file section
*/

void open_history_file()
{
    char * result = "";
    asprintf(&result, "%s%s", get_pwd(),"historyfile.txt");
    fptr = fopen(result,"a");
    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    // you should implement this function
}

void print_history_file()
{

    open_history_file();
    char line [512];
    char *commandd=fgets(line, 512, (FILE*)fptr);

    while (commandd!=NULL)
    {
        if(commandd ==NULL)
            break;
        commandd=line;
        commandd=fgets(line, 512, (FILE*)fptr);
    }

    close_history_file();

}

void close_history_file()
{
    fclose(fptr);
    // you should implement this function
}


/*
	log file section
*/
void open_log_file()
{

    // you should implement this function
    char * result = "";
    asprintf(&result, "%s%s", get_pwd(),"logfile.txt");
    flog = fopen(result,"a");
    if(flog == NULL)
    {
        printf("Error!");
        exit(1);
    }



}

void log_command()
{
    open_log_file();
    fprintf(flog,"child terminated\n");
    close_log_file();
}


void history_command(char* command)
{
    open_history_file();
    fprintf(fptr,"%s\n",command);
    close_history_file();
}


void close_log_file()
{
    fclose(flog);
    // you should implement this function
}


/*
	CommandsBatch file section
*/
void commands_batch_file(char * file_path)
{
    char * commandd;
    char line[512]="";
    size_t len = 0;
    char * result = "";
    asprintf(&result, "%s%s", get_pwd(),file_path);
    file_name_current = fopen(result, "r");
    if (file_name_current == NULL)
    {
        printf("null file \n");
        exit(EXIT_FAILURE);
    }
    commandd=fgets(line, 512, (FILE*)file_name_current);

    while (commandd!=NULL)
    {
        if(commandd ==NULL)
            break;
        commandd=line;
        parse_command(commandd);
        history_command(commandd);
        commandd=fgets(line, 512, (FILE*)file_name_current);
    }

    fclose(file_name_current);
    // you should implement this function
}

