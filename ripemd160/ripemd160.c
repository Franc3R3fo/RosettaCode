#include "ripemd160.h"

typedef uint32_t ripemd160_int;

int ripemd160_rot_shift_s_a[] = {
    11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8,
     7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12,
     11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5,
     11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12,
     9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6
};

int ripemd160_rot_shift_s_b[] = {
     8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6,
     9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11,
     9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5,
     15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8,
      8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11
};

int ripemd160_r_a[] = {
    0, 1, 2, 3, 4,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8,
    3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12,
    1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2,
    4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13
};

int ripemd160_r_b[] = {
    5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12,
    6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2,
    15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13,
    8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14,
    12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11
};

bool ripemd160_rawout=false;

void ripemd160_enable_rawout() {
    ripemd160_rawout = true;
};

void ripemd160_disable_rawout() {
    ripemd160_rawout = true;
};

ripemd160_int ripemd160_rol_a(int j, ripemd160_int x) {
    int quantity = ripemd160_rot_shift_s_a[j];
    return (x<<quantity)|(x>>(32-quantity));
};

ripemd160_int ripemd160_rol_b(int j, ripemd160_int x) {
    int quantity = ripemd160_rot_shift_s_b[j];
    return (x<<quantity)|(x>>(32-quantity));
};

ripemd160_int ripemd160_rol_q(int q, ripemd160_int x) {
    return (x<<q)|(x>>(32-q));
};

ripemd160_int ripemd160_f(int j, ripemd160_int x, ripemd160_int y, ripemd160_int z) {
    if (j>=0 && j<16) {
        return x^y^z;
    } else if (j>=16 && j<32) {
        return (x&y)|((~x)&z);
    } else if (j>=32 && j<48) {
        return (x|(~y))^z;
    } else if (j>=48 && j<64) {
        return (x&z)|((~z)&y);
    } else if (j>=64 && j<80) {
        return (y|(~z))^x;
    };
};

ripemd160_int ripemd160_K(int j, ripemd160_int*k) {
    if (j>=0 && j<16) {
        return k[0];
    } else if (j>=16 && j<32) {
        return k[1];
    } else if (j>=32 && j<48) {
        return k[2];
    } else if (j>=48 && j<64) {
        return k[3];
    } else if (j>=64 && j<80) {
        return k[4];
    };
};

int ripemd160_manuallen=-1;

void ripemd160_enable_manuallen(int len) {
    ripemd160_manuallen=len;
};

void ripemd160_disable_manuallen() {
    ripemd160_manuallen = -1;
};

ripemd160_int* ripemd160_mkpadding(char*str,int*words) {
    long len;
    if (ripemd160_manuallen!=-1)
        len=ripemd160_manuallen;
    else
        len = strlen(str);
    int padding=1;
    while((len+padding)%64!=56) padding++;
    int paddeLen = len+padding+8;
    *words = paddeLen/4;
    //
    char* end = (char*)malloc(sizeof(char)*(paddeLen));
    ripemd160_int* msg = (ripemd160_int*)malloc(sizeof(ripemd160_int)*(*words));
    //
    // printf("len,padding = <%i,%i>\n",len,padding);
    for(int i=0; i<len; i++)
        end[i] = str[i];
    end[len] = (char)0x80;
    for(int i=1; i<padding; i++)
        end[len+i] = '\0';
    //
    // if (paddeLen<2000) for(int i=0; i<paddeLen; i++) printf("%i ",(unsigned char)end[i]); printf("\n");
    for(int i=0; i<(*words)-2; i++) {
        msg[i] =(( ((unsigned char)(end[i*4+0]))<<0)|
                 ( ((unsigned char)(end[i*4+1]))<<8)|
                 ( ((unsigned char)(end[i*4+2]))<<16)|
                 ( ((unsigned char)(end[i*4+3]))<<24));
    };
    len*=8;
    msg[(*words)-2  ] = (len<<32)>>32;
    msg[(*words)-1  ] = len>>32;
    free(end);
    //
    return msg;
};

ripemd160_int ripemd160_modulsum(ripemd160_int x, ripemd160_int y) {
    int c = (x+y);
    return c;
};

char ripemd160_hexval(int v) {
    if (v<10)
        return (char)('0'+v);
    v-=10;
    return (char)('a'+v);
};

