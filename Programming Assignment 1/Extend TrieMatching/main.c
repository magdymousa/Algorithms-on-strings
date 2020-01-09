#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"trie.h"

#define MAX_STRING_LENGTH 100
#define MAX_TEXT_LENGTH 10000UL


int main(void){
    node_t root;
    root = Trie_Create();
    char text[MAX_TEXT_LENGTH + 2];
    gets(text);
    int n = 0;
    scanf("%d\n",&n);
    char  str[MAX_STRING_LENGTH + 2];
    while(n--){
        gets(str);
        strcat(str,"$");
        Trie_AddString(root,str);
    }
    //Trie_Print(root);
    unsigned int i = 0;
    while(text[i] != '\0'){
        if(PrefixTrieMatching(&text[i++],root)){
            printf("%d ",i-1);
        }
    }

    return 0;
}
