#include <stddef.h>
#include <stdlib.h>

#include "ringbuffer/ringbuffer.h"

ring_buffer *init_buffer(const size_t n, void (*f)(void *p)) {
	ring_buffer *res = malloc(sizeof(ring_buffer));
	res->size = n;
	res->count = 0;
	res->head = 0;
	res->elems = malloc(sizeof(void*) * n);
	res->free_callback = f;
	
	return res;
}

int free_buffer(ring_buffer *cb) {
	size_t old_count = cb->count;
	while (cb->count > 0) {
		void *elem = read_buffer(cb);
		cb->free_callback(elem);
	}

	free(cb->elems);
	free(cb);

	return old_count;
}

void *read_buffer(ring_buffer *cb) {
	void *data = NULL;
	if (cb->count > 0) {
		data = *(cb->elems + cb->head);
		cb->head = (cb->head + 1) % cb->size;
		cb->count--;	
	} 
	
	return data;
}

void write_buffer(ring_buffer *cb, void *data) {
	size_t tail = (cb->head + cb->count) % cb->size;
    if (cb->size == cb->count) {
		void *old_elem = read_buffer(cb);
		cb->free_callback(old_elem);
	}

	*(cb->elems + tail) = data;
	cb->count++;
}
