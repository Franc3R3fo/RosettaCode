#include "base58.h"

char base58_alphabeth [] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

int base58_find_number_of_chars_in_int(mpz_t num, int val) {
    int k=0;
    while(mpz_cmp_si(num,0)>0) {
        k++;
        mpz_fdiv_q_ui(num,num,val);
    };
    return k;
};

char* base58_encode_int(mpz_t msg) {
    mpz_t copy; mpz_init_set(copy,msg);
    mpz_t ch; mpz_init_set_ui(ch,0); mpz_set(ch,copy);
    int len = base58_find_number_of_chars_in_int(ch,58);
    char* enc = (char*)malloc(sizeof(char)*(len+1));
    for(int i=len-1; i>=0; i--) {
        mpz_fdiv_qr_ui(copy,ch,copy,58);
        enc[i] = base58_alphabeth[mpz_get_ui(ch) %58];
    };
    mpz_clear(ch);
    mpz_clear(copy);
    enc[len]='\0';
    return enc;
};

int base58_manuallen=-1;

void base58_enable_manuallen(int len) {
    base58_manuallen=len;
};

void base58_disable_manuallen() {
    base58_manuallen = -1;
};

void base58_char_star_to_mpz_t(mpz_t toInt,char*msg,int val) {
    mpz_t ord; mpz_init_set_ui(ord,0);
    long len;
    if (base58_manuallen!=-1)
        len=base58_manuallen;
    else
        len = strlen(msg);
    for(int i=0; i<len; i++) {
        mpz_mul_ui(ord,ord,val);
        mpz_add_ui(ord,ord,(unsigned char)(msg[i]));
    };
    mpz_set(toInt,ord);
    mpz_clear(ord);
};

int base58_ordinal(char c) {
    int k=0;
    while(base58_alphabeth[k]!=c && k<58)
        k++;
    return k;
};

void base58_base58_char_star_to_mpz_t_b58(mpz_t toInt,char*msg,int val) {
    mpz_t ord; mpz_init_set_ui(ord,0);
    int len = strlen(msg);
    for(int i=0; i<len; i++) {
        mpz_mul_ui(ord,ord,val);
        mpz_add_ui(ord,ord,base58_ordinal(msg[i]));
    };
    mpz_set(toInt,ord);
    mpz_clear(ord);
};

char* base58_encode_str(char*msg) {
    mpz_t inte; mpz_init_set_ui(inte,0); base58_char_star_to_mpz_t(inte,msg,256);
    char* res = base58_encode_int(inte);
    mpz_clear(inte);
    return res;
};

void  base58_decode_int(char*enc, mpz_t res) {
    mpz_t inte; mpz_init_set_ui(inte,0); base58_base58_char_star_to_mpz_t_b58(inte,enc,58);
    mpz_set(res,inte);
    mpz_clear(inte);
};

bool base58_is_valid_char(char c) {
    return base58_ordinal(c)!=58;
};

char* base58_decode_str(char*enc) {
    mpz_t inte,ende; mpz_init_set_ui(inte,0); base58_decode_int(enc,inte);
    mpz_init_set(ende,inte);
    int len = base58_find_number_of_chars_in_int(ende,256);
    char* res = (char*)malloc(sizeof(char)*(len+1));
    for(int i=len-1; i>=0; i--) {
        mpz_fdiv_qr_ui(inte,ende,inte,256);
        res[i] = (char)(mpz_get_ui(ende));
    };
    mpz_clear(inte);
    mpz_clear(ende);
    res[len] = '\0';
    return res;
};