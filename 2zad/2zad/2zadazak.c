#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _Person person;
typedef person* Position;

struct _Person {
    char name[50];
    char surname[50];
    int birthYear;
    Position next;
};

void appendList(Position head);
Position createPerson();
int addToEndOfList(Position head);
int printList(Position head);
Position searchList(Position head);
int deletePerson(Position head);
int addInFront(Position head);
int addToBack(Position head);
int sort(Position head);
int writeToFile(Position current);
int ReadFromFile();

int main() {
    char choice='\0';
    int e = 1;
    person head = { .name = {0}, .surname = {0}, .birthYear = {0} , .next = {NULL} };
    Position target = NULL;
   // person target = { .name = {0}, .surname = {0}, .birthYear = {0} , .next = {NULL} };
    char sur[50] = {0};


    while (e) {
        printf("Enter:\n A(Append list)\n E(Put at the end of list)\n P(Print list)\n S(Search)\n D(Delete)\n F(Add after item)\n B(Add before item)\n Z(Sort)\n W(Write to file)\n R(Read from file)\n X(Exit)\n");
        
     scanf(" %c", &choice);
        switch (choice) {

        case 'A':
            appendList(&head);
            break;
        case 'E':
            addToEndOfList(&head);
            break;
        case 'P':
            printList(&head);
            break;
        case 'S':
            printf("unesite prezime koje trazite: ");
            target=searchList(&head);
            printf("student kojg trazite je %s %s\n", target->name, target->surname);
            free(target);
            break;
        case 'D':
            
            deletePerson(&head);
            
            break;
        case 'X':
            e = 0;
            break;
        case 'F':
            addInFront(&head);
            break;
        case 'B':
            addToBack(&head);
            break;
        case 'Z':
            sort(&head);
            break;
        case 'W':
            writeToFile(head.next);
            break;
        case 'R':
            ReadFromFile();
            break;
        }
    }
}


Position createPerson() {

    Position newPerson = NULL;
    char name[50] = { 0 };
    char surname[50] = {0};
    int birth_year=0;

        newPerson = (Position)malloc(sizeof(person));

        printf("unesite novo ime:\n");
        scanf("%s", name);
        printf("unesite novo prezime:\n");
        scanf("%s", surname);
        printf("unesite novu god rodenja:\n");
        scanf("%d", &birth_year);

        strcpy(newPerson->name, name);
        strcpy(newPerson->surname, surname);
        newPerson->birthYear = birth_year;

        return newPerson;
    }

    void appendList(Position head) {
        Position newPerson = NULL;
        newPerson = createPerson();

        if (newPerson) {
            newPerson->next = head->next;
            head->next = newPerson;
        }
       
    }

    int addToEndOfList(Position head) {
        Position newPerson = NULL;
        Position last;

        newPerson = createPerson();

        while (head->next != NULL) {
            head = head->next;
        }
        if (newPerson) {
            last = head;
            newPerson->next = last->next;
            last->next = newPerson;
        }
        return 1;
    }

    int printList(Position head) {
        Position first;
        first = head->next;
        if (first == NULL) {
            printf("prazna lista");
        }
        else {
            printf("ime\tprezime\t god rodenja\n");
            do {
                printf("%s    %s    %d\n", first->name, first->surname, first->birthYear);
                first = first->next;
            } while (first != NULL);
        }
    }

    Position searchList(Position head) {
        Position target = NULL;
        Position p = head->next;
        char surname[50] = {NULL};

        printf("kojeg studenta trazite: \n");
        scanf(" %s", surname);

        while( (p->next != NULL) && (strcmp(p->surname, surname))!=0 ){
            p = p -> next;
        }

        return p;
     
    }
       
    int deletePerson(Position head) {
        Position prev = NULL;
        Position current = head;
        char sur[50];
        printf("unesite prezime koje trazite: ");
        scanf("%s", sur);

        if (head->next) {
            while (current->next && strcmp(sur, current->surname) != 0) {
                prev = current;
                current = current->next;
            }
            if (prev->next && strcmp(sur, current->surname) == 0) {
                prev->next = current->next;
                free(current);
            }
            else {
                printf("ne postoji ta osoba\n");
            }

        }
        else {
            printf("prazna lista\n");
            return -1;
        }
        return 1;
    }
       
    int addInFront(Position head) {
        Position newPerson = NULL;
        Position target = NULL;
        newPerson = createPerson();
        target = searchList(head);
        
        if (newPerson) {
            newPerson->next = target->next;
            target->next = newPerson;
        }
        return 1;
    }

    int addToBack(Position head) {
        Position newPerson = NULL;
        Position target = NULL;
        Position prev = head;
        newPerson = createPerson();
        target = searchList(head);

        while (prev->next != target) {
            prev = prev->next;
        }
        if (newPerson) {
            newPerson->next = prev->next;
            prev->next = newPerson;
        }
        return 1;
    

    }

    int sort(Position head) {       
        Position previous, current, temp,end;
        if (head == NULL)
            printf("empty list");
            return 0;
            end = NULL;
        while (head->next !=end) {
            previous = head;
            current = head->next;

            while (current->next != end) {
                if (strcmp(current->surname, current->next->surname) > 0) {
                    temp = current->next;
                    previous->next = temp;
                    current->next = temp->next;
                    temp->next = current;

                    current = temp;

                }
                previous = current;
                current = current->next;
            }
            end = current;
        }
        return 1;
    }

    int writeToFile(Position current) {
        FILE* fp;
        fp = fopen("list.txt", "w");
        if (current == NULL) {
            printf("prazna lista");
            return -1;
        }
        else {
            while (current != NULL) {
                fprintf(fp, "%s %s %d", current->name, current->surname, current->birthYear);

                current = current->next;

            }
            if (!fp) {
                printf("File not opened\n");
                return -1;
            }
        }
        fclose(fp);
        return EXIT_SUCCESS;
    }

    int ReadFromFile() {
        FILE* fp = NULL;
        
        int counter = 0;
        char name[50];
        char surname[50];
        int birthYear;


        fp = fopen("list.txt","r");


        while (fscanf(fp, "%s %s %d", name, surname, &birthYear)==3) {
            printf("%s %s %d\n", name, surname,birthYear);
         
        }
        return 1;
    }