/* Ghignatti Nicolò  0001028531  classe B  nicolo.ghignatti@studio.unibo.it*/
#include <stdio.h>
#include <stdlib.h>

/* enum to store the value of a cell in the map */
enum cellValue { NON_VISITED = -1, WALL, VISITED };

struct Move {
    int x;
    int y;
    int complexity;
    char *moves;
};

struct Queue {
    int head;
    int tail;
    unsigned int capacity;
    struct Move *data;
};

struct Field {
    int rows;
    int columns;
    enum cellValue **field;
};

/* Function to initialize an instance of the struct field */
static struct Field *initField(int rows, int columns){
    int index;
    struct Field *f = (struct Field *)(malloc(sizeof(struct Field)));
    f->rows = rows;
    f->columns = columns;
    f->field = (int **)(calloc(f->rows, sizeof(int *)));
    for (index = 0; index < f->rows; index++) {
        f->field[index] = (int *)(calloc(f->columns, sizeof(int)));
    }
    return f;
}

/* Function to initialize an instance of the struct Queue */
static struct Queue *initQueue(int head, int tail, unsigned int capacity){
    struct Queue *q = (struct Queue *)(malloc(sizeof(struct Queue)));
    q->head = head;
    q->tail = tail;
    q->capacity = capacity;
    q->data = (struct Move *)(calloc(capacity, sizeof(struct Move)));
    return q;
}

/* Function to initialize an instance of the struct Move */
static struct Move initNode(int x, int y, int complexity, char *moves, char newChar) {
    int index;
    struct Move l;
    l.complexity = complexity;
    l.x = x;
    l.y = y;
    l.moves = (char *)(calloc((complexity + 1), sizeof(char)));
    for(index = 0; index < complexity; index++){
        if(index == (complexity - 1))
            l.moves[index] = newChar;
        else
            l.moves[index] = moves[index];
    }
    l.moves[index] = '\0';
    return l;
}

/* Function to add an element at the head of the queue */
static void push(struct Queue *q, struct Move move){
    q->data[q->tail] = move;
    q->tail += 1;
}

/* Function to get the first element of the queue */
static struct Move *get(struct Queue *q){
    struct Move *data = &(q->data[q->head]);
    q->head += 1;
    return data;
}

static void freeField(struct Field *f){
    int index;
    for(index = 0; index < f->rows; index++ ){
        free(f->field[index]);
    }
    free(f->field);
    free(f);
}

static void freeNode(struct Move node){
    free(node.moves);
}

static void freeQueue(struct Queue *q){
    int index;
    for(index = 0; index < q->capacity; index++){
        freeNode(q->data[index]);
    }
    free(q->data);
    free(q);
}

/* Function to free al the memory allocated */
static void freeAll(struct Field *f, struct Queue *q){
    freeField(f);
    freeQueue(q);
}

/* Function that return to number of moves that the robot should do to get in (x, y) */
static int getComplexity(struct Queue *q, int x, int y){
    int index;
    for(index = 0; index < q->tail; index++){
        if(q->data[index].x == x && q->data[index].y == y)
            return q->data[index].complexity;
    }
    return -1;
}

/* Function that return the sequence of moves that the robot should do to get in (x, y) */
static char* getSequence(struct Queue *q, int x, int y){
    int index;
    for(index = 0; index < q->tail; index++){
        if(q->data[index].x == x && q->data[index].y == y)
            return q->data[index].moves;
    }
    return "";
}

/* Function that return 1 if the queue is empty otherwise 0 */
static int queueIsEmpty(struct Queue *q){
    if(q->head == q->tail)
        return 1;
    return 0;
}

/* Function to initialize the matrix from the file */
static void readMat(FILE *f, struct Field *mat) {
    int i, j;
    char c;
    i = 0, j = 0;
    c = getc(f);
    /* reading each character of the file */
    while (EOF != (c = getc(f))) {
        if (c == '\n') {
            i++;
            j = 0;
        /* if is * is a wall */
        } else if (c == '*') {
            mat->field[i][j] = WALL;
            j++;
        /* else is just not visited */
        } else {
            mat->field[i][j] = NON_VISITED;
            j++;
        }
    }
    /* the starting position is the just one visited */
    mat->field[1][1] = VISITED;
}

