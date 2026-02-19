/*
 * Cycle (with an optional branch that can redirect y1)
 * Author: Sen Ye
 * Date: 11/10/2013
 *
 * What this test stresses:
 *  - Indirect assignments through pointers-to-pointers (x1,y1,z1).
 *  - Flow-sensitivity: the cycle is formed by the specific order of
 *      *x1 = *y1;
 *      *y1 = *z1;
 *      *z1 = *x1;
 *  - Path-sensitivity: the optional branch may change what y1 points to
 *    (either &y2 or &y2_), which affects which aliases can be derived.
 *
 * High-level picture:
 *  x2,y2,z2 are int* variables; x1,y1,z1 are int** pointing to them.
 *  After the three indirect assignments, there should be an alias cycle
 *    among the int* variables:
 *      y2 -> x2 -> z2 -> y2
 *  Hence:
 *      MAYALIAS(x2, y2);
 *      MAYALIAS(z2, x2);
 */
#include "aliascheck.h"

int main() {
    int **x1, **y1, **z1;          // pointers to pointer variables (int**)
    int *x2, *y2, *z2, *y2_;       // pointer variables (int*)
    int x3, y3, z3, y3_;           // pointees (int values)

    // Initialize x2,y2,z2 to point to distinct integers.
    x2 = &x3; y2 = &y3; z2 = &z3;

    // x1,y1,z1 point to the pointer variables x2,y2,z2.
    x1 = &x2; y1 = &y2; z1 = &z2;

    // Optional path: redirect y1 to a different pointer variable y2_.
    // If taken, y1 no longer points to y2 but to y2_, and y2_ points to y3_.
    if (y3_) {
        y1  = &y2_;
        y2_ = &y3_;
    }

    // Indirect assignments that can create a cycle among x2,y2,z2:
    // 1) copy the pointer stored in *y1 into *x1   => x2 = (y2 or y2_)
    *x1 = *y1;
    // 2) copy the pointer stored in *z1 into *y1   => (y2 or y2_) = z2
    *y1 = *z1;
    // 3) copy the pointer stored in *x1 into *z1   => z2 = x2
    *z1 = *x1;

    // Expected: a cycle y2 -> x2 -> z2 -> y2 (at least as MAY-alias),
    // so x2 may alias y2 and z2 may alias x2.
    MAYALIAS(x2, y2);
    MAYALIAS(z2, x2);

    return 0;
}
