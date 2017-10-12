#include "environment.h"
#include "commands.h"
#include "file_processing.h"
#include "variables.h"
#include "command_parser.h"
#include "paths_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

typedef enum { false = 0 , true = 1 } bool ;

void start(bool read_from_file,char *file_name);
void shell_loop(bool input_from_file,char *file_name);

int main(int argc, char *argv[])
{
    signal(SIGCHLD,log_command);
    setup_environment();

    // any other early configuration should be here
    int i;
    char *file_path_1;
    if(argc== 1 ||argc == 2)
    {
        if( argc == 2 )
        {
            file_path_1=argv[1];
            start(true,file_path_1);
        }
        else
        {
            start(false,file_path_1);
        }
    }
    return 0;
}

char * cd_add()
{
    char * shell="cd ";
    char *temp;
    asprintf(&temp, "%s%s", shell, get_current_path());
    return temp;
}


void start(bool read_from_file,char* file_path)
{
    char *home_directory=cd_add();
    cd(home_directory); // let shell starts from home
    if(read_from_file)
    {
        // file processing functions should be called from here

        shell_loop(true,file_path);
    }
    else
    {
        shell_loop(false,file_path);
    }
}

void print_shell()
{

    char * shell="Shell:";
    char *temp;
    asprintf(&temp, "%s%s", shell, get_current_path());
    size_t len = strlen(temp);
    char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
    strcpy(str2, temp);
    strcat(str2,">>\0");
    printf("%s",str2);
}

void shell_loop(bool input_from_file,char *file_path)
{
    bool from_file = input_from_file;

    if(from_file)
    {
        //read next instruction from file
        commands_batch_file(file_path);
    }
    else
    {
        while(exit_detection())
        {

            char commanddd[512];
            print_shell();
            if(feof(stdin))
            {
                exit(0);
            }
            scanf("%[^\n]",commanddd) ;
            getchar();
            char * command=commanddd;
            parse_command(command);
            history_command(command);
            memset(command, 0, 512);

        }

        //parse your command here

        //execute your command here
    }
}
/*
	you don't need to write all logic here, a better practice is to call functions,
	each one contains a coherent set of logical instructions
*/
