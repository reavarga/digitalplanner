#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "functions.h"
#include "helperfunctions.h"
ListaElem *scanEvent(ListaElem *eleje) {

    ListaElem *ujElem = (ListaElem *) malloc(sizeof(ListaElem));
    if (ujElem == NULL) printf("Could not allocate memory.");

    printf("Please enter the date:\n");
    int year, month, day;
    printf("Year: ");
    scanf("%d", &year);
    printf("Month: ");
    scanf("%d", &month);
    printf("Day: ");
    scanf("%d", &day);
    ujElem->esemeny.d.ev = year;
    ujElem->esemeny.d.honap = month;
    ujElem->esemeny.d.nap = day;

    printf("Next enter your event's title.\n");
    getchar();
    ujElem->esemeny.cim = szovegbeolvas();

    printf("Now enter a comment if you want, or enter a space and a new line if you want to leave it empty.\n");

    ujElem->esemeny.leiras = szovegbeolvas();

    if(eleje==NULL){
        ujElem->kov=NULL;
        eleje=ujElem;
    }
    else if (datumCMP(eleje->esemeny.d, ujElem->esemeny.d)) {
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

    return eleje;
}

ListaElem *deleteEvent(ListaElem *eleje) {
    int year, month, day;
    printf("What is your chosen event? A date and title please.\n");
    printf("Year: ");
    scanf("%d", &year);
    printf("Month: ");
    scanf("%d", &month);
    printf("Day: ");
    scanf("%d", &day);
    printf("Title:\n");
    char *cim = szovegbeolvas();

    ListaElem *lemarado = NULL;
    ListaElem *mozgo = eleje;
    while (mozgo != NULL &&
           (mozgo->esemeny.d.ev != year && mozgo->esemeny.d.honap != month && mozgo->esemeny.d.nap != day
            && strcmp(mozgo->esemeny.cim, cim) != 0)) {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }
    if (mozgo == NULL) {           /* nincs ilyen elem */
        printf("Event not found. Try again.\n");
    } else if (lemarado == NULL) { /* az első elemet kell törölni */
        ListaElem *ujeleje = mozgo->kov;
        free(mozgo);
        eleje = ujeleje;
    } else {                       /* a közepéről/végéről törlünk */
        lemarado->kov = mozgo->kov;
        free(mozgo);
    }

    return eleje;
}

ListaElem *editEvent(ListaElem *eleje) {
    deleteEvent(eleje);
    printf("Your new event:");
    return scanEvent(eleje);


}

void searchByDate(ListaElem *eleje) {
    int ev, honap, nap;
    ListaElem *mozgo = eleje;
    printf("Please enter the year the month and the day you want to search.\n");
    printf("Year: ");
    scanf("%d", &ev);
    printf("Month: ");
    scanf("%d", &honap);
    printf("Day: ");
    scanf("%d", &nap);
    while (mozgo != NULL) {
        if (mozgo->esemeny.d.ev == ev && mozgo->esemeny.d.honap == honap && mozgo->esemeny.d.nap == nap) {
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);
        }
        mozgo = mozgo->kov;
    }

}


void searchByTitle(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    getchar();
    char *kcim = szovegbeolvas();
 bool kiirt=false;
    while (mozgo != NULL) {
        if (strcmp(mozgo->esemeny.cim, kcim) == 0) {
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);
                kiirt=true;
        } mozgo = mozgo->kov;

    }
    if(!kiirt){
        printf("no matches");
    }
    free(kcim);
}

void listByYear(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    printf("Year you want to list by?\n");
    int year;
    scanf("%d", &year);
    while (mozgo != NULL) {
        if (mozgo->esemeny.d.ev == year) {
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);
        }

        mozgo = mozgo->kov;
    }

}

void listByMonth(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    printf("Month you want to search by? Please add a year and a month.\n");
    int year, month;
    printf("Year: ");
    scanf("%d", &year);
    printf("Month: ");
    scanf("%d", &month);
    while (mozgo != NULL) {
        if (mozgo->esemeny.d.ev == year && mozgo->esemeny.d.honap == month) {
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);

        }
        mozgo = mozgo->kov;
    }
}

void listByDay(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    printf("Day you want to search by? Please add a year,a month and the day.\n");
    int year, month, day;
    printf("Year: ");
    scanf("%d", &year);
    printf("Month: ");
    scanf("%d", &month);
    printf("Day: ");
    scanf("%d", &day);
    while (mozgo != NULL) {
        if (mozgo->esemeny.d.ev == year && mozgo->esemeny.d.honap == month && mozgo->esemeny.d.nap == day) {
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);

        }
        mozgo = mozgo->kov;
    }

}

void listByInterval(ListaElem *eleje) {
    ListaElem *mozgo = eleje;
    printf("Interval you want to search in? Please enter the year, month and day of the first one then the second one.\nThe first one should be the earlier date.\n");
    int fyear, fmonth, fday;
    printf("1st. of the interval year: ");
    scanf("%d", &fyear);
    printf("1st. of the interval month: ");
    scanf("%d", &fmonth);
    printf("1st. of the interval day: ");
    scanf("%d", &fday);
    int syear, smonth, sday;
    printf("2nd. of the interval year: ");
    scanf("%d", &syear);
    printf("2nd. of the interval month: ");
    scanf("%d", &smonth);
    printf("2nd. of the interval day: ");
    scanf("%d", &sday);
    Datum a;
    a.ev=fyear;
    a.honap=fmonth;
    a.nap=fday;
    Datum b;
    b.ev=syear;
    b.honap=smonth;
    b.nap=sday;
    while (mozgo != NULL) {
        if(datumCMP(mozgo->esemeny.d, a) && !datumCMP(mozgo->esemeny.d,b)){
            printf("%d.%d.%d %s - %s\n", mozgo->esemeny.d.ev, mozgo->esemeny.d.honap, mozgo->esemeny.d.nap,
                   mozgo->esemeny.cim, mozgo->esemeny.leiras);

        }
        mozgo = mozgo->kov;
    }
}



