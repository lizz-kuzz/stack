#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "utils.hpp"

#define stack_ctor(stk, num) stk.info.FUNC =       __FUNCTION__; \
                             stk.info.LINE =       __LINE__;     \
                             stk.info.NAME_FILE =  __FILE__;     \
                             stk.info.NAME_STACK = #stk;     \
                             stack_ctor_(&stk, num);

void stack_ctor_(stack *stk, size_t capasity);

void stack_push(stack *stk, double elem);

void stack_dtor(stack *stk);

void stack_resize(stack *stk);

void stack_pop(stack *stk, elem_stk_t *value);

#endif