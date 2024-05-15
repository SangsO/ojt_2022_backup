#include "circular_buffer.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/* create new circular buffer */
circular_buffer_t *new_circular_buffer(size_t capacity)
{
    circular_buffer_t *cirB = malloc(sizeof(circular_buffer_t)); // length of buffer size
    if (cirB == NULL) {
        return NULL;
    }
    cirB->len = capacity;
    cirB->full = false;
    cirB->r = 0;
    cirB->w = 0;
    cirB->buf = malloc(capacity * sizeof(buffer_value_t)); // split length size
    if (cirB->buf == NULL) {
        free(cirB);
        return NULL;
    }
    return cirB;
}

/* delete the malloc memory (buffer and split space) */
void delete_buffer(circular_buffer_t *cirB)
{
    free(cirB->buf);
    free(cirB);
}

int16_t read(circular_buffer_t *cirB, buffer_value_t *data)
{
    /*Error Exception*/
    if (cirB->w == cirB->r && !cirB->full) {
        errno = ENODATA;
        return EXIT_FAILURE;
    }
    *data = cirB->buf[cirB->r++];
    cirB->r %= cirB->len;
    cirB->full = false;
    return EXIT_SUCCESS;
}

int16_t write(circular_buffer_t *cirB, buffer_value_t data)
{
    /*Error Exception*/
    if (cirB->full) {
        errno = ENOBUFS;
        return EXIT_FAILURE;
    }
    return overwrite(cirB, data);
}

int16_t overwrite(circular_buffer_t *cirB, buffer_value_t data)
{
    cirB->buf[cirB->w++] = data;
    cirB->w %= cirB->len;
    if (cirB->full) {
        cirB->r = (cirB->r + 1) % cirB->len;
    } else if (cirB->w == cirB->r) {
        cirB->full = true;
    }
    return EXIT_SUCCESS;
}

void clear_buffer(circular_buffer_t *cirB)
{
    cirB->full = false;
    cirB->w = 0;
    cirB->r = 0;
}