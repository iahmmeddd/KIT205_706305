#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* String;

// quicksort function
void quicksort(String* a, int first, int last) {
    if (first < last) {
        int i = first;
        int j = last - 1;
        String pivot = a[last]; // last element is pivot
        String temp;

        // move i and j
        while (i <= j) {
            while (i < last && strcmp(a[i], pivot) <= 0) {
                i++; // move i right
            }
            while (j >= first && strcmp(a[j], pivot) > 0) {
                j--; // move j left
            }
            if (i < j) {
                // swap
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        // put pivot in correct place
        temp = a[i];
        a[i] = a[last];
        a[last] = temp;

        // sort left part
        quicksort(a, first, j);

        // sort right part
        quicksort(a, i + 1, last);
    }
}

int main() {
    String* strings;
    char buffer[100];
    int n;

    // read how many strings
    scanf("%d", &n);

    // make space for strings
    strings = malloc(n * sizeof(String));

    // read each string
    for (int i = 0; i < n; i++) {
        scanf("%99s", buffer); // read word
        strings[i] = malloc(strlen(buffer) + 1); // make space
        strcpy(strings[i], buffer); // copy word
    }

    // sort the strings
    quicksort(strings, 0, n - 1);

    // print all strings
    printf("Strings entered:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", strings[i]);
    }

    // free memory
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);

    return 0;
}