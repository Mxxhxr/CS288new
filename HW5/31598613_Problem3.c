#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **x, char **y) {
    char *temp = *x;
    *x = *y;
    *y = temp;
}

int main (int argc, char *argv[], char *envp[]) {
    
    int counter = 0;

    while (envp[counter] != NULL) {
        counter++;
    }

    for (int i = 0; i < counter-1; i++) {
        for (int j = 0; j < counter-i-1; j++) {

            char *first = strdup(envp[j]);
            char *second = strdup(envp[j+1]);
            //made a copy of the env variables because when i was looking
            //at them there were quite a few and they looked important...

            char *firstName = strtok(first, "=");
            char *secondName = strtok(second, "=");

            if (strcmp(firstName, secondName) > 0) {
                swap(&envp[j], &envp[j+1]);
            }
            free(first);
            free(second);
        }
    }

    for (int i = 0; i < counter; i++) {
        printf("%s\n", envp[i]);
    }
    return 0;
}
