#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* massima lunghezza di una parola */
#define WORDLEN 1024

/* Stampa una riga di intestazione di lunghezza `n` */
void header(int n) {
    int i;

    for (i = 1; i <= n; i++) {
        printf("%c", i % 10 ? '-' : '|');
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    FILE *filein = stdin;
    int Lmax;
    // int c;
    if (argc != 3) {
        fprintf(stderr, "Uso: %s Lmax filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    Lmax = atoi(argv[1]);

    if (strcmp(argv[2], "-") != 0) {
        filein = fopen(argv[2], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    header(Lmax);

    int index = 0;
    int *s = (int *)(calloc(Lmax, sizeof(int)));
    int start = 0, end;
    while ((s[index] = fgetc(filein)) != EOF) {
        if (isspace(s[index])) {
            end = index;
            int i;
            for (i = start; i < end; i++) {
                printf("%c", s[i]);
            }
            printf(" ");
            start = (index + 1);
        }
        index++;
        if (index >= Lmax) {
            printf("\n");
            end = index;
            index = 0;
            int b;
            for (b = start; b < end; b++) {
                s[index] = s[b];
                index++;
            }
            start = 0;
            end = 0;
        }
    }
    printf("\n");
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
