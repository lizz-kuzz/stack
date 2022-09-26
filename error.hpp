#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include "utils.hpp"


void to_dump  (stack *stk, FILE *log);
void assert_ok(stack *stk);
extern FILE *logs_;

#endif