#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check for improper usage, otherwise, get filename length
    if (argc != 2)
    {
        printf("Wrong usage: Try ./create [filename]\n");
        return 1;
    }
    int filename_length = strlen((argv[1] + 1));

    // Create a new block of memory to store filename
    char *heapname = malloc(sizeof(char) * filename_length);

    char *stackname = argv[1];

    // Copy argv[1] into block of memory for filename
    sprintf(heapname, "%s", argv[1]);

    // Open new file under the name stored at filename
    FILE *new_file = fopen(stackname, "w");

    // Does file exist
    if (new_file == NULL)
    {
        printf("file does not exist\n");
        fclose(new_file);
        return 2;
    }

    //free memory
    free(heapname);
    fclose(new_file);
}
