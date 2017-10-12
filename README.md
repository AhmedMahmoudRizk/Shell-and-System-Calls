# Shell-and-System-Calls
Organization of the code
First of all, the shell gets the input from the user
check if he wants to run batch file or want or run
commands one by one. if detected the path of batch
file go to shell file mode it and read lines one by
one and execute it then show the result in the
terminal, if not detected any path then go to shell
command mode which wait the input from user one
by one and execute them.
Set the environment of the project.
In the execution check if he wants to run it in
backend or frontend then execute the command,
also check the type of the command and the its
accuracy and then parse it.
Take the variables form user and save them in the
table.
There were the main ideas of the project and how it
works.
Main Functions
• Set_evironment: this function in environment
header file, it imports environment variables
into the project including path and home of the
user device it also creates the call another
function to create the table of variables.
• Parse_command: this function takes the
command and parse it to the suit function to
execute if echo instruction send it to echo
function to execute it, if echo instruction send it
to echo function to execute it, else sent the
command to execute function. Command parse
header file also contain replace variable
function: which replace every variable in the
instruction by its real value from the table.
• Command header file contain three functions:
cd is responsible for implementing the "cd" shell
command,echo is responsible for implementing the "echo"
shell command,
execute function takes the command and
execute it.
• Variables header file contain the table of the
variable and its implementation functions to set
new variables or search for any variable and
return its value.
• History function: which write every command in
history file.
• Log function: write in log file that the child
process terminated.
• Open_shell_file: this function opens the shell file
and read line by line and sends them to parse
command function to execute them.
The rest of the functions which I don’t write here
they were just for handle the data and using point.
Way to run the code
• Open the shell and enter the the directory
which contain the files.
• Enter “make”
• If want to run batch file enter “./shell + path
of the file ” to compile the program the.
• If want to enter command one by one in
terminal enter “./shell” and then enter the
commands one by one will show the result
after each execute.
• If you want run any this in backend enter “&”
at the end of the command and will run it in
the backend.
