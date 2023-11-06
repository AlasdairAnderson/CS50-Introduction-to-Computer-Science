#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //declare varibles
    int sum;
    float average;

    //loop through each pixel
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            //Avarage the value Blue Green Red Value and apply to each aspect to get the pixel

            //Get sumerise RGB values
            sum = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;

            //Average values
            average = (float)sum / 3;

            //Apply product to pixel
            image[h][w].rgbtBlue = round(average);
            image[h][w].rgbtGreen = round(average);
            image[h][w].rgbtRed = round(average);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Reflection buffer
    RGBTRIPLE reflection[width][height];

    int reflectioncolumn;
    //loop through image
    for (int row = 0; row < height;  row++)
    {
        reflectioncolumn = (width - 1);
        for (int column = 0; column < width; column++)
        {
            if (reflectioncolumn >= 0)
            {
                reflection[row][column].rgbtBlue = image[row][reflectioncolumn].rgbtBlue;
                reflection[row][column].rgbtGreen = image[row][reflectioncolumn].rgbtGreen;
                reflection[row][column].rgbtRed = image[row][reflectioncolumn].rgbtRed;
            }
            reflectioncolumn--;
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtBlue = reflection[row][column].rgbtBlue;
            image[row][column].rgbtGreen = reflection[row][column].rgbtGreen;
            image[row][column].rgbtRed = reflection[row][column].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //buffers for bgr values
    RGBTRIPLE buffer[height][width];
    float sumred;
    float sumgreen;
    float sumblue;
    int averagecount;
    //Loop through each pixel
    for (int row = 0; row < height; row ++)
    {
        for (int column = 0; column < width; column++)
        {
            averagecount = 0;
            sumblue = 0;
            sumgreen = 0;
            sumred = 0;
            //loop through 3 by 3 grid around pixel
            for (int i = row - 1; i <= (row + 1); i++)
            {
                for (int j = column - 1; j <= (column + 1); j++)
                {

                    if (i < 0 || i >= height || j < 0 || j >= width)
                    {
                        continue;
                    }
                    else
                    {
                        //avarge out pixels
                        sumblue += image[i][j].rgbtBlue;
                        sumgreen += image[i][j].rgbtGreen;
                        sumred += image[i][j].rgbtRed;
                        averagecount++;
                    }
                }
            }

            //average pixel value
            sumblue = sumblue / averagecount;
            sumgreen = sumgreen / averagecount;
            sumred = sumred / averagecount;

            //copy new pixel value to buffer
            buffer[row][column].rgbtBlue = round(sumblue);
            buffer[row][column].rgbtGreen = round(sumgreen);
            buffer[row][column].rgbtRed = round(sumred);
        }
    }

    //copy buffer to origonal image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtBlue = buffer[row][column].rgbtBlue;
            image[row][column].rgbtGreen = buffer[row][column].rgbtGreen;
            image[row][column].rgbtRed = buffer[row][column].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //declair varible
    int redSobel, greenSobel, blueSobel, kernelrow, kernelcolumn;
    float sumGx, sumGy;
    RGBTRIPLE buffer[height][width];

    //declair kernals
    int kernelGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernelGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //loop each pixel
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            blueSobel = 0;
            greenSobel = 0;
            redSobel = 0;
            for (int colour = 0; colour < 3; colour++)
            {
                sumGx = 0;
                sumGy = 0;
                kernelrow = 0;

                //loop through kernel
                for (int i = (row - 1); i <= (row + 1); i++)
                {
                    kernelcolumn = 0;
                    for (int j = (column - 1); j <= (column + 1); j++)
                    {
                        //is pixel outside of image
                        if (i < 0 || i >= height || j < 0 || j >= width)
                        {
                            sumGx += 0 * kernelGx[kernelrow][kernelcolumn];
                            sumGy += 0 * kernelGy[kernelrow][kernelcolumn];
                        }
                        else if (colour == 0)
                        {
                            sumGx += image[i][j].rgbtBlue * kernelGx[kernelrow][kernelcolumn];
                            sumGy += image[i][j].rgbtBlue * kernelGy[kernelrow][kernelcolumn];
                        }
                        else if (colour == 1)
                        {
                            sumGx += image[i][j].rgbtGreen * kernelGx[kernelrow][kernelcolumn];
                            sumGy += image[i][j].rgbtGreen * kernelGy[kernelrow][kernelcolumn];
                        }
                        else if (colour == 2)
                        {
                            sumGx += image[i][j].rgbtRed * kernelGx[kernelrow][kernelcolumn];
                            sumGy += image[i][j].rgbtRed * kernelGy[kernelrow][kernelcolumn];
                        }
                        kernelcolumn++;
                    }
                    kernelrow++;
                }

                //run Sobel
                if (colour == 0)
                {
                    blueSobel = round(sqrt(powf(round(sumGx), 2) + powf(round(sumGy), 2)));
                    if (blueSobel > 255)
                    {
                        blueSobel = 255;
                    }
                    else if (blueSobel < 0)
                    {
                        blueSobel = 0;
                    }
                }
                else if (colour == 1)
                {
                    greenSobel = round(sqrt(powf(round(sumGx), 2) + powf(round(sumGy), 2)));
                    if (greenSobel > 255)
                    {
                        greenSobel = 255;
                    }
                    else if (greenSobel < 0)
                    {
                        greenSobel = 0;
                    }
                }
                else if (colour == 2)
                {
                    redSobel = round(sqrt(powf(round(sumGx), 2) + powf(round(sumGy), 2)));
                    if (redSobel > 255)
                    {
                        redSobel = 255;
                    }
                    else if (redSobel < 0)
                    {
                        redSobel = 0;
                    }
                }
            }

            //assign colourSobel to image buffer
            buffer[row][column].rgbtRed = redSobel;
            buffer[row][column].rgbtGreen = greenSobel;
            buffer[row][column].rgbtBlue = blueSobel;
        }
    }

    //copy buffer to image
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = buffer[row][column].rgbtRed;
            image[row][column].rgbtGreen = buffer[row][column].rgbtGreen;
            image[row][column].rgbtBlue = buffer[row][column].rgbtBlue;
        }
    }
    return;
}

