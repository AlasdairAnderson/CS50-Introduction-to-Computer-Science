#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char LETTER[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //test
    //printf("Player1: %i Player2: %i\n", score1, score2);
    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
        return 0;
    }
    else
    {
        printf("ERROR\n");
        return 1;
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int sum = 0;

    //Loop through charicters to assess their value
    int i = 0;
    while (word[i] != '\0')
    {
        //convert charicter to lower
        char c = tolower(word[i]);

        //evaluate if character is alphabetical
        if (isalpha(c))
        {
            //loop through and compair charicter to letter array
            for (int j = 0; j < 26; j++)
            {
                //evaluate if character is same as letter
                if (c == LETTER[j])
                {
                    sum += POINTS[j];
                }
            }

        }
        i++;
    }
    return sum;
}
