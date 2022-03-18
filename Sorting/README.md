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
	for j <-- first to high
		if array[j] <= pivot  
			swap(array[j], array[i])
			i++
		swap(array[i+1], array[high])
	return i + 1

QuickSort(array, start, end)
	if start < end
		pi <-- partition(array, start end)
		QuickSort(array, start, pi - 1)
		QuickSort(array, pi + 1, end)
```

#### Merge sort:  
```
```

#### Heap sort:  
```
```

