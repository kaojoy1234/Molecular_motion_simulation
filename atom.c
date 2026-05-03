#include"atom.h"
#include"atom.h"
#include<stdlib.h>

void resizeAGList(struct AGList* agl,int newSize){
                if(agl->capacity==0){
                                agl->data = (struct AtomGroup*)malloc(newSize*sizeof(struct AtomGroup));
                }
                else{
                                agl->data = (struct AtomGroup*)realloc(agl->data,newSize*sizeof(struct AtomGroup));
                }
                agl->capacity = newSize;
}

void addtoList(struct AGList* agl,struct AtomGroup ag){
                if(agl->capacity<=agl->size){
                                resizeAGList(agl,agl->capacity+10);
                }
                agl->data[agl->size]=ag;
                agl->size++;
}