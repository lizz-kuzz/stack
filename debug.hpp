#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include "utils.hpp"



#if MODE != RELIZE
    #define ASSERT(stk) stk->info.FUNC_CALL      = __FUNCTION__; \
                        stk->info.LINE_CALL      = __LINE__;     \
                        stk->info.NAME_FILE_CALL = __FILE__;     \
                        assert_ok(stk);                          \
                        to_dump(stk, logs_);
#else 
    #define ASSERT(stk)                     
#endif

extern FILE *logs_;

void to_dump      (stack *stk, FILE *log);
void printf_errors(stack *stk, FILE *log);
void assert_ok    (stack *stk);
void printf_error (stack *stk, FILE *log);

unsigned long long hash_data (void *data, size_t SIZE);

#endif