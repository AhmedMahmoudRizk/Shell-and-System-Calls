#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
char current_path[1024];
char * user;

char * pwd;
char buffer[500];
FILE * output;

char *get_current_path()
{

    return current_path;

}

void set_current_path(char *path_handled)
{
    memset(current_path,0,1024);
    strncpy(current_path,path_handled,512);
}



void set_pwd()
{

    output = popen("/bin/pwd", "r");
    pwd = fgets(buffer, sizeof(buffer), output);
    int len=strlen(pwd);
    pwd[len-1]='/';

}

void set_user_name(char *homedir)
{

    char str[512];
    strncpy(str,homedir,512);
    char **ress=NULL;
    char* p = strtok (str, "/");
    int n_spaces = 0,i;
    while (p)
    {
        ress = realloc (ress, sizeof (char*) * ++n_spaces);
        if (ress == NULL)
            exit (-1); /* memory allocation failed */

        ress[n_spaces-1] = p;
        p = strtok (NULL, "/");
    }

    /* realloc one extra element for the last NULL */
//
    ress = realloc (ress, sizeof (char*) * (n_spaces+1));
    ress[n_spaces] = 0;

    user=ress[1];


}
char * user_name()
{
    return user;
}

char * get_pwd()
{
    return pwd;
}


