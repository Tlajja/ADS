#include <stdio.h>
#include "Stack.h"

int main() {
    Stack stack;
    initStack(&stack);  // Inicializuojame steką

    // Pridėkite elementus į steką
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);

    // Peržiūrėti viršutinį elementą
    printf("Viršutinė reikšmė: %d\n", peek(&stack));

    // Pašalinti elementus iš steko
    printf("Pašalinta reikšmė: %d\n", pop(&stack));
    printf("Pašalinta reikšmė: %d\n", pop(&stack));

    // Patikrinti, ar stekas tuščias
    if (isEmpty(&stack)) {
        printf("Stekas tuščias\n");
    } else {
        printf("Stekas nėra tuščias\n");
    }

    // Pašalinti paskutinį elementą
    printf("Pašalinta reikšmė: %d\n", pop(&stack));

    // Patikrinti, ar stekas tuščias
    if (isEmpty(&stack)) {
        printf("Stekas tuščias\n");
    } else {
        printf("Stekas nėra tuščias\n");
    }

    // Išvalyti steką
    freeStack(&stack);

    return 0;
}
