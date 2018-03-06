#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#include "ringbuffer.h"

uint8_t read_u8(const uint8_t** Data, size_t* Size, uint8_t* done){
  if(*Size < 1){*done = 1; return 0;}
  *Size-=1;
  uint8_t res = **Data;
  *Data+=1;
  return res;
}

size_t read_size(const uint8_t** Data, size_t* Size, uint8_t* done){
  if(*Size < sizeof(size_t)){*done = 1; return 0;}
  *Size-=sizeof(size_t);
  size_t res = **(size_t**)Data;
  *Data+=sizeof(size_t);
  return res;
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  uint8_t done=0;
  size_t some_val = read_size(&Data, &Size, &done); //you can use the read_size and read_u8 functions to get a part of the data
  if(done){return 0;} // we didn't have enough input data available -> exit
  size_t some_other_val = read_size(&Data, &Size, &done);
  if(done){return 0;}

  assert(some_val*some_val != some_other_val+1); //This is just an example
  return 0;
}
