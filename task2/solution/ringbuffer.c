#include "ringbuffer.h"
#include "stdio.h"


//Constructors
entry_t* NewEntry(int val){
  if(val < 0 ){return NULL;}
  entry_t* res = (entry_t*)malloc(sizeof(entry_t));
  res->val = val;
  return res;
}

ringbuffer_t* NewRingBuffer(size_t size){
  if(size<1){return NULL;}
  if(size > 0xffffff){return NULL;} //BUG
  ringbuffer_t* buf = (ringbuffer_t*)malloc(sizeof(ringbuffer_t));
  buf->size = size;
  // if front == back, the buffer is empty
  buf->front = size/2; //front points to the first empty entry
  buf->back = size/2; //back points to the first used entry
  buf->buffer = (entry_t**)malloc(size*sizeof(entry_t*));
  for(int i = 0; i < size; i++){
    buf->buffer[i] = NULL;
  }
  return buf;
}


//Private Helper functions
void replace(ringbuffer_t* buf, int offset, entry_t* val){
  entry_t* old = buf->buffer[offset % buf->size];
  if(old != NULL) free(old);
  buf->buffer[offset % buf->size] = val;
}

void advance(ringbuffer_t* buf, int* ptr, int amount){
  //avoid integer overflow
  amount = amount % buf->size;
  if(amount < 0){amount = buf->size+amount;}//BUG: can become negative
  *ptr = (*ptr+amount)%buf->size; 
}

//Public API
entry_t* Peek(ringbuffer_t* buf){
  return PeekBack(buf);
}

entry_t* PeekBack(ringbuffer_t* buf){
  return buf->buffer[ buf->back % buf->size];
}

void ReplaceBack(ringbuffer_t* buf, entry_t* val){
  replace(buf, buf->back, val);
}

entry_t* PeekFront(ringbuffer_t* buf){
  return buf->buffer[ (buf->size+(buf->front-1)) % buf->size];
}

void ReplaceFront(ringbuffer_t* buf, entry_t* val){
  replace(buf, buf->front, val);
}

entry_t* Pop(ringbuffer_t* buf){
    entry_t* old = PeekBack(buf);
    if(old){
      buf->buffer[buf->back % buf->size] = NULL;
      advance(buf, &buf->back, 1);
    }
    return old;
}

entry_t* PopFront(ringbuffer_t* buf){
    entry_t* old = PeekFront(buf);
    if(old){
      advance(buf, &buf->front, -1);
      buf->buffer[buf->front % buf->size] = NULL;
    }
    return old;
}

void Push(ringbuffer_t* buf, entry_t* ent){
    ReplaceFront(buf, ent);
    advance(buf, &buf->front, 1);
    if(buf->front == buf->back){free(Pop(buf));}//BUG allows PushFront to Cross Back
}

void PushBack(ringbuffer_t* buf, entry_t* ent){
    advance(buf, &buf->back, -1);
    ReplaceBack(buf, ent);
    if(buf->front == buf->back){free(PopFront(buf));}//BUG allows PushFront to Cross Back
}

int Len(ringbuffer_t* buf){
  //BUG invalid LEN
  if(buf->front < buf->back){
    return buf->size-buf->back + buf->front;
  }
  return buf->front - buf->back;
}

void RemoveOffset(ringbuffer_t* buf, size_t n){
  int len = Len(buf);
  if(!len || n % len == len-1){return;}
  n = n % len;
  entry_t **old = &buf->buffer[(buf->back+n) % buf->size]; // BUG % binds stronger than +
  free(*old);
  *old = NULL; //BUG useafter free if LEN == 1
  *old = PopFront(buf); 
}

void Inspect(ringbuffer_t* buf){
  printf("Ringbuffer[");
  for(int i = 0; i<buf->size; i++){
    if(buf->front == i){printf("F");}
    if(buf->back == i){printf("B");}
    if(buf->buffer[i] !=NULL) {
      printf("%d", buf->buffer[i]->val);
    } else{
      printf("_");
    }
    printf(", ");
  }
  printf("]\n");
}

void DeleteRingbuffer(ringbuffer_t* buf){
  if(!buf){return;}
  entry_t* ent= NULL;
  while((ent = Pop(buf))){
    free(ent);
  }
  free(buf->buffer);
  free(buf);
}
