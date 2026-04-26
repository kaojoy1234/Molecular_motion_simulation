#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"atom.h"
#include"tdvector.h"
#include"grid3.h"

#define W 0.0001

int nowTick = 0;

float dtt = 0.001; //delta time per tick

void step(struct AGList* agl,struct AGList grids[10][10][10])
{
                //x, = v0 * t + 1/2 * a * t^2;
                for(int i=0; i<agl->size; i++)
                {
                                struct AtomGroup* ag = agl->data[i];
                                //collpse
                                float x,y,z;
                                tdGetVXYZ(ag->representAtom.pos,&x,&y,&z);
                                int ix,iy,iz;
                                ix = x/5;
                                iy = y/5;
                                iz = z/5;
                                for(int j=0;j<grids[ix][iy][iz].size;j++){
                                                if(grids[ix][iy][iz].data[j]!=NULL&&
                                                     grids[ix][iy][iz].data[j]->representAtom.id != ag->representAtom.id){
                                                                float length;
                                                                struct TdVector r;
                                                                tdVMin(ag->representAtom.pos,grids[ix][iy][iz].data[j]->representAtom.pos,&r);
                                                                tdLenOfV(r,&length);
                                                                if(length<3){
                                                                                printf("Idx:%d\thit!\n",i);
                                                                }
                                                }
                                }
                                //
                                struct TdVector v;
                                float vx,vy,vz;
                                tdGetVXYZ((*ag).representAtom.p,&vx,&vy,&vz);
                                tdSetVXYZ(vx,vy,vz,&v);
                                tdVMul(1/(W*(*ag).n),v,&v);

                                tdVMul(dtt,v,&v);

                                tdVPlus((*ag).representAtom.pos,v,&((*ag).representAtom.pos));
                                //update grids
                                float nx,ny,nz;
                                tdGetVXYZ(ag->representAtom.pos,&nx,&ny,&nz);
                                int nix,niy,niz;
                                nix = nx/5;
                                niy = ny/5;
                                niz = nz/5;
                                if(nix!=nx||niy!=ny||niz!=nz){
                                                removeFromList(&grids[ix][iy][iz],ag->agIdx);
                                                addtoList(&grids[nix][niy][niz],ag);
                                }

                }
                nowTick++;
}

int main()
{
                //a block measure 5 units.
                struct AGList grids[10][10][10];
                for(int i=0;i<10;i++)
                                for(int j=0;j<10;j++)
                                                for(int k=0;k<10;k++){
                                                                grids[i][j][k].size = 0;
                                                                grids[i][j][k].capacity = 0;
                                                }
                struct AGList agl;
                agl.size=0;
                agl.capacity=0;

                struct AtomGroup ag1;
                tdSetVXYZ(10,10,10,&(ag1.representAtom.pos));
                tdSetVXYZ(-10,-10,-10,&(ag1.representAtom.p));
                ag1.n = 100;
                addtoList(&agl,&ag1);
                float ag1px,ag1py,ag1pz;
                tdGetVXYZ(ag1.representAtom.pos,&ag1px,&ag1py,&ag1pz);
                int i1x,i1y,i1z;
                i1x = ag1px/5;
                i1y = ag1py/5;
                i1z = ag1pz/5;
                addtoList(&grids[i1x][i1y][i1z],&ag1);
                ag1.representAtom.id = 0;

                struct AtomGroup ag2;
                tdSetVXYZ(0,0,0,&(ag2.representAtom.pos));
                tdSetVXYZ(10,10,10,&(ag2.representAtom.p));
                ag2.n = 100;
                addtoList(&agl,&ag2);
                float ag2px,ag2py,ag2pz;
                tdGetVXYZ(ag2.representAtom.pos,&ag2px,&ag2py,&ag2pz);
                int i2x,i2y,i2z;
                i2x = ag2px/5;
                i2y = ag2py/5;
                i2z = ag2pz/5;
                addtoList(&grids[i2x][i2y][i2z],&ag2);
                ag2.representAtom.id = 1;

                while (1)
                {
                                step(&agl,grids);

                                printf("nowTick:%d\n\n",nowTick);
                                for(int i=0; i<agl.size; i++){
                                                printf("index:%d\n",i);
                                                float x,y,z;
                                                tdGetVXYZ(agl.data[i]->representAtom.pos,&x,&y,&z);
                                                printf("pos:%f\t%f\t%f\n",x,y,z);
                                                printf("grid:%f\t%f\t%f\n",x/5,y/5,z/5);
                                }
                                sleep(1);
                }

                return 0;
}
