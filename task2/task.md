Task2, Testing an API
=====================

The file `ringbuffer.c` and `ringbuffer.h` contain a rather buggy ring buffer implementation. `unit_tests.c` provided a set of (bad) unit tests to demonstrate the use of the API.

The goal of this task is to build a fuzzer that tries different combinations of API calls to the Different relevant functions of the ring buffer API. One common way to handle this, is to treat the binary data as a very rudimentary kind of bytecode:
```
switch(next_byte_from_input()%3):
  case 0: function1(next_uint_from_input()); break;
  case 1: function2(); break;
  case 2: function3(); break;
```

Build a fuzzer that tests the various functions in ringbuffer.c and find some of the bugs. 

* Hint: it might be usefull to check various invariants of the ringbuffer after each function call to notice problems as early as possible. Invariants that we assume are for example: 
    * `*buf->front==NULL` will always point to NULL element in the buffer
    * `Len(buf) >= 0` and `Len(buf) <= buf->size`
    * For all `i in (0..Len(buf))` it holds that `buf->buffer[buf->back+i] != Null`, and all other elements should be `NULL`

* Hint: you can use `gdb -ex 'b __sanitizer::Die ()' -ex run --args ./fuzz_tests crash-0151...123` to break the debugger at memory corruptions detected by the sanatizer
