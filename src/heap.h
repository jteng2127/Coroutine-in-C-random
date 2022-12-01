#ifndef __HEAP_H__
#define __HEAP_H__

struct HeapNode { // heap node, store task_struct and heap value(priority)
  int value;
  struct task_struct *task;
};

struct Heap { // min heap
  int size;
  int capacity;
  struct HeapNode *task_array;
};

// create a heap, capacity set to 16 at first
void heap_init(struct Heap *heap);

// insert a task into the heap
int heap_enqueue(struct Heap *heap, struct task_struct *task, int value);

// pop the task
struct task_struct *heap_dequeue(struct Heap *heap);

#endif
