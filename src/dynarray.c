#include "my_bc.h"

#include <stdlib.h>
#include <string.h>

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

static int vec_grow(t_vec *v) {
    size_t ncap;
    if (v->cap) ncap = v->cap * 2;
    else ncap = 8;

    void *p = malloc(ncap * v->elem);
    if (!p) return -1;
    if (v->data) {
        (void)memcpy(p, v->data, v->size * v->elem);
        free(v->data);
    }
    v->data = p;
    v->cap  = ncap;
    return 0;
}

int vec_push(t_vec *v, const void *elem) {
    if (v->size == v->cap && vec_grow(v) != 0) return -1;

    (void)memcpy((char*)v->data + v->size * v->elem, elem, v->elem);
    v->size++;
    return 0;
}

void *vec_back(t_vec *v) {
    if (v->size == 0) return NULL;
    return (char*)v->data + (v->size - 1) * v->elem;
}

int vec_pop(t_vec *v) {
    if (v->size == 0) return -1;
    v->size--;
    return 0;
}
