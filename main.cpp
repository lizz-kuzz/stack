#include "utils.hpp"
#include "stack.hpp"
#include "debug.hpp"
#include "string.h"

int main() {

    stack stk1 = {};
    stack stk3 = {};

    stack_ctor(stk1, 5);

    for (int i = 1; i < 6; i++) {
        stack_push(&stk1, i);
    }
    char* lel =  "aboba";
    printf("%d hash \n", count_hash(lel, strlen(lel)));
    printf("%d hash \n", count_hash(lel, strlen(lel)));

    elem_stk_t value = 0;
    for (int i = 2; i > 0; i--) {
        stack_pop(&stk1, &value);
    }

    stack_dtor(&stk1);
}