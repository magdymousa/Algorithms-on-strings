#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef unsigned short int uint16_T;
#define MAX_STRING_LENGTH (uint16_T)1000
#define DEBUG 0



void print_array_of_strings(char ** array,uint16_T count){
    uint16_T i = 0;
    for(i = 0;i < count;i++){
        printf("%s\n",array[i]);
    }
    printf("\n");
}

uint16_T sort_ptrs(char * ptr1,char * ptr2){
    uint16_T ret = 0;
    uint16_T i = 0;
    while(ptr1[i] == ptr2[i] && ptr1[i] != '\0'){
        i++;
    }
    if(ptr1[i] < ptr2[i]) ret = 0;
    else ret = 1;
    if(ptr2[i] == '$') ret = 1;

    return ret;
}

void sort_array_of_strings(char ** array,uint16_T count){
    uint16_T i = 0,j = 0;
    for(i = 0;i < count-1;i++){
        for(j = i+1;j < count;j++){
            if(sort_ptrs(array[i],array[j])){
                char * temp = array[j];
                array[j] = array[i];
                array[i] = temp;
            }
        }
    }
}



void cycle_text(const char * const text,char * const ptr,uint16_T start,uint16_T length){
    if(start){
        char dummy[length+1];
        strcpy(dummy,text);
        dummy[start] = '\0';
        strcpy(ptr,&text[start]);
        strcat(ptr,dummy);
    }
    else{
        strcpy(ptr,text);
    }
}

int main(void){

    char text[MAX_STRING_LENGTH];
    gets(text);
    uint16_T i = 0;
    const uint16_T text_length = strlen(text);
    char ** M_text = malloc(text_length*sizeof(*M_text));

    for(i = 0;i < text_length;i++){
        M_text[i] = malloc((text_length+1) * sizeof(*M_text[i]));
        if(M_text[i] == NULL) printf("ERROR : NULL POINTER \n");
    }

    for(i = 0;i < text_length;i++){
        cycle_text(text,M_text[i],i,text_length);
    }

    sort_array_of_strings(M_text,text_length);
    for(i = 0;i < text_length;i++){
        printf("%c",M_text[i][text_length-1]);
    }
    printf("\n");

    return 0;
}
