#ifndef TDVECTOR_H
#define TDVECTOR_H

struct TdVector{
	float x;
	float y;
	float z;
};

void tdGetVXYZ(struct TdVector v,float* ox,float* oy,float* oz);

void tdSetVXYZ(float x,float y,float z,struct TdVector* v);

void tdVMul(float factor,struct TdVector v,struct TdVector* o);

void tdVPlus(struct TdVector v1,struct TdVector v2,struct TdVector* o);

void tdVMin(struct TdVector v1,struct TdVector v2,struct TdVector* o);

void tdLenOfV(struct TdVector v,float* o);

void tdVNormalize(struct TdVector* v);

void tdDot(struct TdVector v1,struct TdVector v2,float* o);

void tdCross(struct TdVector v1,struct TdVector v2,struct TdVector* o);

void tdVProject(struct TdVector v1,struct TdVector v2,struct TdVector* o);
#endif