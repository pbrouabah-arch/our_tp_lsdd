#include <stdio.h>
#include <stdlib.h>
#include "tp_lib.h"
void allocate(word_node *p){
*p= malloc(sizeof(word_node));

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
/*..........................................................*/
void alloc_paragraph(ptr_paragraph *p) {
    *p = malloc(sizeof(paragraph_node));
    (*p)->words = NULL;
    (*p)->next  = NULL;
}
/*......................................................................*/
void free_paragraph(ptr_paragraph p) {
    free(p);
}
/*...........................................................................................*/
void set_words(ptr_paragraph p, ptr_word w) {
    p->words = w;
}
/*.....................................................................................*/
void set_next_para(ptr_paragraph p, ptr_paragraph q) {
    p->next = q;
}
/*............................................................................................*/
ptr_word get_words(ptr_paragraph p) {
    return p->words;
}
/*.............................................................................................*/
ptr_paragraph next_para(ptr_paragraph p) {
    return p->next;
}
