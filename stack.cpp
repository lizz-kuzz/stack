#include "stack.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <math.h>


void stack_ctor_(stack *stk, size_t capacity) {

    stk->capacity = capacity;
    stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));
    stk->size = 0;
    ASSERT(stk);

}

void stack_dtor(stack *stk) {
    ASSERT(stk);

    to_dump(stk, logs_);
    free(stk->data);
    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
    ASSERT(stk);

}

void stack_push(stack *stk, double elem) {
    ASSERT(stk);

    to_dump(stk, logs_);

    if (stk->size >= stk->capacity) stack_resize(stk);
    stk->data[stk->size] = elem;
    (stk->size)++;
    ASSERT(stk);

}

void stack_resize(stack *stk) {
    ASSERT(stk);

    to_dump(stk, logs_);

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }
    stk->data = (elem_stk_t *)realloc(stk->data, stk->capacity*sizeof(elem_stk_t));
    for (long unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = NAN;

    ASSERT(stk);
}

void stack_pop(stack *stk, elem_stk_t *value) {
    ASSERT(stk);

    to_dump(stk, logs_);


    *value = stk->data[stk->size];
    stk->size--;
    stk->data[stk->size] = NAN;
    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10) stack_resize(stk);

    ASSERT(stk);
}




