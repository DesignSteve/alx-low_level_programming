#include "shell.h"

/**
 * retrieve_environment - returns the string array copy of the environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **retrieve_environment(info_t *info)
{
	if (!info->environ || info->env_updated)
	{
		info->environ = list_to_strings(info->env);
		info->env_updated = 0;
	}

	return (info->environ);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @variable: the string environment variable property
 * Return: 1 on delete, 0 otherwise
 */
int remove_environment_variable(info_t *info, char *variable)
{
	list_t *node = info->env;
	size_t index = 0;
	char *p;

	if (!node || !variable)
		return (0);

	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			info->env_updated = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		index++;
	}
	return (info->env_updated);
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *                            or modify an existing one
 * @info: Structure containing potential arguments.
 * @variable: the string environment variable property
 * @value: the string environment variable value
 * Return: Always 0
 */
int set_environment_variable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *p;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);

	node = info->env;
	while (node)
	{
		p = starts_with(node->str, variable);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_updated = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_updated = 1;
	return (0);
}

