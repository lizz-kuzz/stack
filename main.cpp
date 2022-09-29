#include "utils.hpp"
#include "stack.hpp"
#include "debug.hpp"

FILE *logs_;

int main() {
    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/stack/log.txt";
    
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";

    logs_ = fopen(LOG_FILE, "w");

    assert(logs_ != nullptr && "coudn't open file");

    if (logs_ == nullptr)
        printf("Could not open file.\n");

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

    fclose(logs_);
}