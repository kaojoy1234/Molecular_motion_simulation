#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include "atom.h"
#include "tdvector.h"
#include "grid3.h"

#define W 0.0001

int nowTick = 0;

float dtt = 0.001; // delta time per tick

static inline int clamp(int* x,int* y,int* z,int size){
     *x = (*x<0)*0 + (*x>=size)*size + *x * (*x>=0&&*x<size);
     *y = (*y<0)*0 + (*y>=size)*size + *y * (*y>=0&&*y<size);
     *z = (*z<0)*0 + (*z>=size)*size + *z * (*z>=0&&*z<size);
}

int check(int x,int y,int z,int size){
     return ( (x>=0 && x<size) && (y>=0 && y<size) && (z>=0 && z<size) );
}

void step(struct AGList *agl, struct Cell grids[10][10][10])
{
     float J = 0;
     int hit = 0;
     int hitWall = 0;
     int out = 0;
     // x, = v0 * t + 1/2 * a * t^2;
     for (int i = 0; i < agl->size; i++)
     {
          struct AtomGroup* ag = &(agl->data[i]);

          // collpse
          int ix, iy, iz;
          ix = ag->pos.x / 10;
          iy = ag->pos.y / 10;
          iz = ag->pos.z / 10;
          
          for(int j=-1;j<=1;j++){
               for(int k=-1;k<=1;k++){
                    for(int l=-1;l<=1;l++){
                         if(check(ix+j,iy+k,iz+l,10)){
                              for (int m = 0; m < grids[ix][iy][iz].size; m++)
                              {
                                   if (grids[ix+j][iy+k][iz+l].ids[m] != ag->id)
                                   {
                                        printf("%d\t%d\t%d\n",grids[ix+j][iy+k][iz+l].ids[m]);
                                        printf("[%d]\n",grids[ix+j][iy+k][iz+l].ids[m]);
                                        /*
                                        float length;
                                        struct TdVector r;
                                        tdVMin(ag->pos, agl->data[grids[ix+j][iy+k][iz+l].ids[m]].pos, &r);
                                        tdLenOfV(r, &length);
                                        if (length < 3)
                                        {
                                             hit++;        
                                        }
                                        */
                                   }
                              }
                                                
                         }
                    }
               }
          }
          
          
          int havehitWall = 0;
          // Wall
          if (ag->pos.x < 3 || ag->pos.x + 3 >= 10)
          {
               struct TdVector n;
               n.x = 1 * (ag->pos.x < 3) - 1 * (ag->pos.x + 3 >= 100);
               n.y = 0;
               n.z = 0;
               if (ag->p.x * n.x < 0)
               {
                    float dJ = 2*ag->p.x;
                    J += dJ / dtt;
                    ag->p.x *= -1;
                    if(!havehitWall){
                         hitWall++;
                         havehitWall = 1;
                    }
               }
          }
          if (ag->pos.y < 3 || ag->pos.y + 3 >= 10)
          {
               struct TdVector n;
               n.x = 0;
               n.y = 1 * (ag->pos.y < 3) - 1 * (ag->pos.y + 3 >= 100);
               n.z = 0;
               if (ag->p.y * n.y < 0)
               {
                    float dJ = 2*ag->p.y;
                    J += dJ / dtt;
                    ag->p.y *= -1;
                    if(!havehitWall){
                         hitWall++;
                         havehitWall = 1;
                    }
               }
          }
          if (ag->pos.z < 3 || ag->pos.z + 3 >= 10)
          {
               struct TdVector n;
               n.x = 0;
               n.y = 0;
               n.z = 1 * (ag->pos.z < 3) - 1 * (ag->pos.z + 3 >= 100);
               if (ag->p.z * n.z < 0)
               {
                    float dJ = 2*ag->p.z;
                    J += dJ / dtt;
                    ag->p.z *= -1;
                    if(!havehitWall){
                         hitWall++;
                         havehitWall = 1;
                    }
               }
          }
          if(!check(ag->pos.x,ag->pos.y,ag->pos.z,97)){
               out++;
          };
          //
          // update pos
          struct TdVector v;
          v = ag->p;
          tdVMul(dtt / (W * ag->n), v, &v);
          tdVPlus(ag->pos, v, &(ag->pos));
          // update grids
          int nix, niy, niz;
          nix = ag->pos.x / 10;
          niy = ag->pos.y / 10;
          niz = ag->pos.z / 10;
          if (nix != ix || niy != iy || niz != iz)
          {
               if(check(nix,niy,niz,100)){
                    //remove
                    assert(grids[ix][iy][iz].size>0);
                    for(int si=0;si<grids[ix][iy][iz].size;si++){
                         if(grids[ix][iy][iz].ids[si] == ag->id){
                              grids[ix][iy][iz].ids[i] = grids[ix][iy][iz].ids[grids[ix][iy][iz].size-1];
                              grids[ix][iy][iz].size--;
                         }
                    }
                    //add
                    printf("From\t%d\t%d\t%d\n",ix,iy,iz);
                    printf("To\t%d\t%d\t%d\n",nix,niy,niz);
                    addToCell(&(grids[nix][niy][niz]),ag->id);
               }
          }
     }
     printf("\nF\t%f\nhitWall\t%d\nhit\t%d\nout\t%d\n", J,hitWall,hit,out);
     nowTick++;
}

int main()
{
     // a block measure 5 units.
     struct Cell grids[10][10][10];
     for (int i = 0; i < 10; i++)
          for (int j = 0; j < 10; j++)
               for (int k = 0; k < 10; k++)
               {
                    grids[i][j][k].size = 0;
                    grids[i][j][k].capacity = 0;
               }

     struct AGList agl;
     agl.size = 0;
     agl.capacity = 0;

     int n;
     scanf("%d",&n);
     for(int i=0;i<n;i++){   
          struct AtomGroup ag;
          float x = 0+i;
          float y = 0;
          float z = 0;
          tdSetVXYZ(x,y,z,&(ag.pos));
          float px = -100;
          float py = -100;
          float pz = -100;
          tdSetVXYZ(px,py,pz,&(ag.p));
          ag.n = 500;
          ag.id = agl.size;
          addtoList(&agl,ag);

          //grid
          int gx = (int)floor(x/10);
          int gy = (int)floor(y/10);
          int gz = (int)floor(z/10);
          addToCell(&grids[gx][gy][gz],ag.id);
          printf("Orogin\t%d\t%d\t%d\t%d\n",gx,gy,gz,grids[gx][gy][gz].size);
     }
     while (1)
     {
          printf("\nnowTick:%d\n", nowTick);
          step(&agl, grids);
          float x,y,z;
          tdGetVXYZ(agl.data[0].pos,&x,&y,&z);
          printf("%f\t%f\t%f\n",x,y,z);
          /*
          for (int i = 0; i < agl.size; i++)
          {
               printf("index:%d\n", i);
               float x, y, z;
               tdGetVXYZ(agl.data[i].representAtom.pos, &x, &y, &z);
               printf("pos:%f\t%f\t%f\n", x, y, z);
               printf("grid:%f\t%f\t%f\n", x / 5, y / 5, z / 5);
          }
          */
          sleep(1);
          system("cls");
     }

     return 0;
}
