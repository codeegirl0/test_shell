#include "lists.h"

/**
 * sum_dlistint - return sum
 * @head: head
 * Return: sum data
 */
int sum_dlistint(dlistint_t *head)
{
	int sum;
	sum = 0;

	if (head != NULL)
	{
		while (head->prev != NULL)
			head = head->prev;

		while (head != NULL)
		{
			sum += head->n;
			head = head->next;
		}
	}

	return (sum);
}