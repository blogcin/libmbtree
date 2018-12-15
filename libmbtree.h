
#ifndef __LIB_MBTREE_H__
#define __LIB_MBTREE_H__

typedef void* mbtree_t;

mbtree_t mbtree_new(char *key, void *data, int data_size);
int mbtree_append(mbtree_t h, mbtree_t c);
void mbtree_free(mbtree_t *h);
void* mbtree_get(mbtree_t h, const char *path);
void* mbtree_get_data(mbtree_t h);

#endif
