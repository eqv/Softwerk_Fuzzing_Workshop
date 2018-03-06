Task 1, A Simple Fuzzer
=======================

Setup
-----
We are going to use libfuzzer to automatize testcase generation
Install clang and libfuzzer (`apt-get install libfuzzer-5.0-dev clang-5.0`)

libfuzzer is a library that gives you the ability to run testcases automatically with cleverly choosen inputs to
maximize your testcoverage. You write one (or many) test functions, that will be called with a variable sized byte
buffer as input. This function converts the buffer into testcases and executes the testcases.


```
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  //Do something with your data here
  return 0;
}
```

To make sure that the functions are actually called, you will need to link the static library libFuzzer.a to your target, it contains all fuzzing functionality. A
buildscript for this example is provided with `make.sh`. Additionally you will need to enable `-fsanitize-coverage=trace-pc-guard` to ensure that libfuzzer gets the coverage information it needs.
Additional sanatizers such as address sanatizer or undefined behaviour sanatizer are also often usefull.

Testcase
--------

in `fuzz_test.c` we supplied a fast and branchfree function that calculates the minimum of two values. Build a simple
fuzzer that checks wether it works. 

* Hint: It is often easier to check some propertys of the correct solution that to check correctness of the whole
solution. Consider string_reverse: it is easier to check that  `str == string_reverse(string_reverse(str))` than to ensure that string_reverse is actually correct.  
In our case we could check that `min(a,b) <= a` and `min(a,b)<= b`

* Hint: A solution is provided in solution/fuzz_tests
