/*
author: Jason Appiah-Kubi
email: jasona2@umbc.edu
description: a simple linux shell designed to perform basic linux commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "utils.h"

#define HISTORY_FILE ".421sh"
/*
In this project, you are going to implement a number of functions to 
create a simple linux shell interface to perform basic linux commands
*/

void user_prompt_loop();
char* get_user_command();
char** parse_command(char* command);
void execute_command(char** parsed_command);
void handle_proc(char* path);
void log_command(char *command);
void show_history();
/*extra credit*/
void change_directory(char **args);


int main(int argc, char **argv)
{
    /*
    Write the main function that checks the number of argument passed to ensure 
    no command-line arguments are passed; if the number of argument is greater 
    than 1 then exit the shell with a message to stderr and return value of 1
    otherwise call the user_prompt_loop() function to get user input repeatedly 
    until the user enters the "exit" command.
    */

   if (argc > 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }
   user_prompt_loop();
    return 0;
}

void change_directory(char **args) {
    if (args[1] == NULL) {
        //home directory is defualt
        chdir(getenv("HOME"));
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

void log_command(char *command){
    FILE *file = fopen(HISTORY_FILE, "a");
    fprintf(file, "%s\n", command);
    fclose(file);
}

void show_history() {
    FILE *file = fopen(HISTORY_FILE, "r");

    if (file == NULL) {
        perror("Failed to open history file");
        return;
    }

    char *history[10] = {NULL}; 
    int count = 0;
    char *buffer = NULL;
    size_t len = 0;

    // Read lines from the file
    while (getline(&buffer, &len, file) != -1) {
        // Remove newline character
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        if (count >= 10) {
            free(history[count % 10]);
        }

        history[count % 10] = strdup(buffer);
        count++;
    }

    fclose(file);
    free(buffer);

    // Display the last 10 commands
    int start = (count > 10) ? count - 10 : 0;
    for (int i = start; i < count; i++) {
        printf("%d: %s\n", i + 1, history[i % 10]);
    }

    // Free memory
    for (int i = 0; i < (count < 10 ? count : 10); i++) {
        free(history[i]);
    }
}


/*
user_prompt_loop():
Get the user input using a loop until the user exits, prompting the user for a command.
Gets command and sends it to a parser, then compares the first element to the two
different commands ("/proc", and "exit"). If it's none of the commands, 
send it to the execute_command() function. If the user decides to exit, then exit 0 or exit 
with the user given value. 
*/

void user_prompt_loop() {
    // initialize variables

    /*
    loop:
        1. prompt the user to type command by printing >>
        2. get the user input using get_user_command() function 
        3. parse the user input using parse_command() function 
        Example: 
            user input: "ls -la"
            parsed output: ["ls", "-la", NULL]
        4. compare the first element of the parsed output to "/proc"and "exit"
        5. if the first element is "/proc" then you have the open the /proc file system 
           to read from it
            i) concat the full command:
                Ex: user input >>/proc /process_id_no/status
                    concated output: /proc/process_id_no/status
            ii) read from the file line by line. you may user fopen() and getline() functions
            iii) display the following information according to the user input from /proc
                a) Get the cpu information if the input is /proc/cpuinfo
                - Cpu Mhz
                - Cache size
                - Cpu cores
                - Address sizes
                b) Get the number of currently running processes from /proc/loadavg
                c) Get how many seconds your box has been up, and how many seconds it has been idle from /proc/uptime
                d) Get the following information from /proc/process_id_no/status
                - the vm size of the virtual memory allocated the vbox 
                - the most memory used vmpeak 
                - the process state
                - the parent pid
                - the number of threads
                - number of voluntary context switches
                - number of involuntary context switches
                e) display the list of environment variables from /proc/process_id_no/environ
                f) display the performance information if the user input is /proc/process_id_no/sched
        6. if the first element is "exit" the use the exit() function to terminate the program
        7. otherwise pass the parsed command to execute_command() function 
        8. free the allocated memory using the free() function
    */

    /*
    Functions you may need: 
        get_user_command(), parse_command(), execute_command(), strcmp(), strcat(), 
        strlen(), strncmp(), fopen(), fclose(), getline(), isdigit(), atoi(), fgetc(), 
        or any other useful functions
    */
   while(1){
    printf(">> ");
    char *command = get_user_command();
    char **parsed_command = parse_command(command);
    log_command(command);

    
  if (parsed_command[0] != NULL) {
            if (strcmp(parsed_command[0], "exit") == 0) {
                free(command);
                free(parsed_command);
                exit(0);
            }

            else if (strncmp(parsed_command[0], "/proc", 5) == 0) {
            handle_proc(parsed_command[0]);  
            } 
            else if(strcmp(parsed_command[0], "history") == 0) {
            show_history();
            }if (strcmp(parsed_command[0], "cd") == 0) {
            change_directory(parsed_command);
            }else {
            execute_command(parsed_command);
            }
   }
       else {
            execute_command(parsed_command);
            }   
    free(command);
    free(parsed_command);

}
}

/*
get_user_command():
Take input of arbitrary size from the user and return to the user_prompt_loop()
*/
char* get_user_command()
{
   char *command = NULL;
   size_t size = 0;
   getline(&command, &size, stdin);
   
   size_t length = strlen(command);
   if (length > 0 && command[length - 1] == '\n') {
        command[length - 1] = '\0'; }
        
    //removes the \n with a space
    for(size_t i = 0; i < length - 1;i++){
        if (command[i] == '\\' && command[i + 1] == 'n') {
           command[i] = ' ';
           memmove(&command[i + 1], &command[i + 2], length - i - 1);
           length--;
       }
    }

   return command;
}

/*
parse_command():
Take command grabbed from the user and parse appropriately.
Example: 
    user input: "ls -la"
    parsed output: ["ls", "-la", NULL]
Example: 
    user input: "echo     hello                     world  "
    parsed output: ["echo", "hello", "world", NULL]
*/
char** parse_command(char* command)
{
    /*
    Functions you may need: 
        malloc(), realloc(), free(), strlen(), first_unquoted_space(), unescape()
    */

   int buffer = 128;
   int position = 0;
   char **strings = malloc(buffer * sizeof(char*));
   char *string;

   //command = unescape(command,stderr);
   char *unescaped_command = unescape(command, stderr);

    if (!strings) {
        fprintf(stderr, "allocation error\n");
        exit(EXIT_FAILURE);
    }

    //Splitting the command at the spaces
    string = strtok(command, " ");
    while (string != NULL) {
        strings[position] = string;
        position++;

        if (position >= buffer) {
            buffer += 64;
            strings = realloc(strings, buffer * sizeof(char*));
            if (!strings) {
                fprintf(stderr, "allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        string = strtok(NULL, " ");
    }
    strings[position] = NULL;  
    free(unescaped_command);

    return strings;
}

/*
execute_command():
Execute the parsed command if the commands are neither /proc nor exit;
fork a process and execute the parsed command inside the child process
*/

void execute_command(char** parsed_command)
{
    /*
    Functions you may need: 
        fork(), execvp(), waitpid(), and any other useful function
    */

    pid_t id = fork();
    if (id == -1){
        perror("failed");
        return;
    }
    else if (id == 0){
        //added because the execution error and exit failure message would be printed when using history or any /proc command
        if (strcmp(parsed_command[0], "history") == 0 || strncmp(parsed_command[0], "/proc", 5) == 0) {
            exit(EXIT_SUCCESS); 
        }
        // message for when a command cant be executed for whatever reason
        if(execvp(parsed_command[0], parsed_command) < 0){
            perror("execution error");
        }
        exit(EXIT_FAILURE); 
    }
    else{
        int status;
        waitpid(id, &status, WUNTRACED);
    }   
}


/*
  Function that opens the specified /proc file, reads it line by line, and prints the contents
*/
void handle_proc(char *path){
    FILE *file = fopen(path, "r");
    if (file == NULL){
        perror("failed to open file");
        return;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, file)) != -1){
        printf("%s", line);
    }
    free(line);
    fclose(file);
}

