#include <stdio.h>
#include <stdlib.h>
#include "libpsgraph.h"

/* Disegna la curva di Koch di ordine n e lunghezza x */
void koch(double x, int n) {
  	if(n == 0){
    	draw(x);
    	return;
  	}
	x = x / 3;
	koch(x, n - 1);
	turn(300);
	koch(x, n - 1);
	turn(120);
	koch(x, n - 1);
	turn(300);
	koch(x, n - 1);
}

int main( void ) {
	int a, b;
	printf("Input 2 numbers :");
	scanf("%d %d", &a, &b);
	start("curva.ps");
	koch(a, b);
	turn(120);
	koch(a, b);
	turn(120);
	koch(a, b);
	end();
	return EXIT_SUCCESS;
}
