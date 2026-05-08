#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
#include <stdbool.h>
#include <ctype.h>

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
/*----------------------------------------------------------*/
void alloc_phrase(ptr_phrase *p) {
    *p = malloc(sizeof(phrase_node));
    (*p)->words = NULL;
    (*p)->next  = NULL;
}
/*----------------------------------------------------------*/
void free_phrase(ptr_phrase p) {
    free(p);
}
/*----------------------------------------------------------*/
void set_phrase_words(ptr_phrase p, ptr_word w) {
    p->words = w;
}
/*----------------------------------------------------------*/
void link_phrase(ptr_phrase p, ptr_phrase q) {
    p->next = q;
}
/*----------------------------------------------------------*/
ptr_word get_phrase_words(ptr_phrase p) {
    return p->words;
}
/*----------------------------------------------------------*/
ptr_phrase next_phrase(ptr_phrase p) {
    return p->next;
}
/*----------------------------------------------------------*/
void add_phrase(ptr_phrase *head, ptr_word w) {
    ptr_phrase new_phrase;
    alloc_phrase(&new_phrase);
    set_phrase_words(new_phrase, w);
    if (*head == NULL) {
        *head = new_phrase;
 return;
    }
    ptr_phrase curr = *head;
    while (next_phrase(curr) != NULL) {
        curr = next_phrase(curr);
    }
    link_phrase(curr, new_phrase);
}
/*----------------------------------------------------------*/
void print_phrases(ptr_phrase head) {
    ptr_phrase curr = head;
    int num = 1;
    while (curr != NULL) {
        printf("  phrase %d: ", num);
        ptr_word w = get_phrase_words(curr);
        while (w != NULL) {
            printf("%s ", words(w));
            w = next(w);
        }
        printf("\n");
        curr = next_phrase(curr);
        num++;
    }
}
/*----------------------------------------------------------*/
void free_phrases(ptr_phrase head) {
    ptr_phrase curr = head;
    ptr_phrase temp = NULL;
    while (curr != NULL) {
        temp = curr;
        curr = next_phrase(curr);
        free_words(get_phrase_words(temp));
        free_phrase(temp);
    }
}
/*----------------------------------------------------------*/

void alloc_paragraph(ptr_paragraph *p) {
    *p = malloc(sizeof(paragraph_node));
    (*p)->phrases = NULL;
    (*p)->next = NULL;
}
/*---------------------------------------------------------*/

void free_paragraph(ptr_paragraph p) {
    free(p);
}
/*---------------------------------------------------------*/
void set_phrases(ptr_paragraph p, ptr_phrase ph) {
    p->phrases = ph;
}
/*---------------------------------------------------------*/
void link_paragraph(ptr_paragraph p, ptr_paragraph q) {
    p->next = q;
}
/*---------------------------------------------------------*/
ptr_phrase get_phrases(ptr_paragraph p) {
    return p->phrases;
}
/*---------------------------------------------------------*/
ptr_paragraph next_para(ptr_paragraph p) {
    return p->next;
}
/*---------------------------------------------------------*/
void add_paragraph(ptr_paragraph *head, ptr_phrase ph) {
    ptr_paragraph new_para;
    alloc_paragraph(&new_para);
    set_phrases(new_para, ph);
    if (*head == NULL) {
        *head = new_para;
        return;
    }
    ptr_paragraph curr = *head;
    while (next_para(curr) != NULL) {
        curr = next_para(curr);
    }
    link_paragraph(curr, new_para);
}
/*---------------------------------------------------------*/
void print_paragraphs(ptr_paragraph head) {
    if (head == NULL) {
        printf("(no paragraphs)\n");
        return;
    }
    ptr_paragraph curr = head;
    int para_num = 1;
    while (curr != NULL) {
        printf("*** Paragraph %d ***\n", para_num);
        print_phrases(get_phrases(curr));
        printf("\n");
        para_num++;
        curr = next_para(curr);
    }
}
/*---------------------------------------------------------*/
void free_paragraphs(ptr_paragraph head) {
    ptr_paragraph curr = head;
    ptr_paragraph temp = NULL;
    while (curr != NULL) {
        temp = curr;
        curr = next_para(curr);
        free_phrases(get_phrases(temp));
        free_paragraph(temp);
    }
}
//-------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
bool equal_words(ptr_word a, ptr_word b) {
    while (a != NULL && b != NULL) {
        if (strcmp(words(a), words(b)) != 0)
            return false;
        a = next(a);
        b = next(b);
    }
    return a == NULL && b == NULL;
}
/*----------------------------------------------------------*/
bool equal_phrases(ptr_phrase a, ptr_phrase b) {
    while (a != NULL && b != NULL) {
        if (!equal_words(get_phrase_words(a), get_phrase_words(b)))
            return false;
        a = next_phrase(a);
        b = next_phrase(b);
    }
    return a == NULL && b == NULL;
}
/*------------------------------------------------------------------*/
bool exists_paragraph(ptr_paragraph head, ptr_paragraph q) {
    ptr_paragraph p = head;
    while (p != NULL) {
        if (equal_phrases(get_phrases(p), get_phrases(q)))
            return true;
        p = next_para(p);
    }
    return false;
}
/*----------------------------------------------------------*/
void set_filename(ptr_file p, char *name) {
    strcpy(p->filename, name);
}
/*----------------------------------------------------------*/
void set_file_paragraphs(ptr_file p, ptr_paragraph ph) {
    p->paragraphs = ph;
}
/*----------------------------------------------------------*/
void link_file(ptr_file p, ptr_file q) {
    p->next = q;
}
/*----------------------------------------------------------*/
char* get_filename(ptr_file p) {
    return p->filename;
}
/*----------------------------------------------------------*/
ptr_paragraph get_file_paragraphs(ptr_file p) {
    return p->paragraphs;
}
/*----------------------------------------------------------*/
void free_file(ptr_file p) {
    free(p);
}
/*----------------------------------------------------------*/
ptr_paragraph read_file(char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) { printf("Error: cannot open %s\n", filename); return NULL; }

    ptr_paragraph para_list = NULL;
    ptr_phrase current_phrases = NULL;
    char line[500];

    while (fgets(line, 500, f) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // remove newline

        if (strlen(line) == 0) {
            // empty line = end of paragraph
            if (current_phrases != NULL) {
                add_paragraph(&para_list, current_phrases);
                current_phrases = NULL;
            }
        } else {
            // build word list from line
            ptr_word word_head = NULL;
            char* token = strtok(line, " \t");
            while (token != NULL) {
                add_word(&word_head, token);
                token = strtok(NULL, " \t");
            }
            add_phrase(&current_phrases, word_head);
        }
    }

    if (current_phrases != NULL)
        add_paragraph(&para_list, current_phrases);

    fclose(f);
    return para_list;
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
        set_filename(new_file, filenames[i]);
        set_file_paragraphs(new_file, read_file(filenames[i]));
        link_file(new_file, NULL);

        if (head == NULL) { head = new_file; tail = new_file; }
        else { link_file(tail, new_file); tail = new_file; }
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
//------------------------------------------------------------------------------------------


