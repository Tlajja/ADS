# Trečiasis laboratorinis darbas

## Kreditai

8. ADT – Eilė (L) (queue.c ir queue.h) \
   Autorė: ulva0857\
   Darbas paimtas iš dėstytojo tinklalapio.\
   Defektų rasta: 0

11. ADT – Ilgas sveikas skaičius (A, B) (BigInt.h ir BigInt.c) \
   autorius: gepa1347\
   Darbas paimtas iš dėstytojo tinklalapio.\
   Defektų rasta: 0

---

13\. Bankas (ADT: eilė, ilgas sveikas skaičius). Procesas: klientai ateina į banką ir kreipiasi į bet kurį laisvą kasininką, jei visi kasininkai užsiėmę, klientai stoja į bendrą eilę. Tikslas: patyrinėti, kaip tikslingiau bankui elgtis – turėti mažiau labiau patyrusių kasininkų (jie aptarnauja klientus greičiau) ar daugiau mažiau patyrusių kasininkų (jie aptarnauja klientus lėčiau). Pradiniai duomenys: kasininkų skaičius, kliento aptarnavimo laikas, kliento atvykimo tikimybė (galima realizacija: generuojamas atsitiktinis skaičius ir tikrinama, ar jis tenkina tam tikrą sąlygą). Rezultatai: statistika kažkuriam (vartotojo nurodytam) laiko momentui, pavyzdžiui, vidutinis ir maksimalus kliento laukimo laikas, vidutinis kasininko užimtumas (procentais), maksimalus eilės dydis ir pan.

## Projekto struktūra

1. **bank.c** – Implementacija funkcijų, kurios leidžia simuliuoti banko aptarnavimą.
2. **bank.h** – Antraštės failas, kuriame aprašytos funkcijos, naudojamos banko aptarnavimui simuliuoti.
3. **queue.c** – eilės duomenų struktūros implementaciją.
4. **queue.h** – Antraštės failas, kuriame aprašytos funkcijos, naudojamos eilei inplementuoti.
5. **main.c** – Testavimo programa, kuriame įvykdomos pagrindinės funkcijos.
6. **Go.cmd** – Komandinė eilutė, skirta paleisti programą.
7. **Makefile** – Naudojama sukompiliuoti programą.
8. **LFF.xlsx** – Laiko fiksavimo forma, kurioje pateikiama informacija apie darbo atlikimo laiką ir veiksmus.
9. **Readme.md** – Trečiojo laboratorinio darbo aprašas.

## Naudojimas

Paleisti programą:

```
make
./bankSim [paramFailas] [-rnd] [-t]
```

[paramFailas] - failas su programos parametrais. Faile galima pakeisti pradinius duomenis:

- Simuliacijos trukmė minutėmis (numatyta: 500)

- Kasininkų skaičius (numatyta: 5)

- Kliento atvykimo tikimybė procentais (numatyta: 50)

- Maksimalus aptarnavimo laikas minutėmis (numatyta: 10)

[-rnd] - Atsitiktinių skaičių generatoriaus pradinė reikšmė (numatyta: sistema)\
[-t] - Programa paleidžiama su numatytais parametrais.

```
./bankSim param.txt -rnd 52
```
