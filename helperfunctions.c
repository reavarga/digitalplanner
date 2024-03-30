#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
#include "debugmalloc.h"
bool datumCMP(Datum a, Datum b) {
    if (a.ev < b.ev) return false;
    else if (b.ev < a.ev) return true;
    else if (a.honap < b.honap) return false;
    else if (b.honap < a.honap) return true;
    else if (a.nap < b.nap) return false;
    else return true;
}

char *filebolStringOlvas(FILE *fp) {
    char *szoveg = (char *) malloc(sizeof(char));
    if (szoveg == NULL) printf("Could not allocate memory.");
    szoveg[0] = '\0';
    int hossz = 1;
    char c;
    while (fscanf(fp, "%c", &c) && c != '\n') {
        char *ujstring = malloc(sizeof(char) * (hossz + 1));
        if (ujstring == NULL) printf("Could not allocate memory.");
        for (int i = 0; i < hossz - 1; i++) {
            ujstring[i] = szoveg[i];
        }
        ujstring[hossz - 1] = c;
        ujstring[hossz] = '\0';
        free(szoveg);
        szoveg = ujstring;
        hossz++;
    }
    return szoveg;
}

char *szovegbeolvas() {
    char *szoveg = (char *) malloc(sizeof(char));
    if (szoveg == NULL) printf("could not allocate memory.");
    szoveg[0] = '\0';
    int hossz = 1;
    char c;
    while (scanf("%c", &c) && c != '\n') {
        char *ujstring = malloc(sizeof(char) * (hossz + 1));
        if (ujstring == NULL) printf("Could not allocate memory.");
        for (int i = 0; i < hossz - 1; i++) {
            ujstring[i] = szoveg[i];
        }
        ujstring[hossz - 1] = c;
        ujstring[hossz] = '\0';
        free(szoveg);
        szoveg = ujstring;
        hossz++;
    }
    return szoveg;
}
ListaElem *readFromFile() {
    FILE *fp;
    fp = fopen("events.txt", "a+");
    if (fp == NULL) {
        perror("Could not open file.");
    }
    if (fp == NULL) {
        return NULL;
    }
    ListaElem *eleje = NULL;

    int ev, honap, nap;

    if (fscanf(fp, "%d %d %d ", &ev, &honap, &nap) == 3) {
        eleje = (ListaElem *) malloc(sizeof(ListaElem));
        eleje->esemeny.d.ev = ev;
        eleje->esemeny.d.honap = honap;
        eleje->esemeny.d.nap = nap;
        eleje->esemeny.cim = filebolStringOlvas(fp);
        eleje->esemeny.leiras = filebolStringOlvas(fp);
        eleje->kov = NULL;
    } else {
        printf("empty.");
        return NULL;
    }


    while (fscanf(fp, "%d %d %d ", &ev, &honap, &nap) == 3) {
        ListaElem *ujElem = (ListaElem *) malloc(sizeof(ListaElem));
        ujElem->esemeny.d.ev = ev;
        ujElem->esemeny.d.honap = honap;
        ujElem->esemeny.d.nap = nap;
        ujElem->esemeny.cim = filebolStringOlvas(fp);
        ujElem->esemeny.leiras = filebolStringOlvas(fp);

        if (datumCMP(eleje->esemeny.d, ujElem->esemeny.d)) {
            ujElem->kov = eleje;
            eleje = ujElem;
        } else {
            ListaElem *lemarado = eleje;
            ListaElem *mozgo = eleje->kov;
            while (mozgo != NULL && !datumCMP(mozgo->esemeny.d, ujElem->esemeny.d)) {
                lemarado = lemarado->kov;
                mozgo = mozgo->kov;
            }
            ujElem->kov = mozgo;
            lemarado->kov = ujElem;
        }
    }
    fclose(fp);
    return eleje;
}
void felszabadit(ListaElem *eleje) {
    ListaElem *iter = eleje;
    while (iter != NULL) {
        ListaElem *kov = iter->kov;
        free(iter->esemeny.cim);
        free(iter->esemeny.leiras);
        free(iter);
        iter = kov;

    }
}

void saveToFile(ListaElem *eleje) {
    FILE *fp;
    fp = fopen("events.txt", "w"); /* megnyitás * w+ vagy r+*/
    if (fp == NULL) {
        perror("Could not open file.");
    }
    ListaElem *mozgo = eleje;
    while (mozgo != NULL) {
        fprintf(fp, "%d\n%d\n%d\n%s\n%s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                mozgo->esemeny.cim, mozgo->esemeny.leiras);
        mozgo = mozgo->kov;
    }
    fclose(fp);
}
