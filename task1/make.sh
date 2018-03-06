clang++-5.0 -g -fsanitize=address -fsanitize-coverage=trace-pc-guard /usr/lib/llvm-5.0/lib/libFuzzer.a fuzz_tests.c -o fuzz_tests
