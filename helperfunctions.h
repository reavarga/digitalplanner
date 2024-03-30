#ifndef HELPERFUNCTIONS_H_INCLUDED
#define HELPERFUNCTIONS_H_INCLUDED
#include "menues.h"
void saveToFile(ListaElem *eleje);
bool datumCMP(Datum a, Datum b);
char *filebolStringOlvas(FILE *fp);
char *szovegbeolvas();
ListaElem *readFromFile();
void felszabadit(ListaElem *eleje);
void saveToFile(ListaElem *eleje);


#endif // HELPERFUNCTIONS_H_INCLUDED
