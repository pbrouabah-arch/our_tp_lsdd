#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
#include <stdbool.h>
#include <ctype.h>

/* Allocates memory for a new word node and stores its address in *p */
void allocate(ptr_word *p) {
    *p = malloc(sizeof(word_node));
}
//----------------------------------------------------------------------------------
/* Frees the memory of a single word node */
void FREE(ptr_word p) {
    free(p);
}
//-------------------------------------------------------------------------------------
/* Copies string v into the word field of node p */
void ass_word(ptr_word p, char* v) {
    strcpy(p->word, v);
}
//----------------------------------------------------------------------------------------------
/* Sets the next pointer of node p to point to node q */
void ass_adr(ptr_word p, ptr_word q) {
    p->addr = q;
}
//-------------------------------------------------------------------------------------
/* Returns the word string stored in node p */
char* words(ptr_word p) {
    return p->word;
}
//----------------------------------------------------------------------
/* Returns the next word node after p */
ptr_word next(ptr_word p) {
    return p->addr;
}
//----------------------------------------------------------------------------------------
/* Appends a new word node with value v at the end of the word list *h */
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
        *h = s;      /* list was empty: s becomes the head */
    } else {
        ass_adr(r, s);
    }
}
//--------------------------------------------------------------------------------------------------
/* Returns true if word v exists in the word list *h, false otherwise */
bool exists_word(ptr_word *h, char* v) {
    ptr_word p = *h;
    while (p != NULL) {
        if (strcmp(words(p), v) == 0)
            return true;
        p = next(p);
    }
    return false;
}
//-------------------------------------------------------------------------------------------------------
/* Frees all nodes in the word list starting at h */
void free_words(ptr_word h) {
    ptr_word p = h, q = NULL;
    while (p != NULL) {
        q = p;
        p = next(p);
        FREE(q);
    }
}
//---------------------------------------------------------------------------------------------------------
/* Prints all words in the list separated by " -> " */
void print_words(ptr_word h) {
    ptr_word p = h;
    while (p != NULL) {
        printf(" -> %s ", words(p));
        p = next(p);
    }
    printf("\n");
}
//----------------------------------------------------------------------------------------------------
/* Allocates a new phrase node and initializes its fields to NULL */
void alloc_phrase(ptr_phrase *p) {
    *p = malloc(sizeof(phrase_node));
    (*p)->words = NULL;
    (*p)->next  = NULL;
}
//-----------------------------------------------------------------------------------------------------
/* Frees the memory of a single phrase node (not its word list) */
void free_phrase(ptr_phrase p) {
    free(p);
}
//---------------------------------------------------------------------------------------------
/* Sets the word list of phrase p to w */
void set_phrase_words(ptr_phrase p, ptr_word w) {
    p->words = w;
}
//---------------------------------------------------------------------------------------------------------------
/* Links phrase p to phrase q (p->next = q) */
void link_phrase(ptr_phrase p, ptr_phrase q) {
    p->next = q;
}
//----------------------------------------------------------------------------------------------------------------------
/* Returns the word list of phrase p */
ptr_word get_phrase_words(ptr_phrase p) {
    return p->words;
}
//----------------------------------------------------------------------------------------------------------------------------
/* Returns the next phrase after p */
ptr_phrase next_phrase(ptr_phrase p) {
    return p->next;
}
//------------------------------------------------------------------------------------------------------------------------
/* Appends a new phrase node containing word list w at the end of *head */
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
//----------------------------------------------------------------------------------------------------------------------------
/* Prints all phrases in the list with numbering, and the words in each phrase */
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
//-------------------------------------------------------------------------------------------------------------------------------------
/* Frees all phrase nodes and their associated word lists */
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
//--------------------------------------------------------------------------------------------------------------------------
/* Allocates a new paragraph node and initializes its fields to NULL */
void alloc_paragraph(ptr_paragraph *p) {
    *p = malloc(sizeof(paragraph_node));
    (*p)->phrases = NULL;
    (*p)->next = NULL;
}
//-------------------------------------------------------------------------------------------------------------------------
/* Frees the memory of a single paragraph node (not its phrase list) */
void free_paragraph(ptr_paragraph p) {
    free(p);
}
//--------------------------------------------------------------------------------------------------------------------
/* Sets the phrase list of paragraph p to ph */
void set_phrases(ptr_paragraph p, ptr_phrase ph) {
    p->phrases = ph;
}
//-----------------------------------------------------------------------------------------------------

