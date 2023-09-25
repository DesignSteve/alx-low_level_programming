#include "lists.h"
#include <stdio.h>

/**
 * print_listint - prints all the elements of a listint_t list.
 *
 * @h: head of linklist node
 *
 * Return: the number of nodes
 *
 */
int main()
{
    listint_t *head = NULL; // Initialize an empty linked list

    // Add nodes to the linked list (not shown here)

    size_t node_count = print_listint(head);

    printf("Number of nodes: %zu\n", node_count);

    return 0;
}

