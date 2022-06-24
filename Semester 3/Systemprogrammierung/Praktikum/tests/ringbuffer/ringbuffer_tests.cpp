#include <string.h>

#include <gtest/gtest.h>

extern "C" {
#include "ringbuffer/ringbuffer.h"
}

char a[] = {'A'};
char b[] = {'B'};
char c[] = {'C'};
char d[] = {'D'};
char e[] = {'E'};

const size_t size = 4;

/**
 * @brief Zähler für das Allozieren / Freigeben.
 *        Allozierung: allocated++
 *        Freigabe:    allocated--
 */
int32_t allocated;

/**
 * @brief Callback für die Freigabe.
 *        Dekrementiert den Allozierungszähler.
 */
void free_callback(void *p) {
	allocated--;
}

/**
 * @brief Initialisiert den Ringpuffer und den Allozierungszähler.
 */
ring_buffer *setup_sut() {
	ring_buffer *sut = init_buffer(size, free_callback);
	allocated = 0;
		
	return sut;
}

/**
 * @brief Gibt den Ringpuffer frei. 
 *        Dabei wird geprüft ob der Allozierungszähler gleich 0 ist, 
 *        und somit, ob jedes Element wieder freigegeben wurde.
 */
void teardown_sut(ring_buffer *sut) {
	free_buffer(sut);
	ASSERT_EQ(allocated, 0);
}

/**
 * @brief Fügt ein Element der Datenstruktur hinzu und inkrementiert den Allozierungszähler.
 */
void add_element(ring_buffer *sut, void *data) {
	write_buffer(sut, data);
	allocated++;
}

/**
 * @brief Holt ein Element aus der Datenstruktur und dekrementiert den Allozierungszähler.
 */
void *get_element(ring_buffer *sut) {
	void *data = read_buffer(sut);
	if (data) {
		allocated--;
	}

	return data;
}

/**
 * @brief Testet ob die Initialisierung erfolgreich ist
 */
TEST(Ringbuffer, test_init_not_null) {
	ring_buffer *sut = setup_sut();

	ASSERT_NE(sut, (void *)NULL);
	ASSERT_EQ(sut->size, size);
	ASSERT_EQ(sut->head, 0);
	ASSERT_EQ(sut->count, 0);
	ASSERT_NE(sut->elems, (void *)NULL);
	ASSERT_EQ(sut->free_callback, free_callback);
	
	teardown_sut(sut);
}

/**
 * @brief Testet ob der Count beim Schreiben erhöht wird
 */ 
TEST(Ringbuffer, test_init_write_count) {
	ring_buffer *sut = setup_sut();	
    add_element(sut, a);
	
	ASSERT_EQ(sut->count, 1);

	teardown_sut(sut);
}

/**
 * @brief Testet wenn der Puffer voll ist, ob das älteste Element überschrieben wird
 */
TEST(Ringbuffer, test_init_write_overflow) {
	ring_buffer *sut = setup_sut();

	// Add first and second element
    add_element(sut, a);
    add_element(sut, b);
	// Fill rest of buffer with third element
	for (size_t i = 2; i < size; i++) {
		add_element(sut, c);		
	}

	// Buffer is now full
	ASSERT_EQ(sut->count, size);
	
	// Add fourth element, overwriting first
    add_element(sut, d);

	// Buffer is still full
	ASSERT_EQ(sut->count, size);
	// Read returns second element
	ASSERT_EQ(get_element(sut), b);

	teardown_sut(sut);
}

/**
 * @brief Testet ob beim Lesen das richtige Element zurückgegeben und der Count dekrementiert wird
 */
TEST(Ringbuffer, test_init_read) {
	ring_buffer *sut = setup_sut();	
    add_element(sut, a);
	
	ASSERT_EQ(get_element(sut), a);
	ASSERT_EQ(sut->count, 0);

	teardown_sut(sut);
}

/**
 * @brief Testet wenn der Puffer leer ist, das ein Lesen NULL zurück gibt
 */
TEST(Ringbuffer, test_init_read_no_element) {
	ring_buffer *sut = setup_sut();	
	
	ASSERT_EQ(get_element(sut), (void *)NULL);
	ASSERT_EQ(sut->count, 0);

	teardown_sut(sut);
}
