#include "aliascheck.h"
int *p,a,b;
void foo(int* p){

    *p=100;

}
int main(){
    int *q,s,c,d;
    q = &s;
    p=q;
    if(a){
	p =&c;
    }
    else{
	p=&d;
    }
    *p = 100;
    foo(p);


/* AUTOGEN_ALIASCHECK */
MAYALIAS(q, &s);
MAYALIAS(p, &d);
NOALIAS(q, p);
/* END_AUTOGEN_ALIASCHECK */

    return 0;
}
