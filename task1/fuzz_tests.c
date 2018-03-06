#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

int fast_min(int x, int y){
  return  y + ((x - y) & ((x - y) >> (sizeof(int) * 8 - 1)));
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  int* ints = (int*)Data;
  if(Size >= 2*sizeof(int)){
    int a = ints[0];
    int b = ints[1];
    int m = fast_min(a,b);

    //Lets add some assertions here

  }
  return 0;
}
