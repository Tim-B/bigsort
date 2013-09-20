#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *input_file;
    char read_buffer[100];
    int value;
    
    int fail = 0;
    int total = 0;
    int prev = -2147483647;

    if (argc != 2) {
        printf("Usage is %s input_file\n", argv[0]);
        return 1;
    }


    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("File %s could not be opened for reading\n", argv[1]);
        perror("Message");
        return 2;
    }

    while (fgets(read_buffer, 100, input_file) != NULL) {
        value = atoi(read_buffer);
        if(value < prev) {
            printf("Failure! %i is not greater than %i on line %i\n", value, prev, total);
            fail++;
        }
        prev = value;
        total++;
    }
    
    printf("Finished, there where %i failures from %i lines examined.\n", fail, total);
    fclose(input_file);
    return 0;
}