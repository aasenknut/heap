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

void bubbleUp(struct MinHeap *h, size_t idx) {
    size_t parenIdx;
    float tmp;
    while (idx > 0) {
        parenIdx = (idx - 1) / 2;
        if (h->arr[idx] >= h->arr[parenIdx]) {
            break;
        } else {
            tmp = h->arr[parenIdx];
            h->arr[parenIdx] = h->arr[idx];
            h->arr[idx] = tmp;
        }
    }
}

void push(struct MinHeap *h, float x) {
    if (h->len >= h->cap) {
        fprintf(stderr, "\nheap is full - len >= cap");
        return;
    }
    h->len++;
    size_t idx = h->len-1;
    h->arr[idx] = x;
    bubbleUp(h, idx);
}


float pop(struct MinHeap *h) {
    float x = h->arr[0];
    h->arr[0] = h->arr[h->len-1];
    h->len--;

    size_t idx = 0;
    size_t smallest;
    size_t parenIdx;
    size_t lIdx;
    size_t rIdx;
    float tmp;

    while (idx >= 0) {
        smallest = idx;
        parenIdx = (idx-1) / 2;
        lIdx = idx * 2 + 1;
        rIdx = idx * 2 + 2;

        if (lIdx < h->len && h->arr[lIdx] < h->arr[smallest]) {
            smallest = lIdx;
        }
        if (rIdx < h->len && h->arr[rIdx] < h->arr[smallest]) {
            smallest = rIdx;
        }

        if (idx != smallest) {
            tmp = h->arr[idx];
            h->arr[idx] = h->arr[smallest];
            h->arr[smallest] = tmp;
            idx = smallest;
        } else {
            break;
        }
    }

    return x;
}

void bubbleDown(struct MinHeap *h, size_t idx) {
    size_t smallest = idx;
    size_t lIdx = idx * 2 + 1;
    size_t rIdx = idx * 2 + 2;
    if (lIdx < h->len && h->arr[lIdx] < h->arr[smallest]) {
        smallest = lIdx;
    }
    if (rIdx < h->len && h->arr[rIdx] < h->arr[smallest]) {
        smallest = rIdx;
    }

    if (idx != smallest) {
        float tmp = h->arr[idx];
        h->arr[idx] = h->arr[smallest];
        h->arr[smallest] = tmp;
        bubbleDown(h, smallest);
    }
}

struct MinHeap heapify(float *arr, size_t arrLen) {
    struct MinHeap heap;
    heap.len = arrLen;
    heap.cap = CAP;
    heap.arr = (float *)malloc(sizeof(float) * CAP);
    if (heap.arr == NULL) {
        fprintf(stderr, "\nfailed to heapify - heap.array = null");
        return heap;
    }
    for (size_t j = 0; j < arrLen; j++) {
        heap.arr[j] = arr[j];
    }
    for (int j = (arrLen / 2) - 1; j >= 0; j--) {
        bubbleDown(&heap, j);
    }
    return heap;
}

int main() {
    struct MinHeap heap;
    float arr[5] = {1.5, 3.2, 5.1, 4.5, 1};
    heap = heapify(arr, 5);
    if (heap.arr == NULL) {
        fprintf(stderr, "\nmemory allocation failed");
        return 1;
    }
    for (size_t j = 0; j < 5; j++) {
        printf("\n%f", heap.arr[j]);
    }
    free(heap.arr);
    return 0;
}
