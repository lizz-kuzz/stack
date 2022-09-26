#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MULTIPLE 2

#define CANARIES_LEFT  0xDEADF00D
#define CANARIES_RIGHT 0xDEADBABE


#define DEBUG 4 //с чиселками работает а не с чиселками нет 

typedef double elem_stk_t;


typedef struct {
    long int   number_of_error; //ошибки
    // инфа о созданном стеке
    int        LINE;
    const char *FUNC; 
    const char *NAME_FILE;
    const char *NAME_STACK;
// инфа о месте где вызван dump
    int        LINE_CALL;
    const char *FUNC_CALL; 
    const char *NAME_FILE_CALL;
} stack_info;

enum DEBUG_ {
    RELIZE = 1,
    DEBUG_CANARIES = 2,
    DEBUG_HASH = 3,
    DEBUG_HASH_CANARIES = 4,
};

typedef struct {
    #if DEBUG == 4
        unsigned long long canaries_left;
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long hash;
        unsigned long long canaries_right;
    #elif DEBUG == 3
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long hash;
    #elif DEBUG == 2
        unsigned long long canaries_left;
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long canaries_right;
    #elif DEBUG == 1
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
    #endif
} stack;

enum ERRORS {
    NULL_POINT_TO_STACK       = 1,
    NULL_POINT_DATE           = 2,
    SIZE_MORE_THAN_CAPACITY   = 3,
    SIZE_OR_CAPACITY_NEGATIVE = 4, 
    ERROR_HASH                = 5,
    ERROR_CANARIES            = 6,
    ERROR_CANARIES_HASH       = 7,
    // канарейки в data
};


#endif