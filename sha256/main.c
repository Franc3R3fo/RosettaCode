#include "sha256.h"

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
    char res_0[] = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    char res_1[] = "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb";
    char res_2[] = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    char res_3[] = "f7846f55cf23e14eebeab5b4e1550cad5b509e3348fbc4efa3a1413d393cb650";
    char res_4[] = "71c480df93d6ae2f1efad1447c66c9525e316218cf51fc8d9ed832f2daf18b73";
    char res_5[] = "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1";
    char res_6[] = "db4bfcbd4da0cd85a60c3c37d3fbd8805c77f15fc6b1fdfe614ee0a7c8fdb4c0";
    char res_7[] = "f371bc4a311f2b009eef952dd83ca80e2b60026c8e935592d0f9c308453c813e";
    char res_8[] = "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0";
    // test mkhash
    char* enc0 = sha256_mkhash_str(src_0);
    char* enc1 = sha256_mkhash_str(src_1);
    char* enc2 = sha256_mkhash_str(src_2);
    char* enc3 = sha256_mkhash_str(src_3);
    char* enc4 = sha256_mkhash_str(src_4);
    char* enc5 = sha256_mkhash_str(src_5);
    char* enc6 = sha256_mkhash_str(src_6);
    char* enc7 = sha256_mkhash_str(src_7);
    char* enc8 = sha256_mkhash_str(src_8);
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