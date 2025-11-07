#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Funkcija, kuri inicializuoja steką
void initStack(Stack* stack) {
    stack->top = NULL; 
}

// Patikriname, ar stekas tuščias
int isEmpty(Stack* stack) {
    return (stack->top == NULL);  // Grąžina 1, jei stekas tuščias, kitaip 0
}

// Funkcija pridėti elementą į steką 
void push(Stack* stack, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));  
    if (newNode == NULL) { 
        printf("Atminties klaida\n");
        exit(1);
    }
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

