#include <stdio.h>
#include "introprog_complexity_steps_input.h"

long for_linear(int n, int* befehle)
{
    long sum = 0;
    *befehle += 1;   // inc wegen Wertzuweisung von sum

    *befehle += 1;   // inc wegen Wertzuweisung von i in for-loop
    for(int i = 1; i <= n; ++i) { // i=0:2 i=1:3 i=2:3 i=3:3 i=4:3 i=5:3 i=6:1
        *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = true
        sum += get_value_one();
        *befehle += 1;   // inc wegen Inkrementierung von sum
        *befehle += 1;   // inc wegen Inkrementierung von i
    }
    *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = false

    return sum;
}

long for_quadratisch(int n, int* befehle)
{
    long sum = 0;
    *befehle += 1;   // inc wegen Wertzuweisung von sum

    *befehle += 1;   // inc wegen Wertzuweisung von i in for-loop
    for(int i = 1; i <= n; ++i) {
        *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = true

        *befehle += 1;   // inc wegen Wertzuweisung von j in for-loop
        for(int j = 1; j <= n; ++j) {
            *befehle += 1;   // inc wegen Vergleich von j und n und Ergebnis = true
            sum += get_value_one();
            *befehle += 1;   // inc wegen Inkrementierung von sum
            *befehle += 1;   // inc wegen Inkrementierung von j
        }
        *befehle += 1;   // inc wegen Vergleich von j und n und Ergebnis = false

        *befehle += 1;   // inc wegen Inkrementierung von i
    }
    *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = false 

    return sum; // 1
}

long for_kubisch(int n, int* befehle)
{
    // TODO: Die Befehle müssen richtig gezählt werden

    long sum = 0;
    *befehle += 1;   // inc wegen Wertzuweisung von sum

    *befehle += 1;   // inc wegen Wertzuweisung von i in for-loop
    for(int i = 1; i <= n; ++i) {
        *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = true
        
        *befehle += 1;   // inc wegen Wertzuweisung von j in for-loop
        for(int j = 1; j <= n; ++j) {            
            *befehle += 1;   // inc wegen Vergleich von j und n und Ergebnis = true

            *befehle += 1;   // inc wegen Wertzuweisung von k in for-loop
            for(int k = 1; k <= n; ++k) {
                *befehle += 1;   // inc wegen Vergleich von k und n und Ergebnis = true
                sum += get_value_one();
                *befehle += 1;   // inc wegen Inkrementierung von sum
                *befehle += 1;   // inc wegen Inkrementierung von k
            }
            *befehle += 1;   // inc wegen Vergleich von k und n und Ergebnis = false

            *befehle += 1;   // inc wegen Inkrementierung von j
        }
        *befehle += 1;   // inc wegen Vergleich von j und n und Ergebnis = false

        *befehle += 1;   // inc wegen Inkrementierung von i
    }
    *befehle += 1;   // inc wegen Vergleich von i und n und Ergebnis = false

    return sum; //1
}


int main(int argc, char *argv[])
{
    const int WERTE[] = {5,6,7,8,9,10};
    const int LEN_WERTE = 6;
    const int LEN_ALGORITHMEN = 3;

    long befehle_array[LEN_ALGORITHMEN][LEN_WERTE];
    long werte_array[LEN_ALGORITHMEN][LEN_WERTE];
    double laufzeit_array[LEN_ALGORITHMEN][LEN_WERTE];

    for(int j = 0; j < LEN_WERTE; ++j) {
        int n = WERTE[j];
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("Starte Algorithmus %d mit Wert %d\n",
                (i+1), n);
            int anzahl_befehle = 0;
            int wert = 0;

            // Starte den Timer
            start_timer();

            // Aufruf der entsprechenden Funktion
            if(i==0) {
                wert = for_linear(n, &anzahl_befehle);
            }
            else if(i==1) {
                wert = for_quadratisch(n, &anzahl_befehle);
            }
            else if(i==2) {
                wert = for_kubisch(n, &anzahl_befehle);
            }

            // Speichere Laufzeit, Rückgabewert und Anzahl
            // ausgeführter Befehle ab
            laufzeit_array[i][j] = end_timer();
            werte_array[i][j] = wert;
            befehle_array[i][j] = anzahl_befehle;
        }
        printf("\n");
    }

    // Ausgabe der Rückgabewerte, Anzahl ausgeführter Befehle
    // sowie der gemessenen Laufzeiten (in Millisekunden)
    printf("%3s \t%-28s \t%-28s \t%-28s\n", "","linear", "quadratisch", "kubisch");
    printf("%3s \t %5s %10s %10s\t %5s %10s %10s\t %5s %10s %10s\n", "n","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit","Wert","Befehle","Laufzeit");

    for(int j = 0; j < LEN_WERTE; ++j) {
        printf("%3d \t ",WERTE[j]);
        for(int i = 0; i < LEN_ALGORITHMEN; ++i) {
            printf("%5ld %10ld %10.4f \t ", werte_array[i][j], befehle_array[i][j], laufzeit_array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
