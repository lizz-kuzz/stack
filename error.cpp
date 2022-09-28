#include "error.hpp"


#if MODE == 2 || MODE == 3 || MODE == 4
void to_dump(stack *stk, FILE *log) {  
    assert(log != nullptr && "coudn't open file");

    fprintf(log, "\n%s() at %s(%d)\n", stk->info.FUNC_CALL, stk->info.NAME_FILE_CALL, stk->info.LINE_CALL);
    fprintf(log, "Stack[%p] ", stk);

    if (stk->info.number_of_error == 0) {
        fprintf(log, "(ok) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC ,stk->info.NAME_FILE, stk->info.LINE);
        fprintf(log, "size = %lu\n",      stk->size);
        fprintf(log, "cappacity = %lu\n", stk->capacity);
        fprintf(log, "data [%p]\n{\n",    stk->data);
        for (unsigned i = 0; i < stk->capacity; i++) {
            if (isnan(stk->data[i])) {
                fprintf(log, "*[%d] = %g (POIZON)\n", i, stk->data[i]);  
            } else {
                fprintf(log, "*[%d] = %g\n", i, stk->data[i]);
            }
        }
        fprintf(log, "}\n");  
    } else {
        printf_errors(stk, log);
        fprintf(log, "size = %lu\n",     stk->size);
        fprintf(log, "capacity = %lu\n", stk->capacity);
        fprintf(log, "data [%p]\n\n",   stk->data);
    }
}

void printf_errors(stack *stk, FILE *log) {

    if (stk->info.number_of_error >> NULL_POINT_DATE & 1) {
        fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
        fprintf(log, "NULL POINER TO DATA\n");
    }

    if (stk->info.number_of_error >> SIZE_MORE_THAN_CAPACITY & 1) {
        fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
        fprintf(log, "SIZE MORE THAN CAPACITY\n");
    }

    if (stk->info.number_of_error >> SIZE_OR_CAPACITY_NEGATIVE & 1) {
        fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
        fprintf(log, "SIZE OR CAPACITY NEGATIVE\n");  
    } 

    #if MODE != 2
        if (stk->info.number_of_error >> ERROR_HASH_STK & 1) {
            fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "ERROR_HASH\n"); 
            fprintf(log, "HASH_STK %llu\n", stk->hash_stk); 
        }
        if (stk->info.number_of_error >> ERROR_HASH_DATA & 1) {
            fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "ERROR_HASH\n"); 
            fprintf(log, "HASH_DATA %llu\n", stk->hash_data);
        }
    #endif
    #if MODE == 2 || MODE == 4
        if (stk->info.number_of_error >> ERROR_CANARIES_STK & 1) {
            fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "ERROR CANARIES IN STACK\n");
        }

        if (stk->info.number_of_error >> ERROR_CANARIES_DATA & 1) {
            fprintf(log, "(ERROR!!!) \"%s\" at %s() at %s(%d) \n", stk->info.NAME_STACK, stk->info.FUNC, stk->info.NAME_FILE, stk->info.LINE);
            fprintf(log, "ERROR CANARIES IN DATA\n");
        }
    #endif
}
#endif


void assert_ok(stack *stk) {

    int arr_degree_two[9] = {};
    for (int i = 0; i < 9; i++) {
        arr_degree_two[i] = pow(2, i);
    }

    #if MODE == 4
        if (stk == nullptr) {
            stk->info.number_of_error += arr_degree_two[NULL_POINT_TO_STACK];
        }
        if (stk->data == nullptr) {
            stk->info.number_of_error += arr_degree_two[NULL_POINT_DATE];
        } 

        if (stk->size > stk->capacity) {
            stk->info.number_of_error += arr_degree_two[SIZE_MORE_THAN_CAPACITY];
        } 

        if (stk->size == -1 || stk->capacity == -1) {
            stk->info.number_of_error += arr_degree_two[SIZE_OR_CAPACITY_NEGATIVE];
        } 

        if (stk->canaries_left != CANARIES_LEFT || stk->canaries_right != CANARIES_RIGHT) {
            stk->info.number_of_error += arr_degree_two[ERROR_CANARIES_STK];
        }
        
        if (((unsigned long long*)stk->data)[-1] != CANARIES_LEFT || ((unsigned long long*)stk->data)[stk->capacity] != CANARIES_RIGHT) {
            stk->info.number_of_error += arr_degree_two[ERROR_CANARIES_DATA]; 
        } 

        if (stk->hash_stk != hash_stack(stk, sizeof(*stk))) {       
            stk->info.number_of_error += arr_degree_two[ERROR_HASH_STK];
        } 

        if (stk->hash_data != hash_data(stk->data, sizeof(*stk->data))) {       
            stk->info.number_of_error += arr_degree_two[ERROR_HASH_DATA];
        }


    #elif MODE == 3
        if (stk == nullptr) {
            stk->info.number_of_error += NULL_POINT_TO_STACK;
        }
        
        if (stk->data == nullptr) {
            stk->info.number_of_error += arr_degree_two[NULL_POINT_DATE];
        } 

        if (stk->size > stk->capacity) {
            stk->info.number_of_error += arr_degree_two[SIZE_MORE_THAN_CAPACITY];
        } 

        if (stk->size == -1 || stk->capacity == -1) {
            stk->info.number_of_error += arr_degree_two[SIZE_OR_CAPACITY_NEGATIVE];
        } 

        if (stk->hash_stk != hash_stack(stk, sizeof(*stk))) {       
            stk->info.number_of_error += arr_degree_two[ERROR_HASH_STK];
        } 

        if (stk->hash_data != hash_data(stk->data, sizeof(*stk->data))) {       
            stk->info.number_of_error += arr_degree_two[ERROR_HASH_DATA];
        }
    #elif MODE == 2
        if (stk->data == nullptr) {
            stk->info.number_of_error += arr_degree_two[NULL_POINT_DATE];
        } 
        if (stk->size > stk->capacity) {
            stk->info.number_of_error += arr_degree_two[SIZE_MORE_THAN_CAPACITY];
        } 
        if (stk->size == -1 || stk->capacity == -1) {
            stk->info.number_of_error += arr_degree_two[SIZE_OR_CAPACITY_NEGATIVE];
        } 
        if (stk->canaries_left != CANARIES_LEFT || stk->canaries_right != CANARIES_RIGHT) {
            stk->info.number_of_error += arr_degree_two[ERROR_CANARIES_STK];
        } 

        if (((unsigned long long*)stk->data)[-1] != CANARIES_LEFT || ((unsigned long long*)stk->data)[stk->capacity] != CANARIES_RIGHT) {
            stk->info.number_of_error += arr_degree_two[ERROR_CANARIES_DATA]; 
        } 

    #endif
}

unsigned long long hash_stack(void *stk, size_t SIZE) {
    unsigned long long hash_stk = 0;
    
    for (unsigned i = 0; i < SIZE; i++) {
        hash_stk += (unsigned long long )(stk + i);
    }
    return hash_stk;
}

unsigned long long hash_data(void *data, size_t SIZE) {
    unsigned long long hash_data = 0;
    
    for (unsigned i = 0; i < SIZE; i++) {
        hash_data += (unsigned long long )(data + i);
    }
    return hash_data;
}



