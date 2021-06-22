#include "secp256k1.h"

int test1() {
    char* src [] = {
        "50863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B2352",
        "2CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BA6",
        "50863AD64A87AE8A2FE83C1AF1A8403CB53F53E486D8511DAD8A04887E5B2352",
        "2CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BF6",
        "ghia asdjsfzekfregbjdfvn bvfjbfjndxnldnlfndlbnlnflbnldnlnlnlbnls",
        "2CD470243453A299FA9E77237716103ABC11A1DF38855ED6F2EE187E9C582BA6",
        NULL
    };
    
    bool res [] = {
        true,
        false,
        false
    };
    
    int i=0,j=0; bool ec;
    while(src[i]!=NULL) {
        ec = secp256k1_belongs_to_curve_str(src[i],src[i+1]);
        if (ec == res[j]) {
            printf("test[%i] is ok!\n",i);
        } else {
            printf("test[%i] got an error: expected %s, got %s\n",i,res[j],ec);
        };
        i+=2; ++j;
    };
};

int main() {
    test1();
};