/*--------------------------------------------------------------------*/
void set_union(ptr_paragraph headp, ptr_paragraph headq) {
    // print all paragraphs from P
    ptr_paragraph p = headp;
    while (p != NULL) {
        print_phrases(get_phrases(p));
        p = next_para(p);
    }
    // print only paragraphs from Q that are not in P
    ptr_paragraph q = headq;
    while (q != NULL) {
        if (!exists_paragraph(headp, q)) {
            print_phrases(get_phrases(q));
        }
        q = next_para(q);
    }
}
/*---------------------------------------------------------------------*/
void set_intersection(ptr_paragraph headp, ptr_paragraph headq) {
    // print only paragraphs that exist in both
    ptr_paragraph q = headq;
    while (q != NULL) {
        if (exists_paragraph(headp, q)) {
            print_phrases(get_phrases(q));
        }
        q = next_para(q);
    }
}

/*------------------------------------------------------------------------*/
void set_difference(ptr_paragraph headp, ptr_paragraph headq) {
    // print only paragraphs from P that are NOT in Q
    ptr_paragraph p = headp;
    while (p != NULL) {
        if (!exists_paragraph(headq, p)) {
            print_phrases(get_phrases(p));
        }
        p = next_para(p);
    }
}
/*-------------------------------------------------------------------------*/
/*----------------others---------------------------------------------------*/
void upper_word(char* word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        word[i] = toupper(word[i]);
    }
}
/*----------------------------------------------------------*/
void upper_paragraph(ptr_paragraph head) {
    ptr_paragraph cur_para = head;
    while (cur_para != NULL) {
        ptr_phrase cur_phrase = get_phrases(cur_para);
        while (cur_phrase != NULL) {
            ptr_word cur_word = get_phrase_words(cur_phrase);
            while (cur_word != NULL) {
                upper_word(words(cur_word));
                cur_word = next(cur_word);
            }
            cur_phrase = next_phrase(cur_phrase);
        }
        cur_para = next_para(cur_para);
    }
}
/*--------------------------------------------------------------*/
void clean_word(char* word) {
    int len = strlen(word);
    int j = 0;
    char cleaned[100];

    for (int i = 0; i < len; i++) {
        // keep only letters, digits, and periods
        if (isalpha(word[i]) || isdigit(word[i]) || word[i] == '.') {
            cleaned[j] = word[i];
            j++;
        }
    }
    cleaned[j] = '\0';
    strcpy(word, cleaned);
}
/*----------------------------------------------------------*/
void clean_paragraph(ptr_paragraph head) {
    ptr_paragraph cur_para = head;
    while (cur_para != NULL) {
        ptr_phrase cur_phrase = get_phrases(cur_para);
        while (cur_phrase != NULL) {
            ptr_word cur_word = get_phrase_words(cur_phrase);
            while (cur_word != NULL) {
                clean_word(words(cur_word));
                cur_word = next(cur_word);
            }
            cur_phrase = next_phrase(cur_phrase);
        }
        cur_para = next_para(cur_para);
    }
}
