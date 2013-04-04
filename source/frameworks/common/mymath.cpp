
#include "mymath.h"


/*int mRoll(int d)
{
    int r = (int)(rnd() * d);
    if (r == 0) r = d;
    return r;
}*/



int next_p2(int a)
{
	int rval=1;
	// rval<<=1 Is A Prettier Way Of Writing rval*=2;
	while(rval<a) rval<<=1;
	return rval;
}



float myAngleClamp(float angle, float min, float max, float delta)
{
	while (angle < min)
	{
		angle += delta;
	}
	while (angle >= max)
	{
		angle -= delta;
	}
	return angle;
}


float myAngleDiff(float angle1, float angle2)
{
	float a = angle1 - angle2;
	return fabs(myAngleClamp(a, -PI, PI, PI * 2));
}


float myAngleBounce(float angle, float normalAngle)
{
	float bouncingDelta = myAngleDiff(angle, normalAngle);
	if (fabs(bouncingDelta) > PI / 2)
	{
		angle = myAngleClamp(normalAngle - (angle - normalAngle) + PI, 0.0f, PI * 2, PI * 2);
	}
	return angle;
}


//
//random
//

int randomInt(int min, int max)
{
	return (rand() % (max - min)) + min;
}

int randomInt(int range)
{
	return (rand() % range);
}

float randomFloat(float min, float max)
{
	return (rand() / (float)RAND_MAX) * (max - min) + min;
}

float randomFloat(float range)
{
	return (rand() / (float)RAND_MAX) * range;
}

bool randomBool(int probability)
{
	if (probability == 0)
		return false;
	else
		return (rand() % probability == 0);
}


//
//vector ops
//

bool v2Intersect(vector2f& pt, const vector2f& p1, const vector2f& p2, const vector2f& p3, const vector2f& p4)
{
    float xD1,yD1,xD2,yD2,xD3,yD3;
    float dot,deg,len1,len2;
    float segmentLen1,segmentLen2;
    float ua,ub,div;

    // calculate differences
    xD1=p2.x-p1.x;
    xD2=p4.x-p3.x;
    yD1=p2.y-p1.y;
    yD2=p4.y-p3.y;
    xD3=p1.x-p3.x;
    yD3=p1.y-p3.y;

    // calculate the lengths of the two lines
    len1=sqrt(xD1*xD1+yD1*yD1);
    len2=sqrt(xD2*xD2+yD2*yD2);

    //not valid line(s)
    if (len1==0 || len2==0) return false;

    // calculate angle between the two lines.
    dot=(xD1*xD2+yD1*yD2); // dot product
    deg=dot/(len1*len2);

    // if abs(angle)==1 then the lines are parallell,
    // so no intersection is possible
    if (fabs(deg)==1) return false;

    // find intersection Pt between two lines
    div=yD2*xD1-xD2*yD1;
    ua=(xD2*yD3-yD2*xD3)/div;
    ub=(xD1*yD3-yD1*xD3)/div;
    pt.x=p1.x+ua*xD1;
    pt.y=p1.y+ua*yD1;

    // calculate the combined length of the two segments
    // between Pt-p1 and Pt-p2
    xD1=pt.x-p1.x;
    xD2=pt.x-p2.x;
    yD1=pt.y-p1.y;
    yD2=pt.y-p2.y;
    segmentLen1=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

    // calculate the combined length of the two segments
    // between Pt-p3 and Pt-p4
    xD1=pt.x-p3.x;
    xD2=pt.x-p4.x;
    yD1=pt.y-p3.y;
    yD2=pt.y-p4.y;
    segmentLen2=sqrt(xD1*xD1+yD1*yD1)+sqrt(xD2*xD2+yD2*yD2);

    // if the lengths of both sets of segments are the same as
    // the lenghts of the two lines the point is actually
    // on the line segment.

    // if the point isn't on the line, return null
    if (fabs(len1-segmentLen1)>0.01 || fabs(len2-segmentLen2)>0.01)
        return false;

    // return the valid intersection
    return true;
}


vector3f v3MakeFaceNormal(const vector3f& v1, const vector3f& v2, const vector3f& v3)
{
	vector3f a = v3 - v2;
	vector3f b = v1 - v2;
	vector3f norm = v3CrossProduct(a, b);
	norm.normalize();
	return norm;
}


