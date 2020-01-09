#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef unsigned long int uint16_T;
#define MAX_STRING_LENGTH (uint16_T)1000000

typedef struct{
    uint16_T order;
    char ch;
}char_t;

unsigned short int index_from_char(char ch);


 void transform_text_to_char_t(const char * const text,char_t * bwt,uint16_T * rep_sort){
    uint16_T i = 0;
    while(text[i] != '\0'){
        rep_sort[index_from_char(text[i])]++;
        bwt[i].ch = text[i];
        bwt[i].order = rep_sort[index_from_char(text[i])];
        i++;
    }
}

 void print_char_t(char_t * text,uint16_T length){
     uint16_T i = 0;
    for(i = 0;i < length;i++){
        printf("<%c,%lu>  [%lu]\n",text[i].ch,text[i].order,i);
    }
    printf("\n");

 }

unsigned short int index_from_char(char ch){
    unsigned short int ret = 0;
    switch(ch){
        case 'A': ret = 0; break;
        case 'C': ret = 1; break;
        case 'G': ret = 2; break;
        case 'T': ret = 3; break;
        case '$': ret = 4; break;
        default: printf("DEFAULT %c \n",ch); ret = 5; break;
    }
    return ret;
}

uint16_T compute_offset(char_t bwt,uint16_T * rep_sort){
   unsigned short int ind  = index_from_char(bwt.ch),i = 0;
   uint16_T ret_ind = 0;
    for(i = 0;i < ind;i++){
        ret_ind += rep_sort[i];
    }
    return ret_ind + bwt.order;
}


int main(void){
    char * text = malloc( (MAX_STRING_LENGTH+1) * sizeof(*text));
    gets(text);

    const uint16_T text_length = strlen(text);


    char_t * bwt = malloc((text_length+1)*sizeof(*bwt));
    if(bwt == NULL) printf("ERROR : NULL POINTER \n");

    char_t * first_colm = malloc((text_length+1)*sizeof(*first_colm));
    if(first_colm == NULL) printf("ERROR : NULL POINTER \n");

    char * original_text = malloc((text_length+1)*sizeof(*original_text));
    if(original_text == NULL) printf("ERROR : NULL POINTER \n");
    uint16_T rep_sort[5] = {0};

    transform_text_to_char_t(text,bwt,rep_sort);

    uint16_T current = 0;
    long int  original = text_length;
    original_text[original--] = '\0';
    original_text[original--] = '$';

    while(original >= 0 && current < text_length){
        original_text[original--] = bwt[current].ch;
        current = compute_offset(bwt[current],rep_sort);
    }

    printf("%s\n",original_text);
    return 0;
}
