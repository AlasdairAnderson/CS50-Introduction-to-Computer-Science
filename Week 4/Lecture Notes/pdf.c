//check if file is PDF or not
//get better understanding of file pointers and file operators
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    //check propper usage
    if (argc != 2)
    {
        printf("Useage: ./pdf filename\n");
        return 1;
    }

    //obtain pointer to file and not NULL
    string filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File does not exist\n");
        return 2;
    }

    //get first 4 bytes of file
    uint8_t buffer[4];
    uint8_t pdfsignature[] = {37, 80, 68, 70};
    fread(buffer, sizeof(uint8_t), 4, file);

    fclose(file);

    // does the buffer signature match?
    for (int i = 0; i < 4; i++)
    {
        if (buffer[i] != pdfsignature[i])
        {
            printf("File likely not PDF\n");
            return 0;
        }
    }


    printf("File likely a PDF\n");
    return 0;

}
