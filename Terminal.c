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

void dateTime(){
    time_t tt = time(NULL);
    printf("%s", ctime(&tt));
}

void clearScr(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("\033[31m");  // Red text
    printf("\033[0m");   // Reset color
}

void startscr(){
    clearScr();
    printf("Welcome to Tamanna's Terminal! Let's make some progress today!\n");
    dateTime();
    printf("\nType \"help\" if you need help!\n\n");
}

void help(){
    printf("\nYou can enter the following commands:\n\n");
    printf("clear       >>> Clear the screen\n");
    printf("dateTime    >>> Display date and time\n");
    printf("startscr    >>> Show start screen\n");
    printf("ls          >>> List files\n");
    printf("cd <dir>    >>> Change directory\n");
    printf("mkdir <dir> >>> Create a directory\n");
    printf("rf <file>   >>> Remove a file\n");
    printf("read <file> >>> Read and display file content\n");
    printf("write <file>>> Write to a file\n");
    printf("append <file> >>> Append content to a file\n");
    printf("mv <file> <new_name> >>> Rename or move a file\n");
    printf("copy <source> <destination> >>> Copy a file\n");
    printf("touch <file> >>> Create an empty file\n");
    printf("ccount <file> >>> Count characters in a file\n");
    printf("lknow <file> >>> Count lines in a file\n");
    printf("cknow <file> <char> >>> Count occurrences of a character\n");
    printf("exit        >>> Exit\n\n");
}

void ls() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory");
        return;
    }

    printf("Files in the current directory:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

void cd(char *path) {
    if (path == NULL || strcmp(path, "") == 0) {
        path = getenv("HOME");
    }
    if (chdir(path) == 0) {
        printf("Changed directory to: %s\n", path);
    } else {
        perror("Error changing directory");
    }
}

void mymkdir(const char *input) {
    char dirname[MAX_INPUT] = "";
    sscanf(input, "mkdir %[^\n]", dirname); // Extract everything after 'mkdir'

    if (strlen(dirname) == 0) {
        printf("Usage: mkdir <directory_name>\n");
        return;
    }

    if (mkdir(dirname, 700) == 0) {
        printf("Directory '%s' created successfully.\n", dirname);
    } else {
        perror("Error creating directory");
    }
}

void append(char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    char content[MAX_INPUT];
    printf("Enter content to append to '%s':\n", filename);
    fgets(content, MAX_INPUT, stdin);
    content[strcspn(content, "\n")] = '\0';  // Remove newline
    fprintf(file, "%s\n", content);
    fclose(file);
    printf("Content appended to '%s'.\n", filename);
}

void mv(char *oldname, char *newname) {
    if (rename(oldname, newname) == 0) {
        printf("Renamed '%s' to '%s'.\n", oldname, newname);
    } else {
        perror("Error renaming file");
    }
}

void copy(char *src, char *dest) {
    FILE *fsrc = fopen(src, "r");
    if (!fsrc) {
        perror("Error opening source file");
        return;
    }
    FILE *fdest = fopen(dest, "w");
    if (!fdest) {
        perror("Error opening destination file");
        fclose(fsrc);
        return;
    }
    char ch;
    while ((ch = fgetc(fsrc)) != EOF) {
        fputc(ch, fdest);
    }
    fclose(fsrc);
    fclose(fdest);
    printf("Copied '%s' to '%s'.\n", src, dest);
}

void ccount(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    int count = 0;
    while (fgetc(file) != EOF) count++;
    fclose(file);
    printf("Total characters in '%s': %d\n", filename, count);
}

void lknow(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    int count = 0;
    char line[MAX_INPUT];
    while (fgets(line, sizeof(line), file)) count++;
    fclose(file);
    printf("Total lines in '%s': %d\n", filename, count);
}

void cknow(char *filename, char c) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == c) count++;
    }
    fclose(file);
    printf("Character '%c' appears %d times in '%s'.\n", c, count, filename);
}

int main() {
    char input[MAX_INPUT];
    char *args[MAX_INPUT / 2 + 1];
    startscr();

    while (1) {
        printf("Input>> ");
        if (!fgets(input, MAX_INPUT, stdin)) {
            continue;
        }
        input[strcspn(input, "\n")] = '\0'; // Remove newline

        int argc = 0;
        char *token = strtok(input, " ");
        while (token) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }
        args[argc] = NULL;

        if (argc == 0) continue;  // Ignore empty input

        if (strcmp(args[0], "clear") == 0) clearScr();
        else if (strcmp(args[0], "help") == 0) help();
        else if (strcmp(args[0], "dateTime") == 0) dateTime();
        else if (strcmp(args[0], "startscr") == 0) startscr();
        else if (strcmp(args[0], "ls") == 0) ls();
        else if (strcmp(args[0], "cd") == 0) cd(args[1]);
        else if (strcmp(args[0], "mkdir") == 0) mymkdir(argc, args);
        else if (strcmp(args[0], "append") == 0) append(args[1]);
        else if (strcmp(args[0], "mv") == 0 && argc > 2) mv(args[1], args[2]);
        else if (strcmp(args[0], "copy") == 0 && argc > 2) copy(args[1], args[2]);
        else if (strcmp(args[0], "ccount") == 0) ccount(args[1]);
        else if (strcmp(args[0], "lknow") == 0) lknow(args[1]);
        else if (strcmp(args[0], "cknow") == 0 && argc > 2) cknow(args[1], args[2][0]);
        else if (strcmp(args[0], "exit") == 0) exit(0);
        else printf("Unknown command!\n");
    }
}
