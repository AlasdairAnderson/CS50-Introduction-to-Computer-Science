// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string word[]);

int main(int argc, string argv[])
{
    //Has the correct comand-line arguments been given
    if (argc == 2)
    {
        //IF correct ammount of argument given run replace
        printf("%s\n", replace(argv));
        return 0;
    }
    else
    {
        //IF incorrect ammount of arguments given print usage and return error code
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
}

string replace(string word[])
{
    //loop through work replaceing vowies with numbers
    int i = 0;
    while (word[1][i] != '\0')
    {
        switch (word[1][i])
        {
            case 'a':
                word[1][i] = '6';
                break;

            case 'e':
                word[1][i] = '3';
                break;

            case 'i':
                word[1][i] = '1';
                break;

            case 'o':
                word[1][i] = '0';
                break;

            default:
                break;
        }
        i++;
    }

    return word[1];
}
