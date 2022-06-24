#include <string.h>
#include <math.h>
#include <gtest/gtest.h>

extern "C" {
#include "speicherverwaltung/speicherverwaltung.h"
}


#define CHECK_MALLOC(p) if (!p) {fprintf(stderr, "[          ] NULL pointer: %s (line %d)!\n", __FILE__, __LINE__); exit(EXIT_FAILURE);}
#define TESTSTART cm_init();freemem=(memblock*)mempool;freemem->size=MEM_POOL_SIZE-sizeof(memblock);freemem->next=NULL;freemem->id=id;


/* ============================TESTS======================================== */
unsigned short id = 0;


/*
 * Testet ob die Konstante MEM_POOL_SIZE definiert wurde und diese die
 * korrekte Groesse hat.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_MEM_POOL_SIZE) {
    ASSERT_GE(MEM_POOL_SIZE, 4096);
}

/*
 * Testet ob die Konstante MAGIC_INT definiert wurde und diese die
 * korrekte Groesse hat.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_MAGIC_INT) {
    ASSERT_EQ(MAGIC_INT, 0xacdcacdc);
}

/*
 * Testet ob die globale Variable mempool angelegt wurde und diese die
 * korrekte Groesse hat.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_mempool_size) {
    ASSERT_EQ(sizeof(mempool), MEM_POOL_SIZE);
}

/*
 * Testet ob die globale Variable freemem angelegt worden ist.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_freemem) {
    memblock *x = freemem;

    ASSERT_EQ(x, freemem);
}

/*
 * Testet ob der Datentyp memblock definiert wurde und welche Groesse er hat.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_memblock) {
    memblock mb;
    mb.size = 16;
    mb.next = &mb;
    mb.id = 42;

    ASSERT_EQ(mb.size, 16);
    ASSERT_EQ(mb.next, &mb);
    ASSERT_EQ(mb.id, 42);
}

/*
 * Testet ob cm_init den Heap initiiert.
 * Precondition: cm_init() darf noch nicht gelaufen sein!
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_init) { /* MUSS als erster Heap-aendernder Test laufen */
    memset(mempool, 2, MEM_POOL_SIZE);
    freemem = NULL;

    int erg = cm_init();

    ASSERT_EQ(erg, 1);
    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, id);
}

/*
 * Testet ob ein doppelter Aufruf von cm_init nichts tut.
 * - zur Kontrolle mit fremem=NULL nach dem ersten Mal.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_init_double_call) {
    char dummy[MEM_POOL_SIZE];

    int erg = cm_init(); /* mind. ein Aufruf */

    memset(mempool, 2, MEM_POOL_SIZE);
    memset(dummy, 2, MEM_POOL_SIZE);
    freemem = NULL;

    erg = cm_init(); /* tut nix mehr */

    ASSERT_EQ(erg, 0);
    ASSERT_TRUE(memcmp(mempool, dummy, MEM_POOL_SIZE) == 0);
    ASSERT_EQ(NULL, freemem);
}

/*
 * Testet ob ein doppelter Aufruf von cm_init nichts tut.
 * - zur Kontrolle mit size/next==0 nach dem ersten Mal.
 *
 * @param void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_init_double_call_blocks) {
    char dummy[MEM_POOL_SIZE];

    int erg = cm_init(); /* mind. ein Aufruf */

    memset(mempool, 2, MEM_POOL_SIZE);
    memset(dummy, 2, MEM_POOL_SIZE);
    ((memblock*) mempool)->size = 0;
    ((memblock*) mempool)->next = 0;
    ((memblock*) mempool)->id = 42;
    ((memblock*) dummy)->size = 0;
    ((memblock*) dummy)->next = 0;
    ((memblock*) dummy)->id = 42;
    freemem = (memblock*) mempool;

    erg = cm_init(); /* tut nix mehr */

    ASSERT_EQ(erg, 0);
    ASSERT_TRUE(memcmp(mempool, dummy, MEM_POOL_SIZE) == 0);
    ASSERT_EQ(freemem, (memblock* ) mempool);
}

