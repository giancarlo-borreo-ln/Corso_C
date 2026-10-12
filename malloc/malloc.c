#include <unistd.h>
#include <stddef.h>
#include <errno.h>

/* 
 * Align memory to 16 bytes. 
 * POSIX requires malloc to return a pointer suitably aligned for any built-in type.
 */
#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

/* Metadata block structure placed just before the allocated memory */
struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
    int magic; /* For debugging/sanity checks */
};

#define META_SIZE ALIGN(sizeof(struct block_meta))

/* Head of the free list */
static void *global_base = NULL;

/* 
 * Iterate through the linked list to find a free block large enough.
 * First-fit algorithm.
 */
static struct block_meta *find_free_block(struct block_meta **last, size_t size) {
    struct block_meta *current = global_base;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

/* 
 * Request space from the OS using sbrk.
 */
static struct block_meta *request_space(struct block_meta *last, size_t size) {
    struct block_meta *block;
    
    /* sbrk(0) gives the current top of the heap */
    block = sbrk(0);
    
    /* Increment the heap size */
    void *request = sbrk(size + META_SIZE);
    if (request == (void *)-1) {
        return NULL; /* sbrk failed */
    }

    if (last) {
        last->next = block;
    }
    
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}

void *malloc(size_t size) {
    struct block_meta *block;
    
    /* POSIX states: if size is 0, malloc may return NULL or a unique pointer */
    if (size == 0) {
        return NULL;
    }

    size_t aligned_size = ALIGN(size);

    if (!global_base) {
        /* First call to malloc */
        block = request_space(NULL, aligned_size);
        if (!block) {
            errno = ENOMEM;
            return NULL;
        }
        global_base = block;
    } else {
        struct block_meta *last = global_base;
        block = find_free_block(&last, aligned_size);
        
        if (!block) {
            /* No suitable free block found, request more from OS */
            block = request_space(last, aligned_size);
            if (!block) {
                errno = ENOMEM;
                return NULL;
            }
        } else {
            /* Found a free block, mark it as used */
            block->free = 0;
            block->magic = 0x77777777;
        }
    }
    
    /* Return a pointer to the memory region just after the metadata */
    return (block + 1);
}
