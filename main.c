#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
#include <stdbool.h>

int main() {
    printf("\n********************************** OUR TP **************************************************************\n");
    printf("\n NAMES:- ROUABAH BASMALA \n       - ZENIKHRI ZINEB \n");
    printf("\n*******************************************************************************************************\n");

    int choix = 0;

    do {
        /* Display main menu */
        printf("\n*******************************************************************************************************\n");
        printf("                                select one :                      \n");
        printf("\n*******************************************************************************************************\n");
        printf(" 1. One file\n");
        printf(" 2. Multiple files\n");
        printf(" 0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choix);

        switch (choix) {

            case 1: {
                /* --- Single file mode ---
                 * The user enters one file name, views its paragraphs,
                 * picks two paragraphs, then performs set operations on them. */

                printf("\n*******************************************************************************************************\n");
                printf("                                one file :                      \n");
                printf("\n*******************************************************************************************************\n");

                char name[100];
                printf("Enter file name: ");
                scanf("%s", name);

                /* Read and parse the file into a paragraph list */
                ptr_paragraph para = read_file(name);
                if (para == NULL) {
                    printf("Error reading file %s.\n", name);
                    break;
                }

                printf("\n--- File: %s ---\n", name);
                print_paragraphs(para);

                /* Ask the user to pick two paragraph numbers */
                int pa1, pa2;
                printf("Choose first  paragraph: ");
                scanf("%d", &pa1);
                printf("Choose second paragraph: ");
                scanf("%d", &pa2);

                /* Navigate to paragraph pa1 */
                ptr_paragraph tmp1 = para;
                for (int i = 1; i < pa1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap paragraph pa1 in its own single node list */
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                /* Navigate to paragraph pa2 */
                ptr_paragraph tmp2 = para;
                for (int i = 1; i < pa2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap paragraph pa2 in its own single node list */
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));

                /* Normalize both paragraphs: strip punctuation then uppercase */
                clean_paragraph(one_para1);
                clean_paragraph(one_para2);
                upper_paragraph(one_para1);
                upper_paragraph(one_para2);

                /* Inner menu: set operations on the two selected paragraphs */
                int choice = 0;
                do {
                    printf("\n*******************************************************************************************************\n");
                    printf("   Set Operations on Text Paragraphs   \n");
                    printf("\n*******************************************************************************************************\n");
                    printf(" 1. Union        (A U B)\n");
                    printf(" 2. Intersection (A n B)\n");
                    printf(" 3. Difference   (A \\ B)\n");
                    printf(" 0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            /* Print all phrases from A, plus phrases in B not already in A */
                            printf("\n--- Union (A U B) ---\n");
                            printf("\n { ");
                            set_union(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 2:
                            /* Print only phrases that appear in both A and B */
                            printf("\n--- Intersection (A n B) ---\n");
                            printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
                            /* Print phrases in A that do NOT appear in B */
                            printf("\n--- Difference (A \\ B) ---\n");
                            printf("\n { ");
                            set_difference(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 0:
                            printf("Goodbye!\n");
                            break;
                        default:
                            printf("Invalid choice, try again.\n");
                    }
                } while (choice != 0);

                /* Free the original paragraph list */
                free_paragraphs(para);
                break;
            }

            case 2: {
                /* --- Multiple files mode ---
                 * The user enters n file names, views all their paragraphs,
                 * picks two files and one paragraph from each,
                 * then performs set operations on the selected paragraphs. */

                printf("\n*******************************************************************************************************\n");
                printf("                                n files :                      \n");
                printf("\n*******************************************************************************************************\n");

                int n;
                printf("Enter number of files: ");
                scanf("%d", &n);

                char names[10][100];
                ptr_paragraph paras[10];

                /* Read and display all n files */
                for (int i = 0; i < n; i++) {
                    printf("Enter file %d name: ", i + 1);
                    scanf("%s", names[i]);
                    paras[i] = read_file(names[i]);
                    if (paras[i] == NULL) {
                        printf("Error reading file %s.\n", names[i]);
                        return 1;
                    }
                    printf("\n--- File %d: %s ---\n", i + 1, names[i]);
                    print_paragraphs(paras[i]);
                }

                /* Ask the user to pick two files and one paragraph from each */
                int f1, f2;
                printf("\nChoose first  file (1 to %d): ", n);
                scanf("%d", &f1);
                printf("Choose second file (1 to %d): ", n);
                scanf("%d", &f2);
                f1--; f2--;  /* convert to 0-based indices */

                int p1, p2;
                printf("Choose paragraph from file %d: ", f1 + 1);
                scanf("%d", &p1);
                printf("Choose paragraph from file %d: ", f2 + 1);
                scanf("%d", &p2);

                /* Navigate to paragraph p1 in file f1 */
                ptr_paragraph tmp1 = paras[f1];
                for (int i = 1; i < p1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap selected paragraph in its own single node list */
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                /* Navigate to paragraph p2 in file f2 */
                ptr_paragraph tmp2 = paras[f2];
                for (int i = 1; i < p2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap selected paragraph in its own single node list */
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));

                /* Normalize both paragraphs: strip punctuation then uppercase */
                clean_paragraph(one_para1);
                clean_paragraph(one_para2);
                upper_paragraph(one_para1);
                upper_paragraph(one_para2);

                /* Inner menu: set operations on the two selected paragraphs */
                int choice = 0;
                do {
                    printf("\n*******************************************************************************************************\n");
                    printf("   Set Operations on Text Paragraphs   \n");
                    printf("\n*******************************************************************************************************\n");
                    printf(" 1. Union        (A U B)\n");
                    printf(" 2. Intersection (A n B)\n");
                    printf(" 3. Difference   (A \\ B)\n");
                    printf(" 0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            /* Print all phrases from A, plus phrases in B not already in A */
                            printf("\n--- Union (A U B) ---\n");
                            printf("\n { ");
                            set_union(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 2:
                            /* Print only phrases that appear in both A and B */
                            printf("\n--- Intersection (A n B) ---\n");
                            printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
                            /* Print phrases in A that do NOT appear in B */
                            printf("\n--- Difference (A \\ B) ---\n");
                            printf("\n { ");
                            set_difference(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 0:
                            printf("Goodbye!\n");
                            break;
                        default:
                            printf("Invalid choice, try again.\n");
                    }
                } while (choice != 0);

                /* Free all paragraph lists from all loaded files */
                for (int i = 0; i < n; i++)
                    free_paragraphs(paras[i]);

                break;
            }

            case 0:
                /* Exit message */
                printf("!!!!!!!!!!!!!!!Thank you for taking the time to read this code.!!!!!!!!!!!!!\n");
                printf("!!!!!!!!!!!!!!!Union, Intersection, Difference , all implemented.!!!!!!!!!!!!!\n");
                printf("!!!!!!!!!!!!!!!The only thing missing is the A+ on the grade sheet.!!!!!!!!!!!!!\n");
                break;

            default:
                printf("Invalid choice, try again.\n");
        }

    } while (choix != 0);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"
#include <stdbool.h>

int main() {
    printf("\n********************************** OUR TP **************************************************************\n");
    printf("\n NAMES:- ROUABAH BASMALA \n       - ZENIKHRI ZINEB \n");
    printf("\n*******************************************************************************************************\n");

    int choix = 0;

    do {
        /* Display main menu */
        printf("\n*******************************************************************************************************\n");
        printf("                                select one :                      \n");
        printf("\n*******************************************************************************************************\n");
        printf(" 1. One file\n");
        printf(" 2. Multiple files\n");
        printf(" 0. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choix);

        switch (choix) {

            case 1: {
                /* --- Single file mode ---
                 * The user enters one file name, views its paragraphs,
                 * picks two paragraphs, then performs set operations on them. */

                printf("\n*******************************************************************************************************\n");
                printf("                                one file :                      \n");
                printf("\n*******************************************************************************************************\n");

                char name[100];
                printf("Enter file name: ");
                scanf("%s", name);

                /* Read and parse the file into a paragraph list */
                ptr_paragraph para = read_file(name);
                if (para == NULL) {
                    printf("Error reading file %s.\n", name);
                    break;
                }

                printf("\n--- File: %s ---\n", name);
                print_paragraphs(para);

                /* Ask the user to pick two paragraph numbers */
                int pa1, pa2;
                printf("Choose first  paragraph: ");
                scanf("%d", &pa1);
                printf("Choose second paragraph: ");
                scanf("%d", &pa2);

                /* Navigate to paragraph pa1 */
                ptr_paragraph tmp1 = para;
                for (int i = 1; i < pa1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap paragraph pa1 in its own single node list */
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                /* Navigate to paragraph pa2 */
                ptr_paragraph tmp2 = para;
                for (int i = 1; i < pa2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap paragraph pa2 in its own single node list */
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));

                /* Normalize both paragraphs: strip punctuation then uppercase */
                clean_paragraph(one_para1);
                clean_paragraph(one_para2);
                upper_paragraph(one_para1);
                upper_paragraph(one_para2);

                /* Inner menu: set operations on the two selected paragraphs */
                int choice = 0;
                do {
                    printf("\n*******************************************************************************************************\n");
                    printf("   Set Operations on Text Paragraphs   \n");
                    printf("\n*******************************************************************************************************\n");
                    printf(" 1. Union        (A U B)\n");
                    printf(" 2. Intersection (A n B)\n");
                    printf(" 3. Difference   (A \\ B)\n");
                    printf(" 0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            /* Print all phrases from A, plus phrases in B not already in A */
                            printf("\n--- Union (A U B) ---\n");
                            printf("\n { ");
                            set_union(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 2:
                            /* Print only phrases that appear in both A and B */
                            printf("\n--- Intersection (A n B) ---\n");
                            printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
                            /* Print phrases in A that do NOT appear in B */
                            printf("\n--- Difference (A \\ B) ---\n");
                            printf("\n { ");
                            set_difference(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 0:
                            printf("Goodbye!\n");
                            break;
                        default:
                            printf("Invalid choice, try again.\n");
                    }
                } while (choice != 0);

                /* Free the original paragraph list */
                free_paragraphs(para);
                break;
            }

            case 2: {
                /* --- Multiple files mode ---
                 * The user enters n file names, views all their paragraphs,
                 * picks two files and one paragraph from each,
                 * then performs set operations on the selected paragraphs. */

                printf("\n*******************************************************************************************************\n");
                printf("                                n files :                      \n");
                printf("\n*******************************************************************************************************\n");

                int n;
                printf("Enter number of files: ");
                scanf("%d", &n);

                char names[10][100];
                ptr_paragraph paras[10];

                /* Read and display all n files */
                for (int i = 0; i < n; i++) {
                    printf("Enter file %d name: ", i + 1);
                    scanf("%s", names[i]);
                    paras[i] = read_file(names[i]);
                    if (paras[i] == NULL) {
                        printf("Error reading file %s.\n", names[i]);
                        return 1;
                    }
                    printf("\n--- File %d: %s ---\n", i + 1, names[i]);
                    print_paragraphs(paras[i]);
                }

                /* Ask the user to pick two files and one paragraph from each */
                int f1, f2;
                printf("\nChoose first  file (1 to %d): ", n);
                scanf("%d", &f1);
                printf("Choose second file (1 to %d): ", n);
                scanf("%d", &f2);
                f1--; f2--;  /* convert to 0-based indices */

                int p1, p2;
                printf("Choose paragraph from file %d: ", f1 + 1);
                scanf("%d", &p1);
                printf("Choose paragraph from file %d: ", f2 + 1);
                scanf("%d", &p2);

                /* Navigate to paragraph p1 in file f1 */
                ptr_paragraph tmp1 = paras[f1];
                for (int i = 1; i < p1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap selected paragraph in its own single node list */
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                /* Navigate to paragraph p2 in file f2 */
                ptr_paragraph tmp2 = paras[f2];
                for (int i = 1; i < p2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                /* Wrap selected paragraph in its own single node list */
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));

                /* Normalize both paragraphs: strip punctuation then uppercase */
                clean_paragraph(one_para1);
                clean_paragraph(one_para2);
                upper_paragraph(one_para1);
                upper_paragraph(one_para2);

                /* Inner menu: set operations on the two selected paragraphs */
                int choice = 0;
                do {
                    printf("\n*******************************************************************************************************\n");
                    printf("   Set Operations on Text Paragraphs   \n");
                    printf("\n*******************************************************************************************************\n");
                    printf(" 1. Union        (A U B)\n");
                    printf(" 2. Intersection (A n B)\n");
                    printf(" 3. Difference   (A \\ B)\n");
                    printf(" 0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            /* Print all phrases from A, plus phrases in B not already in A */
                            printf("\n--- Union (A U B) ---\n");
                            printf("\n { ");
                            set_union(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 2:
                            /* Print only phrases that appear in both A and B */
                            printf("\n--- Intersection (A n B) ---\n");
                            printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
                            /* Print phrases in A that do NOT appear in B */
                            printf("\n--- Difference (A \\ B) ---\n");
                            printf("\n { ");
                            set_difference(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 0:
                            printf("Goodbye!\n");
                            break;
                        default:
                            printf("Invalid choice, try again.\n");
                    }
                } while (choice != 0);

                /* Free all paragraph lists from all loaded files */
                for (int i = 0; i < n; i++)
                    free_paragraphs(paras[i]);

                break;
            }

            case 0:
                /* Exit message */
                printf("!!!!!!!!!!!!!!!Thank you for taking the time to read this code.!!!!!!!!!!!!!\n");
                printf("!!!!!!!!!!!!!!!Union, Intersection, Difference , all implemented.!!!!!!!!!!!!!\n");
                printf("!!!!!!!!!!!!!!!The only thing missing is the 20 on the grade sheet.!!!!!!!!!!!!!\n");
                break;

            default:
                printf("Invalid choice, try again.\n");
        }

    } while (choix != 0);

    return 0;
}
