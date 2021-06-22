#include "base64.h"

void testFunction(int index,char*src,char*res,char*enc,char*dec,int*score,int*antiscore) {
    if (strcmp(enc,res) == 0) {
        *score+=2;
    } else {
        *antiscore+=2;
        printf("encode[%i] failed : got (%s), expected (%s)\n",index,enc,res);
    };
    
    if (strcmp(dec,src) == 0) {
        *score+=2;
    } else {
        *antiscore+=2;
        printf("decode[%i] failed : got (%s), expected (%s)\n",index,dec,src);
    };
};

int main(int argc,char**args) {
    // load data
    char src_0[] = "ciao mondo";
    char src_1[] = "come stai cavolo?";
    char src_2[] = "io sto bene ma 23.5 no";
    char src_3[] = "si 30L va bene";
    char src_4[] = "ma per me si tratta di una sconfitta";
    char res_0[] = "Y2lhbyBtb25kbw==";
    char res_1[] = "Y29tZSBzdGFpIGNhdm9sbz8=";
    char res_2[] = "aW8gc3RvIGJlbmUgbWEgMjMuNSBubw==";
    char res_3[] = "c2kgMzBMIHZhIGJlbmU=";
    char res_4[] = "bWEgcGVyIG1lIHNpIHRyYXR0YSBkaSB1bmEgc2NvbmZpdHRh";
    // test encode
    char* enc0 = base64_encode_str(src_0);
    char* enc1 = base64_encode_str(src_1);
    char* enc2 = base64_encode_str(src_2);
    char* enc3 = base64_encode_str(src_3);
    char* enc4 = base64_encode_str(src_4);
    // test decode
    char* dec0 = base64_decode_str(enc0);
    char* dec1 = base64_decode_str(enc1);
    char* dec2 = base64_decode_str(enc2);
    char* dec3 = base64_decode_str(enc3);
    char* dec4 = base64_decode_str(enc4);
    // validation
    int score=0,antiscore=0;
    testFunction(0,src_0,res_0,enc0,dec0,&score,&antiscore);
    testFunction(1,src_1,res_1,enc1,dec1,&score,&antiscore);
    testFunction(2,src_2,res_2,enc2,dec2,&score,&antiscore);
    testFunction(3,src_3,res_3,enc3,dec3,&score,&antiscore);
    testFunction(4,src_4,res_4,enc4,dec4,&score,&antiscore);
};