#include "bioinformatics.h"

void bioinformatics_pretty_print_base_count(char*genome) {
    int As=0,Gs=0,Ts=0,Cs=0;
    int len = strlen(genome);
    printf("%s\n",genome);
    for(int i=0; i<len; i++) {
        if (genome[i] == 'A')
            As++;
        else if (genome[i] == 'G')
            Gs++;
        else if (genome[i] == 'T')
            Ts++;
        else if (genome[i] == 'C')
            Cs++;
    };
    printf("Base count:\n");
    printf("A:[%.5i] - T:[%.5i]\n",As,Ts);
    printf("G:[%.5i] - C:[%.5i]\n",Gs,Cs);
};

char* bioinformatics_produce_mutation(char*genome) {
    int len = strlen(genome);
    char*nuovo;
    int pos = rand()%len;
    switch( rand()%3 ) {
        case 0 : {
            printf("swapping %c,",genome[pos]);
            int tmp = rand()%4;
            nuovo = (char*)malloc(sizeof(char)*(len+1));
            for(int i=0; i<len; i++) {
                if (i!=pos)
                    nuovo[i] = genome[i];
                else
                    nuovo[i] = (tmp==0) ? 'A' : ((tmp==1) ? 'T' : ((tmp==2) ? 'G' : ((tmp==3) ? 'C' : '\0')));
            };
            printf(" with %c\n",nuovo[pos]);
            nuovo[len] = '\0';
        }; break;
        case 1 : {
            printf("deleting base %c in position %i\n",genome[pos],pos);
            nuovo = (char*)malloc(sizeof(char)*(len));
            for(int i=0; i<len-1; i++) {
                if (i>=pos)
                    nuovo[i] = genome[i+1];
                else
                    nuovo[i] = genome[i];
            };
            nuovo[len-1] = '\0';
        }; break;
        case 2 : {
            int tmp = rand()%4;
            printf("adding base ");
            nuovo = (char*)malloc(sizeof(char)*(len+2));
            for(int i=0; i<len+1; i++) {
                if (i==pos)
                    nuovo[i] = (tmp==0) ? 'A' : ((tmp==1) ? 'T' : ((tmp==2) ? 'G' : ((tmp==3) ? 'C' : '\0')));
                else if (i>pos)
                    nuovo[i] = genome[i-1];
                else if (i<pos)
                    nuovo[i] = genome[i];
            };
            printf("%c in position %i\n",nuovo[pos],pos);
            nuovo[len+1] = '\0';
        }; break;
    };
    return nuovo;
};

char* bioinformatics_mutate_sequence(char*genome) {
    char*newgenome = bioinformatics_produce_mutation(genome);
    char*old;
    for(int i=0; i<9; i++) {
        old = newgenome;
        newgenome = bioinformatics_produce_mutation(newgenome);
        free(old);
    };
    return newgenome;
};

char* bioinformatics_generate_random_sequence(int minlen) {
    int tmp;
    int len = minlen+(rand()%minlen);
    char* nuovo = (char*)malloc(sizeof(char)*(len+1));
    for(int i=0; i<len; i++) {
        tmp = rand()%4;
        nuovo[i] = (tmp==0) ? 'A' : ((tmp==1) ? 'T' : ((tmp==2) ? 'G' : ((tmp==3) ? 'C' : '\0')));
    };
    nuovo[len] = '\0';
    return nuovo;
};