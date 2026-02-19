#include "aliascheck.h"
typedef struct{
    int f1, f2;
}FOO;

int *z;

void f(int*x, FOO*y);

int main(){
    FOO *a,b;
    int *c;

    a=&b;
    c=&b.f1;
    f(a,c);

}

void f(int *x, FOO*y){
    z = &(y->f2);
    
}

/* AUTOGEN_ALIASCHECK */
MAYALIAS(a, &b);
/* END_AUTOGEN_ALIASCHECK */

