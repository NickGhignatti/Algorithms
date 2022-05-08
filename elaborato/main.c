#include <stdio.h>
#include <stdlib.h>

#define WALL -1
#define NOT_DISCOVERED -2
#define START 0

int **mask_matrix;
int rows, columns;

static void printMat() {
    int index, iterator;
    for (index = 0; index < rows; index++) {
        for (iterator = 0; iterator < columns; iterator++)
            printf("[%d] ", mask_matrix[index][iterator]);
        printf("\n");
    }
}

static void readMat(FILE *f) {
    int i, j;
    char c;
    i = 0, j = 0;
    while (EOF != (c = getc(f))) {
        if (c == '\n' && (i != 0 || j != 0)) {
            i++;
            j = 0;
        } else if (c == '*') {
            mask_matrix[i][j] = WALL;
            j++;
        } else {
            mask_matrix[i][j] = NOT_DISCOVERED;
            j++;
        }
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            mask_matrix[i][j] = 0;
}

static void readFile(FILE *f) {
    int index;
    rows = 0;
    columns = 0;

    if (2 != fscanf(f, "%d %d", &rows, &columns)) {
        fprintf(stderr, "ERROR during the read of the heading\n");
        abort();
    }

    /* memory allocation */

    mask_matrix = (int **)(calloc(rows, sizeof(int *)));
    for (index = 0; index < rows; index++)
        mask_matrix[index] = (int *)(calloc(columns, sizeof(int)));

    /* assignements */
    readMat(f);

    printMat();
}

int main(int argc, char *argv[]) {
    FILE *f = fopen("test1.in", "r");

    readFile(f);

    return 0;
}