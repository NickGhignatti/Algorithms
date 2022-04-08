#include <stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int arr[], int n, int i)
{
	int largest = i;						  // default largest index is the one in input
	int left = 2 * i + 1;					  // getting the left child
	int right = 2 * i + 2;					  // getting the right child
	if (left < n && arr[left] > arr[largest]) // and then comparing who is the larger
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;
	if (largest != i)
	{								  // if it found a larger number it will switch
		swap(&arr[i], &arr[largest]); // and then do it again with the child's index
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n)
{
	int i;
	// for (i = 0; i <= (n/2 - 1); i++) // heapifying all the nodes from the last to the beginner
	// 	heapify(arr, n, i);
	for (i = (n / 2 - 1); i >= 0; i--) // heapifying all the nodes from the last to the beginner
		heapify(arr, n, i);
	// for (i = n - 1; i >= 0; i--)
	// {
	//  	swap(&arr[0], &arr[i]); // and then reordering from the smallest to the largest
	//  	heapify(arr, i, 0);
	// }
}


int main(){
	int arr[] = {1, 9, 8, 5, 4};
	int n = 5;
	heapSort(arr, n);
	for (int i = 0; i < n; i++){
		printf("%d ", arr[i]);
	}

	return 0;
}