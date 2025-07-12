#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

typedef struct list {
    char name[40];
    char num[20];
    char gmail[40];
    char fb[40];
    struct list* next;
} add;

int size = 0;

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void input_string(char *prompt, char *str, int len) {
    printf("%s", prompt);
    fgets(str, len, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline
}

void Insert(add** head) {
    if (size >= 5) {
        system(CLEAR);
        printf("\n\n\t\tPhone memory is full!");
        printf("\n\t\tDelete some contacts to add more.\n");
        return;
    }

    add* temp = (add*)malloc(sizeof(add));
    if (!temp) {
        printf("Memory allocation failed!\n");
        return;
    }

    input_string("\n\t\tEnter Contact Name: ", temp->name, 40);
    input_string("\n\t\tEnter Mobile Number: ", temp->num, 20);
    input_string("\n\t\tEnter Gmail ID: ", temp->gmail, 40);
    input_string("\n\t\tEnter Facebook Account: ", temp->fb, 40);
    temp->next = NULL;

    size++;

    if (*head == NULL) {
        *head = temp;
    } else {
        add* p = *head;
        while (p->next != NULL)
            p = p->next;
        p->next = temp;
    }

    system(CLEAR);
    printf("\n\t\tContact added successfully!\n");
}

void Search(add* head) {
    if (head == NULL) {
        system(CLEAR);
        printf("\n\t\tNo contacts in the list.\n");
        return;
    }

    char ch[40];
    input_string("\n\t\tEnter Contact Name to Search: ", ch, 40);
    system(CLEAR);

    add* p = head;
    while (p != NULL) {
        if (strcmp(p->name, ch) == 0) {
            printf("\n\t\tContact Found:");
            printf("\n\t\tName: %s", p->name);
            printf("\n\t\tNumber: %s", p->num);
            printf("\n\t\tGmail: %s", p->gmail);
            printf("\n\t\tFacebook: %s\n", p->fb);
            return;
        }
        p = p->next;
    }

    printf("\n\t\tContact not found!\n");
}

void Delete(add** head) {
    if (*head == NULL) {
        printf("\n\t\tNo contacts to delete.\n");
        return;
    }

    char ch[40];
    input_string("\n\t\tEnter Contact Name to Delete: ", ch, 40);
    system(CLEAR);

    add *p = *head, *prev = NULL;

    while (p != NULL && strcmp(p->name, ch) != 0) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("\n\t\tContact not found!\n");
        return;
    }

    if (prev == NULL) {
        *head = p->next;
    } else {
        prev->next = p->next;
    }

    free(p);
    size--;

    printf("\n\t\tContact deleted successfully!\n");
}

void Display(add* head) {
    if (head == NULL) {
        printf("\n\t\tNo contacts in the list.\n");
        return;
    }

    int i = 1;
    add* p = head;
    while (p != NULL) {
        printf("\n\t\t%d. %s", i++, p->name);
        printf("\n\t\t---------------------------");
        printf("\n\t\tNumber: %s", p->num);
        printf("\n\t\tGmail: %s", p->gmail);
        printf("\n\t\tFacebook: %s\n", p->fb);
        p = p->next;
    }
}

int main() {
    add* head = NULL;
    int ch;

    while (1) {
        printf("\n\n\t\t--- PHONE BOOK ---");
        printf("\n\t\t1) Create a Contact");
        printf("\n\t\t2) Remove a Contact");
        printf("\n\t\t3) Show Contact List");
        printf("\n\t\t4) Find a Contact");
        printf("\n\t\t5) Exit");
        printf("\n\t\tEnter your choice: ");
        scanf("%d", &ch);
        flush_stdin(); // clear newline from buffer

        system(CLEAR);

        switch (ch) {
            case 1:
                Insert(&head);
                break;
            case 2:
                Delete(&head);
                break;
            case 3:
                Display(head);
                break;
            case 4:
                Search(head);
                break;
            case 5:
                printf("\n\t\tExiting...\n");
                return 0;
            default:
                printf("\n\t\tInvalid choice! Try again.\n");
        }
    }

    return 0;
}
