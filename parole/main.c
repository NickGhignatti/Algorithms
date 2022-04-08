#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "hashtable.h"

#define WORDLEN 100

int main( int argc, char *argv[] ) {
    FILE *filein = stdin;
    int c;
    int table_size = 50000;
    HashTable *table;

    if (argc > 1) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    table = ht_create(table_size);
    char string[WORDLEN];
    int i = 0;
    while ((c = fgetc(filein)) != EOF) {
        if (!isspace(c)){
            if(isalpha(c)){
                char a = tolower(c);
                string[i] = a;
                i++;
            }
            else{
                string[i] = '\0';
                if(i != 0) ht_insert(table, string, 0);
                i = 0;
            }
        }
        else{
            string[i] = '\0';
            if(i != 0) ht_insert(table, string, 0);
            i = 0;
        }
    }
    string[i] = '\0';
    if(i != 0) ht_insert(table, string, 0);
    i = 0;

    if (filein != stdin) fclose(filein);

    printf("Numero totale di parole : %u, delle quali %u distinte\n", count_total_word(table), ht_count(table));

    return EXIT_SUCCESS;
}
