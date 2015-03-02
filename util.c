#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "lsm.h"

short convert_bytes(char *output) {
  short rval;
  memcpy(&rval, &output[1], 1);
  rval << 8;
  return (rval | output[0]);
}

unsigned short convert_temp(char *output) {
  short rval;
  memcpy(&rval, &output[1], 1);
  rval << 3;
  return (rval & output[0]);
}
