
#ifndef __LIB_MBTREE_H__
#define __LIB_MBTREE_H__

typedef void* mbtree_t;

mbtree_t mbtree_new();
int mbtree_set_key(mbtree_t t, char *key);
int mbtree_set_data(mbtree_t t, void *data);
mbtree_t mbtree_new_(char *key, void *data);
int mbtree_append(mbtree_t h, mbtree_t c);
void mbtree_iterate(mbtree_t *h, void (*f)(void*));
void mbtree_free(mbtree_t *h, void (*free_function)(void**));
mbtree_t mbtree_get(mbtree_t h, const char *path);
void* mbtree_get_data(mbtree_t h);

#endif
