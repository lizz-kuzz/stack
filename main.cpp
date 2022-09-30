#include "utils.hpp"
#include "stack.hpp"
#include "debug.hpp"

FILE *logs_;

int main() {

    stack stk1 = {};

    stack_ctor(stk1, 5);

    for (int i = 1; i < 45; i++) {
        stack_push(&stk1, i);
    }

    elem_stk_t value = 0;
    for (int i = 40; i > 0; i--) {
        stack_pop(&stk1, &value);
    }

    stack_dtor(&stk1);
}