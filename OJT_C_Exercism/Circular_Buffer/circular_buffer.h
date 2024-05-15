#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* struct for buffer data*/
typedef int buffer_value_t;
typedef struct {
  bool full;
  size_t len, r, w;
  buffer_value_t *buf;
} circular_buffer_t;

circular_buffer_t* new_circular_buffer(size_t capacity);

void delete_buffer(circular_buffer_t *cirB);

int16_t write(circular_buffer_t *cirB, buffer_value_t data);

int16_t overwrite(circular_buffer_t *cirB, buffer_value_t data);

int16_t read(circular_buffer_t *cirB, buffer_value_t *data);

void clear_buffer(circular_buffer_t *cirB);

#endif