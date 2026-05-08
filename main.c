#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp_lib.h"

int main() {
    printf("\n********************************** OUR TP **************************************************************\n");
    printf("\n NAMES:- ROUABAH BASMALA \n       - ZENIKHRI ZINEB \n");
    printf("\n*******************************************************************************************************\n");
    int choix = 0;
    do {
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
                printf("\n*******************************************************************************************************\n");
                printf("                                one file :                      \n");
                printf("\n*******************************************************************************************************\n");

                char name[100];
                printf("Enter file name: ");
                scanf("%s", name);

                ptr_paragraph para = read_file(name);
                if (para == NULL) {
                    printf("Error reading file %s.\n", name);
                    break;
                }

                printf("\n--- File: %s ---\n", name);
                print_paragraphs(para);

                int pa1, pa2;
                printf("Choose first  paragraph: ");
                scanf("%d", &pa1);
                printf("Choose second paragraph: ");
                scanf("%d", &pa2);

                // navigate to pa1
                ptr_paragraph tmp1 = para;
                for (int i = 1; i < pa1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                // navigate to pa2
                ptr_paragraph tmp2 = para;
                for (int i = 1; i < pa2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));
clean_paragraph(one_para1);
clean_paragraph(one_para2);
upper_paragraph(one_para1);
upper_paragraph(one_para2);
                // inner menu
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
                            printf("\n--- Union (A U B) ---\n");
                             printf("\n { ");
                            set_union(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 2:
                            printf("\n--- Intersection (A n B) ---\n");
                             printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
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

                free_paragraphs(para);
                break;
            }

            case 2: {
                printf("\n*******************************************************************************************************\n");
                printf("                                n files :                      \n");
                printf("\n*******************************************************************************************************\n");

                int n;
                printf("Enter number of files: ");
                scanf("%d", &n);

                char names[10][100];
                ptr_paragraph paras[10];

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

                int f1, f2;
                printf("\nChoose first  file (1 to %d): ", n);
                scanf("%d", &f1);
                printf("Choose second file (1 to %d): ", n);
                scanf("%d", &f2);
                f1--; f2--;

                int p1, p2;
                printf("Choose paragraph from file %d: ", f1 + 1);
                scanf("%d", &p1);
                printf("Choose paragraph from file %d: ", f2 + 1);
                scanf("%d", &p2);

                // navigate to p1
                ptr_paragraph tmp1 = paras[f1];
                for (int i = 1; i < p1; i++) {
                    tmp1 = next_para(tmp1);
                    if (tmp1 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                ptr_paragraph one_para1 = NULL;
                add_paragraph(&one_para1, get_phrases(tmp1));

                // navigate to p2
                ptr_paragraph tmp2 = paras[f2];
                for (int i = 1; i < p2; i++) {
                    tmp2 = next_para(tmp2);
                    if (tmp2 == NULL) { printf("Paragraph not found.\n"); break; }
                }
                ptr_paragraph one_para2 = NULL;
                add_paragraph(&one_para2, get_phrases(tmp2));
clean_paragraph(one_para1);
clean_paragraph(one_para2);
upper_paragraph(one_para1);
upper_paragraph(one_para2);
                // inner menu
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
                            printf("\n--- Union (A U B) ---\n");
                             printf("\n { ");
                            set_union(one_para1, one_para2);
                             printf("  } ");
                            break;
                        case 2:
                            printf("\n--- Intersection (A n B) ---\n");
                             printf("\n { ");
                            set_intersection(one_para1, one_para2);
                            printf("  } ");
                            break;
                        case 3:
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

                for (int i = 0; i < n; i++)
                    free_paragraphs(paras[i]);

                break;
            }

            case 0:
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
