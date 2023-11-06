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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 90000;

// Hash table
node *table[N];

// Global File pointer
FILE *openDictionary = NULL;

// Global Word Counter
int wordCount;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Hash word
    int index = hash(word);

    // Access linked list at the index in the hash table
    node *cursor = table[index];

    // Traverse linked list, looking for the word (strcasecmp)
    // Valgrind Error: Conditional jump or move depends on unitiialised vlaue(s): (file: dictionary.c, line: 42)
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int sum = 0;
    for (int j = 0; word[j] != '\0'; j++)
    {
        sum += tolower(word[j]) - 'a';
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open Dictionary File
    FILE *loadedDictionary = fopen(dictionary, "r");
    if (loadedDictionary == NULL)
    {
        printf("Memory Error\n");
        // fclose(loadedDictionary);
        return false;
    }

    // Pointers in table is Null
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Read strings from file one at a time
    char wordBuffer[LENGTH + 1];

    while (fscanf(loadedDictionary, "%s", wordBuffer) != EOF)
    {
        // Create a new node for new word
        // 56 bytes in 1 blocks are still reachable in loss record 1 of 1: (file: dictionary.c, line: 86)
        node *newWord = malloc(sizeof(node));
        if (newWord == NULL)
        {
            printf("Memory Error\n");
            free(newWord);
            return false;
        }
        // Get Hash code
        int index = hash(wordBuffer);

        // Copy word to new node
        strcpy(newWord->word, wordBuffer);
        newWord->next = NULL;

        // Set position index in table equal to node
        if (table[index] == NULL)
        {
            table[index] = newWord;
        }
        else
        {
            // link new word's pointer to current head of the list
            newWord->next = table[index];

            // Insert node as head of list
            table[index] = newWord;
        }

        wordCount++;
    }
    fclose(loadedDictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *temp = NULL;
    int freedListCount = 0;

    // iterate through link list table
    for (int i = 0; i < N; i++)
    {
        // Invalid read of size 8: (file: dictionary.c, line: 143)
        // Conditional jump or move depends on uninitialised value(s): (file: dictionary.c, line: 143)
        if (table[i] != NULL)
        {
            cursor = table[i];

            while (cursor != NULL)
            {
                // set cursor to root
                temp = cursor;

                // set new root to cursor->next
                cursor = cursor->next;
                free(temp);

                freedListCount++;
            }
        }

        // if (cursor == NULL)
        // {
        //     freedListCount++;
        // }
    }

    if (freedListCount == wordCount)
    {
        return true;
    }

    return false;
}
