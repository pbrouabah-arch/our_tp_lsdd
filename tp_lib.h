#include <stdio.h>
#include <stdlib.h>
/* word node */
typedef struct word_node {
    char word[100];
    struct word_node* next;
}word_node;
typedef word_node * ptr_word;

/* paragraph node */
typedef struct paragraph_node {
    struct word_node* words;
    struct paragraph_node* next;
}paragraph_node;
typedef paragraph_node * ptr_paragraph;
/* file node */
typedef struct file_node {
    struct paragraph_node* paragraphs;
}file_node;
/*abstract machines of word*/
void allocate(ptr_word *p);
void FREE(ptr_word p);
void ass_val(ptr_word p,char* v);
void ass_adr(ptr_word p,ptr_word q);
char* words(ptr_word p);
ptr_word next(ptr_word p);
/*abstract machines of paragraph*/ 
void all_paragraph( ptr_paragraph *p) ;
void free_paragraph(ptr_paragraph p); 
void set_words(ptr_paragraph p, ptr_word w);  
void set_next_para(ptr_paragraph p, ptr_paragraph q); // relie 2 paragraph 
ptr_word get_words(ptr_paragraph p);   // recupere la liste des mots de paragraph
ptr_paragraph next_para(ptr_paragraph p);  // move to the next p


