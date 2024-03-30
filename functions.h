#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
typedef struct Datum {
    int ev, honap, nap;
} Datum;

typedef struct Esemeny {
    Datum d;
    char *cim;
    char *leiras;
} Esemeny;

typedef struct ListaElem {
    Esemeny esemeny;
    struct ListaElem *kov;
} ListaElem;

ListaElem *scanEvent(ListaElem *eleje);
void searchByTitle(ListaElem *eleje);
void searchByDate(ListaElem *eleje);
ListaElem *deleteEvent(ListaElem *eleje);
ListaElem *editEvent(ListaElem *eleje);
void listByYear(ListaElem *eleje);
void listByMonth(ListaElem *eleje);
void listByDay(ListaElem *eleje);
void listByInterval(ListaElem *eleje);



#endif // FUNCTIONS_H_INCLUDED
