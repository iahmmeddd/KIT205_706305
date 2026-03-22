// This header file contains declarations for a singly linked list data structure implementation in C.
#pragma once

typedef struct listNode {
    int data;
    struct listNode* next;
} *ListNodePtr;

typedef struct list {
    ListNodePtr head;
} List;

List new_list();
void print_list(List* self);
void insert_at_front(List* self, int data);
void insert_in_order(List* self, int data);
void delete_list(List* self, int data);
void destroy_list(List* self);

void list_test();
void list_adhoc_test();

List reverse(List* self);
List merge(List* list1, List* list2);