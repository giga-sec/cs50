// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// Increase the size of bucket for probably
const unsigned int N = 26;


// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *current = table[index];

    // Traverse the words to each bucket
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    if (word[0] >= 97)  // Small Letter
    {
        return word[0] - 97;
    }
    else  // CAPS
    {
        return word[0] - 65;
    }
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *ptr = fopen(dictionary, "r");
    if (ptr != NULL)
    {
        char word[46];  // 46 is the maximum letter of word
        int index = 0;  // Index returned by hash

        // Get the word first
        while (fscanf(ptr, "%s", word) != EOF)
        {
            // Assign Memory
            index = hash(word);
            node *new_node = malloc(sizeof(node));
            if (new_node == NULL)
            {
                return false;
            }


            // Add the new value at the beginning of linked list
            strcpy(new_node->word, word);
            new_node->next = table[index];
            table[index] = new_node;
        }
        fclose(ptr);
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    node *current;
    for (int i = 0; i <= N; i++)
    {
        current = table[i];
        while (current != NULL)
        {
            count++;
            current = current->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i <= N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

