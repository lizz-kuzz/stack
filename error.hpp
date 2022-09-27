#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include "utils.hpp"
#if MODE != 1
    #define ASSERT(stk) stk->info.FUNC_CALL      = __FUNCTION__; \
                        stk->info.LINE_CALL      =  __LINE__;    \
                        stk->info.NAME_FILE_CALL = __FILE__;     \
                        assert_ok(stk);                          \
                        to_dump(stk, logs_);                        
#endif


void to_dump      (stack *stk, FILE *log);
void printf_errors(stack *stk, FILE *log);
void assert_ok    (stack *stk);
extern FILE *logs_;

unsigned long long hash_stack(void *stk, size_t SIZE);
unsigned long long hash_data (void *data, size_t SIZE);

#endif