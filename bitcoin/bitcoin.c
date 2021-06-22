#include "bitcoin.h"
#include "../base58/base58.h"
#include "../sha256/sha256.h"
#include "../ripemd160/ripemd160.h"
#include "../secp256k1/secp256k1.h"

void printDetailed(const char*msg,char*str,int len) {
    printf("%s:",msg);
    for(int i=0; i<len; i++)
        printf(" %i",(unsigned char)(str[i]));
    printf("\n");
};

int bitcoin_validate_address(char*str) {
    for(int i=0; i<strlen(str); i++) {
        if (base58_is_valid_char(str[i]) != true)
            return 2;
    };
    char*dec = base58_decode_str(str);
    int len=strlen(dec);
    char*hashInput = (char*)malloc(sizeof(char)*25);
    for(int i=0; i<25; i++) {
        if (i<len)
            hashInput[24-i] = dec[len-1-i];
        else
            hashInput[24-i] = '\0';
    };
    sha256_enable_rawout();
    sha256_enable_manuallen(21);
    char* firstHash = sha256_mkhash_str(hashInput);
    sha256_enable_manuallen(32);
    char* secondHash = sha256_mkhash_str(firstHash);
    sha256_disable_manuallen();
    sha256_disable_rawout();
    for(int i=0; i<4; i++)
        if (hashInput[21+i] != secondHash[i])
            return 1;
    free(hashInput);
    free(firstHash);
    free(secondHash);
    return 0;
};

int charToHexVal(char c) {
    switch(c) {
        case '0' : return 0;
        case '1' : return 1;
        case '2' : return 2;
        case '3' : return 3;
        case '4' : return 4;
        case '5' : return 5;
        case '6' : return 6;
        case '7' : return 7;
        case '8' : return 8;
        case '9' : return 9;
        case 'a' : return 10;
        case 'A' : return 10;
        case 'b' : return 11;
        case 'B' : return 11;
        case 'c' : return 12;
        case 'C' : return 12;
        case 'd' : return 13;
        case 'D' : return 13;
        case 'e' : return 14;
        case 'E' : return 14;
        case 'f' : return 15;
        case 'F' : return 15;
        default : break;
    };
    return -1;
};

char* hex_str_of_int_to_bytes(char*X,int*final_len) {
    int lenX = strlen(X);
    char*xmsg;
    if (lenX%2==0) {
        xmsg = (char*)malloc(sizeof(char)*(lenX/2));
        for(int i=0; i<lenX; i+=2) {
            xmsg[i/2] = (char)(16*charToHexVal(X[i])+charToHexVal(X[i+1]));
        };
    } else {
        lenX++;
        xmsg = (char*)malloc(sizeof(char)*(lenX/2));
        for(int i=-1; i<lenX; i+=2) {
            if (i<0)
                xmsg[i/2] = (char)(charToHexVal(X[i+1]));
            else
                xmsg[i/2] = (char)(16*charToHexVal(X[i])+charToHexVal(X[i+1]));
        };
    };
    *final_len = lenX/2;
    return xmsg;
};

char* bitcoin_address_of_public_point(char*X,char*Y) {
    if (secp256k1_belongs_to_curve_str(X,Y) == false)
        return NULL;
    //
    int lenX,lenY;
    char*xmsg = hex_str_of_int_to_bytes(X,&lenX);
    char*ymsg = hex_str_of_int_to_bytes(Y,&lenY);
    //
    char* merged = (char*)malloc(sizeof(char)*65);
    for(int i=0; i<lenX; i++)
        merged[i+1] = xmsg[i];
    for(int i=0; i<lenY; i++)
        merged[i+1+lenX] = ymsg[i];
    merged[0] = (char)4;
    free(xmsg);
    free(ymsg);
    //
    sha256_enable_rawout();
    sha256_enable_manuallen(65);
    char* firstHash = sha256_mkhash_str(merged);
    ripemd160_enable_rawout();
    ripemd160_enable_manuallen(32);
    char* secondHash = ripemd160_mkhash_str(firstHash);
    //
    free(merged);
    merged = (char*)malloc(sizeof(char)*21);
    merged[0] = (char)0;
    for(int i=0; i<20; i++)
        merged[1+i] = secondHash[i];
    //
    sha256_enable_manuallen(21);
    free(firstHash);
    firstHash = sha256_mkhash_str(merged);
    sha256_enable_manuallen(32);
    free(secondHash);
    secondHash = sha256_mkhash_str(firstHash);
    //
    char*to_encode = (char*)malloc(sizeof(char)*25);
    for(int i=0; i<21; i++)
        to_encode[i] = merged[i];
    for(int i=0; i<4; i++)
        to_encode[i+21] = secondHash[i];
    free(merged);
    free(secondHash);
    //
    base58_enable_manuallen(25);
    char*res = base58_encode_str(to_encode);
    free(to_encode);
    //
    return res;
};