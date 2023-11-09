#include "shell.h"

/**
 * get_list_length - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t get_list_length(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}
	return count;
}

/**
 * list_to_array - returns an array of strings from the list
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_array(list_t *head)
{
	list_t *node = head;
	size_t length = get_list_length(head), i;
	char **str_array;
	char *str;

	if (!head || !length)
		return NULL;

	str_array = malloc(sizeof(char *) * (length + 1));
	if (!str_array)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return NULL;
		}

		_strcpy(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return str_array;
}

/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t print_list(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		count++;
	}
	return count;
}

/**
 * find_node_starts_with - returns the node whose string starts with a prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return node;
		node = node->next;
	}
	return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}
	return -1;
}

