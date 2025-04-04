#include "ringbuff.h"

#include <stdint.h>


/* ------------------------------- interface -------------------------------- */

int RingBuffInit(struct RingBuff *buffer, int size, int elem_size, void *data) {
  buffer->size = size;
  buffer->element_size = elem_size;
  buffer->read_it = data;
  buffer->write_it = data;
  buffer->data = data;
  buffer->end = (uint8_t*)data + elem_size * size; 

  return 0;
}


int RingBuffWrite(struct RingBuff *buffer, int num_to_write, void *src) {
  int num_written = 0;
  num_to_write *= buffer->element_size;

  while (num_to_write-- != 0) {
    *((uint8_t*)buffer->write_it++) = *(uint8_t*)(src++);
    num_written++;

    if (buffer->write_it == buffer->end) {
      buffer->write_it = buffer->data;
    }
  }

  return num_written / buffer->element_size;
}


int RingBuffRead(struct RingBuff *buffer, int num_to_read, void *dst) {
  int num_read = 0;
  num_to_read *= buffer->element_size;

  if (buffer->read_it == buffer->write_it)
    return 0;

  while (num_to_read-- != 0) {
    *((uint8_t*)dst++) = *((uint8_t*)buffer->read_it++);
    num_read++;

    /* Must precede if clause checking whether read_it equal write_it. */
    if (buffer->read_it == buffer->end) {
      buffer->read_it = buffer->data;
    }

    if (buffer->read_it == buffer->write_it) {
      break;
    }
  }

    return num_read / buffer->element_size;
}


int RingBuffGetReadItt(struct RingBuff *buffer) {
  return (uint8_t*)buffer->read_it - (uint8_t*)buffer->data;
}


int RingBuffGetWriteItt(struct RingBuff *buffer) {
  return (uint8_t*)buffer->write_it - (uint8_t*)buffer->data;
}
