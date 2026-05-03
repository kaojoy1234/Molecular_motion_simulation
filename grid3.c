#include "grid3.h"
#include <stdlib.h>

void addToCell(struct Cell* cell,int a){
    if(cell->capacity == 0){
        cell->ids = malloc(10*sizeof(int));
        cell->capacity = 10;
    }
    else if (cell->size >= cell->capacity)
    {
        cell->ids = realloc(cell->ids,cell->capacity*2*sizeof(int));
        cell->capacity *= 2;
    }
    cell->ids[cell->size] = a;
    cell->size++;
}