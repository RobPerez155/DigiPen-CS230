//------------------------------------------------------------------------------
//
// File Name:	Vector2D.c
// Author(s):	Robert Perez (rob.perez)
// Project:		Project 1
// Course:		CS230S23
//
// Copyright � 2023 DigiPen (USA) Corporation.
//
// Helpful Links:
//   https://docs.microsoft.com/en-us/cpp/c-runtime-library/math-constants
//   https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atan-atanf-atanl-atan2-atan2f-atan2l
//   https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/cos-cosf-cosl
//   https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/sqrt-sqrtf-sqrtl
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include <DGL.h>
#include "Vector2D.h"

#define _USE_MATH_DEFINES
#include <math.h>

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
//DO A ZERO CHECK ON NORMALIZE TO SAVE A HEADACHE
// This function sets the coordinates of the 2D vector (pResult) to 0
void Vector2DZero(Vector2D* pResult) 
{
	pResult->x = 0;
	pResult->y = 0;
}

// This function sets the coordinates of the 2D vector (pResult) to x & y
void Vector2DSet(Vector2D* pResult, float x, float y) 
{
if (pResult) { //if statement if for error checking
		pResult->x = x;
		pResult->y = y;
	}
}

// In this function, pResult will be set to the opposite of pVec0 (e.g. x = -x & y = -y)
void Vector2DNeg(Vector2D* pResult, const Vector2D* pVec0) 
{
	if (pResult) { //if statement if for error checking
		pResult->x = -pVec0->x;
		pResult->y = -pVec0->y;
	}
}

// In this function, pResult will be the sum of pVec0 and pVec1 (x result = x0 + x1)
void Vector2DAdd(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// In this function, pResult will be the difference between pVec0 and pVec1 (specifically, pVec0 - pVec1)
void Vector2DSub(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1) 
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// In this function, pResult will be the unit vector of pVec0
// (NOTE: Care must be taken when pResult = pVec0!)
//CHECK FOR ERRORS
void Vector2DNormalize(Vector2D* pResult, const Vector2D* pVec0) 
{
	Vector2D result = { pVec0->x, pVec0->y };
	float length = Vector2DLength(&result);

	pResult->x = result.x / length;
	pResult->y = result.y / length;
}

// In this function, pResult will be the vector pVec0 scaled by the value 'scale'
	void Vector2DScale(Vector2D* pResult, const Vector2D* pVec0, float scale)
{
	pResult->x = pVec0->x * scale;
	pResult->y = pVec0->y * scale;
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and added to pVec1
void Vector2DScaleAdd(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1, float scale) 
{
	pResult->x = pVec0->x * scale + pVec1->x;
	pResult->y = pVec0->y * scale + pVec1->y;

	//vel += accel * dt
	//	trans = vel * dt + transl
}

// In this function, pResult will be the vector pVec0 scaled by 'scale' and pVec1 will be subtracted from it
void Vector2DScaleSub(Vector2D* pResult, const Vector2D* pVec0, const Vector2D* pVec1, float scale) 
{
	pResult->x = pVec0->x * scale - pVec1->x;
	pResult->y = pVec0->y * scale - pVec1->y;
}

// This function returns the length of the vector pVec0
float Vector2DLength(const Vector2D* pVec0) 
{
	float result = (pVec0->x * pVec0->x) + (pVec0->y * pVec0->y);
	return sqrtf(result);
}

// This function returns the square of pVec0's length.
// NOTE: The square root function must NOT be called by this function.
float Vector2DSquareLength(const Vector2D* pVec0) 
{
	float result = (pVec0->x * pVec0->x) + (pVec0->y * pVec0->y);
	return (result);
}

// This function returns the distance between two points.
float Vector2DDistance(const Vector2D* pVec0, const Vector2D* pVec1) 
{
	float result = Vector2DSquareDistance(pVec0, pVec1);
	return	sqrtf(result);
}

// This function returns the distance squared between two points.
// NOTE: The square root function must NOT be called by this function.
float Vector2DSquareDistance(const Vector2D* pVec0, const Vector2D* pVec1) 
{
	float resultX = (pVec0->x - pVec1->x);
	resultX *= resultX;
	float resultY = (pVec0->y - pVec1->y);
	resultY *= resultY;

	return (resultX + resultY);
}

// This function returns the dot product between pVec0 and pVec1
float Vector2DDotProduct(const Vector2D* pVec0, const Vector2D* pVec1) 
{
	float result = ((pVec0->x * pVec1->x) + (pVec0->y * pVec1->y));
	return result;
}

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Degrees.
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Vector2DFromAngleDeg(Vector2D* pResult, float angle) 
{
	if (pResult)
	{
		float intoRadian = (angle * (float)M_PI) / 180.0f;
		Vector2DFromAngleRad(pResult, intoRadian);
		return;
	}
}

// This function computes the coordinates of the unit vector represented by the angle "angle", which is in Radians.
// HINT: x = cos(angle), y = sin(angle).
	void Vector2DFromAngleRad(Vector2D* pResult, float angle) 
{
	pResult->x = cosf(angle);
	pResult->y = sinf(angle);
}

// This function computes the angle, in radians, of the specified vector.
// HINT: Angle (radians) = atan2f(direction Y, direction X).
// NOTE: If the pointer is NULL, then return 0.0f.
float Vector2DToAngleRad(const Vector2D* pVec) 
{
	if (pVec) {
		return atan2f(pVec->y, pVec->x);
	}
	return 0.0;
}

//void circleTriangles(int);
void circleTriangles(int divisions)
{
	for (int i = 0; i <= divisions; i++)
	{
		float x;
		float y;
		float u;
		float v;
		float angle = 360.0f / divisions;

		x = (float)sinf(angle * i) * 0.5f;
		y = (float)cosf(angle * i) * 0.5f;

		u = x + 0.5f;
		v = y + 0.5f;

		printf("%f %f 1.0 1.0 1.0 1.0 %f %f\n", x, y, u, v);
	}
}
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

