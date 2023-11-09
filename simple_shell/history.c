#include "shell.h"

/**
 * generate_history_file_path - generates the history file path
 * @info: parameter struct
 *
 * Return: allocated string containing the history file path
 */
char *generate_history_file_path(info_t *info)
{
	char *home_dir = _getenv(info, "HOME=");
	if (!home_dir)
		return NULL;

	char *file_path = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HIST_FILE) + 2));
	if (!file_path)
		return NULL;

	file_path[0] = '\0';
	_strcpy(file_path, home_dir);
	_strcat(file_path, "/");
	_strcat(file_path, HIST_FILE);

	return file_path;
}

/**
 * save_history_to_file - writes history to a file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int save_history_to_file(info_t *info)
{
	ssize_t fd;
	char *filename = generate_history_file_path(info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return 1;
}

/**
 * load_history_from_file - reads history from a file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int load_history_from_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = generate_history_file_path(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return 0;

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return 0;

	buf = malloc(sizeof(char) * (fsize + 1));

	if (!buf)
		return 0;

	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';

	if (rdlen <= 0)
		return free(buf), 0;

	close(fd);

	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}

	if (last != i)
		build_history_list(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return info->histcount;
}

/**
 * append_to_history_list - adds an entry to the history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int append_to_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return 0;
}

/**
 * renumber_history_list - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history_list(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->histcount = i;
}

