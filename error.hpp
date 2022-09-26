#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include "utils.hpp"
#define ASSERT(stk) stk->info.FUNC_CALL =      __FUNCTION__; \
                    stk->info.LINE_CALL =      __LINE__;     \
                    stk->info.NAME_FILE_CALL = __FILE__;     \
                    assert_ok(stk);

void to_dump  (stack *stk, FILE *log);
void assert_ok(stack *stk);

#endif