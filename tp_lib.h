#include <stdio.h>
#include <stdlib.h>
/* word node */
struct word_node {
    char word[50];
    struct word_node* next;
};

/* paragraph node */
struct paragraph_node {
    struct word_node* words;
    struct paragraph_node* next;
};
/* file node */
struct file_node {
    struct paragraph_node* paragraphs;
};
void allocate(word_node *p);
void FREE(word_node p);
void ass_val(word_node p,int v);
void ass_adr(word_node p,word_node q);
int value(word_node p);
word_node next(word_node p);

