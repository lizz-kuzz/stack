#include "stack.hpp"
#include "debug.hpp"
#include "utils.hpp"

#if MODE == 2 || MODE == HASH_CANARY_ON
    elem_stk_t *create_calloc_data(stack *stk) {

        unsigned long long *data = (unsigned long long *) calloc(1,(sizeof(unsigned long long) + sizeof(elem_stk_t)*stk->capacity + sizeof(unsigned long long)));
        
        data[0] = CANARIES_LEFT;
        data++;
        data[stk->capacity*sizeof(elem_stk_t)/sizeof(unsigned long long)] = CANARIES_RIGHT;

        return (elem_stk_t *)data;
    }
#endif

void fill_data(stack *stk) {
    for (unsigned i = stk->size; i < stk->capacity; i++) {
            stk->data[i] = POIZON;
    }
}
#if MODE != RELIZE
void stack_ctor_(stack *stk, size_t capacity, const char *func, int line, const char *name_file) {

    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/stack/log.txt";
    
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";

    logs_ = fopen(LOG_FILE, "w");

    assert(logs_ != nullptr && "coudn't open file");

    if (logs_ == nullptr)
        printf("Could not open file.\n");

    stk->capacity = capacity;
    stk->info.LINE = line;
    stk->info.FUNC = func;
    stk->info.NAME_FILE = name_file; 

    #if MODE == HASH_CANARY_ON || MODE == CANARY_ON
        stk->data = create_calloc_data(stk);
    #else 
        stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));
    #endif
        stk->size = 0;
        fill_data(stk);

    #if MODE == HASH_CANARY_ON || MODE == CANARY_ON
        stk->canaries_left  = CANARIES_LEFT;
        stk->canaries_right = CANARIES_RIGHT;
    #endif

    #if MODE == HASH_CANARY_ON || MODE == HASH_ON
        if (stk->hash_stk == 0) {
            stk->hash_stk = hash_data  (stk, sizeof(*stk));
        }
        if (stk->hash_data == 0) {
            stk->hash_data = hash_data(stk->data, sizeof(*stk->data));
        }
    #endif

    ASSERT(stk);
  
}
#endif

void stack_ctor__(stack *stk, size_t capacity) {

    stk->capacity = capacity;

    stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));

    stk->size = 0;
    fill_data(stk);


}


void stack_dtor(stack *stk) {

    ASSERT(stk);

    #if MODE == CANARY_ON || MODE == HASH_CANARY_ON
        stk->data--;
    #endif

    free(stk->data);

    stk->data = nullptr;
    stk->capacity = -1;
    stk->size = -1;
    #if MODE != RELIZE
        fclose(logs_);
    #endif

}

void stack_push(stack *stk, double elem) {

    ASSERT(stk);

    if (stk->size >= stk->capacity) stack_resize(stk);
    stk->data[stk->size] = elem;
    (stk->size)++;

    ASSERT(stk);

}

#if MODE == CANARY_ON || MODE == HASH_CANARY_ON
    elem_stk_t *stack_realloc_canari(stack *stk) {

        elem_canary_t *data = (elem_canary_t *)stk->data;
        data--;

        data = (elem_canary_t *) realloc(data, sizeof(elem_stk_t)*stk->capacity + 
                                                    2*sizeof(elem_canary_t));

        data[0] = CANARIES_LEFT;
        data++;

        data[stk->capacity*sizeof(elem_stk_t)/sizeof(elem_canary_t)] = CANARIES_RIGHT;

        return (elem_stk_t *)data;
    }
#endif

void stack_resize(stack *stk) {

    ASSERT(stk);

    if (stk->capacity == stk->size) {
        stk->capacity *= MULTIPLE;
    } else if (stk->size + 1 == stk->capacity/MULTIPLE) {
        stk->capacity /= MULTIPLE; 
    }

    #if MODE == RELIZE || MODE == HASH_ON
        stk->data = (elem_stk_t *) realloc(stk->data, stk->capacity * sizeof(elem_stk_t));
    #else  
        stk->data = stack_realloc_canari(stk);
    #endif

    fill_data(stk);
    
    #if MODE == HASH_ON || MODE == HASH_CANARY_ON
        stk->hash_data = hash_data(stk->data, sizeof(*stk->data));
    #endif
        
    ASSERT(stk);
}

void stack_pop(stack *stk, elem_stk_t *value) {
    ASSERT(stk);

    *value = stk->data[stk->size];
    stk->size--;

    stk->data[stk->size] = NAN;
    if (stk->size + 1 == stk->capacity/MULTIPLE && stk->size >= 10) 
        stack_resize(stk);
    
    ASSERT(stk);

}




