#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"atom.h"
#include"tdvector.h"

#define W 0.0001

int nowTick = 0;

float dtt = 0.001; //delta time per tick

void step(struct AtomGroup* ag){
    //x, = v0 * t + 1/2 * a * t^2;

    struct TdVector v0;
    float v0x,v0y,v0z;
    tdGetVXYZ((*ag).representAtom.p,&v0x,&v0y,&v0z);
    tdSetVXYZ(v0x,v0y,v0z,&v0);
    tdVMul(1/(W*(*ag).n),v0,&v0);

    struct TdVector a;
    float ax,ay,az;
    tdGetVXYZ((*ag).representAtom.f,&ax,&ay,&az);
    tdSetVXYZ(ax,ay,az,&a);
    tdVMul(1/(W*(*ag).n),a,&a);

    tdVMul(dtt,v0,&v0);
    tdVMul(dtt*dtt/2,a,&a);

    struct TdVector l;
    tdVPlus(v0,a,&l);

    tdVPlus((*ag).representAtom.pos,l,&((*ag).representAtom.pos));

    nowTick++;
}

int main(){
    struct AtomGroup ag;
    tdSetVXYZ(1,1,2,&(ag.representAtom.pos));
    tdSetVXYZ(1,1,0,&(ag.representAtom.p));
    tdSetVXYZ(1,0,0,&(ag.representAtom.f));

    float posx,posy,posz;
    tdGetVXYZ(ag.representAtom.pos,&posx,&posy,&posz);
    float fx,fy,fz;
    tdGetVXYZ(ag.representAtom.f,&fx,&fy,&fz);
    float px,py,pz;
    tdGetVXYZ(ag.representAtom.p,&px,&py,&pz);
    printf("pos:%f %f %f\nf:%f %f %f\np:%f %f %f",posx,posy,posz,fx,fy,fz,px,py,pz);

    ag.n = 100;

    while (1)
    {
        step(&ag);

        float x,y,z;
        tdGetVXYZ(ag.representAtom.pos,&x,&y,&z);
        printf("pos:%f %f %f\nnowtick:%d\n",x,y,z,nowTick);
        sleep(1);
    }
    
    return 0;
}