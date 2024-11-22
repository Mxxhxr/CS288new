#include <stdio.h>
#include <unistd.h> 
#include <bits/getopt_core.h>

int main (int argc, char *argv[]) {
    
    int opt;

    while((opt = getopt(argc, argv, "cduf:s:")) != -1) {
        switch(opt) {
            case 'c':
                printf("Option c\n");
                break;
            case 'd':
                printf("Option d\n");
                break;
            case 'u':
                printf("Option u\n");
                break;
            case 'f':
                printf("Option f. Field is: %s\n", optarg);
                break;
            case 's':
                printf("Option s. String is: %s\n", optarg);
                break;
            case ':': //for missing arg
                printf("option %c needs a value\n", optopt);
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                break;
            default:
                break;
        }
    }


    for (int i = optind; i < argc; i++) {
        printf("Operand: %s\n", argv[i]);
    }

    return 0;
}