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

Complexity:
--> best case = O(n)
--> worst case = O(n^2)
--> medium case = O(n^2)

```  
#### Quick sort:  
```
Partition(array, first, last)
	pivot <-- array[last]
	i <-- first - 1
	for j <-- first to last
		if array[j] <= pivot  
			i++
			swap(array[j], array[i])
	swap(array[i+1], array[last])
	return i + 1

QuickSort(array, start, end)
	if start < end
		pi <-- partition(array, start end)
		QuickSort(array, start, pi - 1)
		QuickSort(array, pi + 1, end)
		
Complexity:
--> best case = O(n log(n))
--> worst case = O(n^2)
--> medium case = O(n log(n))
		
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
		
Complexity:
--> best case = O(n log(n))
--> worst case = O(n log(n))
--> medium case = O(n log(n))
		
```

#### Heap sort:  
```
Heapify(array, len, index)
	largest <-- index
	leftChild <-- 2 * index + 1
	rightChild <-- 2 * index + 2
	if left < len and array[leftChild] > array[largest]
		largest = leftChild
	if right < len and array[rightChild] > array[largest]
		largest = rightChild
	if largest != index
		swap(array[index], array[largest])
		heapify(array, len, largest)

HeapSort(array)
	* for max heap *
	for i <-- 0 to (len(array) // 2 - 1)
		Heapify(array, len(array), i)
	* add this to min heap *
	for i <-- len(array) - 1 to 0
		swap(array[0], array[i])
		Heapify(array, i, 0)
		
Complexity:
--> best case = O(n log(n))
--> worst case = O(n log(n))
--> medium case = O(n log(n))
		
```

###  Graph pseudocodes:  

#### BFS (breath-first search)
```
BFS(graph, queue, index)
	queue.add(index)
	element = queue.pop()
	for edge in element
		Bfs(graph, queue, next)
		
Complexity = O(V + E)  

```
