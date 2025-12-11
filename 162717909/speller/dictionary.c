// Implements a dictionary's functionality
#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

bool sizeflag = false;
int sizenumber = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int len = strlen(word);
    int index = hash(word);
    char wordcopy[LENGTH + 1];
    for (int i = 0; i < len; i++)
    {
        wordcopy[i] = tolower(word[i]);
    }
    wordcopy[len] = '\0';

    node *p = table[index];
    while (p != NULL)
    {
        int n = strcmp(p->word, wordcopy);
        if (n == 0)
        {
            return true;
        }
        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int len = strlen(word);

    int a = toupper(word[0]) - 'A';
    int b = 0;
    int c = 0;

    if (len > 1)
    {
        b = toupper(word[1]) - 'A';
    }
    if (len > 2)
    {
        c = toupper(word[2]) - 'A';
    }
    return a * 26 * 26 + b * 26 + c;
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("file error");
        return false;
    }
    // Read each word in the file
    char newword[100];
    while (fscanf(source, "%s", newword) == 1)
    {
        // Add each word to the hash table
        int goal = hash(newword);
        if (goal != -1)
        {
            node *newnode = malloc(sizeof(node));
            if (newnode == NULL)
            {
                printf("error malloc");
                return false;
            }
            strcpy(newnode->word, newword);
            newnode->next = table[goal];
            table[goal] = newnode;
            sizenumber++;
        }
    }
    sizeflag = true;
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (sizeflag == true)
    {
        return sizenumber;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // 遍历node数组
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p != NULL)
        {
            node *next = p->next;
            free(p);
            p = next;
        }
    }
    return true;
}
