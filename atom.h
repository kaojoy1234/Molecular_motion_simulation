#ifndef ATOM_H
#define ATOM_H
#include"tdvector.h"

struct Atom {
    struct TdVector pos;
    struct TdVector p;
};

struct AtomGroup{
    struct TdVector pos;
    struct TdVector p;
    float n;
    float r;
    int id;
};

struct AGList{
                int size;
                int capacity;
                struct AtomGroup* data;
};

void resizeAGList(struct AGList* agl,int newSize);

void addtoList(struct AGList* agl,struct AtomGroup ag);

#endif
