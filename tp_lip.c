#include <stdio.h>
#include <stdlib.h>
#include "tp_lib.h"
void allocate(word_node *p){
*p= malloc(sizeof(cell));

}
/*..................................................................*/
void FREE(word_node p){
free(p);
}
/*..................................................................*/
void ass_val(word_node p,int v){
p->val=v;
}
/*..................................................................*/
void ass_adr(word_node p,pointer q){
p->addr=q;
}
/*..................................................................*/
int value(word_node p){
return p->val;
}
pointer next(word_node p){
return p->addr;
}
