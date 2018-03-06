clang++-5.0 -g -fsanitize=address -fsanitize-coverage=trace-pc-guard /usr/lib/llvm-5.0/lib/libFuzzer.a  lodepng/lodepng.cpp fuzz_tests.c -o fuzz_tests
#you can enable value-profile
clang++-5.0 -g -fsanitize=address -fsanitize-coverage=trace-pc-guard,trace-cmp /usr/lib/llvm-5.0/lib/libFuzzer.a  lodepng/lodepng.cpp fuzz_tests.c -o fuzz_tests
clang++-5.0 -fprofile-instr-generate -fcoverage-mapping -pthread lodepng/lodepng.cpp fuzz_tests.c StandaloneFuzzTargetMain.c -o coverage_tests

# Try out the more advanced features, add a single small valid input, a whole list of images, a dict or similarly
# (example dict and images by lcamtuf)
./fuzz_tests -workers=4 -jobs=4 -dict=png.dict -use_value_profile=1 examples images

#to show coverage information:
#./coverage_tests examples/*
#llvm-profdata merge -sparse default.profraw -o default.profdata 
#llvm-cov show coverage_tests -instr-profile=default.profdata

#to debug memory problems you can use the following gdb command line, it will automatically stop at any address sanitizer error, use the command up(4) to get to the offending line
#gdb -ex 'b __sanitizer::Die ()' -ex run --args ./fuzz_tests crash-015136937908e75e94af94bbcb714f0204dad5cd
