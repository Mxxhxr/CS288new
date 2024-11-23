#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *next;
};

// Function to print the list
void printList(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void bubbleSort(struct node **head) {
    int swap = 1;

    while(swap) {
        swap = 0;
        struct node **curr = head;

        while((*curr)->next != NULL) {
            struct node *x = *curr;
            struct node *y = x->next;

            //compare nodes
            if(x->value > y->value) {
                //swap nodes
                x->next = y->next;
                y->next = x;
                *curr = y;
                swap = 1;
            }
            curr = &(*curr)->next;
        }  
    }
}
//user input into unsorted linked list also taken from problem 1
int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    int value;
    
    printf("Please enter the integers (CTRL + D): \n");
    for (int i=0; scanf("%d", &value) != EOF; i++) {
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

    bubbleSort(&head);
    printf("Sorted list:\n");
    printList(head);

    //freeing mem also taken from problem 1
    struct node *curr = head;
    while (curr != NULL) {
        struct node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    return 0;
}