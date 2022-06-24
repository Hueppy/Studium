#include <stdio.h>
#include <stdlib.h>

#include "ringbuffer.c"

#define BUFFER_SIZE 4

void free_callback(void *p) {
	printf("Freeing: %s\n", (char *)p);
}

void print_buffer(ring_buffer *cb) {
	char *data = read_buffer(cb);
	while (data) {
		printf("%s\n", data);
		data = read_buffer(cb);
	}	
}

int main(int argc, char *argv[]){
	ring_buffer *cb = init_buffer(BUFFER_SIZE, &free_callback);

	write_buffer(cb, "A");
	write_buffer(cb, "B");
	write_buffer(cb, "C");

	print_buffer(cb);

	write_buffer(cb, "A");
	write_buffer(cb, "B");
	write_buffer(cb, "C");
	write_buffer(cb, "D");
	write_buffer(cb, "E");

	print_buffer(cb);

	write_buffer(cb, "A");
	write_buffer(cb, "B");
	write_buffer(cb, "C");
	
	free_buffer(cb);
	
    return 0;
}
