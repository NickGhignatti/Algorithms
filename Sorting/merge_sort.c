void merge(int *arr, int start, int middle, int end, int *buffer) {
    int i = start, j = (middle + 1), k = 0;
    while (i <= middle && j <= end) {                           // looping until the 2 index will switch,
        if (arr[i] <= arr[j]){                                  // every time gonna check who has the lower number 
            buffer[k] = arr[i];                                 // between the 2 part (or sub-array) and going to the
            i++;                                                // next value of the onw with it,
        }
        else{
            buffer[k] = arr[j];
            j++;
        }
        k++;                                                    // then increasing the position of the array storing the 
    }                                                           // ordered values.
    while (i <= middle){                                        // The extra value of one of the 2 parts (or sub-arrays)
        buffer[k] = arr[i];                                     // is gonna get inserted at the very least
        i++;
        k++;
    }
    while (j <= r){
        buffer[k] = arr[j];
        j++;
        k++;
    }
    for (k = start; k <= end; k++){                             // and then the array containing the ordered values is copied
        arr[k] = buffer[k - start];                             // in the array
    }
}

void merge_sort(int *arr, int start, int end, int *buffer) {
    if (start < end){                                           // if the start index is less than the end
        int midlle = (start + end) / 2;                         // calculating the half
        merge_sort(arr, start, middle, buffer);                 // dividing, ordering and merging the left part
        merge_sort(arr, middle + 1, end, buffer);               // dividing, ordering and merging the right part
        merge(arr, start, middle, end, buffer);                 // mergin the 2 parts
    }
}
