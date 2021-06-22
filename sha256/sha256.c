#include "sha256.h"

typedef uint32_t sha256_int;

bool sha256_rawout=false;


void sha256_enable_rawout() {
    sha256_rawout=true;
};

void sha256_disable_rawout() {
    sha256_rawout=false;
};

sha256_int sha256_SHR_n(sha256_int x, sha256_int n) {
    return (x>>n);
};

sha256_int sha256_ROTR_n(sha256_int x, sha256_int n) {
    return (x>>n)|(x<<(32-n));
};

sha256_int sha256_ROTL_n(sha256_int x, sha256_int n) {
    return (x<<n)|(x>>(32-n));
};

sha256_int sha256_CH(sha256_int x, sha256_int y, sha256_int z){
	return (x & y) ^ ( (~ x) & z);
};

sha256_int sha256_MAJ(sha256_int x, sha256_int y, sha256_int z){
	return (x & y) ^ (x & z) ^ (y & z);
};

sha256_int sha256_BSIG0(sha256_int x){
	return sha256_ROTR_n(x,2) ^ sha256_ROTR_n(x,13) ^ sha256_ROTR_n(x,22);
};

sha256_int sha256_BSIG1(sha256_int x){
	return sha256_ROTR_n(x,6) ^ sha256_ROTR_n(x,11) ^ sha256_ROTR_n(x,25);
};

sha256_int sha256_SSIG0(sha256_int x){
	return sha256_ROTR_n(x,7) ^ sha256_ROTR_n(x,18) ^ sha256_SHR_n(x,3);
};

sha256_int sha256_SSIG1(sha256_int x){
	return sha256_ROTR_n(x,17) ^ sha256_ROTR_n(x,19) ^ sha256_SHR_n(x,10);
};

sha256_int sha256_K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int sha256_manuallen=-1;

void sha256_enable_manuallen(int len) {
    sha256_manuallen=len;
};

void sha256_disable_manuallen() {
    sha256_manuallen = -1;
};

sha256_int*sha256_mkpadding(char*str,int*words) {
    long originalLen;
    if (sha256_manuallen!=-1)
        originalLen=sha256_manuallen;
    else
        originalLen = strlen(str);
    int padding=1;
    while((originalLen+padding)%64 != 56) padding++;
    int newLen = originalLen+padding+8;
    *words = newLen/4;
    unsigned char* tmp = (unsigned char*)malloc(sizeof(unsigned char)*newLen);
    for(int i=0; i<originalLen; i++)
        tmp[i] = str[i];
    tmp[originalLen] = 0x80;
    int len = originalLen;
    for(int i=1; i<padding; i++)
        tmp[len+i] = 0;
    originalLen=originalLen*8;
    tmp[padding+len+7] = (originalLen>>0)&0xff;
    tmp[padding+len+6] = (originalLen>>8)&0xff;
    tmp[padding+len+5] = (originalLen>>16)&0xff;
    tmp[padding+len+4] = (originalLen>>24)&0xff;
    tmp[padding+len+3] = (originalLen>>32)&0xff;
    tmp[padding+len+2] = (originalLen>>40)&0xff;
    tmp[padding+len+1] = (originalLen>>48)&0xff;
    tmp[padding+len+0] = (originalLen>>56)&0xff;
    sha256_int* msg = (sha256_int*)malloc(sizeof(sha256_int)*(*words));
    for(int i=0; i<*words; i++) {
        msg[i] = ( ( (tmp[i*4+3])<<0 )|
                   ( (tmp[i*4+2])<<8 )|
                   ( (tmp[i*4+1])<<16 )|
                   ( (tmp[i*4+0])<<24 ) );
    };
    free(tmp);
    return msg;
};

char sha256_hexval(int v) {
    if (v<10)
        return (char)('0'+v);
    v-=10;
    return (char)('a'+v);
};

char* sha256_convert_to_hex(unsigned char*str,int len) {
    char* hex = (char*)malloc(sizeof(char)*(2*len+1)); hex[len*2]='\0';
    for(int i=0; i<len; i++) {
        hex[i*2] = sha256_hexval(((unsigned char)(str[i]))>>4);
        hex[i*2+1] = sha256_hexval(((unsigned char)(str[i]))%16);
    };
    free(str);
    return hex;
};

void sha256_playRound(sha256_int*M,sha256_int*H) {
    sha256_int* W = (sha256_int*)malloc(sizeof(sha256_int)*64);
    for(int t=0; t<16; t++) W[t] = M[t];
    for(int t=16; t<64; t++) W[t] = sha256_SSIG1(W[t-2]) + W[t-7] + sha256_SSIG0(W[t-15]) + W[t-16];
    //
    sha256_int a,b,c,d,e,f,g,h,T1,T2;
    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];
    f = H[5];
    g = H[6];
    h = H[7];
    //
    for(int t=0; t<64; t++) {
        T1 = h + sha256_BSIG1(e) + sha256_CH(e,f,g) + sha256_K[t] + W[t];
        T2 = sha256_BSIG0(a) + sha256_MAJ(a,b,c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    };
    //
    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
    H[5] += f;
    H[6] += g;
    H[7] += h;
    free(W);
};

char*sha256_mkhash_str(char*str) {
    int words;
    sha256_int*msg=sha256_mkpadding(str,&words);
    sha256_int*H=(sha256_int*)malloc(sizeof(sha256_int)*8);
    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;
    // printf("len[%i]",words); if(words<2000) for(int i=0; i<words; i++) printf(" %i",msg[i]); printf("\n");
    int blocks = words/16;
    for(int i=0; i<blocks; i++) {
        sha256_playRound(&(msg[16*i]),H);
    };
    unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char)*32);
    for(int i=0; i<8; i++) {
        hash[i*4+0] = (H[i]>>24)&(0xff);
        hash[i*4+1] = (H[i]>>16)&(0xff);
        hash[i*4+2] = (H[i]>>8)&(0xff);
        hash[i*4+3] = (H[i]>>0)&(0xff);
    };
    free(H);
    free(msg);
    if (sha256_rawout)
        return hash;
    else
        return sha256_convert_to_hex(hash,32);
};