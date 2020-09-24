gcc -O2 -I. -I./yespower-1.0.1          \
    yespower-1.0.1/yespower-opt.c       \
    yespower-1.0.1/sha256.c             \
    singlehash.c                        \
    -o test
