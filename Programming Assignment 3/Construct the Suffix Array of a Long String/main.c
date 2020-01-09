#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

#define MAX_STRING_LENGTH (uint32_t)200001
#define DEBUG 021


uint8_t index_from_char(char ch);
uint32_t *  SortCharacters(char * S,uint32_t len,uint32_t * count);
void PrintInts(uint32_t * array,uint32_t len);
uint32_t *  ComputeCharClasses(char * S,uint32_t len,uint32_t * order);
uint32_t * SortDoubled(char * S,uint32_t len,uint32_t L,uint32_t * order,uint32_t * Class);
uint32_t * updateclasses(uint32_t * neworder,uint32_t len,uint32_t * Class,uint32_t L);


int main(void){
    char * S = malloc(MAX_STRING_LENGTH*sizeof(*S));
    gets(S);
    uint32_t text_length = strlen(S);

    uint32_t count[5] ={0};
    uint32_t * order = SortCharacters(S,text_length,count);
    uint32_t * Class = ComputeCharClasses(S,text_length,order);

    uint32_t L =1;
    while(L < text_length){
        order =  SortDoubled(S,text_length,L,order,Class);
        Class =  updateclasses(order,text_length,Class,L);
        //PrintInts(order,text_length);
        L = 2*L;
    }

    PrintInts(order,text_length);

     return 0;
}

uint32_t * updateclasses(uint32_t * neworder,uint32_t len,uint32_t * Class,uint32_t L){
    uint32_t * newclass = calloc(len,sizeof(*newclass));
    if(newclass == NULL) printf("NULL PTR\n");
    newclass[neworder[0]] = 0;
    uint32_t i = 0;
    uint32_t cur,prev,mid,midprev;

    for(i = 1;i < len;i++){

        cur = neworder[i];
        prev = neworder[i-1];
        mid = cur + L;
        midprev = (prev+L) % len;

        if(Class[cur] != Class[prev] || Class[mid] != Class[midprev] ){
            newclass[cur] = newclass[prev] + 1;
        }
        else{
            newclass[cur] = newclass[prev];
        }
    }
    return newclass;
}

uint32_t * SortDoubled(char * S,uint32_t len,uint32_t L,uint32_t * order,uint32_t * Class){
    uint32_t * count = calloc(len,sizeof(*order));
    uint32_t * neworder = calloc(len,sizeof(*order));
    int32_t i = 0;
    for(i = 0;i < len;i++){
        count[Class[i]]++;
       //PrintInts(count,len);
    }
    for(i = 1;i < len;i++){
        count[i] = count[i] + count[i-1];
        //PrintInts(count,len);
    }
    uint32_t start = 0;
    uint32_t cl = 0;

    for(i = len - 1;i >= 0;i--){
       start = (order[i] - L + len ) % len;
       cl = Class[start];
       count[cl] --;

       neworder[count[cl]] = start;
    }

    free(count);
    return neworder;
}

uint8_t index_from_char(char ch){
    uint8_t ret = 0;
    switch(ch){
        case '$': ret = 0; break;
        case 'A': ret = 1; break;
        case 'C': ret = 2; break;
        case 'G': ret = 3; break;
        case 'T': ret = 4; break;
        default: printf("DEFAULT %c \n",ch); ret = 5; break;
    }
    return ret;
}

uint32_t *  SortCharacters(char * S,uint32_t len,uint32_t * count){
    uint32_t * order = malloc(len*sizeof(*order));
    int32_t i = 0;
    for(i = 0;i < len;i++){
        count[index_from_char(S[i])]++;
    }
     for(i = 1;i < 5;i++){
        count[i] = count[i] + count[i - 1];
    }
     char ch;
    for(i = len - 1;i >= 0;i--){
        ch = S[i];

        count[index_from_char(ch)]--;
        order[count[index_from_char(ch)]] = i;
    }
    return order;
}

uint32_t *  ComputeCharClasses(char * S,uint32_t len,uint32_t * order){
    uint32_t * Class = malloc(len*sizeof(*order));
    uint32_t i = 0;
    Class[order[0]] = 0;
    for(i = 1;i < len;i++){

        if(S[order[i]] != S[order[i-1]]){
            Class[order[i]] = Class[order[i-1]] + 1;
        }
        else{
            Class[order[i]] = Class[order[i-1]];
        }
    }
    return Class;
}


void PrintInts(uint32_t * array,uint32_t len){
    #if DEBUG == 1
        printf("ARRAY LEN = %u\n",len);
    #endif // DEBUG

    uint32_t i = 0;
    for(i = 0;i < len;i++){
        printf("%u ",array[i]);
    }
    printf("\n");
}
