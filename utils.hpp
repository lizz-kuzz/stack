#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MODE 3 
#define MULTIPLE 2

#if MODE == 4 || MODE == 2
    #define CANARIES_LEFT  0xDEADF00D
    #define CANARIES_RIGHT 0xDEADBABE
#endif


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

enum DEBUG_MODE {
    RELIZE = 1,
    DEBUG_CANARIES = 2,
    DEBUG_HASH = 3,
    DEBUG_HASH_CANARIES = 4,
};

typedef struct {
    #if MODE == 4
        unsigned long long canaries_left;
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long hash_stk;
        unsigned long long hash_data;
        unsigned long long canaries_right;
    #elif MODE == 3
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long hash_stk;
        unsigned long long hash_data;
    #elif MODE == 2
        unsigned long long canaries_left;
        elem_stk_t         *data;
        size_t             size;
        size_t             capacity;
        stack_info         info;
        unsigned long long canaries_right;
    #elif MODE == 1
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
    ERROR_HASH_STK            = 5,
    ERROR_HASH_DATA           = 6,
    ERROR_CANARIES_STK        = 7,
    ERROR_CANARIES_DATA       = 8,
};


#endif