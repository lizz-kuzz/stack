#include "stack.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <math.h>

// extern FILE *log = fopen("/mnt/c/Users/User/Desktop/programs/stack/log.txt", "w");


void stack_ctor(stack *stk, size_t capasity) {
    stk->capacity = capasity;
    stk->data = (elem_stk *)calloc(capasity + 1, sizeof(elem_stk));
    stk->size = 0;
    assert_ok(stk);

}

void stack_dtor(stack *stk) {
    assert_ok(stk);

    free(stk->data);
    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
    assert_ok(stk);

}

void stack_push(stack *stk, double elem) {
    assert_ok(stk);
    if (stk->size >= stk->capacity) stack_resize(stk);
    stk->data[stk->size] = elem;
    (stk->size)++;
    assert_ok(stk);

}

void stack_resize(stack *stk) {
    assert_ok(stk);

    if (stk->capacity == stk->size) {
        stk->capacity *= multiple;
    } else if (stk->size + 1 == stk->capacity/multiple) {
        stk->capacity /= multiple; 
    }
    stk->data = (elem_stk *)realloc(stk->data, stk->capacity*sizeof(elem_stk));
    for (long unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = NAN;

    assert_ok(stk);
}

void stack_pop(stack *stk, elem_stk *value) {
    assert_ok(stk);

    *value = stk->data[stk->size];
    stk->size--;
    stk->data[stk->size] = NAN;
    if (stk->size + 1 == stk->capacity/2 && stk->size >= 10) stack_resize(stk);

    assert_ok(stk);
}




