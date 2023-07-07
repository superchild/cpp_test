# cpp_test

## Requirement
It needs to implement the following function in this class
1. `mpool init`
inital a mem pool that can alloc/free fixed-size chunk
  - input
    - total_size
    - chunk_size

2. `mpool alloc`
return a chunk from the mpool

3. `mpool release`
release an allocted chunk

4. `mpopol fini`
destroy the whole mem pool

For the performance, it needs to fulfill the following requirements
- Reduce memory manage overhead - `O(1)`
- Efficient alloc/release() - `O(1)`


## Compile & Execute
use `exec.sh` to compile and run the program
