#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1

    // Check if there are are two comand-line arguments
    if (argc != 3)
    {
        printf("Usage: ./reverse inputfile.wav outputfile.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inputfile = fopen(argv[1], "r");
    if (inputfile == NULL)
    {
        printf("Read of inputfile error\n");
        return 1;
    }

    // Read header
    // TODO #3

    //Malloc size of header
    WAVHEADER inputheader;

    //fread input header into Malloced Memory
    fread(&inputheader, sizeof(WAVHEADER), 1, inputfile);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(inputheader);

    // Open output file for writing
    // TODO #5
    FILE *outputfile = fopen(argv[2], "w");
    if (outputfile == NULL)
    {
        printf("output file error\n");
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&inputheader, sizeof(WAVHEADER), 1, outputfile);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(inputheader);

    // Write reversed audio to file
    // TODO #8
    // Declar array for auditory block to be stored in
    BYTE audioblock[blockSize];
    for (int i = 0; i < blockSize; i++)
    {
        audioblock[i] = 0;
    }
    //Set positions for files;
    if (fseek(inputfile, blockSize, SEEK_END))
    {
        printf("fseek error\n");
        return 1;
    }

    if (ftell(outputfile) != 44)
    {
        fseek(outputfile, 44, SEEK_SET);
    }


    // loop through auditory data stopping before the header file
    while (ftell(inputfile) - blockSize > sizeof(inputheader))
    {
        if (fseek(inputfile, - 2 * blockSize, SEEK_CUR))
        {
            printf("fseek error\n");
            return 1;
        }
        // Read audatory data from inputfile to array
        fread(&audioblock, blockSize, 1, inputfile);
        fwrite(&audioblock, blockSize, 1, outputfile);
    }



    // Write array to outputfile

    //close files
    fclose(inputfile);
    fclose(outputfile);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    int correctFormat = 0;
    //read byte 8 - 11 of header

    for (int byte = 0; byte < 5; byte++)
    {
        if (header.format[byte] == 'W' || header.format[byte] == 'A' || header.format[byte] == 'V' || header.format[byte] == 'E')
        {
            correctFormat++;
        }
    }
    //if bytes == W A V E
    //return ture
    if (correctFormat == 4)
    {
        return 0;
    }
    else
    {
        printf("Incorrect File Format\n");
        return 2;
    }
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    //return an integer respresenting the block size of the given WAV file in bytes
    //block calculation: number of channels * bytes per sample.
    int blockSize = header.numChannels * header.bitsPerSample / 8;

    return blockSize;
}
