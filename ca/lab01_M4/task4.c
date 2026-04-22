#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int main(void) {
    Node *head = NULL;
    int x;

    while (scanf("%d", &x) == 1 && x != 0) {
        Node *n = (Node *)malloc(sizeof(Node));
        n->value = x;
        n->next = head;
        head = n;
    }

    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;

    for (Node *p = head; p != NULL; p = p->next)
        printf("%d ", p->value);
    printf("\n");

    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }

    return 0;
}
