#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "utils.hpp"

#define INFO_STK __FUNCTION__, __LINE__, __FILE__


#if MODE != RELEASE
    #define stack_ctor(stk, num) stk.info.NAME_STACK = #stk; \
                                 stack_ctor_(&stk, num, INFO_STK);
#else 
    #define stack_ctor(stk, num) stack_ctor_(&stk, num);
#endif


elem_stk_t *create_calloc_data  (stack *stk);

elem_stk_t *stack_realloc_canari(stack *stk);
#if MODE != RELEASE
void stack_ctor_ (stack *stk, size_t capacity,  const char *func, 
                                                int line, 
                                                const char *name_file);
#else
void stack_ctor_(stack *stk, size_t capacity);
#endif

void stack_push   (stack *stk, double elem);

void stack_dtor   (stack *stk);

void stack_resize (stack *stk);

void stack_pop    (stack *stk, elem_stk_t *value);

void fill_data    (stack *stk);

#endif