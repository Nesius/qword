#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stddef.h>

void *kalloc(size_t);
void kfree(void *);
void *krealloc(void *, size_t);

#endif
