#include <stdio.h>      // For C code
#include <stdlib.h>     // For malloc

// Node structure for LL in C programming
struct ListNode {
    int val;
    struct ListNode* next;
};

// Function to create a new node for LL
struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the beginning of the LL
void insertAtBeginning(struct ListNode** head, int val) {
    struct ListNode* newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
}

void printList(struct ListNode* head) {
    while (head != NULL) {
        printf("%d -> ", head->val);
        head = head->next;
    }
    printf("NULL\n");
}

// Function which returns the modified head of LL 
struct ListNode* removeElements(struct ListNode* head, int val) {
    // If no elements in LL return head
    if(head == NULL) return head;
    // While head points to a node AND value in node is target value, move head to next node in LL
    while(head != NULL && head -> val == val)
        head = head -> next;
    // Create new pointer at heads location
    struct ListNode* curr = head;
    while(curr != NULL && curr -> next != NULL){
        if(curr -> next -> val == val)
            curr -> next = curr -> next -> next;
        else
            curr = curr -> next;
    }
    return head;
}

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* current = head; 
    struct ListNode* next = NULL;
    while(current != NULL){
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next; 
    }
    return prev;
}

void freelist(struct ListNode* head){
    struct ListNode* temp;
    while(head != NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }
}

int main() {
    struct ListNode* head = NULL;

    // Insert elements into the list
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 10);

    // Print LL
    printf("Original List: \n");
    printList(head);
    printf("\n");

    // Reverse the LL
    head = reverseList(head);
    printf("Reversed List: \n");
    printList(head);
    printf("\n");

    // Reverse LL again to restore the original list
    head = reverseList(head);
    printf("Restored Original List: \n");
    printList(head);
    printf("\n");

    // Use removeElements function
    head = removeElements(head, 10);
    printf("Removed Nodes with value 10 in list: \n");
    printList(head);

    // Free memory allocated for LL
    freelist(head);

    return 0;
}