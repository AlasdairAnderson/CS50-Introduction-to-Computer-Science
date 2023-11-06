#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_scentences(string text);
float colemanliau_index(int letters, int words, int scentences);

int main(void)
{
    // prompt user for string
    string text = get_string("Text: ");

    // count number to letters
    int letters = count_letters(text);
    printf("Letters: %i\n", letters);

    // count number of words
    int words = count_words(text);
    printf("Words: %i\n", words);

    // count number of sentences
    int scentences = count_scentences(text);
    printf("Scentences: %i\n", scentences);

    // calcuate Coleman-Liau index
    int index = round(colemanliau_index(letters, words, scentences));

    //print grade level rounded to nearest integer
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    //inicalise vairables
    int c = 0;
    int letters = 0;

    // loop through charicters in string
    while (text[c] != '\0')
    {
        //count number of letters in string
        if (isalpha(text[c]))
        {
            letters++;
        }
        c++;
    }
    return letters;
}

int count_words(string text)
{
    //inicalise variables
    int words = 0;
    int l = 0;

    //loop through characters in string
    while (text[l] != '\0')
    {
        //If charager is a space and not first or last character words++
        if (isspace(text[l]))
        {
            words++;
        }
        l++;
    }
    words++;

    return words;
}

int count_scentences(string text)
{
    //iniciate local veriables
    int scentence = 0;
    int l = 0;

    //loop through charicters in string
    while (text[l] != '\0')
    {
        //If charicter is '.' or '!' or '?' add 1 to scentence
        if (text[l] == '.' || text[l] == '!' || text[l] == '?')
        {
            scentence++;
        }
        l++;
    }

    return scentence;
}

float colemanliau_index(int letters, int words, int scentences)
{
    //iniciate variabels
    float l = (float) letters / (float) words * 100;
    float s = (float) scentences / (float) words * 100;

    float index = 0.0588 * l - 0.296 * s - 15.8;

    return index;
}
