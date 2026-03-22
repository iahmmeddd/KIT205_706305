#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List new_list() {
    List temp;
    temp.head = NULL;
    return temp;
}

void print_list(List* self) {
    ListNodePtr current = self->head;

    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;

        if (current != NULL) {
            printf(", ");
        }
    }
    printf("\n");
}

void insert_at_front(List* self, int data) {
    ListNodePtr new_node = malloc(sizeof * new_node);

    new_node->data = data;
    new_node->next = self->head;
    self->head = new_node;
}

void insert_in_order(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    ListNodePtr new_node = malloc(sizeof * new_node);
    new_node->data = data;
    new_node->next = NULL;

    while (current != NULL && current->data < data) {
        prev = current;
        current = current->next;
    }

    if (current == self->head) {
        new_node->next = current;
        self->head = new_node;
    }
    else {
        new_node->next = current;
        prev->next = new_node;
    }
}

void delete_list(List* self, int data) {
    ListNodePtr current = self->head;
    ListNodePtr prev = NULL;

    while (current != NULL && current->data != data) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        if (prev == NULL) {
            self->head = current->next;
        }
        else {
            prev->next = current->next;
        }
        free(current);
    }
}

void destroy_list(List* self) {
    ListNodePtr current = self->head;

    while (current != NULL) {
        ListNodePtr to_free = current;
        current = current->next;
        free(to_free);
    }

    self->head = NULL;
}

List reverse(List* self) {
    List reversed = new_list();
    ListNodePtr current = self->head;

    while (current != NULL) {
        insert_at_front(&reversed, current->data);
        current = current->next;
    }

    return reversed;
}

List merge(List* list1, List* list2) {
    List merged = new_list();
    ListNodePtr current1 = list1->head;
    ListNodePtr current2 = list2->head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->data <= current2->data) {
            insert_in_order(&merged, current1->data);
            current1 = current1->next;
        }
        else {
            insert_in_order(&merged, current2->data);
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        insert_in_order(&merged, current1->data);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        insert_in_order(&merged, current2->data);
        current2 = current2->next;
    }

    return merged;
}

void list_test() {
    List myList = new_list();

    printf("Testing insert_at_front...\n");
    insert_at_front(&myList, 5);
    insert_at_front(&myList, 3);
    insert_at_front(&myList, 7);
    insert_at_front(&myList, 2);
    insert_at_front(&myList, 0);

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("Result: ");
    print_list(&myList);
    destroy_list(&myList);

    printf("\nTesting insert_in_order...\n");
    List orderedList = new_list();

    insert_in_order(&orderedList, 5);
    insert_in_order(&orderedList, 3);
    insert_in_order(&orderedList, 7);
    insert_in_order(&orderedList, 2);
    insert_in_order(&orderedList, 0);

    printf("Expected: 0, 2, 3, 5, 7\n");
    printf("Result: ");
    print_list(&orderedList);
    destroy_list(&orderedList);

    printf("\nTesting delete_list...\n");
    List deleteTest = new_list();

    insert_in_order(&deleteTest, 1);
    insert_in_order(&deleteTest, 2);
    insert_in_order(&deleteTest, 3);
    insert_in_order(&deleteTest, 4);

    delete_list(&deleteTest, 1);
    delete_list(&deleteTest, 3);

    printf("Expected: 2, 4\n");
    printf("Result: ");
    print_list(&deleteTest);
    destroy_list(&deleteTest);

    printf("\nTesting reverse...\n");
    List reverseTest = new_list();

    insert_at_front(&reverseTest, 5);
    insert_at_front(&reverseTest, 3);
    insert_at_front(&reverseTest, 7);

    printf("Original: ");
    print_list(&reverseTest);

    List reversed = reverse(&reverseTest);
    printf("Expected reversed: 5, 3, 7\n");
    printf("Result: ");
    print_list(&reversed);

    destroy_list(&reverseTest);
    destroy_list(&reversed);

    printf("\nTesting merge...\n");
    List list1 = new_list();
    List list2 = new_list();

    insert_in_order(&list1, 1);
    insert_in_order(&list1, 3);
    insert_in_order(&list1, 5);

    insert_in_order(&list2, 2);
    insert_in_order(&list2, 4);
    insert_in_order(&list2, 6);

    printf("List 1: ");
    print_list(&list1);
    printf("List 2: ");
    print_list(&list2);

    List merged = merge(&list1, &list2);
    printf("Expected merged: 1, 2, 3, 4, 5, 6\n");
    printf("Result: ");
    print_list(&merged);

    destroy_list(&list1);
    destroy_list(&list2);
    destroy_list(&merged);
}

void option_insert(List* self) {
    int value;
    printf("Enter value to insert: ");
    scanf("%d", &value);
    insert_at_front(self, value);
}

void option_delete(List* self) {
    int value;
    printf("Enter value to delete: ");
    scanf("%d", &value);
    delete_list(self, value);
}

void option_print(List* self) {
    printf("List: ");
    print_list(self);
}

void list_adhoc_test() {
    List myList = new_list();
    int quit = 0;

    while (!quit) {
        int option;

        printf("\n0 = quit, 1 = insert, 2 = delete, 3 = print\n");
        printf("Choose option: ");
        scanf("%d", &option);

        if (option == 0) {
            quit = 1;
        }
        else if (option == 1) {
            option_insert(&myList);
        }
        else if (option == 2) {
            option_delete(&myList);
        }
        else if (option == 3) {
            option_print(&myList);
        }
        else {
            printf("Invalid option\n");
        }
    }

    destroy_list(&myList);
}