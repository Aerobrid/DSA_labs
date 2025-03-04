#include <stdio.h>          // just needed for default programs
#include <stdlib.h>         // needed for dynamic memory allocation
#include <stdbool.h>        // since one of the leetcode functions returns a boolean value

typedef struct {
    int *q1;                                                                // Main queue
    int *q2;                                                                // Temporary queue
    int front1, rear1, front2, rear2;                                       // The front & rear of both queues
    int capacity;                                                           // Capacity of the queues
} MyStack;

MyStack* myStackCreate() {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->capacity = 100;                                                  // Set an initial size, can be of any POSITIVE int value (unsigned)
    stack->q1 = (int*)malloc(stack->capacity * sizeof(int));                // Explain rest of function
    stack->q2 = (int*)malloc(stack->capacity * sizeof(int));
    stack->front1 = stack->rear1 = -1;                                      // Both are initially at -1 since no values have been assigned inside
    stack->front2 = stack->rear2 = -1;
    return stack;
}

// helper function
void myQueueEnqueue(int* queue, int* front, int* rear, int x) {             // pass by reference instead of value, why pass in front and rear?
    if (*rear == -1) *front = 0;                                            // Initialize front if queue was empty
    queue[++(*rear)] = x;                                                   // Update where rear is at in queue
}

// helper function
int myQueueDequeue(int* queue, int* front, int* rear) {                     // if not already answered, why queue?
    int val = queue[*front];                                                // for returning val at front of queue (val = queue[0] = ?)
    if (*front == *rear) {                                                  // If only one element left in queue, reset both front and rear
        *front = *rear = -1;
    } else {
        (*front)++;                                                         // else increment front
    }
    return val;
}

void myStackPush(MyStack* obj, int x) {
    myQueueEnqueue(obj->q1, &obj->front1, &obj->rear1, x);                  // given pointer to stack, add to the main queue
}

int myStackPop(MyStack* obj) {
    while (obj->front1 != obj->rear1)                                       // Move all except last to q2 (temporary queue for popping)
        myQueueEnqueue(obj->q2, &obj->front2, &obj->rear2, myQueueDequeue(obj->q1, &obj->front1, &obj->rear1));
    int popped = myQueueDequeue(obj->q1, &obj->front1, &obj->rear1);        // for returning the value of popped last element (q1 is now empty)
    obj->front1 = obj->front2; obj->rear1 = obj->rear2;                     // Swap main and temp queues (updated q2 which becomes q1)
    obj->front2 = obj->rear2 = -1;                                          // Reset q2
    int* temp = obj->q1;                                                    // swap operation                                                   
    obj->q1 = obj->q2;
    obj->q2 = temp;
    return popped;
}

int myStackTop(MyStack* obj) {                                              
    while (obj->front1 != obj->rear1) {                                     // Same operation as last function 
        myQueueEnqueue(obj->q2, &obj->front2, &obj->rear2, myQueueDequeue(obj->q1, &obj->front1, &obj->rear1));
    }
    int top = obj->q1[obj->front1];                                         // To peek at the last element
    myQueueEnqueue(obj->q2, &obj->front2, &obj->rear2, myQueueDequeue(obj->q1, &obj->front1, &obj->rear1));
    obj->front1 = obj->front2; obj->rear1 = obj->rear2;                     // Swap q1 and q2
    obj->front2 = obj->rear2 = -1;
    int* temp = obj->q1;
    obj->q1 = obj->q2;
    obj->q2 = temp;
    return top;
}

bool myStackEmpty(MyStack* obj) {
    return obj->front1 == -1;                                                 // Given pointer to stack struct, return bool if 
}                                                                             // main queue is empty

void myStackFree(MyStack* obj) {                                              // free function FREES:
    free(obj->q1);                                                            // 1. Main queue in stack struct (uses malloc)
    free(obj->q2);                                                            // 2. Temp queue in stack struct (uses malloc)
    free(obj);                                                                // 3. Stack struct itself (uses malloc)
}

// From the leetcode question on how to implement functions in main:
/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/

int main(){
    int x = 15;
    MyStack* obj = myStackCreate();
    myStackPush(obj, x);
    myStackPush(obj, 30);
    myStackPush(obj, 45);
 
    int pop_1 = myStackPop(obj);
    printf("Popped %d from stack\n", pop_1);
    int pop_2 = myStackPop(obj);
    printf("Popped %d from stack\n", pop_2);

    int top = myStackTop(obj);
    printf("Top of stack is: %d\n", top);
 
    bool empty = myStackEmpty(obj);
    if(empty)
        printf("Stack is empty\n");
    else
        printf("Stack is not empty\n");
 
    myStackFree(obj);

    return 0;
}