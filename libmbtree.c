#define _GNU_SOURCE
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


mbtree_t mbtree_new() {
  _mbtree_t *t = calloc(sizeof(_mbtree_t), 1);
  return t;
}

int mbtree_set_key(mbtree_t h, char *key) {
  _mbtree_t* ht = (_mbtree_t*)h;

  if (ht) {
    ht->key = strdup(key);
    if (ht->key) {
      return 0;
    }
  }

  return 1;
}

int mbtree_set_data(mbtree_t h, void *data) {
  _mbtree_t* ht = (_mbtree_t*)h;

  if (ht) {
    ht->data = data;
    return 0;
  }

  return 1;
}

mbtree_t mbtree_new_(char *key, void *data) {
  _mbtree_t *t = calloc(sizeof(_mbtree_t), 1);
  if (!t)
    goto err;

  t->key = strdup(key);

  if (!t->key)
    goto err;

  t->data = data;
  t->childs = NULL;
  return (mbtree_t)t;
err:
  if (t) {
    if (t->key)
      free(t->key);
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

void mbtree_iterate(mbtree_t *h, void (*f)(void*)) {
  _mbtree_t* ht = (_mbtree_t*)*h;

  if (!h) {
    return;
  }

  for(int i = 0; i < ht->size; i++) {
    if (ht->childs[i]) {
      f(ht->childs[i]);
      mbtree_iterate((void**)&ht->childs[i], f);
    }
  }

}

void mbtree_free(mbtree_t *h, void (*free_function)(void**)) {
  _mbtree_t* ht = (_mbtree_t*)*h;

  if (!h) {
    return;
  }

  for(int i = 0; i < ht->size; i++) {
    if (ht->childs[i])
      mbtree_free((void**)&ht->childs[i], free_function);
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
    free_function(&ht->data);
    ht->data = NULL;
  }

  if (ht) {
    free(ht);
    *h = NULL;
  }
}

mbtree_t mbtree_get(mbtree_t h, const char *path) {
  const char *ptr = strchr(path, '.');
  _mbtree_t* ht = (_mbtree_t*)h;
  char *buf = NULL;

  if (!h || !path) {
    return NULL;
  }

  if (!ptr) {
    for(int i = 0; i < ht->size; i++) {
      if (!strncmp(ht->childs[i]->key, path, strlen(ht->childs[i]->key))) {
        return ht->childs[i];
      }
    }
    return NULL;
  }

  asprintf(&buf, "%s", path);

  if (!buf) {
    return NULL;
  }

  for(int i = 0; i < ht->size; i++) {
    if (!strncmp(ht->childs[i]->key, buf, strlen(ht->childs[i]->key))) {
      free(buf);
      return mbtree_get(ht->childs[i], ptr+1);
    }
  }

  free(buf);
  return NULL;
}

void* mbtree_get_data(mbtree_t h) {
  _mbtree_t* ht = (_mbtree_t*)h;
  if (ht)
    return ht->data;
  return NULL;
}
