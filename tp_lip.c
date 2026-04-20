#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
void allocate(ptr_word *p){
*p= malloc(sizeof(word_node));

}
/*..................................................................*/
void FREE(ptr_word p){
free(p);
}
/*..................................................................*/
void ass_word(ptr_word p,char* v){
strcpy(p->word, v);
}
/*..................................................................*/
void ass_adr(ptr_word p,ptr_word q){
p->addr=q;
}
/*..................................................................*/
char* words(ptr_word p){
return p->word;
}
ptr_word next(ptr_word p){
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
void up_words(ptr_paragraph p, ptr_word w) {
    p->words = w;
}
/*.....................................................................................*/
void up_next_para(ptr_paragraph p, ptr_paragraph q) {
    p->next = q;
}
/*............................................................................................*/
ptr_word return_words(ptr_paragraph p) {
    return p->words;
}
/*.............................................................................................*/
ptr_paragraph next_para(ptr_paragraph p) {
    return p->next;
}
