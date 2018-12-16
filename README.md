# libmbtree

Multi-branch tree implements in C language 

# Example

```{.c}
#include "libmbtree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void free_tree (void **data) {
  char *putted_data = (char*)*data;
  
  if (putted_data) {
    free(putted_data);
  }
}

int main() {
  // head
  mbtree_t head_tree = mbtree_new();
  
  mbtree_t child_1 = mbtree_new();
  mbtree_t child_2 = mbtree_new();
  mbtree_t child_1_1 = mbtree_new();

  char *data1 = strdup ("THIS_IS_DATA");
  mbtree_set_key(child_1, "child_1");
  mbtree_set_data(child_1, (void*)data1);
  mbtree_append(head_tree, child_1);
  
  char *data1_1 = strdup ("THIS_IS_DATA");
  mbtree_set_key(child_1_1, "child_1_1");
  mbtree_set_data(child_1_1, (void*)data1_1);
  mbtree_append(child_1, child_1_1);
  
  char *data2 = strdup ("THIS_IS_DATA");
  mbtree_set_key(child_2, "child_2");
  mbtree_set_data(child_2, (void*)data2);
  mbtree_append(head_tree, child_2);
  
  printf("DATA1 : %s\n", (char*)mbtree_get_data(mbtree_get(head_tree, "child_1")));
  printf("DATA2 : %s\n", (char*)mbtree_get_data(mbtree_get(head_tree, "child_2")));
  printf("DATA1_1 : %s\n", (char*)mbtree_get_data(mbtree_get(head_tree, "child_1.child_1_1")));
  
  mbtree_free(&head_tree, &free_tree);
  
  return 0;
}
```
