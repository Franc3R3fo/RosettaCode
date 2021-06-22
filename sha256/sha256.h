#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include "string.h"

void sha256_enable_manuallen(int len);
void sha256_disable_manuallen();
void sha256_enable_rawout();
void sha256_disable_rawout();
char*sha256_mkhash_str(char*str);