/* Links paragraph p to paragraph q (p->next = q) */
void link_paragraph(ptr_paragraph p, ptr_paragraph q) {
    p->next = q;
}
//---------------------------------------------------------------------------------------------------------

/* Returns the phrase list of paragraph p */
ptr_phrase get_phrases(ptr_paragraph p) {
    return p->phrases;
}
//-------------------------------------------------------------------------------------------------------------

/* Returns the next paragraph after p */
ptr_paragraph next_para(ptr_paragraph p) {
    return p->next;
}
//---------------------------------------------------------------------------------------------------------

/* Appends a new paragraph node containing phrase list ph at the end of *head */
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
//------------------------------------------------------------------------------------------

/* Prints all paragraphs with numbering and their phrases */
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
//-----------------------------------------------------------------------------------------------------------

/* Frees all paragraph nodes and their associated phrase and word lists */
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
//------------------------------------------------------------------------------------------------

/* Returns true if two word lists a and b are equal (same words in same order) */
bool equal_words(ptr_word a, ptr_word b) {
    while (a != NULL && b != NULL) {
        if (strcmp(words(a), words(b)) != 0)
            return false;
        a = next(a);
        b = next(b);
    }
    return a == NULL && b == NULL;
}
//-------------------------------------------------------------------------------------------------------

/* Returns true if two phrase lists a and b are equal (same phrases in same order) */
bool equal_phrases(ptr_phrase a, ptr_phrase b) {
    while (a != NULL && b != NULL) {
        if (!equal_words(get_phrase_words(a), get_phrase_words(b)))
            return false;
        a = next_phrase(a);
        b = next_phrase(b);
    }
    return a == NULL && b == NULL;
}
//-------------------------------------------------------------------------------------------------------------------------

