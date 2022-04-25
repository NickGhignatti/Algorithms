#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Non è una buona pratica di programmazione, ma usiamo ugualmente
   variabili globali per evitare di passare parametri alle funzioni.
   Questo può essere accettabile vista la relativa semplicità di
   questo programma. */

int *p;     /* p[i] è il peso dell'oggetto i-esimo */
double *v;  /* v[i] è il valore dell'oggetto i-esimo */
int n;      /* numero di oggetti */
int C;      /* capienza dello zaino */
double **V; /* V[i][j] è il valore massimo ottenibile inserendo
               un opportuno sottoinsieme degli oggetti {0, ... i}
               in un contenitore di capienza massima C. */
int **use;  /* use[i][j] = 1 se e solo se l'oggetto i fa parte
               della soluzione ottima del sottoproblema P(i,j) la
               cui soluzione ottima è V[i][j]. */
FILE *filein;

/* Legge l'input dal file `filein` */
void init(void) {
    int i;
    fscanf(filein, "%d %d", &C, &n);
    p = (int *)malloc(n * sizeof(*p));
    assert(p != NULL);
    v = (double *)malloc(n * sizeof(*v));
    assert(v != NULL);
    for (i = 0; i < n; i++) {
        fscanf(filein, "%d %lf", &p[i], &v[i]);
    }
}

/* Determina la soluzione ottima del problema dello zaino.
   Restituisce il valore massimo degli oggetti selezionati. La
   funzione richiede che i parametri `p[]`, `v[]`, `n` e `C` siano già
   stati inizializzati. Questa funzione alloca gli array (matrici)
   `V[][]` e `use[][]`. */
double solve(void) {
    V = (double **)(calloc(n, sizeof(double *)));
    use = (int **)(calloc(n, sizeof(int *)));
    int k;
    for (k = 0; k < n; k++) {
        V[k] = (double *)(calloc(C + 1, sizeof(double)));
        use[k] = (int *)(calloc(C + 1, sizeof(int)));
    }
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j <= C; j++) {
            // case first line
            if (i == 0) {
                // check if fits in
                if (p[i] <= j) {
                    V[i][j] = v[i];
                    use[i][j] = 1;
                } else {
                    V[i][j] = 0;
                    use[i][j] = 0;
                }
            } else {
                double before = V[i - 1][j];
                double added = 0;
                if (j >= p[i])
                    added = V[i - 1][j - p[i]] + v[i];
                if (before > added) {
                    V[i][j] = before;
                    use[i][j] = 0;
                } else {
                    V[i][j] = added;
                    use[i][j] = 1;
                }
            }
        }
    }
    return 0.0;
}

/* Stampa la soluzione del problema dello zaino, elencando gli oggetti
   selezionati e il loro valore complessivo. Questa funzione fa uso
   della matrice `use[][]` che deve essere stata allocata e riempita
   dalla funzione `solve()`. */
void print(void) {
    int weight = 0, i = (n - 1), j = C;
    printf("Ogg n. peso valore\n");
    printf("------ ---- ------\n");
    while (i >= 0 && j >= 0) {
        if (use[i][j]) {
            printf("%d       %d   %.2lf\n", i, p[i], v[i]);
            j -= p[i];
            weight += p[i];
            i -= 1;
        } else {
            i -= 1;
        }
    }
    printf("\n");
    printf("Peso totale   : %d\n", weight);
    printf("Valore        : %.2lf\n", V[n - 1][C]);
}

/* Dealloca tutta la memoria allocata dinamicamente. */
void destroy(void) {
    free(p);
    free(v);
    /* [TODO]: Liberare ogni altro blocco di memoria allocato con malloc() */
}

int main(int argc, char *argv[]) {
    filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Invocare il programma con: %s input_file\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    init();
    /* il cast a void seguente serve a evitare possibili warning da
       parte di compilatori particolarmente pignoli che si accorgono
       che non usiamo il valore di ritorno di `solve()` */
    (void)solve();
    print();
    destroy();
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
