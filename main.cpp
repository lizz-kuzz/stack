#include "utils.hpp"
#include "stack.hpp"
#include "debug.hpp"
#include "string.h"

int main() {

    stack stk1 = {};

    stack_ctor(stk1, 5);

    for (int i = 1; i < 6; i++) {
        stack_push(&stk1, i);
    }

    // elem_data_t value = 0;
    for (int i = 5; i > 0; i--) {
        // stack_pop(&stk1, &value);
        printf("%g ", stack_pop(&stk1));
    }

    stack_dtor(&stk1);
}