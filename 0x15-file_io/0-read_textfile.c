#include "main.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

/**
 * read_textfile - reads a text file and outputs it to the standard output
 * @filename: the name of the file to be read
 * @letters: the maximum number of characters to read and output
 *
 * Return: the actual number of characters successfully read and output
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int fd;                  // File descriptor
    ssize_t read_bytes, written_bytes; // Number of bytes read and written
    char *buffer;            // Buffer to hold the file content

    // Check if the filename is valid
    if (filename == NULL)
        return (0);

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);

    // Allocate memory for the buffer to read into
    buffer = malloc(letters);
    if (buffer == NULL)
    {
        close(fd);
        return (0);
    }

    // Read from the file into the buffer
    read_bytes = read(fd, buffer, letters);
    close(fd);

    // Check for read errors
    if (read_bytes == -1)
    {
        free(buffer);
        return (0);
    }

    // Write the contents of the buffer to standard output
    written_bytes = write(STDOUT_FILENO, buffer, read_bytes);
    free(buffer);

    // Check for write errors or incomplete writes
    if (read_bytes != written_bytes || written_bytes == -1)
    {
        return (0);
    }

    return (written_bytes);
}

