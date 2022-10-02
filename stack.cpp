#include "stack.hpp"
#include "debug.hpp"
#include "utils.hpp"


static int file_status = FILE_CLOSE;
FILE *logs_;

#if MODE == CANARY_ON || MODE == HASH_CANARY_ON
    elem_stk_t *create_calloc_data(stack *stk) {

        unsigned long long *data = (unsigned long long *) calloc(1,(sizeof(unsigned long long) + sizeof(elem_stk_t)*stk->capacity + sizeof(unsigned long long)));
        
        data[0] = CANARIES_LEFT;
        data++;
        data[stk->capacity*sizeof(elem_stk_t)/sizeof(unsigned long long)] = CANARIES_RIGHT;

        return (elem_stk_t *)data;
    }
#endif

#if MODE != RELEASE
void fill_data(stack *stk) {
    *stk;
    for (unsigned i = stk->size; i < stk->capacity; i++) {
            stk->data[i] = POIZON;
    }
}
#endif
static void open_file() {

    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/stack/log.txt";
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";
    
    if (file_status == FILE_CLOSE) {
        logs_ = fopen(LOG_FILE, "w");
        assert(logs_ != nullptr && "coudn't open file");

        if (logs_ == nullptr)
            printf("Could not open file.\n");

        file_status = 1;
    } else if (file_status == FILE_CLOSE_ADD){
        logs_ = fopen(LOG_FILE, "a");
        assert(logs_ != nullptr && "coudn't open file");

        if (logs_ == nullptr)
            printf("Could not open file.\n");

        file_status = 1;
    }

}

#if MODE != RELEASE
void stack_ctor_(stack *stk, size_t capacity, const char *func, int line, const char *name_file) 
#else 
void stack_ctor_(stack *stk, size_t capacity) 
#endif
{
    
    #if MODE != RELEASE
    open_file();
    #endif

    #if MODE != RELEASE
        stk->info.LINE = line;
        stk->info.FUNC = func;
        stk->info.NAME_FILE = name_file; 
    #endif
    stk->capacity = capacity;


    #if MODE == HASH_CANARY_ON || MODE == CANARY_ON
        stk->data = create_calloc_data(stk);
        fill_data(stk);
    #else 
        stk->data = (elem_stk_t *) calloc(capacity + 1, sizeof(elem_stk_t));
    #endif
    
    stk->size = 0;

    #if MODE == HASH_CANARY_ON || MODE == CANARY_ON
        stk->canaries_left  = CANARIES_LEFT;
        stk->canaries_right = CANARIES_RIGHT;
    #endif

    #if MODE == HASH_CANARY_ON || MODE == HASH_ON
        stk->hash_stk  = hash_data(stk, sizeof(*stk));
        stk->hash_data = hash_data(stk->data, sizeof(*stk->data));
    #endif

    ASSERT(stk);
  
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

    #if MODE != RELEASE
        if (file_status == 1) {
            fclose(logs_);
            file_status = 2;
        }
    #endif

}

void stack_push(stack *stk, double elem) {

    ASSERT(stk);

    if (stk->size >= stk->capacity) 
        stack_resize(stk);
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

    #if MODE == RELEASE || MODE == HASH_ON
        stk->data = (elem_stk_t *) realloc(stk->data, stk->capacity * sizeof(elem_stk_t));
    #else  
        stk->data = stack_realloc_canari(stk);
        fill_data(stk);
    #endif

    
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




