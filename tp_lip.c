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
/*..................................................................*/
ptr_word next(ptr_word p){
return p->addr;
}
/*..................................................................*/
char* words(ptr_word p){
return p->word;
}
/*..................................................................*/
ptr_word next(ptr_word p){
return p->addr;}
/*..................................................................*/
void add_word(ptr_word *h,char* v){
    ptr_word p=NULL;ptr_word s=NULL;ptr_word r=NULL;
    p=*h;
    while(p!= NULL){r=p;
            p=next(p);}
    allocate(&s);
    ass_word(s,v);
    ass_adr(r,s);
    ass_adr(s,NULL);
}
/*...................................................................*/

bool exists_word(ptr_word *h, char* v){
    ptr_word p = *h;

    while(p != NULL){
        if(strcmp(words(p), v) == 0){
            return 1;
        }
        p = next(p);
    }

    return 0;}
/*..................................................................*/
void free_words(ptr_word h){
    ptr_word p = h;ptr_word q=NULL;
while(p != NULL){q=p;p=next(p);FREE(q);}

}
/*...................................................................*/
void print_words(ptr_word h){
ptr_word p=h;
while(p != NULL){printf(" -> %s ",words(p) );p=next(p);}
printf("\n");
}
/*-------------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------------*/
/*.................................................................*/
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
