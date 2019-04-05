// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false

#define DICTIONARY_SIZE 143091

typedef struct node
{
    char word[LENGTH+1];
    struct node* next;
}
node;

int word_counter;
node* hashtable[DICTIONARY_SIZE];
int hash (const char* word);

bool check(const char *word)
{
    char lower_word[LENGTH+1];
    for (int i = 0; i < LENGTH+1; i++)
        lower_word[i] = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
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

    int hashcode = hash(lower_word);
    node* traversal = hashtable[hashcode];

    while (traversal != NULL)
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

    //free(traversal);

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE* infile = fopen(dictionary, "r");

    if (infile == NULL)
    {
        fprintf(stderr, "Could not open %s\n", dictionary);
        return 1;
    }

    word_counter = 0;

    char lower_word[LENGTH+1];

    for (int i = 0; i < LENGTH+1; i++)
        lower_word[i] = 0;

    while (fscanf(infile, "%s", lower_word) == 1)
    {
        node* new_node = malloc(sizeof(node));

        strcpy(new_node->word, lower_word);

        int hashcode = hash(new_node->word);

        if (hashtable[hashcode] == NULL)
        {
            hashtable[hashcode] = new_node;
            new_node->next = NULL;
            word_counter++;
        }
        else
        {
            new_node->next = hashtable[hashcode];
            hashtable[hashcode] = new_node;
            word_counter++;
        }
    }

    //free(new_node);

    fclose(infile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < DICTIONARY_SIZE; i++)
    {
        node* cursor = hashtable[i];

        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free (temp);
        }

        free (cursor);
    }

    return true;
}

int hash (const char* word)
{
    int hash = 0;
    int n;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if(isalpha(word[i]) || word[i] == '\'')
        {
            n = word[i] - 'a' + 1;
        }

        else
        {
            n = 27;
        }

        hash = ((hash << 3) + n) % DICTIONARY_SIZE;
    }

    return hash;
}