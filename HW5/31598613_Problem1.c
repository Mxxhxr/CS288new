#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv[]) {
    // printf("argv    | %p\n", (void *)argv);
    printf("argv    | ");
    unsigned char *argvByte = (unsigned char *)&argv;

    for (int i = sizeof(*argv) - 1; i >= 0; i--) { //my machine is little-endian so i reversed the order
        printf("%02x ", argvByte[i]);
    }
    printf(" | %p\n\n", (void *)argv);


    int i = 0;
    while (argv[i] != NULL) {
        printf("argv[%d] | ", i);

        unsigned char *argvPtrByte = (unsigned char *)&argv[i];
        for (int j = sizeof(argv[i]) - 1; j >= 0; j--) { //my machine is little-endian so i reversed the order
            printf("%02x ", argvPtrByte[j]); 
        }
        printf(" | %p\n", (void *)argv[i]);
        i++;
    }
    printf("\n");
    

    //finding the starting and ending addresses of the string
    unsigned char *start = (unsigned char *)argv[0];
    unsigned char *end = (unsigned char *)argv[argc-1];

    while (*end != '\0') {
        end++;
    }
    end++;

    while ((unsigned long)start % 8 != 0) {
        start--;
    }
    while ((unsigned long)end % 8 != 0) {
        end++;
    }

    unsigned char *ptr = start;
    while (ptr < end) {
        printf("| ");

        for (int i = 7; i >= 0; i--) {  // Reverse the byte order for little-endian
            if (ptr + 1 < end) {
                unsigned char c = *(ptr+i);
                printf(" %02x", c);

                if (isprint(c)) {
                    printf("(%c) ", c);
                }
                else if (c == '\0') {
                    printf("(\\0) ");
                }
                else {
                    printf("(.) ");
                }
            }
            else {
                printf("   ");
            }
            
        }
        printf("| %p\n", (void *)ptr);
        ptr += 8;
    }
    return 0;
}