void insertion_sort(int *arr, int length) {
	int i;
	for (i = 1; i < length; i++) {                     // get every item of the array except for the first one 
		int value = arr[i];                            // and assign it as the value to sort in the array, flowing them another
		int j = (i - 1);                               // time (from the beginning this time)
		while (j >= 0 && arr[j] > value) {             // looking for an higher value
			arr[j + 1] = arr[j];                       // if it has found it, gonna switch and moving to the next index
			j--;
		}
		arr[j + 1] = value;                            // then assigning the lower value to the very first item
	}
}
