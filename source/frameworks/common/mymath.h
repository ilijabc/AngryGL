/*
  Name: mymath.h
  Copyright:
  Author: ilija
  Date: 19/09/07 18:55
  Description: dopuna <math.h>
*/


#ifndef MYMATH_H
#define MYMATH_H

#include <math.h>
#include <stdlib.h>

#include "vector2.h"
#include "vector3.h"
#include "quat.h"

#define PI 3.14159265f
#define TORAD 0.017453f
#define TODEG 57.295779f

#define SQRT(X)				sqrtf(X)
#define POW2(X) 			((X)*(X))
#define DIST(X1,Y1, X2,Y2) (SQRT(POW2((X1)-(X2))+POW2((Y1)-(Y2))))
#define MAX(A,B)           ((A)>(B)?(A):(B))
#define MIN(A,B)           ((A)<(B)?(A):(B))
#define INRANGE(X,A,B)     ((X)<(A)?0:((X)>(B)?0:1))
#define ABS(X)             ((X)>0?(X):-(X))
#define SIGN(X)            ((X)>0?(1):((X)<0?(-1):0))
#define CLAMP(x,A,B)       (MIN(MAX((x),(A)),(B)))

inline int myRound(float v) { return (int)(v + 0.5 * SIGN(v)); }
inline int myFloor(float v) { return (int)v; }

inline float myDegToRad(float deg) { return deg * TORAD; }
inline float myRadToDeg(float rad) { return rad * TODEG; }

inline float myClampDeg(float deg) { return deg - 360.0f * myFloor(deg / 360.0f); }
inline float myClampRad(float rad) { return (rad > PI) ? (rad - PI * 2) : rad; }

inline float myInterpolate(float a, float b, float f) { return a + (b - a) * f; }

template <class A> void SWAP(A& x, A& y)
{
    A tmp;
    tmp = x;
    x = y;
    y = tmp;
}

int next_p2(int a);


float myAngleClamp(float angle, float min = -180.0f, float max = 180.0f, float delta = 360.0f);
float myAngleDiff(float angle1, float angle2);
float myAngleBounce(float angle, float normalAngle);


//
//random
//
int randomInt(int min, int max);
int randomInt(int range);
float randomFloat(float min, float max);
float randomFloat(float range);
bool randomBool(int probability);


//
//vector ops
//

bool v2Intersect(vector2f& v_out, const vector2f& a1, const vector2f& a2, const vector2f& b1, const vector2f& b2);
inline vector2f v2projectXY(const vector3f& v2) { return vector2f(v2.x, v2.y); }
inline vector2f v2polar(float _angle, float _lenght) { return vector2f(cosf(_angle) * _lenght, sinf(_angle) * _lenght); }
inline float v2Side(const vector2f& a, const vector2f& b, const vector2f& c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x); }

inline vector3f v3projectXY(const vector2f& v2) { return vector3f(v2.x, v2.y, 0.0f); }
inline vector3f v3CrossProduct(const vector3f& a, const vector3f& b)
{
	return vector3f(
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y);
}
vector3f v3MakeFaceNormal(const vector3f& v1, const vector3f& v2, const vector3f& v3);
bool v3Intersect(vector3f& v_out, const vector3f& a1, const vector3f& a2,
                 const vector3f& b1, const vector3f& b2);

bool v2PointToLineDistance(const vector2f &a, const vector2f &b, const vector2f &c,
                           float &distanceSegment, float &distanceLine);

quatf slerp(const quatf &qa, const quatf &qb, double t);


#endif //MYMATH_H


