/*
 * Pure PATH-INSENSITIVE-friendly test:
 * path-insensitive -> PASS (merges paths => MAYALIAS)
 * path-sensitive  -> typically PASS as well (conservative)
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

    MAYALIAS(p, q);
    return 0;
}
