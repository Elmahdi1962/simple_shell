#include "main.h"

/**
 * swap - Function to swap two numbers
 * @x: digit
 * @y: digit
 * Return: void
 */
void swap(char *x, char *y)
{
    char t = *x; *x = *y; *y = t;
}
 
/**
 * reverse - Function to reverse `buffer[i…j]`
 * @buffer: buffer to reverse
 * @i: first digit or index
 * @j: last digit or index
 * Return: reversed buffer
 */

char *reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
