#include "commands.h"
#include "variables.h"
#include "paths_handle.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>


char a[1024];
char *delta_handel(char * dr)
{
    int i=0,string_size=strlen(dr);
    char *message="";
    char *var="";
    int delta=0;
    int d=0;
    int dd=0;
    for(i=0; i<string_size; i++)
    {
        char current=dr[i];
        if(current=='~')
        {
            delta=1;
            d=i;
            char *temp=lookup_variable("HOME");
            char * result = "";
            asprintf(&result, "%s%s", message, temp);
            size_t len = strlen(result);
            message=malloc(len);
            strcpy(message,result);
            continue;
        }
        else if(!delta||(delta&&dr[d+1]=='/'))
        {
            size_t len = strlen(message);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, message);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            message=malloc(len);
            strcpy(message,str2);
            continue;
//            last=current;
        }
        else if( delta&&dr[d+1]!='/')
        {
            dd=1;
            size_t len = strlen(var);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, var);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            var=malloc(len);
            strcpy(var,str2);
        }
    }
    if(dd)
    {

        if(checker(var,user_name()))
        {
            return message;
        }
        else
        {
            char * result = "";
            asprintf(&result, "%s%s", message, var);
            return result;
        }
    }
    return message;

}
void cd( char* path )
{
    // you should implement this function
    int string_size=strlen(path);
    if(string_size==2)
    {
        char *path_home=lookup_variable("HOME");
        chdir(path_home);
        set_current_path(path_home);
        return;
    }
    char **ress=NULL;
    char str[512];
    strncpy(str,path,512);
    char* p = strtok (str, " ");
    int n_spaces = 0,i;
    while (p)
    {
        ress = realloc (ress, sizeof (char*) * ++n_spaces);

        if (ress == NULL)
            exit (-1); /* memory allocation failed */

        ress[n_spaces-1] = p;
        p = strtok (NULL, " ");
    }

    if(n_spaces>2)
    {
        return;
    }

    char *t=ress[1];
//    printf("%s \n",t);
    char * dr=delta_handel(t);
    chdir(dr);
    getcwd(a,sizeof(a));
    char *aa=a;
    set_current_path(aa);
    memset(a,0,1024);
}

void variables_handle(char *commannd)
{
    int error=0;
    int string_size;
    int i=0;
    char str[512];
    strncpy(str,commannd,512);
    char* p = strtok (str, "=");
    int n_spaces = 0;
    string_size=strlen(p);
    int first_space=0;
    char *key_ch="";
    char *value_ch="";
    int detectk=0;
    char current;
    int end=0;
    for(i=0; i<string_size; i++)
    {
        current=commannd[i];
        if(current==' '&&detectk)
        {
            end=1;
            continue;
        }
        if(current==' '&&!detectk)
            continue;

        else if(current!=' '&&!end)
        {
            detectk=1;
            size_t len = strlen(key_ch);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, key_ch);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            key_ch=malloc(len);
            strcpy(key_ch,str2);
        }
        else if(current!=' '&&end)
        {
            error =1;
            break;
        }
    }

    if(error)
    {
        perror("Error printed by perror");
        return;
        //step detect error in parce
    }
    i=strlen(p)+1;
    string_size=strlen(commannd);
    detectk=0;
    end=0;
    int quotes=0;
    for(i; i<string_size; i++)
    {
        current=commannd[i];
        if(quotes)
        {
            if(current =='"')
            {
                quotes=0;
                continue;
            }
            else
            {
                size_t len = strlen(value_ch);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, value_ch);
                str2[len] = current;
                str2[len + 1] = '\0';
                len = strlen(str2);
                value_ch=malloc(len);
                strcpy(value_ch,str2);
                continue;
            }
        }

        if(current==' '&&detectk)
        {
            end=1;
            continue;
        }

        if(current==' '&&!detectk)
            continue;

        if(current=='"'&&!end)
        {
            detectk=1;
            quotes=1;
            continue;
        }
        else if(current!=' '&&!end)
        {
            detectk=1;
            size_t len = strlen(value_ch);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, value_ch);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            value_ch=malloc(len);
            strcpy(value_ch,str2);
        }
        else if(current!=' '&&end)
        {
            error =1;
            break;
        }
    }
    if(error)
    {
        return ;
//step detect error in parce
    }
    set_variable(key_ch,value_ch);
}