/*
 * Testet ob ein doppelter Aufruf von cm_init nichts tut.
 * - zur Kontrolle mit next==MAGIC_INT nach dem ersten Mal.
 *
 * @param void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_init_double_call_blocks_next_magic) {
    char dummy[MEM_POOL_SIZE];

    int erg = cm_init(); /* mind. ein Aufruf */

    memset(mempool, 2, MEM_POOL_SIZE);
    memset(dummy, 2, MEM_POOL_SIZE);
    ((memblock*) mempool)->size = MEM_POOL_SIZE - sizeof(memblock);
    ((memblock*) mempool)->next = (memblock*) MAGIC_INT;
    ((memblock*) mempool)->id = 42;
    ((memblock*) dummy)->size = MEM_POOL_SIZE - sizeof(memblock);
    ((memblock*) dummy)->next = (memblock*) MAGIC_INT;
    ((memblock*) dummy)->id = 42;
    freemem = (memblock*) mempool;

    erg = cm_init(); /* tut nix mehr */

    ASSERT_EQ(erg, 0);
    ASSERT_TRUE(memcmp(mempool, dummy, MEM_POOL_SIZE) == 0);
    ASSERT_EQ(freemem, (memblock* ) mempool);
}

/*
 * Testet ob ein doppelter Aufruf von cm_init nichts tut.
 *
 * @param void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_init_double_call_first_char) {
    TESTSTART

    int erg = cm_init(); /* mind. ein Aufruf */

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, id);

    mempool[0] = 0;

    erg = cm_init(); /* tut nix mehr */

    ASSERT_EQ(erg, 0);
    ASSERT_EQ(mempool[0], 0);
    ASSERT_EQ(freemem, (memblock* ) mempool);
}

/*
 * Testet ob ein doppelter Aufruf von cm_init nichts tut.
 *
 * @param void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_init_double_call_first_char_magic) {
    TESTSTART

    int erg = cm_init(); /* mind. ein Aufruf */

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, id);

    *((int*) mempool) = MAGIC_INT;

    erg = cm_init(); /* tut nix mehr */

    ASSERT_EQ(erg, 0);
    ASSERT_EQ(*((int* ) mempool), MAGIC_INT);
    ASSERT_EQ(freemem, (memblock* ) mempool);
}

