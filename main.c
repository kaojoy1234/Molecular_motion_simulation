#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"atom.h"
#include"tdvector.h"

#define W 0.0001

int nowTick = 0;

float dtt = 0.001; //delta time per tick

void step(struct Atom* atom){
    //x, = v0 * t + 1/2 * a * t^2;

    struct TdVector v0;
    float v0x,v0y,v0z;
    tdGetVXYZ((*atom).p,&v0x,&v0y,&v0z);
    tdVMul(1/W,v0,&v0);

    struct TdVector a;
    float ax,ay,az;
    tdGetVXYZ((*atom).f,&ax,&ay,&az);
    tdVMul(1/W,a,&a);

    tdVMul(dtt,v0,&v0);
    tdVMul(dtt*dtt/2,a,&a);

    struct TdVector r;
    tdVPlus(v0,a,&r);

    tdVPlus((*atom).pos,r,&((*atom).pos));

    nowTick++;
}

int main(){
    struct Atom a;
    tdSetVXYZ(1,1,2,&(a.pos));
    tdSetVXYZ(1,1,0,&(a.p));
    tdSetVXYZ(1,0,0,&(a.f));

    while (1)
    {
        step(&a);

        float x,y,z;
        tdGetVXYZ(a.pos,&x,&y,&z);
        printf("pos:%f %f %f\nnowtick:%d\n",x,y,z,nowTick);
    }
    
    return 0;
}