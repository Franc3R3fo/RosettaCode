#include "base58.h"

int main(int argc,char**args) {
    // data
    char* src[] = {
        "ciao mondo",
        "mariuolo demme rda",
        "a",
        "abc",
        "0123456789abcde",
        NULL
    };
    char* res[] = {
        "6awNDz2Jamz4cE",
        "5Y8jwTMyLGPRyaJ5EgeRQX8C8",
        "2g",
        "ZiCa",
        "2MCaDZigsz8QzUsMDmZyN",
        NULL
    };
    int k=0;
    while(src[k]) {
        char*enc = base58_encode_str(src[k]);
        char*dec = base58_decode_str(enc);
        if (strcmp(enc,res[k]) == 0) {
            printf("OK\n");
        } else {
            printf("enc[%i], failed : %s isn't %s\n",k,dec,res[k]);
        };
        if (strcmp(dec,src[k]) == 0) {
            printf("OK\n");
        } else {
            printf("dec[%i], failed : %s isn't %s\n",k,dec,res[k]);
        };
        free(dec);
        k++;
    };
};