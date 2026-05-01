#include <stdio.h>
#include <stdlib.h>


/* word node */
typedef struct word_node {
    char word[100];
    struct word_node* addr;   // 
} word_node;
typedef word_node* ptr_word;

/* paragraph node */
typedef struct paragraph_node {
    struct word_node* words;
    struct paragraph_node* next;
} paragraph_node;
typedef paragraph_node* ptr_paragraph;

/* file node */
typedef struct file_node {
    struct paragraph_node* paragraphs;
} file_node;

/* abstract machines of word */
void allocate(ptr_word *p);
void FREE(ptr_word p);
void ass_word(ptr_word p, char* v);
void ass_adr(ptr_word p, ptr_word q);
char* words(ptr_word p);
ptr_word next(ptr_word p);
void add_word(ptr_word *h, char* v);
bool exists_word(ptr_word *h, char* v);
void free_words(ptr_word h);
void print_words(ptr_word h);

/* abstract machines of paragraph */
void alloc_paragraph(ptr_paragraph *p);   // 
void free_paragraph(ptr_paragraph p);
void up_words(ptr_paragraph p, ptr_word w);
void up_next_para(ptr_paragraph p, ptr_paragraph q);
ptr_word return_words(ptr_paragraph p);
ptr_paragraph next_para(ptr_paragraph p);
void add_paragraph(ptr_paragraph *head, ptr_word w);
void print_paragraphs(ptr_paragraph head);

#endif

