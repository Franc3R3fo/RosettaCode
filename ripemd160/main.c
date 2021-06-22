#include "ripemd160.h"

void testFunction(int index,char*src,char*res,char*enc,int*score,int*antiscore) {
    if (strcmp(enc,res) == 0) {
        *score+=2;
        printf("mkhash[%i] success: got ok (%s)\n",index,enc);
    } else {
        *antiscore+=2;
        printf("mkhash[%i] failed : got (%s), expected (%s)\n",index,enc,res);
    };
};

int main(int argc,char**args) {
    // load data
    char src_0[] = "";
    char src_1[] = "a";
    char src_2[] = "abc";
    char src_3[] = "message digest";
    char src_4[] = "abcdefghijklmnopqrstuvwxyz";
    char src_5[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    char src_6[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char src_7[] = "12345678901234567890123456789012345678901234567890123456789012345678901234567890";
    char*src_8   = (char*)malloc(sizeof(char)*1000001); for(int i=0; i<1000000; i++) src_8[i]='a'; src_8[1000000]='\0';
    char res_0[] = "9c1185a5c5e9fc54612808977ee8f548b2258d31";
    char res_1[] = "0bdc9d2d256b3ee9daae347be6f4dc835a467ffe";
    char res_2[] = "8eb208f7e05d987a9b044a8e98c6b087f15a0bfc";
    char res_3[] = "5d0689ef49d2fae572b881b123a85ffa21595f36";
    char res_4[] = "f71c27109c692c1b56bbdceb5b9d2865b3708dbc";
    char res_5[] = "12a053384a9c0c88e405a06c27dcf49ada62eb2b";
    char res_6[] = "b0e20b6e3116640286ed3a87a5713079b21f5189";
    char res_7[] = "9b752e45573d4b39f4dbd3323cab82bf63326bfb";
    char res_8[] = "52783243c1697bdbe16d37f97f68f08325dc1528";
    // test mkhash
    char* enc0 = ripemd160_mkhash_str(src_0);
    char* enc1 = ripemd160_mkhash_str(src_1);
    char* enc2 = ripemd160_mkhash_str(src_2);
    char* enc3 = ripemd160_mkhash_str(src_3);
    char* enc4 = ripemd160_mkhash_str(src_4);
    char* enc5 = ripemd160_mkhash_str(src_5);
    char* enc6 = ripemd160_mkhash_str(src_6);
    char* enc7 = ripemd160_mkhash_str(src_7);
    char* enc8 = ripemd160_mkhash_str(src_8);
    // validation
    int score=0,antiscore=0;
    testFunction(0,src_0,res_0,enc0,&score,&antiscore);
    testFunction(1,src_1,res_1,enc1,&score,&antiscore);
    testFunction(2,src_2,res_2,enc2,&score,&antiscore);
    testFunction(3,src_3,res_3,enc3,&score,&antiscore);
    testFunction(4,src_4,res_4,enc4,&score,&antiscore);
    testFunction(5,src_5,res_5,enc5,&score,&antiscore);
    testFunction(6,src_6,res_6,enc6,&score,&antiscore);
    testFunction(7,src_7,res_7,enc7,&score,&antiscore);
    testFunction(8,src_8,res_8,enc8,&score,&antiscore);
    // freeing memory
    free(enc0);
    free(enc1);
    free(enc2);
    free(enc3);
    free(enc4);
    free(enc5);
    free(enc6);
    free(enc7);
    free(enc8);
    free(src_8);
};