#include "main.h"

/**
 * create_file - creates a file and writes a NULL-terminated string to it
 *
 * @filename: the name of the file to be created
 * @text_content: the string to write to the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
    int file_descriptor, bytes_written, length = 0;

    if (filename == NULL)
        return (-1);

    if (text_content != NULL)
    {
        for (length = 0; text_content[length]; length++)
            ; // Calculate the length of the text_content
    }

    file_descriptor = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
    bytes_written = write(file_descriptor, text_content, length);

    if (file_descriptor == -1 || bytes_written == -1)
        return (-1);

    close(file_descriptor);

    return (1);
}

