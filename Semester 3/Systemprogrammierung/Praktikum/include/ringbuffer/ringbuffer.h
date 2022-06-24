#include <sys/types.h>

/**
 * @brief Struktur für den Ringpuffer
 */
typedef struct {
    size_t size, count, head;
    void **elems;
    void (*free_callback)(void *p);	
} ring_buffer;

/**
 * @brief Initialisiert einen Ringpuffer
 *
 * @param n Größe des Ringpuffers
 * @param f Callback zum freigeben eines Elements des Ringpuffer
 *
 * @return Pointer zum Ringpuffer
 */
ring_buffer *init_buffer(const size_t n, void (*f)(void *p));
/**
 * @brief Gibt einen Ringpuffer und dessen Elemente frei
 * 
 * @param cb Pointer zum Ringpuffer
 * 
 * @return Anzahl der ursprünglich gespeicherten Datensätze
 */
int free_buffer(ring_buffer *cb);

/**
 * @brief Liefert das älteste Element des Ringpuffers zurück.
 *        Anschließend wird der head des Puffers um ein Element verschoben.
 *        Das zurückgegebene Element *wird nicht* freigegeben.
 * 
 * @param cb Pointer zum Ringpuffer
 *
 * @return Pointer zum Element
 */
void *read_buffer(ring_buffer *cb);
/**
 * @brief Hängt den Datensatz in den Puffer ein.
 *        Ist der Puffer voll so wird das älteste Element ersetzt.
 *        Das ersetzte element *wird* freigegeben.
 * 
 * @param cb Pointer zum Rinpuffer
 * @param data Pointer zu dem Datensatz
 */
void write_buffer(ring_buffer *cb, void *data);

