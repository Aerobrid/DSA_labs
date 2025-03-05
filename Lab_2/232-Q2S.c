#include <stdio.h>          // just needed for default programs
#include <stdlib.h>         // needed for dynamic memory allocation
#include <stdbool.h>        // since one of the leetcode functions returns a boolean value

typedef struct {
    int *inStack;           // pointer in Queue struct pointing to array for enqueue operations (pushing to input stack)
    int *outStack;          // pointer in Queue struct pointing to array for dequeue operations (popping from output stack)
    int inTop;              // the top of inStack
    int outTop;             // the top of outStack
    int capacity;           // capacity of stacks (and therefore the capacity of the queue) **tell viewer about when capacity is necessary**
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));                             // allocate memory in the heap for new Queue struct
    if(!queue){
        printf("Memory Allocation Error");
        return NULL;
    }
    queue->capacity = 100;                                                          // Set an initial size/capacity for queue
    queue->inStack = (int*)malloc(queue->capacity * sizeof(int));                   // Explain rest of function
    queue->outStack = (int*)malloc(queue->capacity * sizeof(int));
    queue->inTop = -1;
    queue->outTop = -1;
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {                                             // Given pointer to Queue struct, add to instack array
    if (obj->inTop + 1 >= obj->capacity) {                                          // To avoid out of bounds with capacity variable
        printf("Queue is full!\n");
        return;
    }
    obj->inStack[++obj->inTop] = x;
}


bool myQueueEmpty(MyQueue* obj) {
    return obj->inTop == -1 && obj->outTop == -1;                                   // Given pointer to Queue struct, 
}                                                                                   // return a bool saying if both stacks are empty or not

int myQueuePop(MyQueue* obj) {
    if (myQueueEmpty(obj)) {                                                        // In case no elements within both stacks in queue
        printf("Queue is empty, cannot pop.\n");    
        return -1;  
    }
    if (obj->outTop == -1) {                                                        // If the outStack is empty, transfer all elements from instack array
        while (obj->inTop >= 0) {                                                   // Explain rest
            obj->outStack[++obj->outTop] = obj->inStack[obj->inTop--];
        }
    }
    return obj->outStack[obj->outTop--];                                            // Pop element from outStack array IF ANY
}

int myQueuePeek(MyQueue* obj) {
    if (myQueueEmpty(obj)) {                                                        // In case no elements within both stacks in queue
        printf("Queue is empty, cannot pop.\n");
        return -1;  
    }
    if (obj->outTop == -1) {                                                        // Transfer elements if outStack is empty IF ANY
        while (obj->inTop >= 0) {                                                   // Explain rest
            obj->outStack[++obj->outTop] = obj->inStack[obj->inTop--];
        }
    }
    return obj->outStack[obj->outTop];                                              // return a peek at the top of outStack
}

void myQueueFree(MyQueue* obj) {                                                    // free function FREES:
    free(obj->inStack);                                                             // 1. instack from Queue struct (we used malloc)
    free(obj->outStack);                                                            // 2. outstack from Queue struct (we used malloc)
    free(obj);                                                                      // 3. Queue struct itself (we used malloc)
}

// From the leetcode question on how to implement functions in main:
/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 
 * int param_2 = myQueuePop(obj);
 
 * int param_3 = myQueuePeek(obj);
 
 * bool param_4 = myQueueEmpty(obj);
 
 * myQueueFree(obj);
*/

int main(){
    int x = 15;

    MyQueue* obj = myQueueCreate();
    myQueuePush(obj, x);
    myQueuePush(obj, 32);
    myQueuePush(obj, 12);
    myQueuePush(obj, 42);
 
    int pop_1 = myQueuePop(obj);
    printf("%d popped from Queue\n", pop_1);
    int pop_2 = myQueuePop(obj);
    printf("%d popped from Queue\n", pop_2);
    int pop_3 = myQueuePop(obj);
    printf("%d popped from Queue\n", pop_3);
    int pop_4 = myQueuePop(obj);
    printf("%d popped from Queue\n", pop_4);
  
    int peek = myQueuePeek(obj);
    printf("%d is at the front of queue\n", peek);
 
    bool empty = myQueueEmpty(obj);
    if(empty)
        printf("Queue is empty\n");
    else
        printf("Queue is not empty\n");
 
   // Call the myQueueFree function in main to free the Queue struct and the 2 stacks inside of it
   myQueueFree(obj);

    return 0;
}


