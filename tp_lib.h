#ifndef TP_H
#define TP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* word node */
typedef struct word_node {
    char word[100];
    struct word_node* addr;
} word_node;
typedef word_node* ptr_word;

/* phrase node */
typedef struct phrase_node {
    char phrase[500];           
    struct phrase_node* next;
} phrase_node;
typedef phrase_node* ptr_phrase;
/* paragraph node */
typedef struct paragraph_node {
    struct phrase_node* phrases; 
    struct paragraph_node* next;
} paragraph_node;
typedef paragraph_node* ptr_paragraph;
/* file node */
typedef struct file_node {
    char filename[100];
    ptr_paragraph paragraphs;
    struct file_node* next;
} file_node;
typedef file_node* ptr_file;

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
/* abstract machines of phrase */
void alloc_phrase(ptr_phrase *p);
void free_phrase(ptr_phrase p);
void set_phrase(ptr_phrase p, char* s);
void link_phrase(ptr_phrase p, ptr_phrase q);
char* get_phrase(ptr_phrase p);
ptr_phrase next_phrase(ptr_phrase p);
void add_phrase(ptr_phrase *head, char* s);
void print_phrases(ptr_phrase head);
void free_phrases(ptr_phrase head);
bool exists_phrase(ptr_phrase head, char* s);
/* abstract machines of paragraph */

void alloc_paragraph(ptr_paragraph *p);
void free_paragraph(ptr_paragraph p);
void set_phrases(ptr_paragraph p, ptr_phrase ph);
void link_paragraph(ptr_paragraph p, ptr_paragraph q);
ptr_phrase get_phrases(ptr_paragraph p);
ptr_paragraph next_para(ptr_paragraph p);
void add_paragraph(ptr_paragraph *head, ptr_phrase ph);
void print_paragraphs(ptr_paragraph head);
void free_paragraphs(ptr_paragraph head);
ptr_paragraph read_file(char* filename);
/* abstract machines of file */
void alloc_file(ptr_file *p);
void free_file(ptr_file p);
ptr_paragraph get_paragraphs(ptr_file p);
ptr_file next_file(ptr_file p);
ptr_file read_files(char* filenames[], int n);
void print_files(ptr_file head);
void free_files(ptr_file head);

#endif
