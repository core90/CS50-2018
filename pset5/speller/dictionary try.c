// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH+1];
    struct node *next;
}
node;

int word_counter;

node *hashtable[143091];

//node *node1 = malloc(sizeof(node));
//node *node2 = malloc(sizeof(node));
//strcpy (node1 -> word, "Hello");
//strcpy (node2 -> word, "World");
//node1 -> next = node2;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char lower_word[LENGTH+1];
    for (int i = 0; i < LENGTH; i++)
    {
        lower_word[i] = 0;
    }

    //iterate over words in dictionary and make them lower case
    for (int i = 0, n = strlen(word); i++)
    {
        if (isupper(word[i]))
        {
            lower_word[i] = tolower(word[i]);
        }

        else
        {
            lower_word[i] = word[i];
        }
    }
//************************************
    node *traversal = hashtable;

    while(traversal != NULL)
    {
        if (strcmp(lower_word, traversal->word) == 0)
        {
            return true;
        }

        else
        {
            traversal = traversal->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //read from dictionary
    FILE *infile = fopen(dictionary, "r");

    //check if dictionary file can be opened
    if (infile == NULL)
    {
        fprintf (stderr, "Could not open %s\n", dictionary);
        return 1;
    }

    while (fscanf(infile, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false
        }
        else
        {
            strcpy(new_node->word, lower_word);
        }
    }
    //return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
