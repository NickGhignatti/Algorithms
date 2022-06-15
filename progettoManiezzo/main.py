__author__ = "Ghignatti Nicolò"
__copyright__ = "Copyright 2022, Alma Mater Studiorum, University of Bologna"

# imports
import csv


# write_data
# filename = name of the file to write
# graph = graph to write
def write_data(filename, graph):
	with open(filename + '.csv', 'w', encoding='UTF8', newline='') as f:
		writer = csv.writer(f)

		# write the data
		writer.writerows(graph)


# read_data
# filename = name of the file to read
# graph = graph to read
def read_data(filename, graph):
	num_lines = 0
	with open(filename + '.csv', 'r') as f:
		reader = csv.reader(f)

		# read data and count lines
		for row in reader:
			graph.append(row)
			num_lines += 1
	return num_lines


# bfs
# matrix = matrix of the graph
# capacity = matrix of the residual capacity
# s = source
# t = sink
def bfs(matrix, capacity, s, t):
	queue = [s]
	paths = {s: []}

	if s == t:
		return paths[s]
	while queue:
		u = queue.pop(0)
		# calculating every node where the node from the queue can go and then calculating the path that
		# I should use from the source
		for v in range(len(matrix)):
			if (int(matrix[u][v]) - capacity[u][v] > 0) and v not in paths:
				# add the node to the paths
				paths[v] = paths[u] + [(u, v)]
				if v == t:
					return paths[v]
				queue.append(v)
	return None


# edmonds_karp
# matrix = matrix of the graph
# s = source
# t = sink
def edmonds_karp(matrix, s, t):
	n = len(matrix)
	# residual capacity array
	capacity = [[0] * n for i in range(n)]

	while (path := bfs(matrix, capacity, s, t)) is not None:
		# max flow passing through
		flow = min(int(matrix[u][v]) - capacity[u][v] for u, v in path)
		# updating the flow
		for u, v in path:
			capacity[u][v] += flow
			capacity[v][u] -= flow
	# and then return the sum of all the flow passing through
	return sum(capacity[s][i] for i in range(n))


if __name__ == '__main__':
	data = []
	end = read_data('data', data) - 1

	source = 0
	sink = end
	max_flow = edmonds_karp(data, source, sink)
	print(max_flow)
