#include "secp256k1.h"

bool secp256k1_belongs_to_curve_int(mpz_t X,mpz_t Y) {
    mpz_t Z; mpz_init_set_ui(Z,0);
    mpz_t W; mpz_init_set_ui(W,0);
    mpz_t p; mpz_init_set_ui(p,0);
    gmp_sscanf("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F","%Zi",p);
    mpz_powm_ui (Z,X,3,p);
    mpz_add_ui(Z,Z,7);
    mpz_powm_ui (Z,Z,1,p);
    mpz_powm_ui (W,Y,2,p);
    if (mpz_cmp(Z,W) == 0) {
        mpz_clear(Z);
        mpz_clear(W);
        return true;
    } else {
        mpz_clear(Z);
        mpz_clear(W);
        return false;
    };
};

bool secp256k1_belongs_to_curve_str(char*X,char*Y) {
    mpz_t x,y;
    mpz_init_set_ui(x,0);
    mpz_init_set_ui(y,0);
    char*nX = (char*)malloc(sizeof(char)*(strlen(X)+3));
    for(int i=0; i<strlen(X); i++)
        nX[2+i] = X[i];
    char*nY = (char*)malloc(sizeof(char)*(strlen(Y)+3));
    for(int i=0; i<strlen(Y); i++)
        nY[2+i] = Y[i];
    nX[0] = '0'; nX[1] = 'x'; nX[strlen(X)+2] = '\0';
    nY[0] = '0'; nY[1] = 'x'; nY[strlen(Y)+2] = '\0';
    if (gmp_sscanf(nX,"%Zi",x)<1 || gmp_sscanf(nY,"%Zi",y)<1) {
        free(nX); free(nY);
        return false;
    };
    free(nX); free(nY);
    bool res = secp256k1_belongs_to_curve_int(x,y);
    mpz_clear(x); mpz_clear(y);
    return res;
};