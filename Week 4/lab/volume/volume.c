// Modifies the volume of an audio file
//LEARNING GOALS
//Get to grips with file pointers
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    //example using the heap
    //create buffer to read the header of input
    uint8_t *inputheader = malloc(sizeof(uint8_t) * HEADER_SIZE);
    fread(inputheader, HEADER_SIZE, 1, input);

    //write the information in inputheader to the output file
    fwrite(inputheader, HEADER_SIZE, 1, output);
    free(inputheader);
    // TODO: Read samples from input file and write updated data to output file

    //example using the stack
    //delcare buffer
    int16_t inputsample;
    while (fread(&inputsample, sizeof(int16_t), 1, input))
    {
        //multiply sample by factor
        inputsample *= factor;

        //write updated sample to output
        fwrite(&inputsample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
