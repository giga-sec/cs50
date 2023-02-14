#include <cs50.h>
#include <stdio.h>

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
void lock_pairs(void);
void print_winner(void);
int chain(int original_winner, int original_loser, int winner, int new_loser);
int check_winner(int loser);

// User defined functions
int bubbleSort(int *arr, int arr_len);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (name == candidates[i])
        {
            ranks[rank] = i;
            return true;
        }
    }
    // Name doesn't exists
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Row
    for (int i = 0; i < candidate_count; i++)
    {
        for (int column = 0; column < candidate_count; column++)
        {
            // int indexOf_prefCandidate = ranks[i];
            if (ranks[i] != column)
            {
                // Scan the previous preferred candidate
                int exclude = 0;
                for (int k = i; k > 0; k--)
                {
                    // Identify if previous pref candidate matched with current column
                    if (column == ranks[k - 1])
                    {
                        exclude = 1;
                        break;
                    }
                }

                // If current column didn't match with any previous preferred candidate
                if (exclude == 0)
                {
                    preferences[ranks[i]][column]++;
                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // i and j are the position index of the candidates
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }
            else  // assumes that a tie exists
            {
                continue;
            }
            pair_count++;
        }
    }
    return;
}




// Sort pairs in decreasing orde    r by strength of victory
void sort_pairs(void)
{
    int arr_len = pair_count;  // this is a temp len for pair_count

    // This is bubble sort algorithm
    while (arr_len != 0)  // 0 means all numbers are now sorted
    {
        // check if swapping occurs
        int swapped = 0;

        for (int i = 0; i < (arr_len - 1); i++)
        {
            int winner1 = pairs[i].winner;
            int loser1 = pairs[i].loser;
            int winner2 = pairs[i + 1].winner;
            int loser2 = pairs[i + 1].loser;

            // preferences[winner1][loser1] - preference[loser1][winner1]
            // basically is (winner's vote preferences - losers vote preferences)
            int first_victStren = preferences[winner1][loser1] - preferences[loser1][winner1];
            int sec_victStren = preferences[winner2][loser2] - preferences[loser2][winner2];
            if (first_victStren < sec_victStren)  // Decreasing
            {
                // Swap
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];  // Higher number to left
                pairs[i + 1] = temp;  // Lower number to right
                swapped = 1;
            }
        }
        // represents how many digits left are unsorted
        arr_len -= 1;
        // no swapping means the array is already sorted
        // so no need for further comparison
        if (swapped == 0)
        {
            break;
        }
    }
    return;
}


int check_winner(int loser)
{
    // See if each column in the losers locked row has a single true in it
    for (int i = 0; i < candidate_count; i++)
        if (locked[loser][i] == true)
        {
            return i;  // Return the new losers index
        }
    return 0;  // The loser is not a winner to other candidate
}

int check_loser(int winner)
{
    // See if each row in the winners locked column has a true in it
    for (int i = 0; i < candidate_count; i++)
        if (locked[winner][i] == true)
        {
            return i;  // Return the new winners index
        }
    return 0;  // The loser is not a winner to other candidate
}

int chain(int original_winner, int original_loser, int winner, int loser)
{
    // See if the loser is a winner to other locked pair array
    int new_loser = check_winner(loser);

    // See if the winner is a loser to other locked pair array
    int new_winner = check_loser(winner);

    if (new_loser == 0)
    {
        // The loser is not a winner to other candidate
        return 0;  // Safe to lock pair
    }

    if (loser == original_winner)
    {
        return 1;  // Creates a cycle, so skip adding it
    }

    if (winner == original_loser)
    {
        return 1;  // creates a cycle, so skip adding it
    }

    return chain(original_winner, original_loser, new_winner, new_loser);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // The cs50 explanation wasn't enough so I had to look for explanations
    // Code is written by me
    // Source: https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9

    for (int i = 0; i < pair_count; i++)
    {
        // Get the pair
        int w = pairs[i].winner;
        int l = pairs[i].loser;

        // Lock the pair first
        locked[w][l] = true;


        if (chain(w, l, w, l) != 0)
        {
            locked[w][l] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Scan each column
    for (int column = 0; column < candidate_count; column++)
    {
        int row;
        for (row = 0; row < candidate_count; row++)
        {
            if (locked[row][column] == true)
            {
                break;
            }
        }

        // If all rows in the column have been checked
        if (locked[row][column] == false)
        {
            printf("%s\n", candidates[column]);
        }
    }
    return;
}