#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

void ripemd160_enable_rawout();
void ripemd160_disable_rawout();
void ripemd160_enable_manuallen(int len);
void ripemd160_disable_manuallen();
char*ripemd160_mkhash_str(char*str);