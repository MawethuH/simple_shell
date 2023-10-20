#include "shell.h"

/**
 * _history - ...
 * @info: ...
 * Return: ...
 */

int _history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - ...
 * @info: ...
 * @str: ...
 * Return: ...
 */

int unset_alias(info_t *info, char *str)
{
	char *ptr, c;
	int r;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = c;
	return (r);
}

/**
 * set_alias - ...
 * @info: ...
 * @str: ...
 * Return: ...
 */

int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - ...
 * @node: ...
 * Return: ...
 */

int print_alias(list_t *node)
{
	char *ptr = NULL, *c = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (c = node->str; c <= ptr; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - ...
 * @info: ...
 *  Return: ...
 */

int _alias(info_t *info)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		ptr = _strchr(info->argv[i], '=');
		if (ptr)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
