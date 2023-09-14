#include "variadic_functions.h"
#include <stdarg.h>

/**
 * sum_them_all - sum of all its parameters
 * @n: The number of parameters
 *
 * Return: The sum of all its parameters
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list lists;
	unsigned int i, sum = 0;

	if (n == 0)
	{
		return (0);
	}
	va_start(lists, n);

	for (i = 0; i < n; i++)
		sum += va_arg(lists, int);
	va_end(lists);
	return (sum);
}
