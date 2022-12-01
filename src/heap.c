#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "heap.h"

// create a heap, capacity set to 16
void heap_init(struct Heap *heap) {
  heap->size = 0;
  heap->capacity = 16;
  heap->task_array = malloc(sizeof(struct HeapNode) * heap->capacity);
}

// insert a task into the heap
int heap_enqueue(struct Heap *heap, struct task_struct *task, int value) {
  if (heap->size == heap->capacity) {
    fprintf(stderr, "heap is full\n");
    return -EAGAIN;
  }

  // insert the task into the heap
  heap->task_array[heap->size].task = task;
  heap->task_array[heap->size].value = value;
  // do the heapify
  int i = heap->size;
  while (i > 0 && heap->task_array[i].value < heap->task_array[(i - 1) / 2].value) {
    struct HeapNode temp = heap->task_array[i];
    heap->task_array[i] = heap->task_array[(i - 1) / 2];
    heap->task_array[(i - 1) / 2] = temp;
    i = (i - 1) / 2;
  }
  // size plus one
  heap->size++;

  fprintf(stderr, "enqueue %d %ld %d\n", heap->size, task, value);
  return 0;
}

// pop the task
struct task_struct *heap_dequeue(struct Heap *heap) {
  // if the heap is empty, return NULL
  if (heap->size == 0) {
    return NULL;
  }

  // pop the task
  struct task_struct *ret_task = heap->task_array[0].task;
  heap->task_array[0] = heap->task_array[heap->size - 1];
  heap->size--;

  // do the heapify
  int i = 0;
  while (i < heap->size) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = i;
    if (left < heap->size && heap->task_array[left].value < heap->task_array[min].value) {
      min = left;
    }
    if (right < heap->size && heap->task_array[right].value < heap->task_array[min].value) {
      min = right;
    }
    if (min == i) {
      break;
    }
    struct HeapNode temp = heap->task_array[i];
    heap->task_array[i] = heap->task_array[min];
    heap->task_array[min] = temp;
    i = min;
  }
  fprintf(stderr, "dequeue %d %ld\n", heap->size, ret_task);

  return ret_task;
}

