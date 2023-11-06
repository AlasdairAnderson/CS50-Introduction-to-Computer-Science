//implement a program that runs a plurality election

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //takes a single argument
    //loop through elements
    for (int i = 0; i < candidate_count; i++)
    {
        //if name matches one of the element names
        if (strcasecmp(candidates[i].name, name) == 0)
        {
            //increment element names vote total and return true
            candidates[i].votes += 1;
            return true;
        }
    }
    //if name does not match one of the element names
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO

    int w = candidates[0].votes;
    //calculate who has the most votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (w < candidates[i].votes)
        {
            w = candidates[i].votes;
        }
    }

    //print out name of canditate who received the most votes in the election
    for (int i = 0; i < candidate_count; i++)
    {
        if (w == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    //if tie print out both names on separate lines
    return;
}
