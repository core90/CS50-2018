// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

node* first;

int word_counter = 0;


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (int i = 0, node* node_ptr = first, len = strlen; i < len; i++)
    {
        if word[i] == '\0')
        {
            if (node_ptr->is_word == true)
                return true;
            else
                return false;
        }

        int index = get_index(word[i]);
        if (node_ptr->children[index] == NULL)
            return false;

        node_ptr = node_ptr->children[index];
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
    //intialize c to get a char from dictionary unti we reach EOF
    node* first = create_init_node();
    int index;
    for (char c = fgetc(infile), node* node_ptr = first; c != EOF; c = fgetc(infile))
    {
        // if the letter is not a newline char then we need to load this letter in our trie
        if (c != '\n')
        {
            index = get_index(c);
            if (node_ptr->children[index] == NULL)
            {
                node_ptr->children[index] = create_init_node();
            }
            node_ptr = node_ptr->children[index];
        }
        else
        {
            // mark the end of the word
            node_ptr->is_word = true;
            // increment word counter because we found a complete word from infile
            word_counter++;
            // go back to homebase
            node_ptr = first;
        }
    }

    return false;
}

//returns the index corresponding to the character enterded
int index(char c)
{
    if (c == '\')
        return 26;
    else if (c >= 'a' && c <= 'z')
        return c - 'a';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A';

    // error index
    return -1;
}

node* create_init_node()
{
    node* node_ptr = malloc(sizeof(node));
    node_ptr -> is_word = false;
    for (int i = 0; i < 27; i++)
    {
        node_ptr -> children[i] = NULL;
    }
    return node_ptr;
}
// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
