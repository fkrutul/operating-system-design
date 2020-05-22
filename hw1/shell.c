#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/wait.h>
#include <signal.h>
#define DELIMITERS " \t\r\n\a"

char *cmd_strgs[] = {
    "cd",
    "help",
    "quit",
    "list"
};

int cd_builtin(char **args)
{
    chdir(args[1]);
    return 1;
}

int help_builtin()
{
    printf("cd <directory>: change current directory to [directory]\n");
    printf("quit: exit the shell\n");
    printf("help: show a list and brief description of shell commands\n");
    printf("list: show contents of current directory\n");
    printf("hello: execute the Hello World program\n");
    printf("fibonacci: execute the Fibonacci program\n");
    return 1;
}

int quit_builtin()
{
    exit(1);
}

void list_builtin()
{
    DIR *directory;
    struct dirent *dirent;
    directory = opendir(".");
    
    while ((dirent = readdir(directory)) != NULL)
    {
        printf("%s\n", dirent->d_name);
    }
    closedir(directory);
}

void execArgs(char** arg) 
{ 

    pid_t pid = fork();  
  
    if (pid == -1) { 
        printf("Error\n"); 
        return; 
    } else if (pid == 0) { 
        if (execvp(arg[0], arg) < 0) { 
            printf("Error\n"); 
        } 
        exit(0); 
    } else { 
        wait(NULL);  
        return; 
    } 
} 

int execInput(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    else if (strcmp(args[0], "help") == 0)
    {
        return help_builtin();
    }

    else if (strcmp(args[0], "list") == 0)
    {
        list_builtin();
    }

    else if (strcmp(args[0], "cd") == 0)
    {
        return cd_builtin(args);
    }

    else if (strcmp(args[0], "cd") == 0 && args[1] == NULL)
    {
        printf("Please pass the desired directory as an argument");
    }

    else if (strcmp(args[0], "quit") == 0)
    {
        return quit_builtin();
    }

    else if (strcmp(args[0], "hello") == 0)
    {
        char *args[] = {"./HelloWorld", NULL};
        execArgs(args);
    }

    else if (strcmp(args[0], "fibonacci") == 0 && args[1] != NULL)
    {
        printf("Please don't provide any arguments - you will be prompted to enter them\n");
    }

    else if (strcmp(args[0], "fibonacci") == 0 && args[1] == NULL) 
    {
        char *args[] = {"./Fibonacci", NULL};
        execArgs(args);
    }

    return 1;
}

char *readInput()
{
    char *line;

    ssize_t allocate = 0;
    getline(&line, &allocate, stdin);
    return line;
}

char **tokenizeInput(char *line)
{
    int buf = 2000;
    int pos = 0;

    char **toks = malloc(buf * sizeof(char *));
    char *tok;

    tok = strtok(line, DELIMITERS);
    while (tok != NULL)
    {
        toks[pos] = tok;
        pos++;

        tok = strtok(NULL, DELIMITERS);
    }
    toks[pos] = NULL;
    return toks;
}

void Loop()
{
    char *line;
    char **args;
    int stat;

    do
    {
        printf("uab_sh> ");

        line = readInput();
        args = tokenizeInput(line);
        stat = execInput(args);

    } while (stat);
}

int main(int argc, char **argv)
{

    Loop();

    return 0;
}
