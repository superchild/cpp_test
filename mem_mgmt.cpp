#include <iostream>
#include <cassert>
#include <list>
#include <vector>
using namespace std;

/*
1.mpool init - inital a mem pool that can alloc/free fixed-size chunk
- input: total_size
- chunk_size
2.mpool alloc - return a chunk from the mpool
3.mpool release - release an allocted chunk
4.mpopol fini - destroy the whole mem pool

* Reduce memory manage overhead - O(1)
* Efficient alloc/release() - O(1)
*/

class MemoryMgmt {
public:
    MemoryMgmt(int total_size, int chunk_size) {
        int num = total_size/chunk_size;
        
        for (int i=0; i<num; i++) {
            void* addr = malloc(chunk_size);
            freeList.push_front(addr);
        }
    }

    void* alloc() {
        if (freeList.empty()) {
            return nullptr;
        }

        void* addr = freeList.front();
        freeList.pop_front();
        return addr;
    }

    void release(void *addr) {
        freeList.push_front(addr);
    }

    ~MemoryMgmt() {
        while (!freeList.empty()) {
            void *addr = freeList.front();
            freeList.pop_front();
            free(addr);
        }
    }
private:
    list<void*> freeList;
};

void test_alloc_release(int total_size, int chunk_size) {
    cout << "test started for total_size: " << total_size << ", chunk_size: " << chunk_size;
    MemoryMgmt memMgt(total_size, chunk_size);
    int num = total_size/chunk_size;
    vector<void*> addrs(num, nullptr);

    for (int i=0; i<num; i++) {
        addrs[i] = memMgt.alloc();
    }

    assert(!memMgt.alloc());
    for (int i=0; i<num; i++) {
        memMgt.release(addrs[i]);
    }
    
    assert(memMgt.alloc());
    cout << "  -> test passed!" << endl;
}

int main() {
    test_alloc_release(100, 10);
    test_alloc_release(1000, 23);
    test_alloc_release(1000, 20);
    test_alloc_release(999, 35);
    test_alloc_release(1234, 77);
}
