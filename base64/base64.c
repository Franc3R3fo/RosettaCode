#include "base64.h"

char base64_alphabeth[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_ALU_encode(unsigned char*src,char*dst) {
    int A = src[0],B = src[1],C = src[2];
    int ra,rb,rc,rd;
    ra = A/4;
    rb = (A%4)*16+(B/16);
    rc = (B%16)*4+(C/64);
    rd = (C%64);
    dst[0] = base64_alphabeth[ra];
    dst[1] = base64_alphabeth[rb];
    dst[2] = base64_alphabeth[rc];
    dst[3] = base64_alphabeth[rd];
};

unsigned char* base64_mk_padding(char*str, int*newLen, int*padding) {
    int realLen = strlen(str); int padLen=0;
    if (realLen%3!=0) {
        padLen = 3-(realLen%3);
    };
    *newLen = realLen+padLen;
    *padding = padLen;
    unsigned char* msg = (unsigned char*)malloc(sizeof(unsigned char)*(*newLen+1));
    for(int i=0; i<realLen; i++)
        msg[i] = (unsigned char)str[i];
    for(int i=realLen; i<*newLen+1; i++)
        msg[i] = (unsigned char)0;
    return msg;
};

char* base64_encode_str(char*str) {
    int newLen=0,padLen=0,encLen;
    unsigned char* msg = base64_mk_padding(str,&newLen,&padLen);
    encLen=(newLen/3)*4;
    char* res = (char*)malloc(sizeof(char)*(encLen+1)); res[encLen]='\0';
    int blocks=newLen/3;
    for(int i=0; i<blocks; i++)
        base64_ALU_encode(&(msg[3*i]),&(res[4*i]));
    for(int i=0; i<padLen; i++)
        res[encLen-i-1] = '=';
    free(msg);
    return res;
};

int base64_ordinal(char c) {
    int k=0;
    while(base64_alphabeth[k]!=c && k<64)
        k++;
    return k;
};

void base64_ALU_decode(char*src,char*dst) {
    int ra = base64_ordinal(src[0]); if (ra == 64) ra = 0;
    int rb = base64_ordinal(src[1]); if (rb == 64) rb = 0;
    int rc = base64_ordinal(src[2]); if (rc == 64) rc = 0;
    int rd = base64_ordinal(src[3]); if (rd == 64) rd = 0;
    int A,B,C;
    A = ra*4 + rb/16;
    B = (rb%16)*16 + rc/4;
    C = (rc%4)*64 + rd;
    dst[0] = (char)A;
    dst[1] = (char)B;
    dst[2] = (char)C;
};

char* base64_decode_str(char*str) {
    int oldLen = strlen(str); int newLen = (oldLen/4)*3;
    char* res = (char*)malloc(sizeof(char)*(newLen+1)); res[newLen]='\0';
    int blocks = oldLen/4;
    for(int i=0; i<blocks; i++)
        base64_ALU_decode(&(str[4*i]),&(res[3*i]));
    return res;
};