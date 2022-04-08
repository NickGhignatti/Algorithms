### Algorithms pseudocodes:  

#### Insertion sort:
```
InsertionSort(array)  
    for i <-- 2 to length(array)  
    	value <-- array[i]  
      	j <-- i - 1  
      	while j > 0 and array(j) > value  
        	array[j + 1] <-- array[j]  
		   	j--  
      	arr[j + 1] <-- value
```  
#### Quick sort:  
```
Partition(array, first, last)
	pivot <-- array[last]
	i <-- first - 1
	for j <-- first to last
		if array[j] <= pivot  
			swap(array[j], array[i])
			i++
		swap(array[i+1], array[last])
	return i + 1

QuickSort(array, start, end)
	if start < end
		pi <-- partition(array, start end)
		QuickSort(array, start, pi - 1)
		QuickSort(array, pi + 1, end)
```

#### Merge sort:  
```
Merge(array, start, middle, end, buffer)
	i <-- start
	j <-- middle + 1
	k <-- 0
	while i <= middle and j <= end
		if array[i] < array[j]
			buffer[k] = array[i]
			i++
		else
			buffer[k] = array[j]
			j++
		k++
	while i <= middle
		buffer[k] = array[i]
		k++
		i++
	while j <= end
		buffer[k] = array[j]
		k++
		j++
	for k <-- start to end
		array[k] <-- array[k - start] 


MergeSort(array, start, end, buffer)
	if start < end
		middle <-- (start + end) // 2
		MergeSort(array, start, middle, buffer)
		MergeSort(array, middle + 1, end, buffer)
		Merge(array, start, middle, end, buffer)
```

#### Heap sort:  
```
Heapify(array, len, index)
	largest <-- index
	leftChild <-- 2 * i + 1
	rightChild <-- 2 * i + 2
	if left < len and array[leftChild] > array[largest]
		largest = leftChild
	if right < len and array[rightChild] > array[largest]
		largest = rightChild
	if largest != i
		swap(arra[i], array[largest])
		heapify(array, largest)

HeapSort(array)
	* for max heap *
	for i <-- 0 to (len(array) // 2 - 1)
		Heapify(array, len(array), i)
	* add this to min heap *
	for i <-- len(array) - 1 to 0
		swap(array[0], array[i])
		Heapify(array, i, 0)
```

