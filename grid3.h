#ifndef GRID3_H
#define GRID3_H
#include"atom.h"

struct AGList{
                int size;
                int capacity;
                struct AtomGroup** data;
};

void resizeAGList(struct AGList* agl,int newSize);

void addtoList(struct AGList* agl,struct AtomGroup* ag);

void removeFromList(struct AGList* agl,int agIdx);

#endif // GRID3_H
