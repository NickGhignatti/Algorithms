#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define MAX_KEY_SIZE 100

int main( int argc, char *argv[] ) {
    int table_size = 10;
    char key[MAX_KEY_SIZE];
    char op;
    int val;
    HashNode *item;
    HashTable *table;
    FILE *filein = stdin;

    if (argc > 1) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    if (1 != fscanf(filein, "%d", &table_size)) {
        fprintf(stderr, "Missing size\n");
        return EXIT_FAILURE;
    }
    printf("INIT %d\n", table_size);
    table = ht_create(table_size);

    while (1 == fscanf(filein, " %c", &op)) {
        switch (op){
        case '+': /* insert */
            fscanf(filein, "%s %d", key, &val);
            printf("INSERT %s %d\n", key, val);
            ht_insert(table, key, val);
            break;
        case '-': /* delete */
            fscanf(filein, "%s", key);
            printf("DELETE %s ", key);
            if (0 == ht_delete(table, key)) {
                printf("NOT FOUND\n");
            } else {
                printf("OK\n");
            }
            break;
        case '?': /* search */
            fscanf(filein, "%s", key);
            printf("SEARCH %s ", key);
            item = ht_search(table, key);
            if (item == NULL) {
                printf("NOT FOUND\n");
            } else {
                printf("%d\n", item->value);
            }
            break;
        default:
            fprintf(stderr, "Unknown command %c\n", op);
        }
    }

    ht_destroy(table);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
