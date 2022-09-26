#include "utils.hpp"
#include "stack.hpp"
#include "error.hpp"

#include <stdio.h>
#include <assert.h>



FILE *logs_;
//  понять что делает # ## этапы компиляции предпроцессор 

// 1 этап условной компиляции вызвать разные структуры для разных модов
// сделать конструктор расширенный

int main() {
    const char *LOG_FILE = "/mnt/c/Users/User/Desktop/programs/stack/log.txt";
    
    // const char *LOG_FILE = "C://Users//User//Desktop//programs//stack//log.txt";

    logs_ = fopen(LOG_FILE, "w");

    assert(logs_ != nullptr && "coudn't open file");

    if (logs_ == nullptr)
        printf("Could not open file.\n");

    stack stk1 = {};

    stack_ctor(stk1, 10);
    to_dump(&stk1, logs_);
    for (int i = 1; i <= 40; i++) {
        stack_push(&stk1, i);
    }

    elem_stk_t value = 0;

    for (int i = 40; i > 0; i--) {
        stack_pop(&stk1, &value);
    }
    stack_dtor(&stk1);

    fclose(logs_);

}