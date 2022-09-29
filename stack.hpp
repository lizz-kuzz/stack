#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "utils.hpp"


#if MODE != 1
    #define stack_ctor(stk, num) stk.info.FUNC       = __FUNCTION__; \
                                 stk.info.LINE       = __LINE__;     \
                                 stk.info.NAME_FILE  = __FILE__;     \
                                 stk.info.NAME_STACK = #stk;         \
                                 stack_ctor_(&stk, num);
#else 
    #define stack_ctor(stk, num) stack_ctor_(&stk, num);
#endif


elem_stk_t *create_data         (stack *stk);

elem_stk_t *stack_realloc_canari(stack *stk);

void stack_ctor_  (stack *stk, size_t capasity);

void stack_push   (stack *stk, double elem);

void stack_dtor   (stack *stk);

void stack_resize (stack *stk);

void stack_pop    (stack *stk, elem_stk_t *value);

#endif