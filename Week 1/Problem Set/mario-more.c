#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_blocks(int height);

int main(void)
{

    int height = get_size();
    print_blocks(height);

}

int get_size(void)
{
    //get high of pyramid: must be between 1 - 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height > 8 || height < 1);
    return height;
}

void print_blocks(int height)
{

    int width = 1;
//set number of spaces needed
    int spaces = height - 1;

//print pyramid: every loop exicution should add an additional #
    for (int i = 0; i < height; i++)
    {
//print spaces decending ammount
        for (int j = 0; j < spaces; j++)
        {
            printf(" ");
        }
//print blocks set 1
        for (int j = 0; j < width; j++)
        {
            printf("#");
        }
//print 2 spaces
        printf("  ");
//print blocks set 2
        for (int j = 0; j < width; j++)
        {
            printf("#");
        }
        width++;
        spaces--;
        printf("\n");

    }

}
