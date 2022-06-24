#include <stdio.h>
#include "speicherverwaltung.c"

#define MALLOCSPLIT

/**
 * @brief Demoanwendung
 */
int main(void) {
	cm_init();

	char* a = cm_malloc(100);
	char* b = cm_malloc(50);

	*a = 'a';
	*b = 'b';

/*
	printf("%d\n", (size_t)a);
	printf("%d\n", b);
*/

	cm_free(a);
	cm_free(b);
	
	return 0;
}