void echo(char* p )
{
    int i=0;

    char last='0';
    char *message="";
    int number=0;
    int quotes=0;
    int dollarsignmode=0;
    char *var="";
    int string_size=strlen(p);
    for(i=4; i<string_size; i++)
    {
        char  current=p[i];
        if(quotes)
        {
            if(current == '$')
            {
                dollarsignmode=1;
                continue;
            }
            else if(current =='"')
            {
                quotes=0;
                dollarsignmode=0;
                var="";
                continue;
            }
            else if(current!='$'&&!dollarsignmode)
            {
                size_t len = strlen(message);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, message);
                str2[len] = current;
                str2[len + 1] = '\0';
                len = strlen(str2);
                message=malloc(len);
                strcpy(message,str2);
                last=current;
                continue;
            }
            else if(dollarsignmode &&
                    (current==' '||current=='/'||
                     current=='*'||current=='+'||
                     current=='-'))
            {
                char *temp=lookup_variable(var);
                size_t len = strlen(temp);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, temp);
                str2[len] = current;
                str2[len + 1] = '\0';
                len = strlen(str2);
                temp=malloc(len);
                strcpy(temp,str2);
                char * result = "";
                asprintf(&result, "%s%s", message, temp);
                len = strlen(result);
                message=malloc(len);
                strcpy(message,result);
                dollarsignmode=0;
                var="";
                last=current;
                continue;
            }

            else if(dollarsignmode && i==string_size-1)
            {

                size_t len = strlen(var);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, var);
                str2[len] = current;
                str2[len + 1] = '\0';
                len = strlen(str2);
                var=malloc(len);
                strcpy(var,str2);
                char *temp=lookup_variable(var);
                char * result = "";
                asprintf(&result, "%s%s", message, temp);
                len = strlen(result);
                message=malloc(len);
                strcpy(message,result);
                dollarsignmode=0;
                var="";
                last=current;
                continue;
            }
            else if(dollarsignmode)
            {
                size_t len = strlen(var);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, var);
                str2[len] = current;
                str2[len + 1] = '\0';
                len = strlen(str2);
                var=malloc(len);
                strcpy(var,str2);
                continue;
            }

        }

        if(current == '$')
        {
            dollarsignmode=1;
            last=current;
            continue;
        }
        else  if(current == '"')
        {
            quotes=1;
            continue;
        }
        else if(dollarsignmode &&
                (current==' '||current=='/'||
                 current=='*'||current=='+'||
                 current=='-'))
        {
            char *temp=lookup_variable(var);
            size_t len = strlen(temp);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, temp);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            temp=malloc(len);
            strcpy(temp,str2);
            char * result = "";
            asprintf(&result, "%s%s", message, temp);
            len = strlen(result);
            message=malloc(len);
            strcpy(message,result);
            dollarsignmode=0;
            var="";
            last=current;
            continue;
        }

        else if(dollarsignmode && i==string_size-1)
        {

            size_t len = strlen(var);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, var);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            var=malloc(len);
            strcpy(var,str2);
            char *temp=lookup_variable(var);
            char * result = "";
            asprintf(&result, "%s%s", message, temp);
            len = strlen(result);
            message=malloc(len);
            strcpy(message,result);
            dollarsignmode=0;
            var="";
            last=current;
            continue;
        }
        else if(dollarsignmode==1)
        {
            size_t len = strlen(var);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, var);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            var=malloc(len);
            strcpy(var,str2);
            continue;
        }

        if(current==' '&&(last=='0'||last==' ')&&quotes==0)
            continue;
        else
        {
            size_t len = strlen(message);
            char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
            strcpy(str2, message);
            str2[len] = current;
            str2[len + 1] = '\0';
            len = strlen(str2);
            message=malloc(len);
            strcpy(message,str2);
            last=current;
        }
    }
    printf("%s\n",message);
}


int execute(char* program , char** arg_list )
{

    pid_t child_pid;
    child_pid =fork();
    if(child_pid==0)
    {
        char *pwdd=lookup_variable("PATH");
        if(program[0]=='/')
        {
            execv(program,arg_list);
        }
        else
        {
            char **ress=NULL;
            char str[512];
            strncpy(str,pwdd,512);
            char* p = strtok (str, ":");
            int n_spaces = 0,i;
            while (p)
            {
                ress = realloc (ress, sizeof (char*) * ++n_spaces);

                if (ress == NULL)
                    exit (-1); /* memory allocation failed */

                ress[n_spaces-1] = p;
                p = strtok (NULL, ":");
            }

            /* realloc one extra element for the last NULL */
//
            ress = realloc (ress, sizeof (char*) * (n_spaces+1));
            ress[n_spaces] = 0;

            for (i = 0; i < (n_spaces+1); ++i)
            {
                char *temp2=ress[i];
                size_t len = strlen(temp2);
                char *str2 = malloc(len + 1 +1 ); /* one for extra char, one for trailing zero */
                strcpy(str2, temp2);
                strcat(str2,"/\0");
                FILE* fptr = fopen(str2,"r");

                if(fptr == NULL)
                {
                    printf("Error!");
                    exit(1);
                }
                else
                {

                    len = strlen(str2);
                    temp2=malloc(len);
                    strcpy(temp2,str2);
                    char * result = "";
                    asprintf(&result, "%s%s", temp2, program);
                    execv(result,arg_list);

                }
            }
        }


        perror("Error printed by perror");
        abort();
    }
    else
    {
        if(!backend_detection())
            waitpid(child_pid, NULL, 0);
        // log print
        return child_pid;
    }

}
