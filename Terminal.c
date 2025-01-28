#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

#define MAX_INPUT 1024
#define MAX_PATH 256

void dateTime(){
	time_t tt = time(NULL);
    printf("%s", ctime(&tt));
}

void clear(){
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/Mac
    #endif
    	printf("\033[31m"); // Red text color
}

void startscr(){
    clear();
    printf("Welcome to Tamanna's Terminal! Let's make some progress today!\n");
	dateTime();
	printf("\nType \"help\" if you need help to figure out things in this terminal!\n\n");
}

void help(){
    printf("\n");
    printf("You can enter the following commands:\n\n");
    printf("clr         >>> To clear the screen\n");
    printf("dateTime    >>> To display date and time\n");
    printf("startscr    >>> To show start screen\n");
    printf("ls          >>> To list files\n");
    printf("mkdir <dir> >>> To create a new folder\n");
    printf("cd <dir>    >>> To change directory\n");
    printf("exit        >>> To exit\n");
    printf("\n");
}

void ls() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // Opens the current directory using opendir().
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) { // Reads entries one by one using readdir() and prints their names.
        printf("%s\n", entry->d_name);
	}
    closedir(dir); // Closes the directory stream with closedir().
}

void mkdir(const char *dirname) {
    if(mkdir(dirname, 0777) == 0){ // mkdir(dirname, 0777) == 0 means "Did making the folder succeed?"
        printf("Directory '%s' created successfully.\n", dirname);
    }
	else{
        perror("Error creating directory");
    }
}

void cd(const char *path) {
    if(chdir(path) == 0){ // System function chdir() to change the current working directory.
        printf("Changed directory to: %s\n", path);
    }
	else{
        perror("Error changing directory");
    }
}

void exit(){
	printf("\nExiting the terminal...");
    exit(1);
}

int main(){
	char input[MAX_INPUT];
	char command[MAX_INPUT];
    char argument[MAX_INPUT];
	startscr();
	while(1){
		printf("Input>> ");
    	fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
    	
    	sscanf(input, "%s %[^\n]", command, argument);
    	
		if(strcmp(, "clear") == 0) clear();
		else if(strcmp(a, "help") == 0) help();
		else if(strcmp(a, "dateTime") == 0) dateTime();
		else if(strcmp(a, "startscr") == 0) startscreen();
		else if(strcmp(command, "ls") == 0) ls();
        else if (strcmp(command, "cd") == 0) cd(argument);
        else if (strcmp(command, "mkdir") == 0) mkdir(argument);
		else if(strcmp(a, "exit") == 0) exit();
		else printf("Unknown command: Refer to the \"help\" function");
	}
}
