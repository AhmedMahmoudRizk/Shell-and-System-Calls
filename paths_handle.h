#ifndef PATHS_HANDLE_H_   /* Include guard */
#define PATHS_HANDLE_H_


char *get_current_path();
void set_current_path(char *path_handled);
void set_pwd();
void set_user_name(char *homedir);
char * user_name();
char * get_pwd();

#endif // PATHS_HANDLE_H_
