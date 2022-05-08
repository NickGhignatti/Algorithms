#include <stdio.h>
#include <stdlib.h>

#define WALL -1
#define NOT_DISCOVERED -2
#define START 0
/*
enum direction { UP = 85,
                 DOWN = 68,
                 LEFT = 76,
                 RIGHT = 82 };
*/
int **mask_matrix;
char **dir_matrix;
int rows, columns;

/*
static void printMat() {
    int index, iterator;
    for (index = 0; index < rows; index++) {
        for (iterator = 0; iterator < columns; iterator++) {
            if (mask_matrix[index][iterator] < 0)
                printf("[%d] ", mask_matrix[index][iterator]);
            if (mask_matrix[index][iterator] < 10 && mask_matrix[index][iterator] >= 0)
                printf("[0%d] ", mask_matrix[index][iterator]);
            if (mask_matrix[index][iterator] >= 10)
                printf("[%d] ", mask_matrix[index][iterator]);
        }
        printf("\n");
    }
    printf("\n");
}
*/

static void readMat(FILE *f) {
    int i, j;
    char c;
    i = 0, j = 0;
    c = getc(f);
    while (EOF != (c = getc(f))) {
        if (c == '\n') {
            i++;
            j = 0;
        } else if (c == '*') {
            mask_matrix[i][j] = WALL;
            dir_matrix[i][j] = 'W';
            j++;
        } else {
            mask_matrix[i][j] = NOT_DISCOVERED;
            j++;
        }
    }
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            mask_matrix[i][j] = 0;
            if (i == 0)
                dir_matrix[i][j] = 'B';
            else
                dir_matrix[i][j] = 'S';
        }
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
    dir_matrix = (char **)(calloc(rows, sizeof(char *)));
    for (index = 0; index < rows; index++) {
        mask_matrix[index] = (int *)(calloc(columns, sizeof(int)));
        dir_matrix[index] = (char *)(calloc(columns, sizeof(char)));
    }

    /* assignements */
    readMat(f);
}

static void findDistance() {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            /* UP */
            if ((i - 1) >= 0 && mask_matrix[i - 1][j] != WALL && !(mask_matrix[i][j] == WALL || mask_matrix[i][j] == NOT_DISCOVERED)) {
                if (mask_matrix[i - 1][j] > (mask_matrix[i][j] + 1) || mask_matrix[i - 1][j] == NOT_DISCOVERED) {
                    mask_matrix[i - 1][j] = (mask_matrix[i][j] + 1);
                    dir_matrix[i - 1][j] = 'N';
                }
            }
            /* LEFT */
            if ((j - 1) >= 0 && mask_matrix[i][j - 1] != WALL && !(mask_matrix[i][j] == WALL || mask_matrix[i][j] == NOT_DISCOVERED)) {
                if (mask_matrix[i][j - 1] > (mask_matrix[i][j] + 1) || mask_matrix[i][j - 1] == NOT_DISCOVERED) {
                    mask_matrix[i][j - 1] = (mask_matrix[i][j] + 1);
                    dir_matrix[i][j - 1] = 'W';
                }
            }
            /* RIGHT */
            if ((j + 1) < columns && mask_matrix[i][j + 1] != WALL && !(mask_matrix[i][j] == WALL || mask_matrix[i][j] == NOT_DISCOVERED)) {
                if (mask_matrix[i][j + 1] > (mask_matrix[i][j] + 1) || mask_matrix[i][j + 1] == NOT_DISCOVERED) {
                    mask_matrix[i][j + 1] = (mask_matrix[i][j] + 1);
                    dir_matrix[i][j + 1] = 'E';
                }
            }
            /* DOWN */
            if ((i + 1) < rows && mask_matrix[i + 1][j] != WALL && !(mask_matrix[i][j] == WALL || mask_matrix[i][j] == NOT_DISCOVERED)) {
                if (mask_matrix[i + 1][j] > (mask_matrix[i][j] + 1) || mask_matrix[i + 1][j] == NOT_DISCOVERED) {
                    mask_matrix[i + 1][j] = (mask_matrix[i][j] + 1);
                    dir_matrix[i + 1][j] = 'S';
                }
            }
        }
    }
}

static void printRoute() {
    int i, j;
    int len;
    char *arr;
    len = mask_matrix[rows - 1][columns - 1] - 1;
    arr = (char *)(calloc(len, sizeof(char)));
    i = (rows - 3);
    j = (columns - 1);

    while (i != 0 || j != 0) {
        arr[len] = dir_matrix[i + 2][j];
        if (dir_matrix[i + 2][j] == 'N')
            i++;
        else if (dir_matrix[i + 2][j] == 'S')
            i--;
        else if (dir_matrix[i + 2][j] == 'E')
            j--;
        else
            j++;
        len--;
    }
    while (len >= 0) {
        if (i == 0 && j != 0)
            arr[len] = 'E';
        else
            arr[len] = 'S';
        len--;
    }

    for (len = 0; len < mask_matrix[rows - 1][columns - 1]; len++)
        printf("%c", arr[len]);
}

int main(int argc, char *argv[]) {
    FILE *f = fopen("test1.in", "r");

    readFile(f);

    findDistance();

    if (mask_matrix[rows - 1][columns - 1] == (mask_matrix[rows - 3][columns - 3] + 4)) {
        printf("%d\n", mask_matrix[rows - 1][columns - 1]);
        printRoute();
    } else
        printf("%d\n", -1);

    return 0;
}