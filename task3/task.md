Task3, Geting Coverage
======================

In this task we use a small library that parses png files to try some tricks to meassure and increase the coverage produced by our
fuzzers. Try to optimize the coverage obtained by running `./fuzz_tests`.

Meassure Coverage
-----------------
By linking agains `libfuzzer.a` we introduce a `main` function that spawns the fuzzing process. We can replace this with
another `main` function that simply runs the target on a set of inputs (Such a main function is provided in
`StandaloneFuzzTargetMain.c`). Then we can compile the fuzzer with `clang++ -fprofile-instr-generate -fcoverage-mapping -pthread lodepng/lodepng.cpp fuzz_tests.c StandaloneFuzzTargetMain.c -o coverage_tests`. This gives us a binary that produces combined coverage information for all inputs passed as arguments. When we run `./coverage_tests some interesting inputs `, we obtain `default.profraw` which we need to convert first: `llvm-profdata merge -sparse default.profraw -o default.profdata`. The resulting `default.profdata` can then be used by `llvm-cov show coverage_tests -instr-profile=default.profdata` to produce an accurate image of which code was covered and which wasn't.

Try to figure out what code is hard to cover and how to cover it.

* Hint:  If you add `-fsanitize-coverage=trace-pc-guard,trace-cmp` to the compilation, you can use a smart feature of
  libfuzzer, where it automatically learns interessting strings by adding `-use_value_profile=1` to the fuzzing command
  line.
* Hint: add `-workers=4 -jobs=4` to spawn more fuzzing threads.
* Hint: get a dictionary of interessting strings and add `dict=some.dict`
* Hint: get an set of example images (or even just one) in a corpus folder and run `./fuzz_tests corpus` to start with a
  sensible input. Notice the difference in the coverage found.
* Hint: You can find a extensive set of inputs and a dictionary for png files in the solution folder (Provided by lcamtuf the author of the famous AFL fuzzer). 