// float Gx(int height, int width, int row, int column, int colour, RGBTRIPLE image[height][width])
// {
//     //declar variables
//     int kernelGx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
//     int ki = 0, kl;
//     float sumGx = 0;

//     //loop through kernel
//     for(int i = (row - 1); i <= (row + 1); i++)
//     {
//         kl = 0;
//         for(int j = (column - 1); j <= (column + 1); j++)
//         {
//             //is pixel outside of image
//             if(i < 0 || i >= height || j < 0 || j >= width)
//             {
//                 sumGx += 0 * kernelGx[ki][kl];
//             }
//             else if(colour == 0)
//             {
//                 sumGx += image[i][j].rgbtBlue * kernelGx[ki][kl];
//             }
//             else if(colour == 1)
//             {
//                 sumGx += image[i][j].rgbtRed * kernelGx[ki][kl];
//             }
//             else if(colour == 2)
//             {
//                 sumGx += image[i][j].rgbtGreen * kernelGx[ki][kl];
//             }
//             kl++;
//         }
//         ki++;
//     }

//     return sum;
// }

// float Gy(int height, int width, int row, int column, int colour, RGBTRIPLE image[height][width])
// {
//     //declar variables
//     int kernelGy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
//     int kl, ki = 0;
//     float sumGy = 0;

//     //loop through kernel
//     for(int i = (row - 1); i <= (row + 1); i++)
//     {
//         kl = 0;
//         for(int j = (column - 1); j <= (column + 1); j++)
//         {
//             //is pixel outside of image
//             if(i < 0 || i >= height || j < 0 || j >= width)
//             {
//                 sumGy += 0 * kernelGy[ki][kl];
//             }
//             else if(colour == 0)
//             {
//                 sumGy += image[i][j].rgbtBlue * kernelGy[ki][kl];
//             }
//             else if(colour == 1)
//             {
//                 sumGy += image[i][j].rgbtRed * kernelGy[ki][kl];
//             }
//             else if(colour == 2)
//             {
//                 sumGy += image[i][j].rgbtGreen * kernelGy[ki][kl];
//             }
//             kl++;
//         }
//         ki++;
//     }

//     return sum;
// }


