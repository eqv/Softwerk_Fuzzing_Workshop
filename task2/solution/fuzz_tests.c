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


void check_assertions(ringbuffer_t* buf){
  assert(Len(buf) >= 0);
  assert(Len(buf) < buf->size);

  //all elements that are not used are correctly zeroed
  for(int i = 0; i<buf->size-Len(buf); i++){
    assert(buf->buffer[(buf->front+i)%buf->size] == NULL);
  }
  //front always points to an empty element
  assert(buf->buffer[buf->front] == NULL);

  //if the len is > 0, back always points to a valid element
  if(Len(buf)>0){
    assert(buf->buffer[buf->back]);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  uint8_t done = 0;
  size_t buf_len = read_size(&Data, &Size, &done);
  uint8_t num_iters = 0;

  if(done){return 0;}
  ringbuffer_t* buffer = NewRingBuffer(buf_len % 20);
  if(!buffer){goto exit;}
  //Inspect(buffer);

  num_iters = read_u8(&Data, &Size, &done);
  if(done){goto exit;}
  for(uint8_t i=0; i<num_iters; i++){
    uint8_t op = read_u8(&Data, &Size, &done);
    if(done){goto exit;}
    switch(op % 5){
      case 0: 
        printf("Push \n");
        Push(buffer, NewEntry(i));  
        break;
      case 1: 
        printf("PushBack \n"); 
        PushBack(buffer, NewEntry(i)); 
        break;
      case 2: 
        printf("Pop \n");
        free(Pop(buffer)); 
        break;
      case 3: 
        printf("PopFront\n");
        free(PopFront(buffer)); 
        break;
      case 4: 
        size_t n = read_size(&Data, &Size, &done);
        if(done){goto exit;}
        printf("Remove Offset %ld\n", n);
        RemoveOffset(buffer,n); 
        break;
    }
    Inspect(buffer);
    check_assertions(buffer);
  }
  exit:
  DeleteRingbuffer(buffer);
  return 0;
}
