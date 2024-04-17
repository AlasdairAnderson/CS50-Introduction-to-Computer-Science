//Learning Goals
//1. Deepen my understanding of strings
//2. Practice creating recursive functions

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO


    // get index of the last char in string
    int n = strlen(input);

    //Conver char into it numeric value
    int c = input[n-1] - '0';

    //base case
    if(input[1] == '\0')
    {
        return c;
    }

    //Remove the last char from the sting by moving the null terminator one position to the left
    input[n-1] = '\0';

    //Return this value plus 10 time the integer value of the new shortened string
    return  (convert(input) * 10) + c;


}
