#include<math.h>
#include"tdvector.h"

void tdGetVXYZ(struct TdVector v,float* ox,float* oy,float* oz){
	*ox = v.x;
	*oy = v.y;
	*oz = v.z;
}

void tdSetVXYZ(float x,float y,float z,struct TdVector* v){
	(*v).x = x;
	(*v).y = y;
	(*v).z = z;
}

void tdVMul(float factor,struct TdVector v,struct Tdvecor* o){
	float x,y,z;
	tdGetVXYZ(v,&x,&y,&z);

	tdSetVXYZ(factor * x,factor * y,factor * z,o);
}

void tdVPlus(struct TdVector v1,struct TdVector v2,struct TdVector* o){
	float x1,y1,z1;
	tdGetVXYZ(v1,&x1,&y1,&z1);	
	float x2,y2,z2;
	tdGetVXYZ(v2,&x2,&y2,&z2);

	tdSetVXYZ(x1+x2,y1+y2,z1+z2,o);
}

void tdVMin(struct TdVector v1,struct TdVector v2,struct TdVector* o){
	tdVMul(-1,v2,&v2);
	tdVPlus(v1,v2,o);	
}

void tdLenOfV(struct TdVector v,float* o){
	float x,y,z;
	tdGetVXYZ(v,&x,&y,&z);	

	*o = sqrt( x * x + y * y + z * z );
}

void tdVnormalize(struct TdVector v,struct TdVector* o){
	float lenOfV;
	tdLenOfV(v,&lenOfV);

	tdVMul(1/lenOfV,v,&v);
}

void tdDot(struct TdVector v1,struct TdVector v2,float* o){
	float x1,y1,z1;
	tdGetVXYZ(v1,&x1,&y1,&z1);	
	float x2,y2,z2;
	tdGetVXYZ(v2,&x2,&y2,&z2);

	*o = x1 * x2 + y1 * y2 + z1 * z2;
}

void tdCross(struct TdVector v1,struct TdVector v2,struct TdVector* o){
	/* y1 z1 x1 y1
	 *   x  x  x
	 * y2 z2 x2 y2
	 * */
	float x1,y1,z1;
	tdGetVXYZ(v1,&x1,&y1,&z1);	
	float x2,y2,z2;
	tdGetVXYZ(v2,&x2,&y2,&z2);
	
	tdSetVXYZ(y1 * z2 - z1 * y2,
		  z1 * x2 - x1 * z2,
		  x1 * y2 - y1 * x2,o);
}

void tdVProject(struct TdVector v1,struct TdVector v2,struct TdVector* o){
	//define "dot" as v1 dor v1
	float dot;
	tdDot(v1 , v2 , &dot);

	float lenOfv2;
	tdLenOfV(v2,&lenOfv2);

	float t = dot/(lenOfv2 * lenOfv2);
	
	float x2,y2,z2;
	tdGetVXYZ(v2,&x2,&y2,&z2);

	tdSetVXYZ(x2,y2,z2,o);
	tdVMul(t,*o,o);
}