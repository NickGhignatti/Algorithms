#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum {VERDE, BIANCO, ROSSO} Colore;


void stampa( const Colore *a, int n ) {
    int i;
    printf("[");
    for( i=0; i<n; i++ ) {
        printf("%d ", a[i]);
    }
    printf("]\n");
}

void swap(Colore *a, Colore *b){
    Colore temp = *a;
    *a = *b;
    *b = temp;
}

void bandiera( Colore *a, int n ) {
    if(n == 1)
        return;
    int i, v = 0, r = (n - 1);
    for (i = 0; i < n; i++){
        if(a[i] == VERDE){
            swap(&a[i], &a[v]);
            v++;
        }
    }
    for (i = r; i >= v; i--){
        if (a[i] == ROSSO){
            swap(&a[i], &a[r]);
            r--;
        }
    }
}

#define ARRAY_LEN(x) (sizeof(x)/sizeof(x[0]))

int main( void )
{
    Colore p1[] = {BIANCO, VERDE, ROSSO, ROSSO, BIANCO, ROSSO, ROSSO, VERDE, VERDE, BIANCO, ROSSO, ROSSO, ROSSO, BIANCO};
    const int n1 = ARRAY_LEN(p1);
    Colore p2[] = {VERDE, VERDE, VERDE, VERDE};
    const int n2 = ARRAY_LEN(p2);
    Colore p3[] = {BIANCO, BIANCO, BIANCO, BIANCO};
    const int n3 = ARRAY_LEN(p3);
    Colore p4[] = {ROSSO};
    const int n4 = ARRAY_LEN(p4);
    Colore p5[] = {VERDE, ROSSO, BIANCO, ROSSO, BIANCO, BIANCO, BIANCO};
    const int n5 = ARRAY_LEN(p5);
    Colore p6[] = {ROSSO, ROSSO, ROSSO, VERDE};
    const int n6 = ARRAY_LEN(p6);

    bandiera(p1, n1);
    stampa(p1, n1);
    bandiera(p2, n2);
    stampa(p2, n2);
    bandiera(p3, n3);
    stampa(p3, n3);
    bandiera(p4, n4);
    stampa(p4, n4);
    bandiera(p5, n5);
    stampa(p5, n5);
    bandiera(p6, n6);
    stampa(p6, n6);
    return EXIT_SUCCESS;
}
