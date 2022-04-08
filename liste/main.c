#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Nota: si assume che ListInfo sia il tipo "int" */
int main( int argc, char *argv[] )
{
    char op;
    ListInfo k;
    List *L;
    ListNode *n;
    FILE *filein = stdin;

    if (argc > 1) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    L = list_create();

    while (1 == fscanf(filein, " %c", &op)) {
        switch (op) {
        case '+': /* insert */
            fscanf(filein, "%d", &k);
            printf("INSERT %d\n", k);
            list_add_first(L, k);
            break;
        case '-': /* delete */
            fscanf(filein, "%d", &k);
            printf("DELETE %d ", k);
            n = list_search(L, k);
            if (n != list_end(L)) {
                list_remove(L, n);
                printf("OK\n");
            } else {
                printf("NOT FOUND\n");
            }
            break;
        case '?': /* search */
            fscanf(filein, "%d", &k);
            printf("SEARCH %d ", k);
            n = list_search(L, k);
            if (n != list_end(L)) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
            break;
        case 'l': /* length */
            printf("LENGTH %d\n", list_length(L));
            break;
        case 'p': /* print */
            list_print(L);
            break;
        case 'r': /* remove all */
            printf("CLEAR\n");
            list_clear(L);
            break;
        default:
            fprintf(stderr, "Unknown command %c\n", op);
        }
    }

    list_destroy(L);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
