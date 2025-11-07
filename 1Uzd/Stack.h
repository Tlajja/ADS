#ifndef STACK_H
#define STACK_H

// Mazgas, kuris bus naudojamas steko įgyvendinimui
typedef struct Node {
    int value;          // Reikšmė
    struct Node* next;  // Nuoroda į kitą mazgą
} Node;

// Stekas, kurio viršus nurodo į pirmąjį mazgą
typedef struct {
    Node* top;  
} Stack;

// Funkcijos prototipai
void initStack(Stack* stack);          // Inicializuoti steką
int isEmpty(Stack* stack);             // Patikrinimas, ar stekas tuščias
void push(Stack* stack, int value);    // Pridėti elementą į steką
int pop(Stack* stack);                 // Pašalinti ir grąžinti elementą iš steko
int peek(Stack* stack);                // Peržiūrėti viršutinį elementą
void freeStack(Stack* stack);          // Išvalyti visą atmintį

#endif

