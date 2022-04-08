#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

unsigned long hash_function(const HashTable *table, unsigned long k)
{
	assert(table != NULL);
	return k % table->size;
}

unsigned long encode(const char *key)
{
	int i;
	unsigned long s;

	assert(key != NULL);

	s = 0;
	for (i = 0; key[i]; i++)
	{
		s += key[i];
	}
	return s;
}

static int keys_equal(const char *k1, const char *k2)
{
	assert(k1 != NULL);
	assert(k2 != NULL);

	return (0 == strcmp(k1, k2));
}

HashTable *ht_create(const int size)
{
	HashTable *h = (HashTable *)malloc(sizeof(*h));
	int i;

	assert(h != NULL);
	h->size = size;
	h->values_count = 0;
	h->items = (HashNode **)malloc(h->size * sizeof(*(h->items)));
	assert(h->items != NULL);
	for (i = 0; i < h->size; i++)
	{
		h->items[i] = NULL;
	}
	return h;
}

static HashNode *hashtable_new_node(const char *key, int value, HashNode *next)
{
	HashNode *item = (HashNode *)malloc(sizeof(HashNode));
	const int keylen = strlen(key);

	assert(item != NULL);
	item->key = (char *)malloc(keylen + 1);
	assert(item->key != NULL);
	strcpy(item->key, key);
	item->next = next;
	item->value = value;
	return item;
}

int ht_insert(HashTable *h, const char *key, int value)
{
	unsigned long sum = encode(key);
	unsigned long index = hash_function(h, sum);

	// printf("%s\n", key);

	HashNode *node = ht_search(h, key);
	if (node != NULL)
	{
		node->value++;
		return 0;
	}

	HashNode *new_node = hashtable_new_node(key, value, h->items[index]);
	h->items[index] = new_node;
	h->values_count++;

	return 1;
}

HashNode *ht_search(HashTable *h, const char *key) {
	unsigned long sum = encode(key);
	unsigned long index = hash_function(h, sum);
	HashNode *temp = h->items[index];

	while (temp != NULL && !keys_equal(temp->key, key)) {
		temp = temp->next;
	}

	return temp;
}

int ht_count(const HashTable *h)
{
	assert(h != NULL);
	return (h->values_count);
}

static unsigned int count_list(HashTable *h, int index){
	HashNode *temp = h->items[index];
	int total = 0;
	while(temp != NULL){
		total += temp->value;
		temp = temp->next;
	}
	return total;
}

unsigned int count_total_word(HashTable *h){
	int total = 0;
	for (int i = 0; i < h->size; i++){
		total += count_list(h, i);
	}
	return total + ht_count(h);
}
