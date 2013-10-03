/*
 * GameCommon.h
 *
 *  Created on: Jun 15, 2012
 *      Author: Ilija
 */

#ifndef GAMECOMMON_H_
#define GAMECOMMON_H_

#include "glplus/glplus.h"
#include "common/vector3.h"
#include "common/matrix4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <list>

inline float randf() { return (float)rand() / (float)RAND_MAX; }
inline float randf(float max) { return (float)rand() / (float)RAND_MAX * max; }
inline float randf(float min, float max) { return (float)rand() / (float)RAND_MAX * (max - min) + min; }

inline void set4fv(float *pf, float x, float y, float z, float w) { pf[0]=x; pf[1]=y; pf[2]=z; pf[3]=w; }

//#define MIN(A, B) (((A) < (B)) ? (A) : (B))
//#define MAX(A, B) (((A) > (B)) ? (A) : (B))

inline void parseIntColor(int color, float *vcolor)
{
	vcolor[0] = ((color >> 16) & 0xFF) / 255.0f;
	vcolor[1] = ((color >> 8) & 0xFF) / 255.0f;
	vcolor[2] = ((color >> 0) & 0xFF) / 255.0f;
	vcolor[3] = ((color >> 24) & 0xFF) / 255.0f;
}

#endif /* GAMECOMMON_H_ */
