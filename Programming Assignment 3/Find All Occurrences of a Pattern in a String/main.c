#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

 #define MAX_STRING_SIZE (uint32_t)1000000
#define DEBUG 0

void print_ints(uint32_t * array,uint32_t len){
    #if DEBUG == 1
        printf("ARRAY LEN = %u\n",len);
    #endif // DEBUG

    uint32_t i = 0;
    for(i = 0;i < len;i++){
        printf("%u ",array[i]);
    }
    printf("\n");
}

void create_suffixArray(char * str,uint32_t *suffix_array,uint32_t len){
    uint32_t i = 0,border = 0;
    suffix_array[border] = 0;

    for(i = 1;i < len;i++){
        while(border > 0 && str[i] != str[border]){
            border = suffix_array[border - 1];
        }
        if(str[i] == str[border]){
            border++;
        }
        else{
            border = 0;
        }
        suffix_array[i] = border;
    }


}

void output_matching_indices(uint32_t * suffix_array,uint32_t len,uint32_t n_pattern){
    uint32_t i = 0;
    for( i = n_pattern+1; i < len;i++){
        if(suffix_array[i] == n_pattern){
            printf("%u ",i - 2*n_pattern);
        }
    }
}

int main(){
    uint32_t n_pattern = 0 ,n_string = 0;

    char * pattern = malloc((MAX_STRING_SIZE+1) * sizeof(*pattern));
    char * string = malloc((MAX_STRING_SIZE+1) * sizeof(*string));
    gets(pattern);
    gets(string);

    n_pattern = strlen(pattern);
    n_string = strlen(string);
    char * new_str = malloc((n_pattern+n_string+2) * sizeof(*new_str));

    uint32_t suffix_array[n_pattern+n_string+1];


    if(n_pattern <= n_string){
        strcpy(new_str,pattern);
        strcat(new_str,"$");

        strcat(new_str,string);

        create_suffixArray(new_str,suffix_array,n_pattern+n_string+1);
        output_matching_indices(suffix_array,n_pattern+n_string+1,n_pattern);

    }


    return 0;
}
