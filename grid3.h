#ifndef GRID3_H
#define GRID3_H

struct Cell{
    int* ids;
    int size;
    int capacity;
};

void addToCell(struct Cell* cell,int a);

void removeFromCell(struct Cell* cell,int idx);

#endif