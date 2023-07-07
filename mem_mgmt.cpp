#include <iostream>
#include <cstring>
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

struct Chunk {
  Chunk* next;
};

class MemoryMgmt {
public:
    MemoryMgmt(int total_size, int chunk_size) {
        int num = total_size/chunk_size;
        dummyHead.next = nullptr;

        for (int i=0; i<num; i++) {
            void* addr = malloc(chunk_size);
            memset(addr, 0, sizeof(chunk_size));
            Chunk* cur = static_cast<Chunk*>(addr);
            cur->next = dummyHead.next;
            dummyHead.next = cur;
        }
    }

    void* alloc() {
        if (!dummyHead.next) {
            return nullptr;
        }

        void* addr = static_cast<void*>(dummyHead.next);
        dummyHead.next = dummyHead.next->next;
        return addr;
    }

    void release(void *addr) {
        Chunk* cur = static_cast<Chunk*>(addr);
        cur->next = dummyHead.next;
        dummyHead.next = cur;
    }

    ~MemoryMgmt() {
        while (dummyHead.next) {
            void *addr = static_cast<void*>(dummyHead.next);
            dummyHead.next = dummyHead.next->next;
            free(addr);
        }
    }
private:
    Chunk dummyHead;
};

void test_alloc_release(int total_size, int chunk_size) {
    cout << "test started for total_size: " << total_size << ", chunk_size: " << chunk_size;
    MemoryMgmt a(total_size, chunk_size);
    int num = total_size/chunk_size;
    vector<Chunk*> addrs(num, nullptr);

    for (int i=0; i<num; i++) {
        Chunk* curAddr = static_cast<Chunk*>(a.alloc());
        addrs[i] = curAddr;
    }

    assert(!a.alloc());
    for (int i=0; i<num; i++) {
        a.release(addrs[i]);
    }
    
    assert(a.alloc());
    cout << "  -> test passed!" << endl;
}

int main() {
    // the chunk size MUST larger than Chunk strcture
    test_alloc_release(100, 10);
    test_alloc_release(1000, 23);
    test_alloc_release(1000, 20);
    test_alloc_release(999, 35);
    test_alloc_release(1234, 77);
}
