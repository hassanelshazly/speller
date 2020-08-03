// Implements a dictionary's functionality
#include "dictionary.h"

// hash funchtion
int hash(const char f)
{
    if (isalpha(f))
    {
        if (isupper(f))
        {
            return f - 'A' ;
        }
        else
        {
            return f - 'a' ;
        }
    }
    else
    {
        return 26 ;
    }
}

node *create_node()
{
    node* temp = (node*)malloc(sizeof(node));
    temp->is_word = false ;
    for (int i = 0 ; i < 27 ; i++)
    {
        temp->next[i] = NULL;
    }
    return temp ;
}
node *head ;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *temp = head ;
    for(int i = 0, n = strlen(word); i < n ; i++)
    {
        int current_letter = hash(word[i]);
        if (temp->next[current_letter])
        {
            temp = temp->next[current_letter] ; 
        }
        else
        {
            return false ;
        }
    }
    if (temp->is_word)
    {
        return true ;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    _size_ = 0 ;
    head = create_node() ;
    char word[LENGTH + 1];
    FILE * dictionary_file = fopen(dictionary , "r");
    while(fscanf(dictionary_file , "%s" , word) != EOF)
    {
        node *temp = head ;
        for(int i = 0, n = strlen(word); i < n ; i++)
        {
            int current_letter = hash(word[i]);
            if (!temp->next[current_letter])
            {
                temp->next[current_letter] = create_node();
            }
            temp = temp->next[current_letter] ; 
        }
        temp->is_word = true ;
        _size_++;
    }
    fclose(dictionary_file) ;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return _size_;
}

// Unloads dictionary from memory, returning true if successful else false
void unload_helper(node* temp)
{
    if(!temp) return ;
    for (int i = 0 ; i < 27 ; i++)
    {
        unload_helper(temp->next[i]);
    }
    free(temp);
}
bool unload(void)
{
    unload_helper(head) ;
    return true ;
}

