# Ketvirtasis laboratorinis darbas

5. Duota mokomųjų dalykų bazė: dalyko pavadinimas, dalykai, kuriuos būtina išklausyti anksčiau. Patikrinti, ar būtina, pavyzdžiui, išklausyti „Mat. analizę“ prieš klausant „Optimizavimo metodus“. (grafo realizacija paremta kaimynystės matrica; naudoti paieškos į gylį metodą)

## Projekto struktūra

1. **main.c**: Pagrindinė programa, apdorojanti įvestį ir vykdanti logiką.
2. **course_graph.c**: Grafo struktūros ir priklausomybių tikrinimo funkcijos.
3. **course_graph.h**: Antraštės failas su struktūromis ir funkcijų deklaracijomis.
4. **courses.txt**: Kursų ir jų priklausomybių sąrašas.
5. **Makefile**: Kompiliavimo instrukcijos.
6. **Go.cmd**: Komandinė eilutė, skirta paleisti programą.
7. **PSP.xlsx** – Laiko fiksavimo forma, kurioje pateikiama informacija apie darbo atlikimo laiką ir veiksmus.

## Naudojimas

Paleisti programą:

```
make
./courseCheck [failas] [kursas] [-test/-t]
```

- **[failas]**: Failas su kursų ir jų priklausomybių sąrašu (pvz., courses.txt). Jei naudojamas -test arba -t, failas nereikalingas.
- **[kursas]**: Kursas, kurio priklausomybių tikrinti. Jei naudojamas -test arba -t, kursas nereikalingas.
- **[-test|-t]**: Parametras, skirtas įmontuotam testavimo atvejui paleisti.

**Įvesties failo formatas**:<br>
Kiekviena eilutė: _kursas: priklausomybė1, priklausomybė2, ..._<br>
Jei kursas neturi priklausomybių, nurodoma tuščia priklausomybė (pvz., _kursas:_ ). <br>
Priklausomybės atskiriamos kableliais.

**Pavyzdys (courses.txt):<br>**
Mathematical Analysis: <br>
Linear Algebra:<br>
Programming Fundamentals:<br>
Statistics: Probability Theory, Algorithms<br>
Optimization Methods: Mathematical Analysis, Linear Algebra<br>
