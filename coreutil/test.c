#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int main(void)
{
    printf("=== Testing Phase 1A/B Syscalls ===\n\n");
    
    /* Test getpid/getppid */
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());
    printf("\n");
    
    /* Test getcwd */
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd))) {
        printf("Current directory: %s\n", cwd);
    } else {
        printf("getcwd failed\n");
    }
    printf("\n");
    
    /* Test malloc */
    printf("Testing malloc...\n");
    char *str = (char *)malloc(20);
    if (str) {
        strcpy(str, "Hello from malloc!");
        printf("Allocated string: %s\n", str);
        free(str);
        printf("Memory freed\n");
    } else {
        printf("malloc failed\n");
    }
    printf("\n");
    
    /* Test calloc */
    printf("Testing calloc...\n");
    int *arr = (int *)calloc(5, sizeof(int));
    if (arr) {
        printf("Allocated array of 5 ints (should be zero): ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        /* Fill array */
        for (int i = 0; i < 5; i++) {
            arr[i] = i * 10;
        }
        printf("After filling: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
        printf("Memory freed\n");
    } else {
        printf("calloc failed\n");
    }
    printf("\n");
    
    /* Test realloc */
    printf("Testing realloc...\n");
    char *buf = (char *)malloc(10);
    if (buf) {
        strcpy(buf, "Small");
        printf("Original: %s (size 10)\n", buf);
        
        buf = (char *)realloc(buf, 50);
        if (buf) {
            strcpy(buf, "Now this is a much larger string!");
            printf("After realloc: %s (size 50)\n", buf);
            free(buf);
            printf("Memory freed\n");
        } else {
            printf("realloc failed\n");
        }
    } else {
        printf("malloc failed\n");
    }
    printf("\n");
    
    printf("=== All tests completed! ===\n");
    exit(0);
}