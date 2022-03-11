#include <stdio.h>

void insertion_sort(int *arr, int length) {
	int i;
	for (i = 1; i < length; i++) {
		int value = arr[i];
		int j = (i - 1);
		while (j >= 0 && arr[i] > value) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = value;
	}
}