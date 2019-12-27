#include <stdio.h>
#include <stdlib.h>
#include "trie.h"

#define MAX_STRING_LENGTH 100


int main(){
    node_t root;
    root = Trie_Create();
    int n = 0;
    scanf("%d\n",&n);
    char  str[MAX_STRING_LENGTH];
    while(n--){
        gets(str);
        Trie_AddString(root,str);
    }
    Trie_Print(root);
    return 0;
}



