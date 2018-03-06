#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stddef.h>

#include "ringbuffer.h"

void unit_tests(){
  ringbuffer_t* buffer = NewRingBuffer(10);
  Inspect(buffer);
  assert(Peek(buffer) == NULL); // initially no entries 

  assert(Len(buffer) == 0);

  Push(buffer, NewEntry(3) ); 

  assert(Len(buffer) == 1);
  Inspect(buffer);

  assert(Peek(buffer) != NULL); 
  assert(Peek(buffer)->val == 3);

  Push(buffer, NewEntry(4) ); 
  assert(Peek(buffer) != NULL); 
  assert(Peek(buffer)->val == 3);
  assert(Len(buffer) == 2);
  Inspect(buffer);

  Push(buffer, NewEntry(5) ); 
  assert(Peek(buffer) != NULL); 
  assert(Peek(buffer)->val == 3);
  assert(Len(buffer) == 3);
  Inspect(buffer);

  entry_t* ent = Pop(buffer);
  assert(ent != NULL);
  assert(ent->val == 3);
  assert(Peek(buffer)->val == 4);
  assert(Len(buffer) == 2);
  Inspect(buffer);
  free(ent);

  ent = Pop(buffer);
  assert(ent != NULL);
  assert(ent->val == 4);
  assert(Peek(buffer)->val == 5);
  assert(Len(buffer) == 1);
  Inspect(buffer);
  free(ent);

  ent = Pop(buffer);
  assert(ent != NULL);
  assert(ent->val == 5);
  assert(Peek(buffer) == NULL);
  assert(Len(buffer) == 0);
  Inspect(buffer);
  free(ent);

  PushBack(buffer, NewEntry(1) ); 
  assert(Peek(buffer) != NULL); 
  assert(Peek(buffer)->val == 1);
  assert(Len(buffer) == 1);
  Inspect(buffer);

  PushBack(buffer, NewEntry(2) ); 
  assert(Peek(buffer) != NULL); 
  assert(Peek(buffer)->val == 2);
  assert(Len(buffer) == 2);
  Inspect(buffer);

  ent = PopFront(buffer); 
  assert(ent && ent->val == 1);
  assert(PeekFront(buffer)->val == 2);
  assert(Len(buffer) == 1);
  Inspect(buffer);
  free(ent);

  ent = PopFront(buffer); 
  assert(ent && ent->val == 2);
  assert(PeekFront(buffer) == NULL);
  assert(Len(buffer) == 0);
  Inspect(buffer);
  free(ent);

  ent = PopFront(buffer); 
  assert(!ent);
  assert(Len(buffer) == 0);
  Inspect(buffer);
  free(ent);

  Push(buffer, NewEntry(1) ); 
  Inspect(buffer);
  Push(buffer, NewEntry(2) ); 
  Inspect(buffer);
  Push(buffer, NewEntry(3) ); 
  Inspect(buffer);
  RemoveOffset(buffer, 2);
  Inspect(buffer);
  RemoveOffset(buffer, 0);
  Inspect(buffer);
  RemoveOffset(buffer, 0);

  Inspect(buffer);
  printf("All Tests Passed!\n");
  DeleteRingbuffer(buffer);
}

int main(int argc, char *argv[])
{
  unit_tests();
	return 0;
}
