#ifndef __KLIB_H__
#define __KLIB_H__

#include <stdint.h>
#include <stddef.h>
#include <proc/task.h>

#define KPRN_MAX_TYPE 3

#define KPRN_INFO   0
#define KPRN_WARN   1
#define KPRN_ERR    2
#define KPRN_DBG    3
#define KPRN_PANIC  4

#define EMPTY ((void *)(size_t)(-1))

__attribute__((always_inline)) inline int is_printable(char c) {
    return (c >= 0x20 && c <= 0x7e);
}

__attribute__((always_inline)) inline void atomic_fetch_add_int(int *p, int *v, int x) {
    int h = x;
    asm volatile (
        "lock xadd dword ptr [%1], %0;"
        : "+r" (h)
        : "r" (p)
        : "memory"
    );
    *v = h;
}

__attribute__((always_inline)) inline void atomic_add_uint64_relaxed(uint64_t *p, uint64_t x) {
    asm volatile (
        "lock xadd qword ptr [%1], %0;"
        : "+r" (x)
        : "r" (p)
    );
}

int exec(pid_t, const char *, const char **, const char **);

pid_t kexec(const char *, const char **, const char **,
            const char *, const char *, const char *);

void execve_send_request(pid_t, const char *, const char **, const char **, lock_t **, int **);
void exit_send_request(pid_t, int);
void userspace_request_monitor(void *);

int ktolower(int);
char *kstrchrnul(const char *, int);
char *kstrcpy(char *, const char *);
size_t kstrlen(const char *);
int kstrcmp(const char *, const char *);
int kstrncmp(const char *, const char *, size_t);
void kprint(int type, const char *fmt, ...);

void *kmemset(void *, int, size_t);
void *kmemset64(void *, uint64_t, size_t);
void *kmemcpy(void *, const void *, size_t);
void *kmemcpy64(void *, const void *, size_t);
int kmemcmp(const void *, const void *, size_t);
void *kmemmove(void *, const void *, size_t);

void readline(int, const char *, char *, size_t);

#endif
