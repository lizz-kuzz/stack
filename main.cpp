#include "utils.hpp"
#include "stack.hpp"
#include "error.hpp"

#include <stdio.h>
#include <assert.h>

FILE *logs_;
//  понять что делает # ## этапы компиляции предпроцессор 

int main() {
    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/stack/log.txt";
    
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";

    logs_ = fopen(LOG_FILE, "w");

    assert(logs_ != nullptr && "coudn't open file");

    if (logs_ == nullptr)
        printf("Could not open file.\n");

    stack stk1 = {
        .data = nullptr,
        .size = 0,
        .capacity = 0,
        .info = { 
            0, 
            __LINE__, 
            __FUNCTION__, 
            __FILE__, 
        },
    };

    stack_ctor(&stk1, 10);
    // to_dump(&stk1, logs_);
    for (int i = 1; i <= 40; i++) {
        stack_push(&stk1, i);
        // to_dump(&stk1, logs_);
    }

    elem_stk_t value = 0;

    for (int i = 40; i > 0; i--) {
        stack_pop(&stk1, &value);
        // to_dump(&stk1, logs_);
    }
    stack_dtor(&stk1);

    fclose(logs_);

}