/*
 * Testet ob ein Aufruf von cm_malloc mit null Bytes nichts tut.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_null_bytes) {
    TESTSTART

    void *tmp = cm_malloc(0);

    ASSERT_EQ(NULL, tmp);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, id);
}

#ifndef MALLOCSPLIT
/*
 * Test von cm_malloc mit 1 Byte.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_one_byte) {
    TESTSTART

    void *tmp = cm_malloc(1);
    ++id;

    ASSERT_EQ(NULL, freemem);

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);
}
#endif

#ifdef MALLOCSPLIT
/*
 * Test von cm_malloc mit 1 Byte.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_one_byte_with_split) {
    TESTSTART

    void *tmp = cm_malloc(1);
    ++id;

    ASSERT_EQ(freemem, (memblock* ) (mempool + sizeof(memblock) + 1));
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - 2 * sizeof(memblock) - 1);
    ASSERT_EQ(NULL, freemem->next);

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);
}
#endif

/*
 * Test von cm_malloc mit dem gesamten Speicher.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_all_bytes) {
    TESTSTART

    void *tmp = cm_malloc(MEM_POOL_SIZE - sizeof(memblock));
    ++id;

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);

    ASSERT_EQ(NULL, freemem);
}

/*
 * Test von cm_malloc mit dem gesamten Speicher plus ein Byte.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_all_plus_one_bytes) {
    TESTSTART

    void *tmp = cm_malloc(MEM_POOL_SIZE - sizeof(memblock) + 1);

    ASSERT_EQ(NULL, tmp);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, id);
}

/*
 * Test von cm_malloc mit ohne freiem Speicher.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_no_free_mem) {
    TESTSTART

    freemem = NULL;

    void *tmp = cm_malloc(10);

    ASSERT_EQ(NULL, tmp);
    ASSERT_EQ(NULL, freemem);
}

/*
 * Test von cm_malloc ohne Split.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_without_split) {
    TESTSTART

    size_t size = MEM_POOL_SIZE - sizeof(memblock) - 2 * sizeof(memblock);
    void *tmp = cm_malloc(size);
    ++id;

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);

    ASSERT_EQ(NULL, freemem);
}

/*
 * Test von cm_malloc ohne Split (limit).
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_without_split_limit) {
    TESTSTART

    size_t size = MEM_POOL_SIZE - sizeof(memblock) - 2 * sizeof(memblock) - 32;
    void *tmp = cm_malloc(size);
    ++id;

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);

    ASSERT_EQ(NULL, freemem);
}

#ifdef MALLOCSPLIT
/*
 * Test von cm_malloc mit Split (limit).
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_with_split_limit) {
    TESTSTART

    size_t size = MEM_POOL_SIZE - sizeof(memblock) - 2 * sizeof(memblock) - 33;
    void *tmp = cm_malloc(size);
    ++id;

    ASSERT_EQ((memblock* ) tmp, ((memblock* ) mempool) + 1);
    ASSERT_EQ((((memblock* )tmp) - 1)->size, size);
    ASSERT_EQ((((memblock* )tmp) - 1)->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ((((memblock* )tmp) - 1)->id, id);

    ASSERT_EQ(freemem, (memblock* ) (mempool + sizeof(memblock) + size));
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock) - sizeof(memblock) - size);
    ASSERT_EQ(NULL, freemem->next);
}
#endif

/*
 * Test von cm_malloc (letzer Block alloziert wird).
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_last_block) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a + 1) + 100);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b + 1) + 140);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c + 1) + 100);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d + 1) + 500);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e + 1) + 160);
    e->size = 160;
    e->next = f;

    f->size = &mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1));
    f->next = NULL;

    tmp = cm_malloc(&mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1)));
    ++id;

    ASSERT_EQ(a, freemem);
    ASSERT_EQ(a->next, b);
    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, d);
    ASSERT_EQ(d->next, e);
    ASSERT_EQ(NULL, e->next);
    ASSERT_EQ((char* )tmp, (char* )(f + 1));
    ASSERT_EQ((f->next), (memblock* ) MAGIC_INT);
    ASSERT_EQ(f->size, &mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1)));
    ASSERT_EQ(f->id, id);
}

/*
 * Test von cm_malloc (kein Split, Grenze).
 * Reagiert Split am Grenzwert richtig?
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_list_no_split_first) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f, *g;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a + 1) + 100);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b + 1) + 140);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c + 1) + 100);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d + 1) + 500);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e + 1) + 160);
    e->size = 160;
    e->next = f;

    f->size = &mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1));
    f->next = NULL;

    tmp = cm_malloc(90);
    ++id;
    g = (memblock*) tmp - 1;

    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, d);
    ASSERT_EQ(d->next, e);
    ASSERT_EQ(e->next, f);
    ASSERT_EQ(NULL, f->next);
    ASSERT_EQ((char* )tmp, ((char* )(a + 1)));
    ASSERT_EQ((g->next), (memblock* ) MAGIC_INT);
    ASSERT_EQ(g->size, 100);
    ASSERT_EQ(g->id, id);
    ASSERT_EQ(b, freemem);
}

/*
 * Test von cm_malloc - keine freien Bloecke.
 * Passender freier Block am Ende, der nicht in der Liste ist
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_no_block_in_list_fits) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a) + 180);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b) + 220);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c) + 180);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d) + 580);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e) + 240);
    e->size = 160;
    e->next = NULL;

    f->size = 1000;
    f->next = NULL;

    tmp = cm_malloc(800);

    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, d);
    ASSERT_EQ(d->next, e);
    ASSERT_EQ(NULL, e->next);
    ASSERT_EQ(NULL, f->next);
    ASSERT_EQ(NULL, tmp);
    ASSERT_EQ(a, freemem);
}

/*
 * Test von cm_malloc - keine freien Bloecke
 * und ein nicht eingehaengter Block in der mitte.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_no_listed_block_fits_unlisted_in_middle) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a) + 180);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b) + 220);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c) + 180);
    c->size = 100;
    d->next = NULL;

    e = (memblock*) ((char*) (d) + 580);
    d->size = 500;
    c->next = e;

    f = (memblock*) ((char*) (e) + 240);
    e->size = 160;
    e->next = f;

    f->size = 220;
    f->next = NULL;

    tmp = cm_malloc(400);

    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, e);
    ASSERT_EQ(NULL, d->next);
    ASSERT_EQ(e->next, f);
    ASSERT_EQ(NULL, f->next);
    ASSERT_EQ(NULL, tmp);
    ASSERT_EQ(a, freemem);
}

#ifdef MALLOCSPLIT
/*
 * Test von cm_malloc (mehrere Allokationen nacheinander).
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_iteration) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f, *g;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a + 1) + 100);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b + 1) + 140);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c + 1) + 100);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d + 1) + 500);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e + 1) + 160);
    e->size = 160;
    e->next = f;

    f->size = &mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1));
    f->next = NULL;

    tmp = cm_malloc(300);
    ++id;
    g = (memblock*) ((char*) (d + 1) + 300);

    ASSERT_EQ(a, freemem);
    ASSERT_EQ(a->next, b);
    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, g);
    ASSERT_EQ(e->next, f);
    ASSERT_EQ(NULL, f->next);
    ASSERT_EQ(g->next, e);
    ASSERT_EQ(g->size, 200 - sizeof(memblock));
    ASSERT_EQ((char* )tmp, (char* )(d + 1));
    ASSERT_EQ(d->next, (memblock* ) MAGIC_INT);
    ASSERT_EQ(d->size, 300);
    ASSERT_EQ(d->id, id);
}

/*
 * Test von cm_malloc (Split).
 * Reagiert Split von cm_malloc richtig?
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_list_split_first) {
    TESTSTART

    memblock *a, *b, *c, *d, *e, *f, *g;
    void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a + 1) + 120);
    a->size = 120;
    a->next = b;

    c = (memblock*) ((char*) (b + 1) + 140);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c + 1) + 100);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d + 1) + 500);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e + 1) + 160);
    e->size = 160;
    e->next = f;

    f->size = &mempool[MEM_POOL_SIZE - 1] - ((char*) (f + 1));
    f->next = NULL;

    tmp = cm_malloc(20);
    ++id;
    g = (memblock*) ((char*) (a + 1) + 20);

    ASSERT_EQ(b->next, c);
    ASSERT_EQ(c->next, d);
    ASSERT_EQ(d->next, e);
    ASSERT_EQ(e->next, f);
    ASSERT_EQ(NULL, f->next);
    ASSERT_EQ((char* )tmp, (char* )(a + 1));
    ASSERT_EQ((a->next), (memblock* ) MAGIC_INT);
    ASSERT_EQ(a->size, 20);
    ASSERT_EQ(a->id, id);
    ASSERT_EQ(g, freemem);
    ASSERT_EQ(g->next, b);
    ASSERT_EQ(g->size, 100 - sizeof(memblock));
}
#endif

/*
 * Test von cm_malloc wobei freemem ausserhalb von mempool ist.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_mem_in_array) {
    TESTSTART

    char dummy[200];

    freemem = (memblock*) dummy;
    freemem->size = 200 - sizeof(memblock);
    freemem->next = NULL;
    freemem->id = 0;

    void* a = cm_malloc(150);

    ASSERT_EQ(NULL, a);

    ASSERT_EQ(freemem, (memblock* )dummy);
    ASSERT_EQ(freemem->size, 200 - sizeof(memblock));
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->id, 0);
}

/*
 * Test von cm_malloc wobei fremem in mempool.
 * Erster freier Block ausserhalb von mempool.
 *
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_malloc_outside_mempool) {
    TESTSTART

    char dummy[200];
    memblock *a, *out;

    out = (memblock*) dummy;
    out->size = 300 - sizeof(memblock);
    out->next = NULL;
    out->id = 7;

    a = (memblock*) mempool;
    freemem = a;
    a->size = 100;
    a->next = out;
    a->id = 42;

    void* t = cm_malloc(200);

    ASSERT_EQ(NULL, t);

    ASSERT_EQ(out, (memblock* )dummy);
    ASSERT_EQ(out->size, 300 - sizeof(memblock));
    ASSERT_EQ(NULL, out->next);
    ASSERT_EQ(out->id, 7);
}

/*
 * Test von cm_free(): Null-Pointer
 * 4b, 1
 * @return void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_free_null) {
    TESTSTART

    char mempoolcopy[MEM_POOL_SIZE];
    memcpy(mempoolcopy, mempool, MEM_POOL_SIZE);

    cm_free(NULL);

    ASSERT_EQ((memblock* ) mempool, freemem);
    ASSERT_EQ(memcmp(mempoolcopy, mempool, MEM_POOL_SIZE), 0);
}

/*
 * Test von cm_free() (Ersten Block free'en)
 * 4b, 1
 * @return void
 * @param void
 */
