def get_index(word):
	num = 0
	for digit in word:
		num += ord(digit)
	num = (num % 5)
	return num

def chaining(word, array):
	index = get_index(word)
	array[index].append(word)

array = [None] * 5
for i in range(0, 5):
	array[i] = list()
print(array)

chaining("Qui", array)
chaining("Quo", array)
chaining("Qua", array)
chaining("Pippa", array)
chaining("Barbarossa", array)
print(array)
