#include "command_parser.h"
#include "commands.h"
#include "variables.h"
#include "file_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
char ** res  = NULL;
char echoo[4]="echo";
char cdd[2]="cd";
char dollarsign[1]="$";
char exitt[4]="exit";
char historyy[7]="history";

int exitflag=1;
int backend_mode=0;
char stringn[512];
char string2[512];
char string3[512];

char * set_variables_command(char *test)
{
    char *message="";
    int dollarsignmode=0;
    char *var="";
    int i=0,string_size=strlen(test);
    for(i=0; i<string_size; i++)
    {
        char  current=test[i];
        if(current == '$')
        {
            dollarsignmode=1;
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
        }

    }
    return message;

}

int exit_detection()
{
    return exitflag;
}

int backend_detection()
{
    return backend_mode;
}


int subCheck(char str[],char sub[])
{
    char *p1, *p2, *p3;
    int i=0,j=0,flag=0;

    p1 = str;
    p2 = sub;

    for(i = 0; i<strlen(str); i++)
    {
        if(*p1 == *p2)
        {
            p3 = p1;
            for(j = 0; j<strlen(sub); j++)
            {
                if(*p3 == *p2)
                {
                    p3++;
                    p2++;
                }
                else
                    break;
            }
            p2 = sub;
            if(j == strlen(sub))
            {
                flag = 1;
            }
        }
        p1++;
    }
    return flag;
}

void check_backend(char*command)
{
    int len=strlen(command);
    if(command[len-1]=='&')
        backend_mode=1;
    else
        backend_mode=0;
}


char * clear_wite_space(char *test)
{
    memset(stringn,0,512);

    int len=strlen(test);
    int i=0;
    for(i=0; i<len; i++)
    {
        if(test[i]!=' ')
            break;

    }
    int j=0;
    for(i; i<len; i++)
    {
        stringn[j]=test[i];
        j++;
    }
    char * point=stringn;
    return point;

}

char * trim_command(char *test)
{
    memset(string2,0,512);
    int len=strlen(test);
    int i=len-1;
    for(i; i>=0; i--)
    {
        if(test[i]!=' '&&test[i]!='\n')
            break;
    }
    int j=0;
    for(j; j<=i; j++)
    {
        string2[j]=test[j];
    }
    char * point=string2;
    return point;
}

char * and_sign_handle(char *test)
{
    memset(string3,0,512);
    int len=strlen(test);
    int i=len-1;
    for(i; i>=0; i--)
    {
        if(test[i]!='&')
            break;
    }
    int j=0;
    for(j; j<=i; j++)
    {
        string3[j]=test[j];
    }
    char * point=string3;
    return point;
}



int check_equal(char str[])
{
    char equal='=';
    int string_len=strlen(str);
    char c;
    int result=0,i;
    for(i=0; i<string_len; i++)
    {
        c=str[i];
        if(c==equal)
        {
            result=1;
            return result;
        }
    }
    return result;
}

int checker(char input[],char check[])
{
    int i,result=1;
    for(i=0; input[i]!='\0' && check[i]!='\0'; i++)
    {
        if(input[i]!=check[i])
        {
            result=0;
            break;
        }
    }
    return result;
}

void parse_command(char *commonand)
{
    // you should implement this function
    commonand=clear_wite_space(commonand);//delete white spaces in first
    commonand=trim_command(commonand);//delete white spaces in end of string (trim)
    backend_mode=0;
    check_backend(commonand); //check if & in the end of the command
    //handle empty line
    if(strlen(commonand)==0||(strlen(commonand)==1&&commonand[0]=='\n'))
        return ;
    char str[512];
    strncpy(str,commonand,512);
    char* p = strtok (str, " ");
    int n_spaces = 0,i;
    if(checker(p,exitt)==1)
    {
        exitflag=0;
        return;
    }

    if(checker(p,historyy)==1)
    {
        print_history_file();
        return ;
    }
    if(checker(p,echoo)==1)
    {
//        printf( " Done echo fun \n");
        echo(commonand);
        return;
    }
    commonand=set_variables_command(commonand);
    if(checker(p,cdd)==1)
    {
        cd(commonand);
        return;
    }
    else if(checker(p,exitt)==1)
    {
        exitflag=1;
        close_history_file();
        return;
    }

    else if(check_equal(p)==1)
    {
        variables_handle(commonand);
        return;
    }

    /* split string and append tokens to 'res' */
    else
    {
        commonand=and_sign_handle(commonand);
        char str22[512];
        strncpy(str22,commonand,512);
        char* pp = strtok (str22, " ");
        while (pp)
        {
            res = realloc (res, sizeof (char*) * ++n_spaces);

            if (res == NULL)
                exit (-1); /* memory allocation failed */

            res[n_spaces-1] = pp;
            pp = strtok (NULL, " ");
        }

        /* realloc one extra element for the last NULL */
//
        res = realloc (res, sizeof (char*) * (n_spaces+1));
        res[n_spaces] = 0;

        execute(res[0],res);
    }

}

