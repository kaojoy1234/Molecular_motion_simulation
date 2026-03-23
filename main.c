#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"atom.h"

#define W 0.0001

int nowTick = 0;

float dtt = 0.001; //delta time per tick

void step(struct Atom* atom){
    float v0x = (*atom).px/W;
    float v0y = (*atom).py/W;
    float v0z = (*atom).pz/W;

    float dx = v0x+(1/2)*(*atom).fx/W*dtt*dtt;
    float dy = v0y+(1/2)*(*atom).fy/W*dtt*dtt;
    float dz = v0z+(1/2)*(*atom).fz/W*dtt*dtt;

    (*atom).x += dx;
    (*atom).y += dy;
    (*atom).z += dz;

    nowTick++;
}

int main(){
    struct Atom a =
        {
            10, //x
            10, //y
            0,  //z
            10, //px
            10, //py
            0,  //pz
            0,  //fx
            0,  //fy
            0   //fz
        };
    while(1){
        step(&a);
        printf("pos:%f %f %f\n",a.x,a.y,a.z);
        printf("%d\n",nowTick);
        sleep(1);
    }
    return 0;
}