#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate get_candidate(string name);

int main(void)
{
    candidate candidate_array[3];
    for (int i = 0; i < 3; i++)
    {
        candidates_array[i] = get_candidate("Enter candidates: ");
    }
}

candidate get_candidate(string name)
{
    printf("%s\n", name);
    candidate c;
    c.name = get_string("Enter a name: ");
    c.votes = get_int("Enter number of votes: ");

    return c;
}
