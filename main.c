#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "debugmalloc.h"
#include "functions.h"
#include "helperfunctions.h"

int main() {

    ListaElem *eleje;
    eleje = readFromFile();

    bool vege=true;
    while (vege) {
        eleje=menu(eleje, &vege);
    }
    saveToFile(eleje);
    felszabadit(eleje);

    return 0;
}

