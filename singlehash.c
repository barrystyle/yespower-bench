#include "yespower-1.0.1/yespower.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//! for timer
struct timespec before, after;
long elapsed_nsecs;

void yespower_sugarhash(const void* input, void* output, int len)
{
    static const yespower_params_t params = {
        .version = YESPOWER_1_0,
        .N = 2048,
        .r = 32,
        .pers = (const uint8_t*)"Satoshi Nakamoto 31/Oct/2008 Proof-of-work is essentially one-CPU-one-vote",
        .perslen = 74
    };
    yespower_tls(input, len, &params, &output);
}

void hash_timerloop()
{
    char *blkheader = (char*)malloc(80);
    char *outhash = (char*)malloc(32);
    memset(blkheader,0,80);
    memset(outhash,0,32);
    unsigned int hashCount = 0;

    clock_gettime(CLOCK_REALTIME, &before);           //! start
    while ((hashCount++)<0x400) {
        yespower_sugarhash(blkheader, outhash, 80);
    }
    clock_gettime(CLOCK_REALTIME, &after);            //! stop
    elapsed_nsecs = (after.tv_sec - before.tv_sec) * 1000000000 + (after.tv_nsec - before.tv_nsec);

    printf("1024 hashes took %lld ms\n", elapsed_nsecs / 1000000);
}

int main()
{
    hash_timerloop();
    return 0;
}
