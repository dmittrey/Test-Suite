/*
 * Pure PATH-SENSITIVE test:
 * path-sensitive -> PASS (NOALIAS holds on each path)
 * path-insensitive -> FAIL (merges paths, may-alias via &b)
 */
#include "aliascheck.h"

int main()
{
    int *p, *q;
    int a, b, c;

    if (c) {
        p = &a;
        q = &b;
    } else {
        p = &b;
        q = &c;
    }

    NOALIAS(p, q);
    return 0;
}
