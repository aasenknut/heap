#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define CAP 12345

struct MinHeap {
    float *arr;
    size_t len;
    size_t cap;
};


void push(struct MinHeap *h) {
}

float pop(struct MinHeap *h) {
    float x = h->arr[0];
    h->arr[0] = h->arr[h->len-1];
    h->len--;

    size_t idx = 0;
    size_t smallest;
    float parenIdx;
    float lIdx;
    float rIdx;
    
    while (1) {
        if (idx < 0) {
            break;
        }
        smallest = idx;
        parenIdx = idx / 2;
        lIdx = idx * 2 + 1;
        rIdx = idx * 2 + 2;
        if (lIdx < h->len) && (h->arr[lIdx] < h->arr[smallest]) {
            smallest = lIdx
        }
        if (rIdx < h->len) && (h->arr[rIdx] < h->arr[smallest]) {
            smallest = rIdx
        }
    }

    return x;
}

void arrange(struct MinHeap *h) {
}


struct MinHeap heapify(float *arr, size_t arrLen) {
    struct MinHeap heap;
    heap.len = arrLen;
    heap.cap = CAP;
    heap.arr = (float *)malloc(sizeof(float) * CAP);
    if (heap.arr == NULL) {
        return heap; // Return an error code
    }
    for (size_t j = 0; j < arrLen; j++) {
        heap.arr[j] = arr[j];
    }
    return heap;
}

int main() {
    struct MinHeap heap;
    float arr[5] = {1.5, 3.2, 1.1, 4.5, 7.9};
    heap = heapify(arr, 5);
    if (heap.arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }
    free(heap.arr);
    return 0;
}
