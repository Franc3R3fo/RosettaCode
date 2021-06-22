#include "bitcoin.h"

int test0() {
    char* src [] = {
        "Lo8zNd27ojJF2KzuCyKXzzUGKcgWUx991R",
        "1Q1pE5vPGEEMqRcVRMbtBK842Y6Pzo6nK9",
        "1AGNa15ZQXAZUgFiqJ2i7Z2DPU2J6hW62i",
        "1Q1pE5vPGEEMqRcVRMbtBK842Y6Pzo6nJ9",
        "1AGNa15ZQXAZUgFiqJ2i7Z2DPU2J6hW62I",
        "6UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM",
        NULL
    };
    
    int res [] = {
        1,0,0,1,2,0,-1
    };
    
    int i=0,ec;
    while((src[i]!=NULL) && (res[i] != -1)) {
        ec = bitcoin_validate_address(src[i]);
        if (ec == res[i]) {
            printf("test[%i] is ok!\n",i);
        } else {
            printf("test[%i] got an error: expected %i, got %i\n",i,res[i],ec);
        };
        ++i;
    };
};

int test1() {
    char* src [] = {
        "50863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B2352",
        "2CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BA6",
        NULL
    };
    
    char* res [] = {
        "6UwLL9Risc3QfPqBUvKofHmBQ7wMtjvM",
        NULL
    };
    
    int i=0,j=0; char*ec;
    while((src[i]!=NULL) && (res[i]!=NULL)) {
        ec = bitcoin_address_of_public_point(src[i],src[i+1]);
        if ((ec != NULL) && (strcmp(ec,res[j]) == 0)) {
            printf("test[%i] is ok!\n",i);
        } else {
            printf("test[%i] got an error: expected %s, got %s\n",i,res[j],ec);
        };
        i+=2; ++j;
    };
};

int main() {
    test0();
    test1();
};