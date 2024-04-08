#ifndef SEARCH_ALGOS_H
#define SEARCH_ALGOS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * struct listint_s - singly linked list
 *
 * @n: Integer
 * @index: Index of the node in the list
 * @next: Pointer to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct listint_s
{
	int n;
	size_t index;
	struct listint_s *next;
} listint_t;

/**
 * struct skiplist_s - Singly linked list with an express lane
 *
 * @n: Integer
 * @index: Index of the node in the list
 * @next: Pointer to the next node
 * @express: Pointer to the next node in the express lane
 *
 * Description: singly linked list node structure with an express lane
 */
typedef struct skiplist_s
{
	int n;
	size_t index;
	struct skiplist_s *next;
	struct skiplist_s *express;
} skiplist_t;

/* Prototype for 0-linear.c */
int linear_search(int *array, size_t size, int value);

/* Prototype for 1-binary.c */
int binary_search(int *array, size_t size, int value);

/* Prototype for 100-jump.c */
int jump_search(int *array, size_t size, int value);

/* Prototype for 102-interpolation.c */
int interpolation_search(int *array, size_t size, int value);

/* Prototype for 103-exponential.c */
int exponential_search(int *array, size_t size, int value);

/* Prototype for 104-advanced_binary.c */
int advanced_binary(int *array, size_t size, int value);

/* Prototype for 105-jump_list.c */
listint_t *jump_list(listint_t *list, size_t size, int value);

/* Prototype for 106-linear_skip.c */
skiplist_t *linear_skip(skiplist_t *list, int value);

#endif /* SEARCH_ALGOS_H */