#define EPS  0.000001
/*
   Calculate the line segment PaPb that is the shortest route between
   two lines P1P2 and P3P4. Calculate also the values of mua and mub where
      Pa = P1 + mua (P2 - P1)
      Pb = P3 + mub (P4 - P3)
   Return FALSE if no solution exists.
*/
static bool LineLineIntersect3D(
   const float *p1, const float *p2, const float *p3, const float *p4,
   float *pa, float *pb)
{
   float p13[3], p43[3], p21[3];
   float d1343,d4321,d1321,d4343,d2121;
   float numer,denom;
   float mua, mub;

   p13[0] = p1[0] - p3[0];
   p13[1] = p1[1] - p3[1];
   p13[2] = p1[2] - p3[2];
   p43[0] = p4[0] - p3[0];
   p43[1] = p4[1] - p3[1];
   p43[2] = p4[2] - p3[2];
   if (fabs(p43[0])  < EPS && fabs(p43[1])  < EPS && fabs(p43[2])  < EPS)
      return false;
   p21[0] = p2[0] - p1[0];
   p21[1] = p2[1] - p1[1];
   p21[2] = p2[2] - p1[2];
   if (fabs(p21[0])  < EPS && fabs(p21[1])  < EPS && fabs(p21[2])  < EPS)
      return false;

   d1343 = p13[0] * p43[0] + p13[1] * p43[1] + p13[2] * p43[2];
   d4321 = p43[0] * p21[0] + p43[1] * p21[1] + p43[2] * p21[2];
   d1321 = p13[0] * p21[0] + p13[1] * p21[1] + p13[2] * p21[2];
   d4343 = p43[0] * p43[0] + p43[1] * p43[1] + p43[2] * p43[2];
   d2121 = p21[0] * p21[0] + p21[1] * p21[1] + p21[2] * p21[2];

   denom = d2121 * d4343 - d4321 * d4321;
   if (fabs(denom) < EPS)
      return false;
   numer = d1343 * d4321 - d1321 * d4343;

   mua = numer / denom;
   mub = (d1343 + d4321 * (mua)) / d4343;

   pa[0] = p1[0] + mua * p21[0];
   pa[1] = p1[1] + mua * p21[1];
   pa[2] = p1[2] + mua * p21[2];
   pb[0] = p3[0] + mub * p43[0];
   pb[1] = p3[1] + mub * p43[1];
   pb[2] = p3[2] + mub * p43[2];

   return true;
}


bool v3Intersect(vector3f& v_out, const vector3f& a1, const vector3f& a2, const vector3f& b1, const vector3f& b2)
{
	vector3f p1, p2;
	if (!LineLineIntersect3D(a1.getConstPtr(), a2.getConstPtr(), b1.getConstPtr(), b2.getConstPtr(), p1.getPtr(), p2.getPtr()))
		return false;

	v_out = p1 + p2;
	v_out /= 2;
	return true;
}

bool v2PointToLineDistance(const vector2f &a, const vector2f &b, const vector2f &c,
                           float &distanceSegment, float &distanceLine)
{
	float r_numerator = (c.x-a.x)*(b.x-a.x) + (c.y-a.y)*(b.y-a.y);
	float r_denomenator = (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
	float r = r_numerator / r_denomenator;
//
    float px = a.x + r*(b.x-a.x);
    float py = a.y + r*(b.y-a.y);
//
    float s =  ((a.y-c.y)*(b.x-a.x)-(a.x-c.x)*(b.y-a.y) ) / r_denomenator;

	distanceLine = fabs(s)*sqrt(r_denomenator);

//
// (xx,yy) is the point on the lineSegment closest to (cx,cy)
//
	float xx = px;
	float yy = py;

	if ( (r >= 0) && (r <= 1) )
	{
		distanceSegment = distanceLine;
		return true;
	}
	else
	{
		float dist1 = (c.x-a.x)*(c.x-a.x) + (c.y-a.y)*(c.y-a.y);
		float dist2 = (c.x-b.x)*(c.x-b.x) + (c.y-b.y)*(c.y-b.y);
		if (dist1 < dist2)
		{
			xx = a.x;
			yy = a.y;
			distanceSegment = sqrt(dist1);
		}
		else
		{
			xx = b.x;
			yy = b.y;
			distanceSegment = sqrt(dist2);
		}
        return false;
	}
}

quatf slerp(const quatf &qa, const quatf &qb, double t)
{
    // quaternion to return
    quatf qm;
    // Calculate angle between them.
    double cosHalfTheta = qa.w * qb.w + qa.x * qb.x + qa.y * qb.y + qa.z * qb.z;
    // if qa=qb or qa=-qb then theta = 0 and we can return qa
    if (abs(cosHalfTheta) >= 1.0){
        qm.w = qa.w;qm.x = qa.x;qm.y = qa.y;qm.z = qa.z;
        return qm;
    }
    // Calculate temporary values.
    double halfTheta = acos(cosHalfTheta);
    double sinHalfTheta = sqrt(1.0 - cosHalfTheta*cosHalfTheta);
    // if theta = 180 degrees then result is not fully defined
    // we could rotate around any axis normal to qa or qb
    if (fabs(sinHalfTheta) < 0.001){ // fabs is floating point absolute
        qm.w = (qa.w * 0.5 + qb.w * 0.5);
        qm.x = (qa.x * 0.5 + qb.x * 0.5);
        qm.y = (qa.y * 0.5 + qb.y * 0.5);
        qm.z = (qa.z * 0.5 + qb.z * 0.5);
        return qm;
    }
    double ratioA = sin((1 - t) * halfTheta) / sinHalfTheta;
    double ratioB = sin(t * halfTheta) / sinHalfTheta;
    //calculate Quaternion.
    qm.w = (qa.w * ratioA + qb.w * ratioB);
    qm.x = (qa.x * ratioA + qb.x * ratioB);
    qm.y = (qa.y * ratioA + qb.y * ratioB);
    qm.z = (qa.z * ratioA + qb.z * ratioB);
    return qm;
}


