#include "libmbtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __mbtree_t{
  char* key;
  void *data;
  struct __mbtree_t** childs;
  int size;
} _mbtree_t;

mbtree_t mbtree_new(char *key, void *data, int data_size) {
  _mbtree_t *t = calloc(sizeof(_mbtree_t), 1);
  if (!t)
    goto err;

  t->key = strdup(key);

  if (!t->key)
    goto err;

  t->data = malloc(data_size);

  if (!t->data)
    goto err;

  t->childs = NULL;
  memcpy(t->data, data, data_size);
  return (mbtree_t)t;
err:
  if (t) {
    if (t->key)
      free(t->key);
    if (t->data)
      free(t->data);
    if (t->childs)
      free(t->childs);
  }
  return NULL;
}


int mbtree_append(mbtree_t h, mbtree_t c) {
  _mbtree_t* ht = (_mbtree_t*)h;
  _mbtree_t* ct = (_mbtree_t*)c;

  if (!h || !c) {
    return 1;
  }

  ht->size += 1;
  if (ht->childs)
    ht->childs = realloc(ht->childs, sizeof(_mbtree_t*) * ht->size);
  else
    ht->childs = calloc(sizeof(_mbtree_t*), ht->size);

  ht->childs[ht->size-1] = c;

  return 0;
}

void mbtree_free(mbtree_t *h) {
  _mbtree_t* ht = (_mbtree_t*)*h;

  if (!h) {
    return;
  }

  for(int i = 0; i < ht->size; i++) {
    if (ht->childs[i])
      mbtree_free((void**)&ht->childs[i]);
  }

  if (ht->childs) {
    free(ht->childs);
    ht->childs = NULL;
  }

  if (ht->key) {
    free(ht->key);
    ht->key = NULL;
  }

  if (ht->data) {
    free(ht->data);
    ht->data = NULL;
  }

  if (ht) {
    free(ht);
    *h = NULL;
  }
}

void* mbtree_get(mbtree_t h, const char *path) {
  const char *ptr = strchr(path, '.');
  _mbtree_t* ht = (_mbtree_t*)h;

  if (!h || !path) {
    return NULL;
  }

  if (!ptr) {
    for(int i = 0; i < ht->size; i++) {
      if (!strcmp(ht->childs[i]->key, path)) {
        return ht->childs[i];
      }
    }
    return NULL;
  }

  char buf[ptr - path];
  strncpy(buf, path, ptr-path);

  for(int i = 0; i < ht->size; i++) {
    if (!strcmp(ht->childs[i]->key, buf)) {
      return mbtree_get(ht->childs[i], ptr+1);
    }
  }

  return NULL;
}

void* mbtree_get_data(mbtree_t h) {
  _mbtree_t* ht = (_mbtree_t*)NULL;
  if (ht)
    return ht->data;
  return NULL;
}
