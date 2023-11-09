#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length)
{
    ssize_t read_bytes = 0;
    size_t buffer_length = 0;

    if (!*length) /* if nothing left in the buffer, fill it */
    {
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, sigintHandler);

#if USE_GETLINE
        read_bytes = getline(buffer, &buffer_length, stdin);
#else
        read_bytes = custom_getline(info, buffer, &buffer_length);
#endif

        if (read_bytes > 0)
        {
            if ((*buffer)[read_bytes - 1] == '\n')
            {
                (*buffer)[read_bytes - 1] = '\0'; /* remove trailing newline */
                read_bytes--;
            }

            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);

            /* if (_strchr(*buffer, ';')) is this a command chain? */
            {
                *length = read_bytes;
                info->cmd_buffer = buffer;
            }
        }
    }

    return read_bytes;
}

/**
 * get_user_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_user_input(info_t *info)
{
    static char *buffer; /* the ';' command chain buffer */
    static size_t buffer_index, buffer_length;
    ssize_t read_bytes = 0;
    char **buffer_ptr = &(info->arguments), *current_position;

    _putchar(BUF_FLUSH);
    read_bytes = buffer_input(info, &buffer, &buffer_length);

    if (read_bytes == -1) /* EOF */
        return -1;

    if (buffer_length) /* we have commands left in the chain buffer */
    {
        buffer_index = buffer_index;
        current_position = buffer + buffer_index; /* get pointer for return */

        check_command_chain(info, buffer, &buffer_index, buffer_index, buffer_length);

        while (buffer_index < buffer_length) /* iterate to semicolon or end */
        {
            if (is_command_chain(info, buffer, &buffer_index))
                break;
            buffer_index++;
        }

        buffer_index = buffer_index + 1; /* increment past nulled ';'' */

        if (buffer_index >= buffer_length) /* reached end of buffer? */
        {
            buffer_index = buffer_length = 0; /* reset position and length */
            info->cmd_buffer_type = CMD_NORMAL;
        }

        *buffer_ptr = current_position; /* pass back pointer to current command position */
        return _strlen(current_position); /* return length of current command */
    }

    *buffer_ptr = buffer; /* else not a chain, pass back buffer from custom_getline() */
    return read_bytes; /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @index: size
 *
 * Return: bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *index)
{
    ssize_t read_bytes = 0;

    if (*index)
        return 0;

    read_bytes = read(info->readfd, buffer, READ_BUF_SIZE);

    if (read_bytes >= 0)
        *index = read_bytes;

    return read_bytes;
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @pointer: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bytes read
 */
int custom_getline(info_t *info, char **pointer, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t buffer_index, buffer_length;
    size_t characters_to_copy;
    ssize_t read_bytes = 0, total_characters = 0;
    char *current_position = NULL, *new_position = NULL, *cursor;

    current_position = *pointer;

    if (current_position && length)
        total_characters = *length;

    if (buffer_index == buffer_length)
    {
        buffer_index = buffer_length = 0;
    }

    read_bytes = read_buffer(info, buffer, &buffer_length);

    if (read_bytes == -1 || (read_bytes == 0 && buffer_length == 0))
        return -1;

    cursor = _strchr(buffer + buffer_index, '\n');
    characters_to_copy = cursor ? 1 + (unsigned int)(cursor - buffer) : buffer_length;
    new_position = _realloc(current_position, total_characters, total_characters ? total_characters + characters_to_copy : characters_to_copy + 1);

    if (!new_position) /* MALLOC FAILURE! */
    {
        return (current_position ? free(current_position), -1 : -1);
    }

    if (total_characters)
    {
        _strncat(new_position, buffer + buffer_index, characters_to_copy - buffer_index);
    }
    else
    {
        _strncpy(new_position, buffer + buffer_index, characters_to_copy - buffer_index + 1);
    }

    total_characters += characters_to_copy - buffer_index;
    buffer_index = characters_to_copy;
    current_position = new_position;

    if (length)
    {
        *length = total_characters;
    }

    *pointer = current_position;
    return total_characters;
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