TEST(Speicherverwaltung, test_cm_free_first_block) {
    TESTSTART

    memblock *a, *b;
    void *ptr;

    a = (memblock*) mempool;
    b = (memblock*) (mempool + 200);

    a->size = 200 - sizeof(memblock);
    a->next = (memblock*) MAGIC_INT;
    a->id = 7;

    b->size = MEM_POOL_SIZE - 200 - sizeof(memblock);
    b->next = NULL;
    b->id = 42;

    freemem = b;
    ptr = (void*) (mempool + sizeof(memblock));

    cm_free(ptr);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(a->size, 200 - sizeof(memblock));
    ASSERT_EQ(a->next, b);
    ASSERT_EQ(a->id, 7);
    ASSERT_EQ(b->size, MEM_POOL_SIZE - 200 - sizeof(memblock));
    ASSERT_EQ(NULL, b->next);
    ASSERT_EQ(b->id, 42);
}

/*
 * Test von cm_free() (In der Mitte free'en)
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_second_block) {
    TESTSTART

    memblock *a, *b, *c;
    void *ptr;

    a = (memblock*) mempool;
    b = (memblock*) (mempool + 200);
    c = (memblock*) (mempool + 500);

    a->size = 200 - sizeof(memblock);
    a->next = NULL;
    a->id = 1;

    b->size = 300 - sizeof(memblock);
    b->next = (memblock*) MAGIC_INT;
    b->id = 2;

    c->size = MEM_POOL_SIZE - 500 - sizeof(memblock);
    c->next = a;
    c->id = 3;

    freemem = c;
    ptr = (void*) (b + 1);

    cm_free(ptr);

    ASSERT_EQ(freemem, b);
    ASSERT_EQ(NULL, a->next);
    ASSERT_EQ(a->size, 200 - sizeof(memblock));
    ASSERT_EQ(a->id, 1);
    ASSERT_EQ(b->next, c);
    ASSERT_EQ(b->size, 300 - sizeof(memblock));
    ASSERT_EQ(b->id, 2);
    ASSERT_EQ(c->next, a);
    ASSERT_EQ(c->size, MEM_POOL_SIZE - 500 - sizeof(memblock));
    ASSERT_EQ(c->id, 3);
}

/*
 * Test von free (kein Speicher).
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_no_freemem) {
    TESTSTART

    memblock *a;
    void *ptr;

    a = (memblock*) mempool;
    a->size = MEM_POOL_SIZE - sizeof(memblock);
    a->next = (memblock*) MAGIC_INT;
    a->id = 7;

    freemem = NULL;
    ptr = (void*) (mempool + sizeof(memblock));

    cm_free(ptr);

    ASSERT_EQ(freemem, a);
    ASSERT_EQ(NULL, a->next);
    ASSERT_EQ(a->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(a->id, 7);
}

/*
 * Test von cm_free() (Fehlermeldung wenn next nicht MAGIC_INT)
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_wrong_next_null) {
    TESTSTART

    memblock *a, *b;
    void *ptr;

    a = (memblock*) mempool;
    b = (memblock*) (mempool + 200);

    a->size = 200 - sizeof(memblock);
    a->next = NULL;
    a->id = 1;

    b->size = MEM_POOL_SIZE - 200 - sizeof(memblock);
    b->next = NULL;
    b->id = 2;

    freemem = b;
    ptr = (void*) (mempool + sizeof(memblock));

    cm_free(ptr);

    ASSERT_EQ(freemem, b);
    ASSERT_EQ(NULL, a->next);
    ASSERT_EQ(a->size, 200 - sizeof(memblock));
    ASSERT_EQ(a->id, 1);
    ASSERT_EQ(NULL, b->next);
    ASSERT_EQ(b->size, MEM_POOL_SIZE - 200 - sizeof(memblock));
    ASSERT_EQ(b->id, 2);
}

/*
 * Test von cm_free() (Fehlermeldung wenn next nicht MAGIC_INT)
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_wrong_next_b) {
    TESTSTART

    memblock *a, *b;
    void *ptr;

    a = (memblock*) mempool;
    b = (memblock*) (mempool + 200);

    a->size = 200 - sizeof(memblock);
    a->next = b;
    a->id = 1;

    b->size = MEM_POOL_SIZE - 200 - sizeof(memblock);
    b->next = NULL;
    b->id = 2;

    freemem = b;
    ptr = (void*) (mempool + sizeof(memblock));

    cm_free(ptr);

    ASSERT_EQ(freemem, b);
    ASSERT_EQ(NULL, b->next);
    ASSERT_EQ(b->size, MEM_POOL_SIZE - 200 - sizeof(memblock));
    ASSERT_EQ(b->id, 2);
    ASSERT_EQ(a->next, b);
    ASSERT_EQ(a->size, 200 - sizeof(memblock));
    ASSERT_EQ(a->id, 1);
}

/*
 * Test von free (Array-Grenzen).
 *
 * Pointer auf anscheinend belegten Block ausserhalb vom Array
 *
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_wrongblock_outside) {
    TESTSTART

    char reserved_space[100];
    memblock *a;
    void *ptr;

    a = (memblock*) reserved_space;
    a->size = 100 - sizeof(memblock);
    a->next = (memblock*) MAGIC_INT;
    a->id = 1;

    ptr = (void*) (reserved_space + sizeof(memblock));
    cm_free(ptr);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(a->next, (memblock*) MAGIC_INT);
    ASSERT_EQ(a->size, 100 - sizeof(memblock));
    ASSERT_EQ(a->id, 1);
}

/*
 * Test von free (Adresse von lokaler Variable +1).
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_wrong_pointer_localvariable) {
    TESTSTART

    memblock a;

    a.size = 10;
    a.next = (memblock*) MAGIC_INT;
    a.id = 99;

    cm_free(&a + 1);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(NULL, freemem->next);
    ASSERT_EQ(freemem->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(a.next, (memblock*) MAGIC_INT);
    ASSERT_EQ(a.size, 10);
    ASSERT_EQ(a.id, 99);
}

/*
 * Test von free (ptr zeigt nicht auf den Anfang eines Blocks).
 * 4b, 1
 * @param void
 * @return void
 */
TEST(Speicherverwaltung, test_cm_free_wrong_pointer_mempool) {
    TESTSTART

    memblock *a;
    void *ptr;

    a = (memblock*) mempool;
    a->size = MEM_POOL_SIZE - sizeof(memblock);
    a->next = (memblock*) MAGIC_INT;
    a->id = 4;

    ptr = (void*) (mempool + 1);

    cm_free(ptr);

    ASSERT_EQ(freemem, (memblock* ) mempool);
    ASSERT_EQ(a->next, (memblock*) MAGIC_INT);
    ASSERT_EQ(a->size, MEM_POOL_SIZE - sizeof(memblock));
    ASSERT_EQ(a->id, 4);
}

// ==========================================================================

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
