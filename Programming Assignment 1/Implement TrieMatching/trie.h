#ifndef TRIE_H
#define TRIE_H


#include <stdio.h>
#include <stdlib.h>

#define debug 0

typedef struct trie_tag * node_t;

node_t Trie_Create(void);
void Trie_AddString(node_t root,char * pattern);
void Trie_Print(node_t root);
int PrefixTrieMatching(char * text,node_t root);

//void output_trie_level_oder(node_t root);

#endif // TRIE_H
