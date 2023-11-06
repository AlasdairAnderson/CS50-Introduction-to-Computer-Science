// Implement a program that runs a Tideman election
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool make_circle(int circle_start, int loser);
void lock_pairs(void);
int is_source(int winner);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    //if name is a match to argv[i]
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(name, candidates[i]) == 0)
        {
            //update the ranks array to indicate that the candidtate is their rank preferance (where 0 is first and so on)
            // return true if rank was successfully recorded
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    //Update the global preferences array to add the current voter's preferences
    //recall that preferences[i][j] should represent the number of voters who prefer candidate i over candidate j
    for (int rank = 0; rank < candidate_count; rank++)
    {
        for (int candidate = 0; candidate < candidate_count; candidate++)
        {
            if (ranks[rank] == candidate)
            {
                for (int opperstion = 0; opperstion < candidate_count; opperstion++)
                {
                    //Is current oppersition a higher rated candidate
                    bool prevcandiate = false;
                    for (int i = 0; i < rank; i++)
                    {
                        if (ranks[i] == opperstion)
                        {
                            prevcandiate = true;
                        }
                    }
                    //if previous candiate == flase && candidate != opperstion
                    if (prevcandiate == false && candidate != opperstion)
                    {
                        preferences[candidate][opperstion] += 1;
                    }
                }
            }
        }

    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int candidate = 0; candidate < candidate_count; candidate++)
    {
        for (int oppersition = 0; oppersition < candidate_count; oppersition++)
        {
            if (preferences[candidate][oppersition] > preferences[oppersition][candidate])
            {
                pairs[pair_count].winner = candidate;
                pairs[pair_count].loser = oppersition;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //look at pairs array
    //sort array form pair array winner with the strongest preference to weekest pair array winner with weekest preference
    for (int l = 0; l < pair_count; l++)
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair t = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = t;
            }
        }
    }
    return;
}

// Check to see if pair makes a circle
bool make_circle(int circle_start, int loser)
{
    if (loser == circle_start)
    {
        //If the current loser is the circle start it makes circle
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (make_circle(circle_start, i))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //Starting with the strongest pair
    //for pairs[0] to pairs[n-1]
    for (int i = 0; i < pair_count; i++)
    {
        //if all condaidates not = losers
        if (make_circle(pairs[i].winner, pairs[i].loser) == false)
        {
            //Lock the pairs unless it makes a circle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}



// Print the winner of the election
void print_winner(void)
{
    // TODO
    //winner is the candidate with no true value in their pair[i].loser column
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;

                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
