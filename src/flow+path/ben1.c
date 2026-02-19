#include "aliascheck.h"
void foo(int **s){
    
}
int main(){

    int* a;
    int* b;
    int**c;
    
    int x,y;

    int *w;
    int **s;
    int u;
    a=&x;
    b=&y;
    c=&a;
    s = c;
    s=&w;
    w=&u;
    u = 9;
    foo(s); 
    if(x==5){
    	**c = 10;
    }
    else{
	*b = 100;
    }

    while(u>10){
	*w = 100;
    }

/* AUTOGEN_ALIASCHECK */
MAYALIAS(a, &x);
MAYALIAS(b, &y);
MAYALIAS(c, &a);
MAYALIAS(s, &w);
NOALIAS(a, b);
/* END_AUTOGEN_ALIASCHECK */

    return 0;

}
