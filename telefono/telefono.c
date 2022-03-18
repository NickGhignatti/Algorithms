#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 1000000


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n){
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (i = n - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int most_frequent(int *arr, int n){
    heapSort(arr, n);
    int res = arr[0], curr_count = 1, i;
    for (i = 1; i < n; i++){
        if (arr[i] == arr[i - 1])
            curr_count++;
        else {
            if (curr_count > 1) 
                return arr[i - 1];
            curr_count = 1;
        }
    }
    if (curr_count > 1)
        return arr[i - 1];
    return res;
}

int main( int argc, char *argv[] ) {
    FILE *fin;
    int num_tel;
    int i = 0;
    int *buffer = (int *)(calloc(MAXN, sizeof(int)));
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file_name\n", argv[0]);
        return EXIT_FAILURE;
    }

    fin = fopen(argv[1], "r");
    if (fin == NULL) {
        fprintf(stderr, "Can not open \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    while (1 == fscanf(fin, "%d", &num_tel)) {
        buffer[i] = num_tel;
        i++;
    }
    fclose(fin);

    printf("Most frequent value = %d\n",most_frequent(buffer, i));

    free(buffer);

    end = clock();
    cpu_time_used = ((double)(end - start));
    printf("Time = %f\n", cpu_time_used);
    printf("Time = %f\n", cpu_time_used / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
