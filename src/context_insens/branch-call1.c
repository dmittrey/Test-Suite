/*
 * Pure context-INSENSITIVE-friendly test:
 * Here aliasing is real in the only call context, so MAYALIAS must hold.
 * context-insensitive -> PASS
 * context-sensitive  -> PASS (too; alias is genuine)
 */
#include "aliascheck.h"

void foo(int *m, int *n)
{
    MAYALIAS(m, n);   // в этом тесте это истинно
    int x = *n;
    int y = *m;
    *m = x;
    *n = y;
}

int main()
{
    int a;
    int *p = &a;

    foo(p, p);  // single context: m==n==&a, алиас точно есть

    return 0;
}
