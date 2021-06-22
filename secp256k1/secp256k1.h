#include <string.h>   /*  */
#include <stdlib.h>   /*  */
#include <stdio.h>    /*  */
#include <stdbool.h>  /*  */
#include <gmp.h>      /*  */

bool secp256k1_belongs_to_curve_int(mpz_t X,mpz_t Y);
bool secp256k1_belongs_to_curve_str(char*X,char*Y);