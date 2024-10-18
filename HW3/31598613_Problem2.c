#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h> //found this online, helpful for info about files and dirs

#define MAX_LENGTH 1000

int count_file_lines(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    int lines = 0;
    int ch;
    int prev_ch = '\0';

    while (ch = fgetc(f), ch != EOF) {
        if (ch == '\n') {
            lines++;
        }
        prev_ch = ch;
    }

    if (lines > 0 || (lines == 0 && prev_ch != '\n')) {
        lines++;
    }

    fclose(f);
    return lines;
}

void traverse_dir(const char *path, int *total_lines) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Error while trying to opening the directory.\n");
        return;
    }

    struct dirent *entry; //predefined struct
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
            continue;
        }

        char full_path[MAX_LENGTH];
        snprintf(full_path, MAX_LENGTH, "%s/%s", path, entry->d_name);

        
        if (strlen(full_path) >= MAX_LENGTH) {
            printf("Path is too long: %s\n", full_path);
            continue; //should we should exit or continue?
        }


        struct stat statbuf;

        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) { //if path exsist, and if its a dir or not, ive used this before
            traverse_dir(full_path, total_lines);
        } 
        else if (strstr(full_path, ".txt") != NULL) {
            *total_lines += count_file_lines(full_path);
        }
    }
    closedir(dir);

}

int main() {
    char path[MAX_LENGTH];
    int total_lines = 0;

    printf("Enter the directory path:\n");
    scanf("%s", path);

    //not sure if this is needed but ignore the . in the path?
    if (strncmp(path, "./", 2) == 0) {
        memmove(path, path + 2, strlen(path) - 1);
    }

    traverse_dir(path, &total_lines);

    printf("The total number of lines in the directorty is: %d\n", total_lines);
    return 0;
}