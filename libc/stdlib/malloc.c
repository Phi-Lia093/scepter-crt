/* Simple malloc implementation using brk syscall
 * Uses a simple first-fit allocator with free list */

#include <stddef.h>

/* Block header structure */
typedef struct block {
    size_t size;           /* Size of data area (excluding header) */
    struct block *next;    /* Next block in free list */
    int is_free;          /* 1 if free, 0 if allocated */
} block_t;

#define BLOCK_SIZE sizeof(block_t)
#define ALIGN4(x) (((x) + 3) & ~3)

/* Head of free list */
static block_t *free_list = NULL;

/* Heap boundaries */
static void *heap_start = NULL;
static void *heap_end = NULL;

/* External syscall - defined in syscall.c */
extern int brk(void *addr);

/* Get current heap end (brk(0) returns current break) */
static void *sbrk(size_t increment)
{
    if (!heap_start) {
        /* First call - get initial heap position */
        heap_start = (void *)brk(0);
        heap_end = heap_start;
    }
    
    void *old_break = heap_end;
    void *new_break = (char *)heap_end + increment;
    
    if (brk(new_break) < 0) {
        return (void *)-1;  /* Failed to expand heap */
    }
    
    heap_end = new_break;
    return old_break;
}

/* Find a free block that fits size */
static block_t *find_free_block(block_t **last, size_t size)
{
    block_t *current = free_list;
    
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    
    return current;
}

/* Request more memory from kernel */
static block_t *request_space(block_t *last, size_t size)
{
    block_t *block;
    
    block = (block_t *)sbrk(BLOCK_SIZE + size);
    if (block == (void *)-1) {
        return NULL;  /* sbrk failed */
    }
    
    if (last) {
        last->next = block;
    }
    
    block->size = size;
    block->next = NULL;
    block->is_free = 0;
    
    return block;
}

void *malloc(size_t size)
{
    block_t *block;
    
    if (size <= 0) {
        return NULL;
    }
    
    /* Align size to 4 bytes */
    size = ALIGN4(size);
    
    if (!free_list) {
        /* First allocation */
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
        }
        free_list = block;
    } else {
        /* Try to find a free block */
        block_t *last = free_list;
        block = find_free_block(&last, size);
        
        if (!block) {
            /* No free block found, request more space */
            block = request_space(last, size);
            if (!block) {
                return NULL;
            }
        } else {
            /* Found a free block */
            block->is_free = 0;
        }
    }
    
    return (void *)(block + 1);  /* Return pointer after header */
}

void free(void *ptr)
{
    if (!ptr) {
        return;
    }
    
    /* Get block header */
    block_t *block = (block_t *)ptr - 1;
    block->is_free = 1;
    
    /* TODO: Coalesce adjacent free blocks for better memory reuse */
}

void *calloc(size_t nmemb, size_t size)
{
    size_t total_size = nmemb * size;
    void *ptr;
    
    /* Check for overflow */
    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }
    
    ptr = malloc(total_size);
    if (!ptr) {
        return NULL;
    }
    
    /* Zero the memory */
    char *byte_ptr = (char *)ptr;
    for (size_t i = 0; i < total_size; i++) {
        byte_ptr[i] = 0;
    }
    
    return ptr;
}

void *realloc(void *ptr, size_t size)
{
    if (!ptr) {
        return malloc(size);
    }
    
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    
    /* Get old block */
    block_t *block = (block_t *)ptr - 1;
    
    /* If new size fits in current block, just return it */
    if (block->size >= size) {
        return ptr;
    }
    
    /* Need to allocate new block and copy data */
    void *new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }
    
    /* Copy old data */
    char *src = (char *)ptr;
    char *dst = (char *)new_ptr;
    size_t copy_size = (block->size < size) ? block->size : size;
    
    for (size_t i = 0; i < copy_size; i++) {
        dst[i] = src[i];
    }
    
    free(ptr);
    return new_ptr;
}