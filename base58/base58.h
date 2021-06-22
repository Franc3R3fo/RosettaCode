#include <string.h>   /*  */
#include <stdlib.h>   /*  */
#include <stdio.h>    /*  */
#include <stdbool.h>  /*  */
#include <gmp.h>      /*  */

void base58_enable_manuallen(int len);
void base58_disable_manuallen();
char* base58_encode_int(mpz_t msg);
char* base58_encode_str(char*msg);
void  base58_decode_int(char*enc,mpz_t res);
char* base58_decode_str(char*enc);
bool base58_is_valid_char(char c);