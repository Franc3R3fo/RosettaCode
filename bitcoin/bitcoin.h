#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

/*
  returns {
      0 -> valid
      1 -> checksum invalid
      2 -> bad char
      3 -> length error
  }
*/
int bitcoin_validate_address(char*str);

/*
  X and Y are hex string representing int numbers
*/
char* bitcoin_address_of_public_point(char*X,char*Y);