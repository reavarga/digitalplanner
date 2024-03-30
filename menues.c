#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

void searchEventMenu(ListaElem *eleje){
    int sorszam;
    printf("How would you like to search? Pick a number.\n");
    printf("1. By date\n2. By event title\n");
    scanf("%d", &sorszam);

    if (sorszam == 1) {
        searchByDate(eleje);
    } else if (sorszam == 2) {
        (searchByTitle(eleje));
    } else {
        printf("\nNot a valid number\n");
    }
}

void listEventsMenu(ListaElem *eleje) {
    int sorszam;
    printf("How would you like to list? Pick a number.\n");
    printf("1. By year\n2. By month\n3. By day\n4. By intervall\n");
    scanf("%d", &sorszam);
    switch (sorszam) {
        case 1:
            listByYear(eleje);
            break;
        case 2:
            listByMonth(eleje);
            break;
        case 3:
            listByDay(eleje);
            break;
        case 4:
            listByInterval(eleje);
    }
    if (sorszam > 4) {
        printf("Invalid number. Try again.");
    }
}

ListaElem *menu(ListaElem *eleje, bool *vege) {
    int sorszam;
    printf("Hello! What would you like to do? Please pick a number.\n");
    printf("1. New event\n");
    printf("2. Delete event\n");
    printf("3. Search event\n");
    printf("4. Edit event\n");
    printf("5. List events\n");
    printf("6. Escape\n");
    scanf("%d", &sorszam);
    switch (sorszam) {
        case 1:
            eleje = scanEvent(eleje); //esemenyt beolvas
            break;
        case 2:
            eleje = deleteEvent(eleje);//torol
            break;
        case 3:
            searchEventMenu(eleje);//keres datum vagy cim alapjan
            break;
        case 4:
            eleje = editEvent(eleje);//megkeres es utana valtoztat
            break;
        case 5:
            listEventsMenu(eleje);//keres es listaz
            break;
        case 6:
            *vege=false;
            printf("Now you can close the program.\n");
            break;
    }
    if (sorszam > 6 || sorszam < 1) {
        printf("Invalid numer. Try again.\n");
    }
    return eleje;
}
