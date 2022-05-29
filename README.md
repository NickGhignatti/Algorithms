<details>
<summary><h3><b>Sorting algorithms pseudocodes:</b></h3></summary>

#### Insertion sort:
```js  
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
```js  
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
		pi <-- Partition(array, start end)
		QuickSort(array, start, pi - 1)
		QuickSort(array, pi + 1, end)
		
Complexity:
--> best case = O(n log(n))
--> worst case = O(n^2)
--> medium case = O(n log(n))
		
```

#### Merge sort:  
```js  
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
```js 
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
</details>

<details>
<summary><h3><b>Graph pseudocodes:</b></h3></summary>

#### BFS (breath-first search)
```js  
bfs(G)
	foreach v ∈ V[G]
		color[u] = white
		d[u] = INFINITY
		p[u] = NULL
	color[s] = WHITE
	d[s] = 0
	Q = EMPTY
	while Q
		u = head(Q)
		foreach v ∈ Adj(u)
			if color[v] == white
				color[v] = gray
				d[v] = d[u] + 1
				p[v] = u
				enqueue(Q, v)
		dequeue(Q, v)
		color[v] = black
		
Complexity = O(V + E)  

```
	
#### DFS (depth-first search)
```js  
DFS(G)
	foreach v ∈ V[G]
		color[v] = white
		p[v] = NULL
	time = 0
	foreach v ∈ V[G]
		if color[v] == white
			dfsVisit(v)

dfsVisit(v)
	color[v] = gray
	time++
	d[v] = time
	foreach u ∈ Adj(v)
		if color[u] == white
			p[u] = v
			dfsVisit(u)
	color[v] = black
	time++
	f[v] = time
		
Complexity = O(V + E)  

```
</details>
	
<details>
<summary><h3><b>Topologial sort pseudocodes:</b></h3></summary>

#### Topological sort
```js  
TopologicalSort(G)
	dfs(G)
	when the visit of a vertex is ended push it at the head of the list
	return list
		
Complexity = O(V + E)  
```
</details>
	
<details>
<summary><h3><b>MST algorithms pseudocodes:</b></h3></summary>

#### Kruskal
```js  
Kruskal(G)
	A = NULL
	foreach v ∈ V[G]
		Make-Set(v)
	Sort(E[G], +)
	foreach (u, v) ∈ E[G]
		if Find-Set(u) != Find-Set(v)
			A = A ∪ { (u, v) }
			union(u, v)
	return A
	
Complexity = O(E log E)
```

#### Prim
```js  
Prim(G, s)
	Q = V[G]
	foreach v ∈ V[G]
		key[u] = INFINITY
	key[s] = 0
	p[s] = NULL
	while Q != NULL
		u = ExtractMin(Q)
		foreach v ∈ Adj(u)
			if v ∈ Q && w(u, v) < key[v]
				p[v] = u
				key[v] = w(u, v)

Complexity = O(E log V) // O(E + V log V)
```

</details>
	
<details>
<summary><h3><b>Minimum path from single source algorithms pseudocodes:</b></h3></summary>

#### Dijkstra
```js
Dijkstra(G, w, s)
	foreach v ∈ V[G]
		d[v] = INFINITY
		p[v] = NULL
	d[s] = 0
	S = NULL
	Q = V[G]
	while Q != NULL
		u = ExtractMin(Q)
		S = S ∪ u
		for v ∈ Adj(u)
			if d[v] > d[u] + w(u, v)
				d[v] = d[u] + w(u, v)
				p[v] = u
	
Complexity = O(VV)
```
	
#### Bellman-Ford
```js
BellmanFord(G, w, s)
	foreach v ∈ V[G]
		d[v] = INFINITY
		p[v] = NULL
	d[s] = 0
	for i = 1 to |V[G] - 1|
		for (u, v) ∈ E[G]
			relax(u, v, w)
	for (u, v) ∈ E[G]
		if d[v] > d[u] + w(u, v)
			return False
	return True
	
Complexity = O(VE)
```
</details>
	
<details>
<summary><h3><b>Minimum path from all the nodes algorithms pseudocodes:</b></h3></summary>

#### Floyd-Warshall
```js
FloydWarshall(W)
	n = rows(W)
	D(0) = W
	for k = 1 to n
		for i = 1 to n
			for j = 1 to n
				d(i, j)[k] = min (d(i, j)[k - 1], d(i, k)[k - 1] + d(k, j)[k - 1])
	return D(n)
	
Complexity = O(VVV)
```
</details>

<details>
<summary><h3><b>Max flow algorithms pseudocodes:</b></h3></summary>

#### Ford-Fulkerson
```js
FordFulkerson(G, s, t)
	foreach (u, w) ∈ E[G]
		f[u, v] = 0
		f[v, u] = c[v, u] = 0
	while (p = path(s, t))
		c(p) = min { c(u, v) : (u, v) }
		foreach (u, v) in p
			f[u, v] = [u, v] + c(p)
			c[v, u] = c[v, u] + c(p)
	
Complexity = O(Ef*)
```

#### Edmonds - Karp
```js
EdmondsKarp(G, s, t)
1) set f(u, v) = 0
2) p = bfs(Gf)
3) increase the flow on p and update Gf
4) repeat 2-3 while a path exists
	
Complexity = O(nmm)
```
</details>
