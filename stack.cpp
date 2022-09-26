#include "stack.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <math.h>


void stack_ctor_(stack *stk, size_t capacity) {
    stk->capacity = capacity;
    stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));
    for (unsigned i = 0; i < stk->capacity; i++) {
        stk->data[i] = NAN;
    }
    stk->size = 0;

    #if MODE == 4 || MODE == 2
        stk->canaries_left  = CANARIES_LEFT;
        stk->canaries_right = CANARIES_RIGHT;
    #endif
    #if MODE != 1
        ASSERT(stk);
    #endif

    
}

void stack_dtor(stack *stk) {
    #if MODE != 1
        ASSERT(stk);
    #endif

    free(stk->data);
    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;

    #if MODE != 1
        ASSERT(stk);
    #endif
    
}

void stack_push(stack *stk, double elem) {
    #if MODE != 1
        ASSERT(stk);
    #endif

    if (stk->size >= stk->capacity) stack_resize(stk);
    stk->data[stk->size] = elem;
    (stk->size)++;

    #if MODE != 1
        ASSERT(stk);
    #endif

}

void stack_resize(stack *stk) {
    #if MODE != 1
        ASSERT(stk);
    #endif

    to_dump(stk, logs_);

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }
    stk->data = (elem_stk_t *)realloc(stk->data, stk->capacity*sizeof(elem_stk_t));
    for (long unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = NAN;

    #if MODE != 1
        ASSERT(stk);
    #endif
}

void stack_pop(stack *stk, elem_stk_t *value) {
    #if MODE != 1
        ASSERT(stk);
    #endif

    *value = stk->data[stk->size];
    stk->size--;
    stk->data[stk->size] = NAN;
    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10) stack_resize(stk);
    
    #if MODE != 1
        ASSERT(stk);
    #endif
}




