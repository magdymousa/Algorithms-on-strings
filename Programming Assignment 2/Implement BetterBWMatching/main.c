#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#define DEBUG 12

#define MAX_STRING_LENGTH (uint32_t)1000000


unsigned short int index_from_char(char ch);


void PrintInts(uint32_t * array,uint32_t len);
unsigned short int index_from_char(char ch);
uint32_t BWMatching(uint32_t * FirstOccurrence,char * LastColumn,char * Pattern,uint32_t len,uint32_t len2,uint32_t **Count_Symbol);
void Compute_FirstOccurrence(uint32_t *FirstOccurrence,char * LastColumn, uint32_t **Count_Symbol);
//uint32_t Count_Symbol(char ch,uint32_t NFirst,char * column);
uint8_t FindSymbol(char * LastColumn,uint32_t top,uint32_t bottom,char sybmol);

int main(void){
    char * LastColumn = malloc( (MAX_STRING_LENGTH+1) * sizeof(*LastColumn));
    gets(LastColumn);
    uint32_t len = strlen(LastColumn);

    char * Pattern = malloc( (MAX_STRING_LENGTH+1) * sizeof(*Pattern));

    uint32_t FirstOccurrence[5] = {0};
    uint32_t ** Count_Symbol = malloc((len+1)*sizeof(*Count_Symbol));
    if(Count_Symbol == NULL) printf("NULL PTR\n");
    Compute_FirstOccurrence(FirstOccurrence,LastColumn,Count_Symbol);

    uint16_t n = 0;
    scanf("%hu\n",&n);
    uint32_t i = 0;
    char ch;
    while(n--){
        do{
        scanf("%c",&ch);
        Pattern[i++] = ch;
        }while(ch != ' ' && ch != '\n');
        Pattern[--i] = '\0';
        printf("%u ",BWMatching(FirstOccurrence, LastColumn, Pattern,len,i,(uint32_t**)Count_Symbol));
        i = 0;
    }

    return 0;
}

uint8_t FindSymbol(char * LastColumn,uint32_t top,uint32_t bottom,char sybmol){
    uint8_t ret = 0;
    uint32_t i = 0;
    for(i = top;i <= bottom;i++){
        if(LastColumn[i] == sybmol){ ret = 1; break;}
    }
    return ret;
}

uint32_t BWMatching(uint32_t * FirstOccurrence,char * LastColumn,char * Pattern,uint32_t len,uint32_t len2,uint32_t **Count_Symbol){
    uint32_t top = 0;
    uint32_t bottom = len - 1;
    uint32_t i = len2;
    char symbol;
    while(top <= bottom){
        if(i > 0){
            symbol = Pattern[--i];
            if(FindSymbol(LastColumn, top, bottom,symbol)){
                    uint8_t ind = index_from_char(symbol);
                    uint32_t counttop = *(*(Count_Symbol+top) + ind);
                    uint32_t countbottom = *(*(Count_Symbol+ (bottom+1)) + ind);

                top = FirstOccurrence[ind] + counttop;
                bottom = FirstOccurrence[ind] + countbottom - 1;
            }
            else{
                return 0;
            }
        }
        else{
            return bottom - top + 1;
        }
    }

    return 0;
}

void copy_array(uint32_t * a,uint32_t *b){
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    a[3] = b[3];
    a[4] = b[4];
}

void Compute_FirstOccurrence(uint32_t *FirstOccurrence,char * LastColumn,uint32_t ** count_symbol){
    uint32_t i = 0;
    uint32_t rep[5] = {0};
    uint8_t ind = 0;
    count_symbol[0] = calloc(5,sizeof(*count_symbol[0]));
    while(LastColumn[i] != '\0'){
        ind = index_from_char(LastColumn[i]);
        count_symbol[i+1] = calloc(5,sizeof(*count_symbol[i+1]));
          rep[ind]++;
         copy_array(count_symbol[i+1] ,rep);
          i++;
    }
     if(rep[1] ) FirstOccurrence[1] = 1;
    for(i = 2;i < 5;i++){
        if(rep[i]) FirstOccurrence[i] = rep[i-1]+FirstOccurrence[i-1];
        else{
            FirstOccurrence[i] = FirstOccurrence[i-1];
            rep[i] = rep[i-1];
        }
    }
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


unsigned short int index_from_char(char ch){
    unsigned short int ret = 0;
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
