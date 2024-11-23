#include <stdio.h>
#include <stdlib.h>



struct node {
    int value;
    struct node *next;
};

void printList(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

struct node* reverseList(struct node *head) {
    struct node *reverseHead = NULL;
    struct node *reverseCurrent = head;

    while(reverseCurrent != NULL) {
        //remove node from og list
        struct node *reverseNext = reverseCurrent->next;

        //insert the node at the front of reverse list
        reverseCurrent->next = reverseHead;
        reverseHead = reverseCurrent;
        reverseCurrent = reverseNext;
    }
    return reverseHead;
}


int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int value;
    
    printf("Please enter the integers (CTRL + D): \nInput data for node 0: ");
    for (int i=0; scanf("%d", &value) != EOF; i++) {
        printf("Input data for node %d: ", i+1);
        //create the node
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->value = value;
        newNode->next = NULL;

        if (newNode == NULL) {
            printf("Allocation failed\n");
            return 1;
        }

        //link it
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } 
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    
    printf("\nThe linked list in normal order is: ");
    printList(head);

    head = reverseList(head);
    printf("\nThe linked list in reverse order is: ");
    printList(head);

    //free the mem'
    struct node *curr = head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    return 0;
}