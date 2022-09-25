#include "error.hpp"

// extern FILE *log = fopen("/mnt/c/Users/User/Desktop/programs/stack/log.txt", "w");

void to_dump(stack *stk, FILE *log) {  
    // как сделать макросом?
    assert(log != nullptr && "coudn't open file");
    assert(stk != nullptr && "coudn't open file");

    stk->info.FUNC_CALL =      __FUNCTION__;
    stk->info.LINE_CALL =      __LINE__;
    stk->info.NAME_FILE_CALL = __FILE__;

    fprintf(log, "\n%s() at %s(%d)\n", stk->info.FUNC_CALL, stk->info.NAME_FILE_CALL, stk->info.LINE_CALL);
    fprintf(log, "Stack[%p] ", stk);

    if (stk->info.number_of_error == 0) {
        fprintf(log, "(ok) \"stk1\" at %s() at %s(%d) \n", stk->info.FUNC ,stk->info.NAME_FILE, stk->info.LINE);
        fprintf(log, "size = %lu\n",      stk->size);
        fprintf(log, "cappacity = %lu\n", stk->capacity);
        fprintf(log, "data [%p]\n{\n",    stk->data);
        for (unsigned i = 0; i < stk->capacity; i++) {
            if (stk->data[i] == NAN) {
                fprintf(log, "*[%d] = %g (POIZON)\n", i, stk->data[i]);  
            } else {
                fprintf(log, "*[%d] = %g\n", i, stk->data[i]);
            }
        }
        fprintf(log, "}\n");  
    } else {
        if (stk->info.number_of_error == NULL_POINT_DATE) {
            fprintf(log, "(ERROR!!!) \"stk1\" at %s() at %s(%d) \n", stk->info.FUNC ,stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "NULL POINER TO DATA\n");
        } else if (stk->info.number_of_error == SIZE_MORE_THAN_CAPACITY) {
            fprintf(log, "(ERROR!!!) \"stk1\" at %s() at %s(%d) \n", stk->info.FUNC ,stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "SIZE MORE THAN CAPACITY\n");
        } else if (stk->info.number_of_error == SIZE_OR_CAPACITY_NEGATIVE) {
            fprintf(log, "(ERROR!!!) \"stk1\" at %s() at %s(%d) \n", stk->info.FUNC ,stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "SIZE OR CAPACITY NEGATIVE\n");    
        }
            fprintf(log, "size = %lu\n",     stk->size);
            fprintf(log, "capacity = %lu\n", stk->capacity);
            fprintf(log, "data [%p]\n{\n",   stk->data);
    }
}

void assert_ok(stack *stk) {
    assert(stk != nullptr && "null pointer");

    if (stk->data == NULL) {
        stk->info.number_of_error = NULL_POINT_DATE;
    } else if (stk->size > stk->capacity) {
        stk->info.number_of_error = SIZE_MORE_THAN_CAPACITY;
    } else if (stk->size == -1 || stk->capacity == -1) {
        stk->info.number_of_error = SIZE_OR_CAPACITY_NEGATIVE;
    }
}