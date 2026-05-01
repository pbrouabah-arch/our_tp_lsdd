#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
void allocate(ptr_word *p) {
    *p = malloc(sizeof(word_node));
}

//-----------------------------------------------------------------------------
void FREE(ptr_word p) {
    free(p);
}

//--------------------------------------------------------
void ass_word(ptr_word p, char* v) {
    strcpy(p->word, v);
}
//-----------------------------------------------------------------------------
void ass_adr(ptr_word p, ptr_word q) {
    p->addr = q;
}

char* words(ptr_word p) {
    return p->word;
}
//--------------------------------------------------------------------------------
ptr_word next(ptr_word p) {
    return p->addr;
}

//---------------------------------------------------------------------------------------

void add_word(ptr_word *h, char* v) {
    ptr_word p = NULL, s = NULL, r = NULL;
    p = *h;

    while (p != NULL) {
        r = p;
        p = next(p);
    }

    allocate(&s);
    ass_word(s, v);
    ass_adr(s, NULL);

    if (r == NULL) {
        // list was empty: s becomes the head
        *h = s;
    } else {
        ass_adr(r, s);   // fixed: only call when r is not NULL
    }
}
//------------------------------------------------------------------------------

bool exists_word(ptr_word *h, char* v) {
    ptr_word p = *h;
    while (p != NULL) {
        if (strcmp(words(p), v) == 0)
            return true;
        p = next(p);
    }
    return false;
}
//----------------------------------------------------------------------------------------
void free_words(ptr_word h) {
    ptr_word p = h, q = NULL;
    while (p != NULL) {
        q = p;
        p = next(p);
        FREE(q);
    }
}
//------------------------------------------------------------------------------------------
void print_words(ptr_word h) {
    ptr_word p = h;
    while (p != NULL) {
        printf(" -> %s ", words(p));
        p = next(p);
    }
    printf("\n");
}

/* --------------------------------------------------------- */

void alloc_paragraph(ptr_paragraph *p) {   // fixed: was "all_paragraph" in .h
    *p = malloc(sizeof(paragraph_node));
    (*p)->words = NULL;
    (*p)->next  = NULL;
}
//---------------------------------------------------------------------------
void free_paragraph(ptr_paragraph p) {
    free(p);
}

void up_words(ptr_paragraph p, ptr_word w) {
    p->words = w;
}
//-----------------------------------------------------------------------------------------
void up_next_para(ptr_paragraph p, ptr_paragraph q) {
    p->next = q;
}

ptr_word return_words(ptr_paragraph p) {
    return p->words;
}
//--------------------------------------------------------------------------------------------
ptr_paragraph next_para(ptr_paragraph p) {
    return p->next;
}
//------------------------------------------------------------------------------------------

void add_paragraph(ptr_paragraph *head, ptr_word w) {
    ptr_paragraph new_para;
    alloc_paragraph(&new_para);
    up_words(new_para, w);

    if (*head == NULL) {
        *head = new_para;
        return;
    }

    ptr_paragraph curr = *head;
    while (next_para(curr) != NULL) {
        curr = next_para(curr);
    }

    up_next_para(curr, new_para);   
}
//--------------------------------------------------------------------
void print_paragraphs(ptr_paragraph head) {
    if (head == NULL) {
        printf("(there is no paragraph)\n");
        return;
    }

    ptr_paragraph curr_para = head;
    int para_number = 1;

    while (curr_para != NULL) {
        printf("*** Paragraphe %d ***\n", para_number);

        ptr_word curr_word = return_words(curr_para);
        while (curr_word != NULL) {
            printf("%s ", words(curr_word));      
            curr_word = next(curr_word);         
        }

        printf("\n\n");
        para_number++;
        curr_para = next_para(curr_para);
    }
}

//----------------------------------------------------------------------------------------------------
void free_paragraphs(ptr_paragraph head) {
    ptr_paragraph curr = head;
    ptr_paragraph temp = NULL;

    while (curr != NULL) {
        temp = curr;
        curr = next_para(curr);
        free_words(return_words(temp));  // free the words list inside first
        free_paragraph(temp);            // then free the paragraph node itself
    }
}
//-------------------------------------------------------------------------------------------------------
ptr_paragraph read_file(char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error: cannot open file '%s'\n", filename);
        return NULL;
    }

    ptr_paragraph head = NULL;
    ptr_word word_list = NULL;
    char line[1000];

    while (fgets(line, sizeof(line), f) != NULL) {

      
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            // empty line = end of a paragraph
            if (word_list != NULL) {
                add_paragraph(&head, word_list);
                word_list = NULL;  // reset for next paragraph
            }
        } else {
          
            char* token = strtok(line, " ");
            while (token != NULL) {
                add_word(&word_list, token);
                token = strtok(NULL, " ");
            }
        }
    }

   
    if (word_list != NULL) {
        add_paragraph(&head, word_list);
    }

    fclose(f);
    return head;
}
//---------------------------------------------------------------------------------------------------
void alloc_file(ptr_file *p) {
    *p = malloc(sizeof(file_node));
    (*p)->paragraphs = NULL;
    (*p)->next = NULL;
}

ptr_paragraph get_paragraphs(ptr_file p) {
    return p->paragraphs;
}

ptr_file next_file(ptr_file p) {
    return p->next;
}
//--------------------------------------------------------------------------------------------
// read N files and return a file list
ptr_file read_files(char* filenames[], int n) {
    ptr_file head = NULL;
    ptr_file tail = NULL;

    for (int i = 0; i < n; i++) {
        ptr_file new_file;
        alloc_file(&new_file);
        strcpy(new_file->filename, filenames[i]);
        new_file->paragraphs = read_file(filenames[i]);
        new_file->next = NULL;

        if (head == NULL) {
            head = new_file;
            tail = new_file;
        } else {
            tail->next = new_file;
            tail = new_file;
        }
    }
    return head;
}
//------------------------------------------------------------------------------------------
void print_files(ptr_file head) {
    ptr_file curr = head;
    int file_num = 1;
    while (curr != NULL) {
        printf("========== File %d: %s ==========\n", file_num, curr->filename);
        print_paragraphs(curr->paragraphs);
        file_num++;
        curr = next_file(curr);
    }
}
//-------------------------------------------------------------------
void free_files(ptr_file head) {
    ptr_file curr = head;
    ptr_file temp = NULL;
    while (curr != NULL) {
        temp = curr;
        curr = next_file(curr);
        free_paragraphs(temp->paragraphs);
        free(temp);
    }
}
