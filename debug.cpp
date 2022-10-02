#include "debug.hpp"


#if MODE == CANARY_ON || MODE == HASH_ON || MODE == HASH_CANARY_ON 
void to_dump (stack *stk, FILE *log, const char *func, int line, const char *name_file) {

    assert(log != nullptr && "coudn't open file");
    stk->info.LINE_CALL = line;
    stk->info.NAME_FILE_CALL = name_file;
    stk->info.FUNC_CALL = func;
    fprintf(log, "\n%s() at %s(%d)\n", stk->info.FUNC_CALL, stk->info.NAME_FILE_CALL, stk->info.LINE_CALL);
    fprintf(log, "Stack[%p] ", stk);

    if (stk->info.number_of_error == 0) {
        fprintf(log, "(ok) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, 
                                                         stk->info.FUNC, 
                                                         stk->info.NAME_FILE, 
                                                         stk->info.LINE);

        fprintf(log, "  size = %lu\n",      stk->size);
        fprintf(log, "  cappacity = %lu\n", stk->capacity);
        fprintf(log, "  data [%p]\n  {\n",    stk->data);

        for (unsigned i = 0; i < stk->capacity; i++) {
            if (isnan(stk->data[i])) {
                fprintf(log, "      *[%d] = %g (POIZON)\n", i, stk->data[i]);  
            } else {
                fprintf(log, "      *[%d] = %g\n",          i, stk->data[i]);
            }
        }
        fprintf(log, "  }\n");  
    } else {
        printf_errors(stk, log);
        fprintf(log, "  size = %lu\n",     stk->size);
        fprintf(log, "  capacity = %lu\n", stk->capacity);
        fprintf(log, "  data [%p]\n\n",    stk->data);
    }
}

void printf_error(stack *stk, FILE *log) {
    fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, 
                                                               stk->info.FUNC, 
                                                               stk->info.NAME_FILE, 
                                                               stk->info.LINE);
}

void printf_errors(stack *stk, FILE *log) {

    if (stk->info.number_of_error >> NULL_POINT_DATE & 1) {
        printf_error(stk, log);
        fprintf(log, "NULL POINER TO DATA\n");
    }

    if (stk->info.number_of_error >> SIZE_MORE_THAN_CAPACITY & 1) {
        printf_error(stk, log);
        fprintf(log, "SIZE MORE THAN CAPACITY\n");
    }

    if (stk->info.number_of_error >> SIZE_OR_CAPACITY_NEGATIVE & 1) {
        printf_error(stk, log);
        fprintf(log, "SIZE OR CAPACITY NEGATIVE\n");  
    } 

    #if MODE != CANARY_ON
        if (stk->info.number_of_error >> ERROR_HASH_STK & 1) {
            printf_error(stk, log);
            fprintf(log, "ERROR_HASH\n"); 
            fprintf(log, "HASH_STK %llu\n", stk->hash_stk); 
        }
        if (stk->info.number_of_error >> ERROR_HASH_DATA & 1) {
            printf_error(stk, log);
            fprintf(log, "ERROR_HASH\n"); 
            fprintf(log, "HASH_DATA %llu\n", stk->hash_data);
        }
    #endif

    #if MODE == CANARY_ON || MODE == HASH_CANARY_ON
        if (stk->info.number_of_error >> ERROR_CANARIES_STK & 1) {
            printf_error(stk, log);
            fprintf(log, "ERROR CANARIES IN STACK\n");
        }

        if (stk->info.number_of_error >> ERROR_CANARIES_DATA & 1) {
            printf_error(stk, log);
            fprintf(log, "ERROR CANARIES IN DATA\n");
        }
    #endif
}
#endif


void assert_ok(stack *stk) {

    #if MODE != RELEASE
        if (stk == nullptr) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << NULL_POINT_TO_STACK);
        }

        if (stk->data == nullptr) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << NULL_POINT_DATE);
        } 

        if (stk->size > stk->capacity) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << SIZE_MORE_THAN_CAPACITY);
        } 

        if (stk->size == -1 || stk->capacity == -1) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << SIZE_OR_CAPACITY_NEGATIVE);
        } 
    #endif

    #if MODE == HASH_CANARY_ON || MODE == HASH_ON
        if (stk->hash_stk != hash_data(stk, sizeof(*stk))) { 
            stk->info.number_of_error = stk->info.number_of_error | (1 << ERROR_HASH_STK);
        } 

        if (stk->hash_data != hash_data(stk->data, sizeof(*stk->data))) {       
            stk->info.number_of_error = stk->info.number_of_error | (1 << ERROR_HASH_DATA);
        }

    #endif

    #if MODE == HASH_CANARY_ON || MODE == CANARY_ON 
        if (stk->canaries_left != CANARIES_LEFT || stk->canaries_right != CANARIES_RIGHT) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << ERROR_CANARIES_STK);        
        }
        
        if (((elem_canary_t*)stk->data)[-1] != CANARIES_LEFT || ((elem_canary_t*)stk->data)[stk->capacity] != CANARIES_RIGHT) {
            stk->info.number_of_error = stk->info.number_of_error | (1 << ERROR_CANARIES_DATA);               
        } 
    #endif
    
}

unsigned long long hash_data(void *data, size_t SIZE) {
    unsigned long long hash_data = 0;
    
    for (unsigned i = 0; i < SIZE; i++) {
        hash_data += (unsigned long long )(data + i);
    }
    return hash_data;
}