/* Function to read the file */
static struct Field *readFile(FILE *f) {
    int rows, columns;
    struct Field *mat;

    /* reading the first 2 values at the head of the file, that are the number of rows and columns the matrix has */
    if (2 != fscanf(f, "%d %d", &rows, &columns)) {
        fprintf(stderr, "ERROR during the read of the heading\n");
        abort();
    }

    /* allocating the memory for the struct */
    mat = initField(rows, columns);

    /* and then initializing it */
    readMat(f, mat);

    return mat;
}

/* Function that return 1 if the cell is free around, otherwise 0 */
static int canMove(struct Field *f, int x, int y) {
    int i, j;
    for(i = (x - 1); i <= (x + 1); i++){
        for(j = (y - 1); j <= (y + 1); j++){
            /* if I am at the edge of the map */
            if(i < 0 || j < 0)
                return 0;
            if(i >= f->rows || j >= f->columns)
                return 0;
            /* or a cell around is a wall */
            if(f->field[i][j] == WALL)
                return 0;
            /* I can't move */
        }
    }
    return 1;
}

/* Function to visit a node */
static void visit(struct Field *f, struct Queue *q, struct Move *node, int x, int y, char direction) {
    if (!canMove(f, x, y))
        return;
    /* visiting a node and then pushing the node in the queue */
    if(f->field[x][y] == NON_VISITED) {
        f->field[x][y] = VISITED;
        push(q, (initNode(x, y, (node->complexity + 1), node->moves, direction)));
    }
}

/* Function get the direction where the robot is going to move */
static char getDirection(int x, int y, int i, int j){
    if (i == (x - 1) && j == y)
        return 'N';
    if (i == (x + 1) && j == y)
        return 'S';
    if (i == x && j == (y - 1))
        return 'O';
    if (i == x && j == (y + 1))
        return 'E';
    return 'R';
}

/* breath-first search function */
static void bfs(struct Field *f, struct Queue *q) {
    int i, j;
    char direction;
    struct Move *node;
    push(q, initNode(1, 1, 0, "", 'B'));
    while(!queueIsEmpty(q)){
        node = get(q);
        for(i = (node->x - 1); i <= (node->x + 1); i++){
            for(j = (node->y - 1); j <= (node->y + 1); j++){
                /* if I'm not in the corners */
                if(i != node->x && j != node->y)
                    continue;
                /* and not even in the center */
                if (i == node->x && j == node->y)
                    continue;
                /* I am getting the direction where the robot is going to move */
                direction = getDirection(node->x, node->y, i, j);
                /* and then visiting the node */
                visit(f, q, node,  i, j, direction);
            }
        }
    }
    /* add */

}

int main(int argc, char *argv[]) {
    FILE *f;
    struct Queue *q;
    struct Field *fi;
    /*unsigned int capacity;*/

    /* check if the number arguments passed in is correct */
    if (argc != 2) {
        printf("Different numbers of args");
        return -1;
    }

    f = fopen(argv[1], "r");

    /* initializing the matrix (field) from the file and the queue*/
    fi = readFile(f);
    /*capacity = (fi->rows - 3) * ((fi->columns / 3) + 1) + (fi->columns - 3) * ((fi->rows / 3) + 1);*/
    q = initQueue(0, 0, (unsigned int)(((fi->rows )*(fi->columns)))); /* (fi->rows * fi->columns) */

    /* doing the bfs */
    bfs(fi, q);

    /* printing the information (the time that the robot spend to reach the target, if he can) */
    /* and the sequence of moves */

    printf("%d\n", getComplexity(q, (fi->rows - 2), (fi->columns - 2)));
    printf("%s\n", getSequence(q, (fi->rows - 2), (fi->columns - 2)));

    /* and then freeing all the memory allocated */
    freeAll(fi, q);

    fclose(f);

    return 0;
}