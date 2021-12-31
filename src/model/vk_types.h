
#define foo

#ifdef foo



#include <vk_mem_alloc.h>

struct AllocatedBuffer {
    VkBuffer _buffer;
    VmaAllocation _allocation;
};

#endif // DEBUG
