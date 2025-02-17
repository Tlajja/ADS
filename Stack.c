#include <stdio.h>
#include <stdlib.h>

// Mazgas, kuris bus naudojamas steko įgyvendinimui
typedef struct Node{
    int value;          // Reikšmė
    struct Node* next;  // Nuoroda į kitą mazgą
} Node;

// Stekas, kurio viršus nurodo į pirmąjį mazgą
typedef struct{
    Node* top;  
} Stack;

// Funkcija, kuri inicializuoja steką
void initStack(Stack* stack) {
    stack->top = NULL; 
}

// Patikriname, ar stekas tuščias
int isEmpty(Stack* stack) {
    if(stack->top == NULL)
        return 1;
    else
        return 0;
}

// Funkcija pridėti elementą į steką 
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));  
    newNode->value = value;  
    newNode->next = stack->top;  
    stack->top = newNode;  
}

// Funkcija pašalinti ir grąžinti elementą iš steko
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Klaida: Stekas tuščias, nėra ką gražinti\n");
        exit(1);  
    }
    Node* temp = stack->top;  
    int value = temp->value;         
    stack->top = stack->top->next;   
    free(temp);  
    return value;  
}

// Funkcija peržiūrėti viršutinį elementą (peek)
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Klaida: Stekas tuščias nėrą ką peržiūrėti\n");
        exit(1);  // Jei stekas tuščias, nutraukiame programą su klaidos pranešimu
    }
    return stack->top->value;  
}

// Funkcija, kuri išlaisvina visą atmintį, susijusią su steku
void freeStack(Stack* stack) {
    Node* current = stack->top;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;  
        free(current);  
        current = nextNode;  
    }

    stack->top = NULL;  
}

int main(){
    Stack stack;
    initStack(&stack);  

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    printf("Viršutinė reikšmė: %d\n", peek(&stack));  

    printf("Pašalinta reikšmė: %d\n", pop(&stack));  
    printf("Pašalinta reikšmė: %d\n", pop(&stack));  

    if (isEmpty(&stack)) {
        printf("Stekas tuščias\n");
    } else {
        printf("Stekas nėra tuščias\n");
    }

    printf("Pašalinta reikšmė: %d\n", pop(&stack));  

    if (isEmpty(&stack)) {
        printf("Stekas tuščias\n");
    } else {
        printf("Stekas nėra tuščias\n");
    }

    freeStack(&stack);

    return 0;
}
