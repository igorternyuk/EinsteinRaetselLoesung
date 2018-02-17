#include <stdio.h>
#include <stdbool.h>

enum { Unbekante= 5, HAUS_ANZAHL = 5, BESCHAFFENHEIT_ANZAHL = 5};
enum Beschaffenheit { Farbe, Nationalitaet, Getraenk, Haustier, Sport };
enum { Rot, Gelb, Blau, Gruen, Weiss };
enum { Brite, Schwede, Daene, Norweger, Deutsche };
enum { Tee, Kaffee, Milch, Saft, Wasser };
enum { Hund, Katze, Papagei, Fisch, Hamster };
enum { Golf, Fussball, Tennis, Tischtennis, Handball };
const char *Beschreibung[BESCHAFFENHEIT_ANZAHL][BESCHAFFENHEIT_ANZAHL] =
{
    {"rot", "gelb", "blau", "grün", "weiß"},
    {"Brite", "Schwede", "Däne", "Norweger", "Deutsche"},
    {"Tee", "Kaffee", "Milch", "Saft", "Wasser"},
    {"Hund", "Katze", "Papagei", "Fisch", "Hamster"},
    {"Golf", "Fußball", "Tennis", "Tischtennis", "Handball"}
};

int loesung[HAUS_ANZAHL][BESCHAFFENHEIT_ANZAHL];

bool pruefen_nachbar(size_t i, int beschaffenheit, int wert)
{
    return (i >= 1 && (loesung[i - 1][beschaffenheit] == Unbekante ||
            loesung[i - 1][beschaffenheit] == wert)) ||
           (i < HAUS_ANZAHL - 1 && (loesung[i + 1][beschaffenheit] == Unbekante ||
            loesung[i + 1][beschaffenheit] == wert));
}

bool pruefen_die_loesung()
{
    /*
    Fünf Häuser stehen nebeneinander. In diesen Häusern wohnen
    Menschen von fünf unterschiedlichen Nationalitäten,
    die fünf unterschiedliche Getränke trinken,
    fünf unterschiedliche Sportarten nachgehen und
    fünf unterschiedliche Haustiere haben.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        for(size_t j = 0; j < BESCHAFFENHEIT_ANZAHL; ++j)
        {
            int b1 = loesung[i][j];
            for(size_t k = i + 1; k < HAUS_ANZAHL; ++k)
            {
                int b2 = loesung[k][j];
                if(b1 != Unbekante && b2 != Unbekante && b1 == b2)
                    return false;
            }
        }
    }

    /*1. Der Brite lebt im roten Haus.*/

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
        if(loesung[i][Nationalitaet] == Brite &&
           loesung[i][Farbe] != Unbekante && loesung[i][Farbe] != Rot)
            return false;

    /*2. Der Schwede hält sich einen Hund.*/

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
        if(loesung[i][Nationalitaet] == Schwede &&
           loesung[i][Haustier] != Unbekante && loesung[i][Haustier] != Hund)
            return false;

    /*3. Der Däne trinkt gern Tee.*/

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
        if(loesung[i][Nationalitaet] == Daene &&
           loesung[i][Getraenk] != Unbekante && loesung[i][Getraenk] != Tee)
            return false;

   /* 4. Das grüne Haus steht (direkt) links neben dem weißen Haus.*/

    for(size_t i = 0; i < HAUS_ANZAHL - 1; ++i)
    {
        if(loesung[i][Farbe] == Gruen && loesung[i + 1][Farbe] != Unbekante  &&
           loesung[i + 1][Farbe] != Weiss)
            return false;
    }

    /*5. Der Besitzer des grünen Hauses trinkt Kaffee.*/

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Farbe] == Gruen && loesung[i][Getraenk] != Unbekante &&
           loesung[i][Getraenk] != Kaffee)
            return false;
    }

    /*6. Die Person, die Fußball spielt, hat einen Fisch.*/

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Sport] == Fussball && loesung[i][Haustier] != Unbekante &&
           loesung[i][Haustier] != Fisch)
            return false;
    }

    /*7. Der Mann im mittleren Haus trinkt Milch.*/

    if(loesung[HAUS_ANZAHL / 2][Getraenk] != Unbekante &&
       loesung[HAUS_ANZAHL / 2][Getraenk] != Milch)
        return false;

    /*8. Der Bewohner des gelben Hauses spielt Tennis.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Farbe] == Gelb && loesung[i][Sport] != Unbekante &&
           loesung[i][Sport] != Tennis)
            return false;
    }

    /*
    9. Der Norweger lebt im ersten Haus.
    */

    if(loesung[0][Nationalitaet] != Unbekante &&
       loesung[0][Nationalitaet] != Norweger)
        return false;

    /*
    10. Der Golfspieler wohnt neben der Person mit der Katze.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Sport] == Golf && !pruefen_nachbar(i, Haustier, Katze))
            return false;
    }

    /*
    11. Der Mann mit dem Hamster lebt neben der Person, die Tennis spielt.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Haustier] == Hamster && !pruefen_nachbar(i, Sport, Tennis))
            return false;
    }

    /*
    12. Der Tischtennisspieler trinkt gerne Saft.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Sport] == Tischtennis && loesung[i][Getraenk] != Unbekante &&
           loesung[i][Getraenk] != Saft)
            return false;
    }

    /*
    13. Der Norweger wohnt neben dem blauen Haus.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Nationalitaet] == Norweger &&
           !pruefen_nachbar(i, Farbe, Blau))
            return false;
    }

    /*
    14. Der Deutsche spielt Handball.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Nationalitaet] == Deutsche && loesung[i][Sport] != Unbekante &&
           loesung[i][Sport] != Handball)
            return false;
    }

    /*
    15. Der Golfspieler hat einen Nachbarn, der gerne Wasser trinkt.
    */

    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        if(loesung[i][Sport] == Golf && !pruefen_nachbar(i, Getraenk, Wasser))
            return false;
    }

    return true;
}

void drucken_die_loesung()
{
    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
    {
        printf("|%ld|", i + 1);
        for(size_t j = 0; j < BESCHAFFENHEIT_ANZAHL; ++j)
        {
            printf("%s ", Beschreibung[j][loesung[i][j]]);
        }
        printf("|\n");
    }
}

bool finden_die_losoesung(int x /*Beschaffenheitsnummber*/, int y /*Hausnummer*/)
{
    static int count = 0;
    printf("\nFunktionsaufrufnummer - %ld\n", ++count);
    int tmp = loesung[y][x];
    for(size_t i = 0; i < BESCHAFFENHEIT_ANZAHL; ++i)
    {
        loesung[y][x] = i;
        if(pruefen_die_loesung())
        {
            const size_t new_x = (x + 1) % BESCHAFFENHEIT_ANZAHL;
            const size_t new_y = y + (new_x == 0 ? 1 : 0);
            if(new_y >= HAUS_ANZAHL || finden_die_losoesung(new_x, new_y))
                return true;
        }
    }
    loesung[y][x] = tmp;
    return false;
}

/* Die Frage lautet: Wem gehört der Papagei? */

int main()
{
    for(size_t i = 0; i < HAUS_ANZAHL; ++i)
        for(size_t j = 0; j < BESCHAFFENHEIT_ANZAHL; ++j)
            loesung[i][j] = Unbekante;
    if(finden_die_losoesung(0,0))
        drucken_die_loesung();
    else
        printf("\nKeine Lösung gefunden!\n");
    return 0;
}
