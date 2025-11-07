# 7. ADT – Stekas (L)

Ši dokumentacija aprašo, kaip naudotis `stack.h` biblioteką, kuri implementuoja **steką** (angl. *stack*). Stekas yra duomenų struktūra, kuriai taikomas **LIFO** (Last In, First Out) principas: paskutinis įdėtas elementas yra pirmasis išimamas.

---

## Funkcijos

### initStack() 
Sukuria ir grąžina steką.

### freeStack()
Sunaikina steką ir atlaisvina jo atmintį.

### isEmpty()
Tikrina, ar stekas yra tuščias.

### Push()
Prideda naują elementą į steko viršų.

### Pop()
Pašalina ir grąžina elementą iš steko viršaus.

### Peek()
Gražina viršutinį steko elementą jo nepašalindamas

---

## Pastaba

**Atminties Valdymas**: 
   - Išimti elementai ***turi būti*** atlaisvinami naudojant `freeStack()`.
   - Sunaikinus steką, visi jo elementai automatiškai atlaisvinami.


---

