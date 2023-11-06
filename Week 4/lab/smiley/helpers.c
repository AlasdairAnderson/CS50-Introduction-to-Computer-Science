#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    //Change all black pixels to a color of your choosing
    //Itterate through the hight of the image
    for (int i = 0; i < height; i++)
    {
        //Itterate throug the width of the image
        for (int j = 0; j < width; j++)
        {
            //Is the pixel not white
            if ((image[i][j].rgbtRed != 0xff) && (image[i][j].rgbtGreen != 0xff) && (image[i][j].rgbtBlue != 0xff))
            {
                //Change pixel to blue
                image[i][j].rgbtRed = 0x26;
                image[i][j].rgbtGreen = 0x42;
                image[i][j].rgbtBlue = 0xE0;
            }
        }
    }
}