/* Returns true if paragraph q (by content) exists somewhere in the list head */
bool exists_paragraph(ptr_paragraph head, ptr_paragraph q) {
    ptr_paragraph p = head;
    while (p != NULL) {
        if (equal_phrases(get_phrases(p), get_phrases(q)))
            return true;
        p = next_para(p);
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------------------

/* Copies the filename string into the file node p */
void set_filename(ptr_file p, char *name) {
    strcpy(p->filename, name);
}
//-------------------------------------------------------------------------------------------------
/* Sets the paragraph list of file p to ph */
void set_file_paragraphs(ptr_file p, ptr_paragraph ph) {
    p->paragraphs = ph;
}
//----------------------------------------------------------------------------------------------

/* Links file node p to file node q (p->next = q) */
void link_file(ptr_file p, ptr_file q) {
    p->next = q;
}
//--------------------------------------------------------------------------------------------------

/* Returns the filename stored in file node p */
char* get_filename(ptr_file p) {
    return p->filename;
}
//----------------------------------------------------------------------------------------------
/* Returns the paragraph list of file node p */
ptr_paragraph get_file_paragraphs(ptr_file p) {
    return p->paragraphs;
}
//----------------------------------------------------------------------------------------------

/* Frees the memory of a single file node (not its paragraph list) */
void free_file(ptr_file p) {
    free(p);
}

/*
 * Opens the file with the given filename and parses it into a paragraph list.
 * Each non-empty line becomes a phrase (list of words).
 * Empty lines act as paragraph delimiters.
 * Returns the head of the paragraph list, or NULL on error.
 */
//-----------------------------------------------------------------------------------------------------------

ptr_paragraph read_file(char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) { printf("Error: cannot open %s\n", filename); return NULL; }

    ptr_paragraph para_list = NULL;
    ptr_phrase current_phrases = NULL;
    char line[500];

    while (fgets(line, 500, f) != NULL) {
        line[strcspn(line, "\n")] = '\0';  /* remove trailing newline */

        if (strlen(line) == 0) {
            /* empty line: finalize current paragraph */
            if (current_phrases != NULL) {
                add_paragraph(&para_list, current_phrases);
                current_phrases = NULL;
            }
        } else {
            /* tokenize the line into words and build a phrase */
            ptr_word word_head = NULL;
            char* token = strtok(line, " \t");
            while (token != NULL) {
                add_word(&word_head, token);
                token = strtok(NULL, " \t");
            }
            add_phrase(&current_phrases, word_head);
        }
    }

    /* add the last paragraph if the file doesn't end with a blank line */
    if (current_phrases != NULL)
        add_paragraph(&para_list, current_phrases);

    fclose(f);
    return para_list;
}
//--------------------------------------------------------------------------------------------------------------

/* Allocates a new file node and initializes its fields to NULL */
void alloc_file(ptr_file *p) {
    *p = malloc(sizeof(file_node));
    (*p)->paragraphs = NULL;
    (*p)->next = NULL;
}
//--------------------------------------------------------------------------------------------------------------------------

/* Returns the paragraph list of file node p */
ptr_paragraph get_paragraphs(ptr_file p) {
    return p->paragraphs;
}
//--------------------------------------------------------------------------------------------------------------------------------

/* Returns the next file node after p */
ptr_file next_file(ptr_file p) {
    return p->next;
}

/*
 * Reads n files from the filenames array, builds a linked list of file nodes,
 * each containing the parsed paragraph list of the corresponding file.
 * Returns the head of the file list.
 */
//-----------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------------

/* Prints all files in the list with their filename header and paragraphs */
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
//-----------------------------------------------------------------------------------------------------------

/* Frees all file nodes and their associated paragraph, phrase, and word lists */
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

/*
 * Prints the union of two paragraph lists (headp and headq).
 * All paragraphs from P are printed, then paragraphs from Q
 * that do not already exist in P.
 */
//-------------------------------------------------------------------------------------------------------
void set_union(ptr_paragraph headp, ptr_paragraph headq) {
    ptr_paragraph p = headp;
    while (p != NULL) {
        print_phrases(get_phrases(p));
        p = next_para(p);
    }
    ptr_paragraph q = headq;
    while (q != NULL) {
        if (!exists_paragraph(headp, q)) {
            print_phrases(get_phrases(q));
        }
        q = next_para(q);
    }
}

/*
 * Prints the intersection of two paragraph lists (headp and headq).
 * Only paragraphs that exist in both lists are printed.
 */
//------------------------------------------------------------------------------------------------------------------------------------
void set_intersection(ptr_paragraph headp, ptr_paragraph headq) {
    ptr_paragraph q = headq;
    while (q != NULL) {
        if (exists_paragraph(headp, q)) {
            print_phrases(get_phrases(q));
        }
        q = next_para(q);
    }
}

/*
 * Prints the difference P - Q of two paragraph lists.
 * Only paragraphs from P that do NOT exist in Q are printed.
 */
//---------------------------------------------------------------------------------------------------------
void set_difference(ptr_paragraph headp, ptr_paragraph headq) {
    ptr_paragraph p = headp;
    while (p != NULL) {
        if (!exists_paragraph(headq, p)) {
            print_phrases(get_phrases(p));
        }
        p = next_para(p);
    }
}

//----------------------------------------------------------------------------------------------------------------
/* Converts all characters in word to uppercase in place */
void upper_word(char* word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        word[i] = toupper(word[i]);
    }
}
//--------------------------------------------------------------------------------------------------------------

/* Converts every word in all phrases of all paragraphs to uppercase */
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

/*
 * Removes all non-alphanumeric characters from word, except periods.
 * The word is modified in place.
 */
//--------------------------------------------------------------------------------------------------------
void clean_word(char* word) {
    int len = strlen(word);
    int j = 0;
    char cleaned[100];

    for (int i = 0; i < len; i++) {
        /* keep only letters, digits, and periods */
        if (isalpha(word[i]) || isdigit(word[i]) || word[i] == '.') {
            cleaned[j] = word[i];
            j++;
        }
    }
    cleaned[j] = '\0';
    strcpy(word, cleaned);
}
//--------------------------------------------------------------------------------------------------------

/* Cleans every word in all phrases of all paragraphs using clean_word() */
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
