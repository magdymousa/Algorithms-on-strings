#include "trie.h"

struct trie_tag{
unsigned long int trie_nodes_count;
unsigned long int label;
char symbol;
unsigned int  branches_count;
node_t branches;
};

static void Trie_AddBranchToNode(node_t * node,struct trie_tag branch);
static int Trie_NodeHasSymbol(node_t * currentNode,char current_symbol);


static void Trie_AddBranchToNode(node_t * node,struct trie_tag branch){

    (*node)->branches = realloc((*node)->branches,((*node)->branches_count + 1) * sizeof(*((*node)->branches)));
    (*node)->branches[(*node)->branches_count] = branch;
    ((*node)->branches_count)++;
    (*node) = &(*node)->branches[(*node)->branches_count - 1];
   #if debug == 1
        printf("added branch is %d,%c with count = %d\n",(*node)->label,(*node)->symbol,(*node)->branches_count);
   #endif // debug
}


static int Trie_NodeHasSymbol(node_t * currentNode,char current_symbol){
    #if debug == 1
        printf("searching for symbol in %d,%c  branches = %d\n",(*currentNode)->label,(*currentNode)->symbol,(*currentNode)->branches_count);
    #endif // debug
   int j = 0, ret = 0;
    for(j = 0;j < (*currentNode)->branches_count;j++){
        if((*currentNode)->branches[j].symbol == current_symbol){
            (*currentNode) = &(*currentNode)->branches[j];
            ret = 1;
            break;
        }
    }
    return ret;
}

void Trie_AddString(node_t root,char * pattern){
    node_t currentNode = root;
    int i = 0;
    char current_symbol = pattern[i++];
    #if debug == 1
        printf("try to add pattern %s\n",pattern);
    #endif // debug
    while(current_symbol != '\0'){
             if(!Trie_NodeHasSymbol(&currentNode,current_symbol)){
                 #if debug == 1
                   //printf("not found %c\n",current_symbol);
                #endif // debug
               // }
                struct trie_tag branch;
                branch.branches_count = 0;
                branch.symbol = current_symbol;
                branch.label = root->trie_nodes_count++;
                branch.branches = NULL;
                Trie_AddBranchToNode(&currentNode,branch);
            }
            else{
                #if debug == 1
                    printf("found %c\n",current_symbol);
                #endif // debug

            }
            current_symbol = pattern[i++];
        }
}

node_t Trie_Create(void){
    node_t head = malloc(sizeof(*head));
    head->branches = NULL;
    head->branches_count = 0;
    head->label = 0;
    head->symbol = '!';
    head->trie_nodes_count = 1;
    return head;
}



void Trie_Print(node_t root){
    node_t current_node = root;
    int i = 0;
    int counter = current_node->branches_count;
    #if debug == 1
        printf("branches_count = %d\n",current_node->branches_count);
   #endif // debug

    for(i = 0;i < counter;i++){
        printf("%ld->%ld:%c\n",current_node->label,current_node->branches[i].label,current_node->branches[i].symbol);
        Trie_Print(&(current_node->branches[i]));
    }
}
