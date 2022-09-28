#include "stack.hpp"
#include "error.hpp"
#include "utils.hpp"
#include <math.h>


// void create_data(stack *stk) {
//     stk->data = (elem_stk_t *) calloc(stk->capacity + 2, sizeof(elem_stk_t));
//     // stk->data[0] = CANARIES_LEFT;
//     // stk->data[stk->capacity] = CANARIES_RIGHT;
//     for (unsigned i = 0; i < stk->capacity; i++) {
//         stk->data[i] = NAN;
//     }
//     stk->size = 0;
//     ASSERT(stk);
//     // return 
// }
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
    #if MODE == 4 || MODE == 3
        if (stk->hash_stk == 0) {
            stk->hash_stk = hash_stack(stk, sizeof(*stk));
        }
        if (stk->hash_data == 0) {
            stk->hash_data = hash_data(stk->data, sizeof(*stk->data));
        }
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
    // stk->data[stk->capacity] = NAN;

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }
    stk->data = (elem_stk_t *)realloc(stk->data, stk->capacity*sizeof(elem_stk_t));
    // stk->data[0] = (unsigned long long ) calloc(1, sizeof(unsigned long long));
    // stk->data[0] = CANARIES_LEFT;
    // stk->data[stk->capacity-1] = (unsigned long long ) calloc(1, sizeof(unsigned long long));
    // stk->data[stk->capacity-1] = CANARIES_RIGHT;

    for (long unsigned i = stk->size; i < stk->capacity; i++)
        stk->data[i] = NAN;
    // stk->hash_data = hash_data(stk->data, sizeof(stk));
    stk->hash_data = hash_data(stk->data, sizeof(stk->data));

    fprintf(logs_, "HASH_DATA %llu\n", stk->hash_data);

        
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




