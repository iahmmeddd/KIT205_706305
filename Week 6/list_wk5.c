#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_wk5.h"

//TODO: change data type to char*

List new_list() {
	List temp;
	temp.head = NULL;
	return temp;
}

// after changing to char*:
// -- need to change printf for string
void print_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		printf("%s", current->data);
		current = current->next;

		if (current != NULL)
			printf(", ");
	}
	printf("\n");
}

// after changing to char*:
// -- check how long data parameter is (strlen)
// -- allocate just enough memory for newNode->data (malloc)
// -- copy string from parameter into newNode->data (strcpy)
void insert_at_front(List* self, String data) {
	ListNodePtr new_node = malloc(sizeof * new_node);
	new_node->data = malloc(strlen(data) + 1);
	strcpy(new_node->data, data);

	new_node->next = self->head;
	self->head = new_node;
}

// after changing to char*:
// -- change test in if statement to string compare (strcmp)
// -- free current->data (memory allocated for string) before freeing current
void delete_from_list(List* self, String data) {
	ListNodePtr current = self->head;
	ListNodePtr prev = NULL;

	while (current != NULL) {
		if (strcmp(current->data, data) == 0) {
			if (prev == NULL) {        // front of list
				self->head = current->next;
				free(current->data);
				free(current);
				current = self->head;
			}
			else {                    // middle of list
				prev->next = current->next;

				free(current->data);
				free(current);
				current = prev->next;
			}
		}
		else {
			prev = current;
			current = current->next;
		}
	}
}

// after changing to char*:
// -- need to free memory allocated for string before freeing node
void destroy_list(List* self) {
	ListNodePtr current = self->head;
	while (current != NULL) {
		ListNodePtr to_free = current;

		current = current->next;
		free(to_free->data);
		free(to_free);
	}
	self->head = NULL;
}
void list_test() {
    List myList = new_list();

    printf("Testing insert_at_front...\n");
    insert_at_front(&myList, "5");
    insert_at_front(&myList, "3");
    insert_at_front(&myList, "7");
    insert_at_front(&myList, "2");
    insert_at_front(&myList, "0");

    printf("Expected: 0, 2, 7, 3, 5\n");
    printf("Result: ");
    print_list(&myList);
    destroy_list(&myList);

    /*
    printf("\nTesting insert_in_order...\n");
    List orderedList = new_list();

    insert_in_order(&orderedList, "5");
    insert_in_order(&orderedList, "3");
    insert_in_order(&orderedList, "7");
    insert_in_order(&orderedList, "2");
    insert_in_order(&orderedList, "0");

    printf("Expected: 0, 2, 3, 5, 7\n");
    printf("Result: ");
    print_list(&orderedList);
    destroy_list(&orderedList);
    */

    printf("\nTesting delete_from_list...\n");
    List deleteTest = new_list();

    insert_at_front(&deleteTest, "1");
    insert_at_front(&deleteTest, "2");
    insert_at_front(&deleteTest, "3");
    insert_at_front(&deleteTest, "4");

    delete_from_list(&deleteTest, "1");
    delete_from_list(&deleteTest, "3");

    printf("Expected: 4, 2\n");
    printf("Result: ");
    print_list(&deleteTest);
    destroy_list(&deleteTest);

    /*
    printf("\nTesting reverse...\n");
    List reverseTest = new_list();

    insert_at_front(&reverseTest, "5");
    insert_at_front(&reverseTest, "3");
    insert_at_front(&reverseTest, "7");

    printf("Original: ");
    print_list(&reverseTest);

    List reversed = reverse(&reverseTest);
    printf("Expected reversed: 5, 3, 7\n");
    printf("Result: ");
    print_list(&reversed);

    destroy_list(&reverseTest);
    destroy_list(&reversed);
    */

    /*
    printf("\nTesting merge...\n");
    List list1 = new_list();
    List list2 = new_list();

    insert_in_order(&list1, "1");
    insert_in_order(&list1, "3");
    insert_in_order(&list1, "5");

    insert_in_order(&list2, "2");
    insert_in_order(&list2, "4");
    insert_in_order(&list2, "6");

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
    */
}