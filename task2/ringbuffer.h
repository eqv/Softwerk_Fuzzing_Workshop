#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct Entry {
  int val;
} entry_t;

typedef struct RingBuffer {
  int size;
  int front;
  int back;
  entry_t** buffer;
} ringbuffer_t;

entry_t* NewEntry(int val);

ringbuffer_t* NewRingBuffer(size_t size);

entry_t* Peek(ringbuffer_t* buf);

entry_t* PeekBack(ringbuffer_t* buf);

void ReplaceBack(ringbuffer_t* buf, entry_t* val);



entry_t* PeekFront(ringbuffer_t* buf);

void ReplaceFront(ringbuffer_t* buf, entry_t* val);

entry_t* Pop(ringbuffer_t* buf);

entry_t* PopFront(ringbuffer_t* buf);

void Push(ringbuffer_t* buf, entry_t* ent);

void PushBack(ringbuffer_t* buf, entry_t* ent);

int Len(ringbuffer_t* buf);

void Inspect(ringbuffer_t* buf);

void DeleteRingbuffer(ringbuffer_t* buf);

void RemoveOffset(ringbuffer_t* buf, size_t n);

//entry_t* Min(ringbuffer_t* buf);
