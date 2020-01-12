#include <stdio.h>
#include <stdlib.h>
#include <string.h> // fuer memcpy

// https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/** Jonas Berger 2020.
 *  Implementierung des Mergesort Sortieralgorithmus from scratch, sortiert ein hardgecodetes int Array
 **/

// Strukturdefinition des Elements. Im Gegensatz zum Array wird die Groesse mitgespeichert.
typedef struct element {
    int groesse;
    int *inhalt;
} element_t;

// Funktionsdeklarationen
element_t *create_element(int);
void init_element(element_t *);
void print_element(element_t *);
void divide(element_t *);
void conquer(element_t *, element_t *, element_t *);

/** MAIN **/
int main() {
    printf(ANSI_COLOR_RED);

    printf("===       ===\n");
    printf("= MERGESORT =\n");
    printf("===       ===\n");

    // Init
    element_t *elem = create_element(10);
    init_element(elem);
    print_element(elem);

    // Mergesort rekursiv
    divide(elem);

    print_element(elem);

    printf(ANSI_COLOR_RESET);
    return 0;
}

/** Erstellt ein Element vorgegebener Groesse
 *  Uebergabeparameter: groesse [int]
 *  Rueckgabeparameter: Pointer auf element_t
 **/
element_t *create_element(int groesse) {
    printf(ANSI_COLOR_BLUE);
    printf("DEBUG : CREATE_ELEMENT(%d)\n", groesse);
    element_t *elem = (element_t *) malloc(sizeof(element_t));
    elem->groesse = groesse;
    elem->inhalt = (int *) malloc(sizeof(int)*groesse);

    printf("Speicherallokation in %p erfolgreich\n", elem);
    printf(ANSI_COLOR_RESET);
    return elem;
}

/** Initialisiert ein Element mit 0 => Zufallszahlen < 100
 *  Uebergabeparameter: Pointer auf element_t
 *  Rueckgabeparameter: keine
 **/
void init_element(element_t *elem) {
    printf(ANSI_COLOR_GREEN);
    printf("DEBUG : INIT_ELEMENT(%p)\n", elem);
    printf("DEBUG : Element hat die Groesse %d\n", elem->groesse);
    //init rand()
    srand(1);

    // Struktur befuellen
    for(int i = 0; i < elem->groesse; i++) {
        elem->inhalt[i] = rand()%100;
    }
    printf(ANSI_COLOR_RESET);
}

/** Druckt den Inhalts eines element_t auf die Standardausgabe
 *  Uebergabeparameter: Pointer auf element_t
 *  Rueckgabeparameter: keine
 **/
void print_element(element_t *elem) {
    printf(ANSI_COLOR_YELLOW);
    printf("DEBUG : PRINT_ELEMENT(%p)\n", elem);
    printf("DEBUG : Element hat die Groesse %d\n", elem->groesse);

    for(int i = 0; i < elem->groesse; i++) {
        printf("[%d] = %2d\n", i, elem->inhalt[i]);
    }
    printf(ANSI_COLOR_RESET);
}

/** Teilt ein uebergegebenes element_t in zwei kleinere element_t auf, soweit moeglich; arbeitet rekursiv bis zur Atomaritaet
 *  Uebergabeparameter: Pointer auf element_t
 *  Rueckgabeparameter: keine
 **/
void divide(element_t *elem) {
    printf(ANSI_COLOR_CYAN);
    printf("DEBUG : DIVIDE(%p)\n", elem);
    printf("DEBUG : Element hat die Groesse %d\n", elem->groesse);

    if(elem->groesse > 2) {
        printf("DEBUG : Element kann weiter unterteilt werden\n");
        element_t *elem01 = create_element(elem->groesse/2);
        // Daten transferieren
        memcpy(elem01->inhalt, elem->inhalt, sizeof(int)*elem->groesse/2);
        divide(elem01);

        printf(ANSI_COLOR_CYAN "DEBUG : Fahre mit zweitem Element fort\n");
        element_t *elem02 = create_element(elem->groesse-(elem->groesse/2));
        // Daten transferieren, zweite Haelfte (Start dort wo Transfer zu elem01 geendet hat)
        memcpy(elem02->inhalt, (elem->inhalt)+elem->groesse/2, sizeof(int)*((elem->groesse-(elem->groesse/2))));
        divide(elem02);

        conquer(elem, elem01, elem02);
    }

    /*if(elem->groesse <= 2) {
        print_element(elem);
    }*/

    printf(ANSI_COLOR_RESET);
}

/** Sortiert ein uebergebenes element_t aufsteigend
 *  Uebergabeparameter: Pointer auf element_t
 *  Rueckgabeparameter: keine
 **/
void conquer(element_t *elem, element_t *elem01, element_t *elem02) {
    printf(ANSI_COLOR_MAGENTA);
    printf("DEBUG : CONQUER(elem:%p, elem01:%p, elem02:%p)\n", elem, elem01, elem02);
    printf("DEBUG : Ergebnis Element hat die Groesse %d\n", elem->groesse);
    printf("DEBUG : elem01 hat die Groesse %d\n", elem01->groesse);
    printf("DEBUG : elem02 hat die Groesse %d\n", elem02->groesse);

    int elem01_count = 0, elem02_count = 0, elem_count = 0;

    // Sortieren startet, fuege das naechstkleinere obenliegende Objekt aus den Stapeln elem01 oder elem02 ein
    while(elem_count<=elem->groesse) {
        if(elem01_count <= elem01->groesse && elem01->inhalt[elem01_count] < elem02->inhalt[elem02_count]) {
            printf("DEBUG : elem01[%d] = %d < elem02[%d] = %d ODER COUNT MAX fuege ein in elem[%d]\n", elem01_count, elem01->inhalt[elem01_count], elem02_count, elem02->inhalt[elem02_count], elem_count);
            elem->inhalt[elem_count] = elem01->inhalt[elem01_count];
            elem01_count++;
            printf("DEBUG : elem01_count = %d; elem_count = %d\n", elem01_count, elem_count);
        } else if(elem02_count <= elem02->groesse && elem01->inhalt[elem01_count] > elem02->inhalt[elem02_count]) {
            printf("DEBUG : elem02[%d] = %d < elem01[%d] = %d ODER COUNT MAX fuege ein in elem[%d]\n", elem02_count, elem02->inhalt[elem02_count], elem01_count, elem01->inhalt[elem01_count],elem_count);
            elem->inhalt[elem_count] = elem01->inhalt[elem01_count];
            elem02_count++;
            printf("DEBUG : elem02_count = %d; elem_count = %d\n", elem02_count, elem_count);

        }
        elem_count++;
    }

    printf(ANSI_COLOR_RESET);
}
