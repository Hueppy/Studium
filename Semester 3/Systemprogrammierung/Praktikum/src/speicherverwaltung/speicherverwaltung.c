#include <stdbool.h>
#include "speicherverwaltung/speicherverwaltung.h"

char mempool[MEM_POOL_SIZE];
memblock* freemem = NULL;

/**
 * @brief Überprüfung ob der übergebene Zeiger auf einen Wert im Pool zeigt
 * 
 * @return true, wenn der Zeiger auf einen Wert im Pool zeigt
 * @return false, wenn der Zeiger auf einen Wert außerhalb des Pools zeigt
 */
bool ptr_in_pool(void *ptr) {
	void *first = (char *)mempool;
	void *last = (char *)mempool + MEM_POOL_SIZE;

	return ptr >= first && ptr <= last;
}

int cm_init(void) {
	static bool initialized = false;
	if (initialized) {
		return 0;
	}

	freemem = (memblock*)mempool;
	freemem->size = MEM_POOL_SIZE - sizeof(memblock);
	freemem->next = NULL;
	freemem->id = 0;

	initialized = true;
	return 1;
}

void *cm_malloc(size_t size) {
    static unsigned short block_id = 0;
	if (size == 0) {
		return NULL;
	}

	memblock** pblock = &freemem;
	while (ptr_in_pool(*pblock) && (*pblock)->size < size) {
		pblock = &(*pblock)->next;
	}

	memblock *block = *pblock;
	if (!ptr_in_pool(block)) {
		return NULL;
	}

#ifdef MALLOCSPLIT
	if (block->size > size + 2 * sizeof(memblock) + 32){
		size_t new_size = size + sizeof(memblock);

		memblock *next = (memblock *)((char *)(block + 1) + size);
		next->size = block->size - new_size;
		next->next = block->next;
		next->id = 0;
		*pblock = next;

		block->size = size;
	} else {
		*pblock = block->next;
	}
#else
	*pblock = block->next;
#endif
	block->id = ++block_id;
	block->next = (memblock *)MAGIC_INT;

	return block + 1;
}

void cm_free(void *ptr) {
	if (!ptr_in_pool((char *)ptr - sizeof(memblock))) {
		return;
	}

	memblock *block = (memblock *)ptr - 1;
	if (block->next != (memblock *)MAGIC_INT) {
		return;
	}

	block->next = freemem;
	freemem = block;
}
