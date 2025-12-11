#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define max_voter 100
#define max_candidate 9

typedef struct
{
    string name;
    int vote;
    bool eliminate;
}candidate;

int preference[max_voter][max_candidate];
candidate candidates[max_candidate];

int candidate_count;
int voter_count;

bool vote(string name, int rank, int voter);
void tabulate(void);
bool print_win(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void clear(void);

int main(int argc, string argv[])
{
    if (argc == 1)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc -1;

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i+1];
        candidates[i].vote = 0;
        candidates[i].eliminate = false;
    }
    if (candidate_count > max_candidate)
    {
        printf("Maximum number of candidates is %d\n", max_candidate);
        return 2;
    }

    voter_count = get_int("Number of voters: ");

    if (voter_count > max_voter)
    {
        printf("Maximum number of voters is %i\n", max_voter);
        return 3;
    }

    if (voter_count < 0)
    {
        printf("the number invalid");
        return 4;
    }

    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; i < candidate_count; j++)
        {
            string name = get_string("Rank : %d", j+1);
            if (vote(name, j, i))
            {
                printf("Invalid vote.\n");
                return 5;
            }
        }
        printf("\n");
    }

    while (true)
    {
        tabulate();
        bool win = print_win();
        if (win)
        {
            break;
        }
        int min = find_min();
        bool tie = is_tie(min);
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (candidates[i].vote == min)
                {
                    printf("%s\n",candidates[i].name);
                }
            }
            break;
        }
        eliminate(min);
        clear();
    }

    return 0;
}

bool vote(string name, int rank, int voter)
{
    int index = -1;
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i].name))
        {
            index = i;
            preference[voter][i] = rank;
            return false;
        }
    }
        return true;
}
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        int min = 0;
        bool flag = true;
        while (flag == true)
        {
            for (int j = 0; j <candidate_count; j++)
            {
                if (preference[i][j] == min || candidates[min].eliminate == false)
                {
                    candidates[min].vote++;
                    flag = false;
                    break;
                }
            }
            min++;
        }
    }
}
bool print_win(void)
{
    // int count = 0;
    // int half = (voter_count + 1) / 2;
    // int index = -1;
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     if (candidates[i].vote > count)
    //     {
    //         count = candidates[i].vote;
    //         index = i;
    //     }
    // }
    // if (count > voter_count)
    // {
    //     printf("%s\n", candidates[i].name);
    //     return ture;
    // }
    // return false;
    int half = (voter_count + 1) / 2;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].vote > half)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}
int find_min(void)
{
    int min = max_voter + 1;
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].vote < min)
        {
            min = candidates[i].vote;
        }
    }
    return min;
}

bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].vote != min && candidates[i].eliminate == false)
        {
            return false;
        }
    }
    return true;
}
void eliminate(int min)
{
    for (int i = 0; i <candidate_count; i++)
    {
        if (candidates[i].vote == min)
        {
            candidates[i].eliminate = true;
        }
    }
}
void clear(void)
{
    for (int i = 0; i< candidate_count;i++)
    {
        candidates[i].vote = 0;
    }
}
