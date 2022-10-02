#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define RELEASE        1 
#define CANARY_ON      2
#define HASH_ON        3
#define HASH_CANARY_ON 4

#define MODE           CANARY_ON
#define MULTIPLE       2


#if MODE == HASH_CANARY_ON || MODE == CANARY_ON
    #define CANARIES_LEFT  0xDEADF00D
    #define CANARIES_RIGHT 0xDEADBABE
#endif

#if MODE == HASH_CANARY_ON || MODE == CANARY_ON
    #define ON_CANARY(...) __VA_ARGS__
#else
    #define ON_CANARY(...)
#endif

#if MODE == HASH_CANARY_ON || MODE == HASH_ON
    #define ON_HASH(...) __VA_ARGS__
#else
    #define ON_HASH(...)
#endif

#if MODE != RELEASE
    #define ON_DEBUG_INFO(...) __VA_ARGS__
#else
    #define ON_DEBUG_INFO(...)
#endif


typedef unsigned long long elem_canary_t;
typedef double             elem_stk_t;
#define POIZON NAN

enum FILE_STATUS {
    FILE_CLOSE     = 0,
    FILE_OPEN      = 1,
    FILE_CLOSE_ADD = 2,
};



typedef struct {
    long int    number_of_error; //ошибки
// инфа о созданном стеке
    int         LINE;
    const char *FUNC; 
    const char *NAME_FILE;
    const char *NAME_STACK;
// инфа о месте где вызван dump
    int         LINE_CALL;
    const char *FUNC_CALL; 
    const char *NAME_FILE_CALL;
} stack_info;


typedef struct {
    ON_CANARY     (elem_canary_t canaries_left;)
    ON_DEBUG_INFO (stack_info info;)

    elem_stk_t         *data;
    size_t              size;
    size_t              capacity;

    ON_HASH       (unsigned long long hash_stk;)
    ON_HASH       (unsigned long long hash_data;)
    ON_CANARY     (elem_canary_t canaries_right;)
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