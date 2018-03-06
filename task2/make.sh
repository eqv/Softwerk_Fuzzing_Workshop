clang++ -g -fsanitize=address  unit_tests.c ringbuffer.c -o unit_tests
clang++ -g -fsanitize=address -fsanitize-coverage=trace-pc-guard /usr/lib/llvm-5.0/lib/libFuzzer.a fuzz_tests.c ringbuffer.c -o fuzz_tests

#to debug memory problems you can use the following gdb command line, it will automatically stop at any address sanitizer error, use the command up(4) to get to the offending line
#gdb -ex 'b __sanitizer::Die ()' -ex run --args ./fuzz_tests crash-015136937908e75e94af94bbcb714f0204dad5cd
