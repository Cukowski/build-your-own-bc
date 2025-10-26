#include "my_bc.h"

#include <stdlib.h>

int vec_init(t_vec *v, size_t elem_size) {
    v->data = NULL;
    v->size = 0;
    v->cap  = 0;
    v->elem = elem_size;
    return 0;
}

void vec_free(t_vec *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->cap  = 0;
    v->elem = 0;
}

