#ifndef SPEICHERVERWALTUNG_H
#define SPEICHERVERWALTUNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#define MEM_POOL_SIZE 8 * 1024
#define MAGIC_INT 0xacdcacdc

/**
 * @brief Struktur für einen Speicherblock
 */
typedef struct memblock {
  size_t size; // Für User nutzbare Länge des Blocks [Bytes]
  struct memblock
      *next; // Zeiger auf Anfang des nächsten freien Blocks (oder NULL)
  unsigned short id; // Fortlaufende und eindeutige Nummer des Blockes
} memblock;

/**
 * @brief Simulierter Heap
 */
extern char mempool[];

/**
 * @brief Zeiger auf den ersten freien Speicherblock
 */
extern memblock *freemem;

/**
 * @brief Initialisiert den malloc
 *
 * @return int 0 wenn bereits initialisiert, 1 bei erfolgreicher Initialisierung
 */
int cm_init(void);

/**
 * @brief Alloziert einen Speicherblock
 *
 * @return void* Zeiger auf den allozierten Speicherbereich (User-Daten),
 *         NULL wenn das allozieren fehlschlägt
 */
void *cm_malloc(size_t size);

/**
 * @brief Gibt einen allozierten Speicherblock wieder frei
 *
 * @param ptr Zeiger auf den freizugebenden Speicherbereich
 */
void cm_free(void *ptr);

#ifdef __cplusplus
}
#endif

#endif
