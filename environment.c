#include "environment.h"
#include "variables.h"
#include "paths_handle.h"
#include "file_processing.h"
#include "paths_handle.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


char * path_key="PATH";
char * home_key="HOME";
char * path_value;

void setup_environment( void )
{
    //to handle the last character
    set_pwd();
    path_value=getenv("PATH");
    char *homedir = getenv("HOME");
    set_user_name(homedir);
    set_variable(home_key,homedir);
    set_variable(path_key,path_value);
    set_current_path(homedir);
    open_history_file();
    // you should implement this function
}
