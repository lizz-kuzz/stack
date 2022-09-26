#include <stdio.h>
    enum DEBUG_MODE {
        FULL_DEBUG = 0,
        RELIZE = 1,
        LOL = 2
    };

#define debug LOL
int main() {


#if debug == 0
    printf("ffff\n");
#elif debug == 1
    printf("ssss\n");
#elif debug == 2 
    printf("lol\n");
#else 
    printf("no");
#endif



}