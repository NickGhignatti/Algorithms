void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int array[], int low, int high) {
	int pivot = array[high];                               // select the right-most element as pivot
	int i = (low - 1);									   // pointer for greater element
	for (int j = low; j < high; j++) {					   // traverse each element of the array compare them with the pivot
		if (array[j] <= pivot) {                           // if element smaller than pivot is found
			i++;                                           // swap it with the greater element pointed by i
			swap(&array[i], &array[j]);					   // swap element
		}
	}
	swap(&array[i + 1], &array[high]);                     // swap the pivot element with the greater element at i
	return (i + 1);
}

void quickSort(int array[], int low, int high) {
	if (low < high) {
		int pi = partition(array, low, high);              // find the pivot element such that
		quickSort(array, low, pi - 1);
		quickSort(array, pi + 1, high);
	}
}