char* ripemd160_convert_to_hex(unsigned char*str,int len) {
    char* hex = (char*)malloc(sizeof(char)*(2*len+1)); hex[len*2]='\0';
    for(int i=0; i<len; i++) {
        hex[i*2] = ripemd160_hexval(((unsigned char)(str[i]))>>4);
        hex[i*2+1] = ripemd160_hexval(((unsigned char)(str[i]))%16);
    };
    free(str);
    return hex;
};

char*ripemd160_mkhash_str(char*str) {
    //
    int words=0;
    ripemd160_int* msg = ripemd160_mkpadding(str,&words);
    // if (words<1000) for(int i=0; i<words; i++) printf("%i ",msg[i]); printf("\n");
    int blocks = words/16;
    ripemd160_int* h = (int*)malloc(sizeof(int)*5);
    ripemd160_int* K_a = (int*)malloc(sizeof(int)*5);
    ripemd160_int* K_b = (int*)malloc(sizeof(int)*5);
    h[0] = 0x67452301; h[1] = 0xefcdab89; h[2] = 0x98badcfe; h[3] = 0x10325476; h[4] = 0xc3d2e1f0;
    K_a[0] = 0x00000000; K_a[1] = 0x5A827999; K_a[2] = 0x6ED9EBA1; K_a[3] = 0x8F1BBCDC; K_a[4] = 0xA953FD4E;
    K_b[0] = 0x50A28BE6; K_b[1] = 0x5C4DD124; K_b[2] = 0x6D703EF3; K_b[3] = 0x7A6D76E9; K_b[4] = 0x00000000;
    //
    ripemd160_int A_a,A_b,B_a,B_b,C_a,C_b,D_a,D_b,E_a,E_b,T;
    //
    for(int i=0; i<blocks; i++) {
        A_a = h[0]; B_a = h[1]; C_a = h[2]; D_a = h[3]; E_a = h[4];
        A_b = h[0]; B_b = h[1]; C_b = h[2]; D_b = h[3]; E_b = h[4];
        for(int j=0; j<80; j++) {
            T = ripemd160_modulsum(A_a,ripemd160_f(j,B_a,C_a,D_a));
            T = ripemd160_modulsum(T,msg[16*i+ripemd160_r_a[j]]);
            T = ripemd160_modulsum(T,ripemd160_K(j,K_a));
            T = ripemd160_rol_a(j,T);
            T = ripemd160_modulsum(T,E_a);
            A_a = E_a; E_a = D_a; D_a = ripemd160_rol_q(10,C_a); C_a = B_a; B_a = T;
            T = ripemd160_modulsum(A_b,ripemd160_f(79-j,B_b,C_b,D_b));
            T = ripemd160_modulsum(T,msg[16*i+ripemd160_r_b[j]]);
            T = ripemd160_modulsum(T,ripemd160_K(j,K_b));
            T = ripemd160_rol_b(j,T);
            T = ripemd160_modulsum(T,E_b);
            A_b = E_b; E_b = D_b; D_b = ripemd160_rol_q(10,C_b); C_b = B_b; B_b = T;
        };
        T = ripemd160_modulsum(ripemd160_modulsum(h[1],C_a),D_b);
        h[1] = ripemd160_modulsum(ripemd160_modulsum(h[2],D_a),E_b);
        h[2] = ripemd160_modulsum(ripemd160_modulsum(h[3],E_a),A_b);
        h[3] = ripemd160_modulsum(ripemd160_modulsum(h[4],A_a),B_b);
        h[4] = ripemd160_modulsum(ripemd160_modulsum(h[0],B_a),C_b);
        h[0] = T;
    };
    //
    free(K_a);
    free(K_b);
    unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char)*21);
    for(int i=0; i<5; i++) {
        hash[i*4+0] = (unsigned char)((h[i]>>0)&(0xFF));
        hash[i*4+1] = (unsigned char)((h[i]>>8)&(0xFF));
        hash[i*4+2] = (unsigned char)((h[i]>>16)&(0xFF));
        hash[i*4+3] = (unsigned char)((h[i]>>24)&(0xFF));
    };
    hash[20]='\0';
    free(h);
    free(msg);
    if (ripemd160_rawout)
        return hash;
    else
        return ripemd160_convert_to_hex(hash,20);
};