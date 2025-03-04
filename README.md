7. ADT – Stekas (L)

Ši dokumentacija aprašo, kaip naudotis `stack.h` biblioteką, kuri implementuoja **steką** (angl. *stack*) naudojant **ciklinį susietą sąrašą** (angl. *cyclic linked list*). Stekas yra duomenų struktūra, kuriai taikomas **LIFO** (Last In, First Out) principas: paskutinis įdėtas elementas yra pirmasis išimamas.

---

## Funkcijos

### initStack  
Sukuria ir grąžina steką.

### freeStack 
Sunaikina steką ir atlaisvina jo atmintį.

### isEmpty 
Tikrina, ar stekas yra tuščias.

### Push
Prideda naują elementą į steko viršų.

### Pop 
Pašalina ir grąžina elementą iš steko viršaus.

### Peek 
Gražina viršutinį steko elementą jo nepašalindamas

---

## Pastabos

1. **Atminties Valdymas**: 
   - Išimti elementai turi būti atlaisvinami naudojant `free()`.
   - Sunaikinus steką, visi jo elementai automatiškai atlaisvinami.

2. **Cikliškumas**:
   - Stekas yra realizuotas kaip ciklinis sąrašas, todėl operacijos su juo yra efektyvios.

3. **Klaidų Valdymas**:
   - Visos funkcijos grąžina klaidos kodus, kurie turėtų būti patikrinami, kad būtų užtikrintas teisingas programos veikimas.

---

