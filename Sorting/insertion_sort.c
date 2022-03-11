// Insertion sort function
void insertion_sort(int *arr, int length) {
	int i;
	// get every item of the array except for the first one
	for (i = 1; i < length; i++) {
		// and assign it as the value to sort in the array, flowing them another 
		// time (from the beginning this time) to see if there is a lower value
		int value = arr[i];
		int j = (i - 1);
		// looking for an higher value
		while (j >= 0 && arr[j] > value) {
			// if it has found it, gonna switch and moving to the next index
			arr[j + 1] = arr[j];
			j--;
		}
		// then assigning the lower value to the very first item
		arr[j + 1] = value;
	}
}
