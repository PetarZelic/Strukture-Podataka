#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct _polynome Polynome;
typedef Polynome* Position;
struct _polynome {
    int coefficient;
    int exponent;
    Position next;
};

int ReadFromFile(Position head1, Position head2);
void StringToList(char* buffer, Position head);
int AddSorted(Position head, int coef, int expo);
void PrintList(Position head1);
void AddPolynomes(Position head1, Position head2, Position adding_head);
void MultiplyPolynomes(Position head1, Position head2, Position multiply_head);


int main() {
    Polynome FirstHead = { .coefficient = 0, .exponent = 0, .next = NULL };
    Polynome SecondHead = { .coefficient = 0, .exponent = 0, .next = NULL };
    Polynome SumHead = { .coefficient = 0, .exponent = 0, .next = NULL };
    Polynome MultipliedHead = { .coefficient = 0, .exponent = 0, .next = NULL };

    ReadFromFile(&FirstHead, &SecondHead);

    printf("First polynome:");
    PrintList(&FirstHead);

    printf("\nSecond polynome:");
    PrintList(&SecondHead);

    printf("\nAdded polynome:");
    AddPolynomes(&FirstHead, &SecondHead, &SumHead);
    PrintList(&SumHead);

    printf("\nMultiplied polynome:");
    MultiplyPolynomes(&FirstHead, &SecondHead, &MultipliedHead);
    PrintList(&MultipliedHead);

    return 0;
}



int ReadFromFile(Position FirstHead, Position SecondHead) {
    FILE* file = NULL;
    file = fopen("polynome.txt", "r");
    if (!file) {
        printf("Error opening file");
        return 0;
    }
    char buffer[1024] = { 0 };

    fgets(buffer, 1024, file);
    StringToList(buffer, FirstHead);

    fgets(buffer, 1024, file);
    StringToList(buffer, SecondHead);

    return 0;
}

void StringToList(char* buffer, Position head) {
    char* CurrentBuffer = buffer;
    int numBytes, coef, expo, status;

    while (strlen(CurrentBuffer) > 0) {
        if (status = sscanf(CurrentBuffer, "%dx^%d %n", &coef, &expo, &numBytes) != 2) {
            printf("Unable to read polynome");
            CurrentBuffer += numBytes;
            break;
        }
        AddSorted(head, coef, expo);
        CurrentBuffer += numBytes;
    }
}

int AddSorted(Position head, int coef, int expo) {
    Position current = head->next;
    Position previous = head;
    Position NewElement = (Position)malloc(sizeof(Polynome));
    if (NewElement == NULL) {
        printf("Allocation Error!");
        return 1;
    }
    NewElement->coefficient = coef;
    NewElement->exponent = expo;
    if (NewElement->coefficient == 0) {
        free(NewElement);
        return 0;
    }

    while (current != NULL) {
        if (NewElement->exponent > current->exponent) {
            NewElement->next = previous->next;
            previous->next = NewElement;
            break;
        }
        else if (NewElement->exponent == current->exponent) {
            current->coefficient = current->coefficient + NewElement->coefficient;
            free(NewElement);
            if (current->coefficient == 0) {
                previous->next = current->next;
                free(current);
            }
            break;
        }

        current = current->next;
        previous = previous->next;
    }
    if (current == NULL) {
        NewElement->next = previous->next;
        previous->next = NewElement;
    }
    return 0;

}

void PrintList(Position head) {
    Position current = head;

    while (current->next != NULL) {
        current = current->next;
        printf("%dx^%d ", current->coefficient, current->exponent);
    }
}
void AddPolynomes(Position head1, Position head2, Position SumHead) {
    Position temp;
    Position current1 = head1->next;
    Position current2 = head2->next;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent == current2->exponent) {
            AddSorted(SumHead, current1->coefficient + current2->coefficient, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
        else if (current1->exponent > current2->exponent) {
            AddSorted(SumHead, current1->coefficient, current1->exponent);
            current1 = current1->next;
        }
        else {
            AddSorted(SumHead, current2->coefficient, current2->exponent);
            current2 = current2->next;
        }
    }

    if (current1 != NULL) {
        temp = current1;
    }
    else {
        temp = current2;
    }
    while (temp != NULL) {
        AddSorted(SumHead, temp->coefficient, temp->exponent);
        temp = temp->next;
    }

}

void MultiplyPolynomes(Position head1, Position head2, Position MultipliedHead) {
    Position current1;
    Position current2;
    for (current1 = head1->next; current1 != NULL; current1 = current1->next) {
        for (current2 = head2->next; current2 != NULL; current2 = current2->next) {
            AddSorted(MultipliedHead, current1->coefficient * current2->coefficient, current1->exponent + current2->exponent);
        }
    }
}