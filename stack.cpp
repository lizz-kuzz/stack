#include "stack.hpp"
#include "debug.hpp"
#include "utils.hpp"

#if MODE == 2 || MODE == 4
    elem_stk_t *create_data(stack *stk) {

        unsigned long long *data = (unsigned long long *) calloc(1,(sizeof(unsigned long long) + sizeof(elem_stk_t)*stk->capacity + sizeof(unsigned long long)));
        data[0] = CANARIES_LEFT;
        data++;
        data[stk->capacity*sizeof(elem_stk_t)/sizeof(unsigned long long)] = CANARIES_RIGHT;
        return (elem_stk_t *)data;
    }
#endif

void stack_ctor_(stack *stk, size_t capacity) {
    stk->capacity = capacity;

    #if MODE == 4 || MODE == 2
        stk->data = create_data(stk);

        for (unsigned i = 0; i < stk->capacity; i++) {
            stk->data[i] = NAN;
        }
        stk->size = 0;
    #else 
        stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));
        for (unsigned i = 0; i < stk->capacity; i++) {
            stk->data[i] = NAN;
        }
        stk->size = 0;
    #endif

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

    #if MODE == 2 || MODE == 4
        stk->data--;
    #endif

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;

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
#if MODE == 2 || MODE == 4
    elem_stk_t *stack_realloc_canari(stack *stk) {

        unsigned long long *data = (unsigned long long *)stk->data;
        data--;

        data = (unsigned long long *) realloc(data, sizeof(unsigned long long) + 
                                                    sizeof(elem_stk_t)*stk->capacity + 
                                                    sizeof(unsigned long long));

        data[0] = CANARIES_LEFT;
        data++;

        data[stk->capacity*sizeof(elem_stk_t)/sizeof(unsigned long long)] = CANARIES_RIGHT;

        return (elem_stk_t *)data;
    }
#endif

void stack_resize(stack *stk) {
    #if MODE != 1
        ASSERT(stk);
    #endif

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }

    #if MODE == 1 || MODE == 3
        stk->data = (elem_stk_t *)realloc(stk->data, stk->capacity*sizeof(elem_stk_t));
        for (long unsigned i = stk->size; i < stk->capacity; i++)
            stk->data[i] = NAN;
    #else  
        stk->data = stack_realloc_canari(stk);
        for (long unsigned i = stk->size; i < stk->capacity; i++)
            stk->data[i] = NAN;
    #endif
    
    #if MODE == 3 || MODE == 4
        stk->hash_data = hash_data(stk->data, sizeof(*stk->data));
    #endif
        
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
    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10) 
        stack_resize(stk);
    
    #if MODE != 1
        ASSERT(stk);
    #endif
}




