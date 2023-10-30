#include "main.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * create_file - Create a file and write contents to it
 * @filename: Pointer to the file name
 * @text_content: Pointer to the text content
 *
 * Description: This function creates a file and writes text content to it.
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
    int count = 0;
    int fd = 0;
    int output = 0;

    // Check if the filename is valid
    if (filename == NULL)
        return (-1);

    // Open the file for writing, creating it if it doesn't exist
    fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
    if (fd == -1)
        return (-1);

    // If text_content is not NULL, determine its length
    if (text_content != NULL)
    {
        while (text_content[count] != '\0')
            count++;
    }
    else
    {
        // If text_content is NULL, close the file and return success
        close(fd);
        return (1);
    }

    // Write the text content to the file
    output = write(fd, text_content, count);

    // Check for write errors or incomplete writes
    if (output == -1 || output != count)
    {
        close(fd);
        return (-1);
    }

    // Close the file
    close(fd);

    return (1);
}

