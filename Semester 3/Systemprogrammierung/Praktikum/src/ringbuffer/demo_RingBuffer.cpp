#include "ringbuffer/RingBuffer.h"
#include "ringbuffer/CustomAllocator.h"
#include "speicherverwaltung/speicherverwaltung.h"

int main(int argc, char *argv[]) {
#ifdef CM_MALLOC
    cm_init();
#endif
    
    CustomAllocator<int> allocator;
    RingBuffer<int, 4, CustomAllocator<int>> buffer;

    for (int i = 0; i < 10; ++i) {
        int *num = allocator.allocate(1);
        *num = i;
        buffer.writeBuffer(num);
        buffer.displayStatus();
    }

    std::cout << "\n";

    int *num = buffer.readBuffer();
    while (num != nullptr) {
        std::cout << *num << "    ";
        buffer.displayStatus();
        allocator.deallocate(num, 1);
        num = buffer.readBuffer();
    }
    
    std::cout << "\n";
    
    for (int i = 0; i < 10; ++i) {
        int *num = allocator.allocate(1);
        *num = i;
        buffer.writeBuffer(num);
        buffer.displayStatus();
    }
    
    return 0;
}

