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

// Number of buckets in hash table
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

//Loaded Word Count
int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    //send word to hash function to get index
    unsigned int index = hash(word);

    //traverse list with (strcasecmp)
    //cursor = start of the list
    node *cursor = table[index];

    while (cursor != NULL)
    {
        int test = strcasecmp(word, cursor->word);
        //is the word at this node a match?
        if (test == 0)
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
    //printf("%s\n", word);
    //https://www.strchr.com/hash_functions
    //https://eternallyconfuzzled.com/hashing-c-introduction-to-hashing

    //need to convert the case to lower here

    const int wordsize = strlen(word);

    char *temp;
    temp = (char *)malloc(sizeof(char) * wordsize);

    for (int j = 0; j < wordsize; j++)
    {
        temp[j] = tolower(word[j]);
    }

    const char *p = temp;
    unsigned h = 0;
    int i;

    for (i = 0; i < wordsize; i++)
    {
        h += p[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    int hashvalue = h % N;
    free(temp);
    return hashvalue;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *fp;

    //OPEN the dictionary file    FILE * fp;
    fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        return false;
    }

    //READ STRINGS
    //create buffer and allocate memory to it
    char *readbuffer;
    readbuffer = (char *)malloc(sizeof(char) * 46);

    while (fscanf(fp, "%s", readbuffer) == 1)
    {

        //Store
        node *n = (node *)malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //strcpy to copy word into the node
        strcpy(n->word, readbuffer);

        //pass to hash function to get index of list to place this string into
        unsigned int index = hash(n->word);

        //insert node into linked list at index, pointing to wherever the top was pointing to, then point top to this node
        n->next = table[index];
        table[index] = n;
        wordcount++;
    }
    //free the buffers
    free(readbuffer);
    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordcount;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //traverse the hash table
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        node *cursor = table[i];

        bool end = false;
        while (end != false)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;

            if (cursor->next == NULL)
            {
                end = true;
            }

        }
        free(tmp);

    }


    return true;
}

