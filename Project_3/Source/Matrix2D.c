//------------------------------------------------------------------------------
//
// File Name:	Matrix2D.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 3
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#define _USE_MATH_DEFINES

#include "Matrix2D.h"
#include <math.h>
#include "Vector2D.h"
#include "DGL.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
static Matrix2D tempMatrix;
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void Swap(float* one, float* two);

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// This function sets the matrix equal to the identity matrix.
void Matrix2DIdentity(Matrix2D* pResult)
{
	if (pResult != NULL)
	{
		// Sets values to zero
		memset(pResult, 0, sizeof(Matrix2D));

		pResult->m[0][0] = 1;
		pResult->m[1][1] = 1;
		pResult->m[2][2] = 1;
	}
}

// This function calculates the transpose matrix of Mtx and saves it in the result matrix.
// Flip matrix on its diagonal to swap the columns and rows with eachother
// (NOTE: Care must be taken when pResult = pMtx.)
void Matrix2DTranspose(Matrix2D* pResult, const Matrix2D* pMtx)
{
	// Initialize identity matrix in tempMatrix
	Matrix2DIdentity(&tempMatrix);

	tempMatrix = *pMtx;

	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 3; j++)
		{
			Swap(&tempMatrix.m[i][j], &tempMatrix.m[j][i]);
		}
	}

	*pResult = tempMatrix;
}

// This function multiplies Mtx0 with Mtx1 and saves the result in Result.
// Result = Mtx0*Mtx1
// (NOTE: Care must be taken when pResult = either pMtx0 or pMtx1.)
void Matrix2DConcat(Matrix2D* pResult, const Matrix2D* pMtx0, const Matrix2D* pMtx1)
{
	Matrix2DIdentity(&tempMatrix);

	int i, j, k;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			tempMatrix.m[i][j] = 0;
			for (k = 0; k < 3; k++)
			{
				tempMatrix.m[i][j] += pMtx0->m[i][k] * pMtx1->m[k][j];
			}
		}
	}

	*pResult = tempMatrix;
}

// This function creates a translation matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DTranslate(Matrix2D* pResult, float x, float y)
{
	// Goal
	// 1 0 X
	// 0 1 Y
	// 0 0 1

	Matrix2DIdentity(pResult);

	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// This function creates a scaling matrix from x & y and saves it in Result.
// (Hint: This function must initialize all matrix values.)
void Matrix2DScale(Matrix2D* pResult, float x, float y)
{
	// x 0 0
	// 0 y 0
	// 0 0 1

	Matrix2DIdentity(pResult);

	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// This matrix creates a rotation matrix from "Angle" whose value is in degrees.
// (Hint: This function must initialize all matrix values.)
// Converting from degrees to radians can be performed as follows:
//	 radians = (angle * M_PI) / 180.0f
// M_PI is defined in "math.h", which may be included as follows:
//   #define _USE_MATH_DEFINES
//   #include <math.h>
void Matrix2DRotDeg(Matrix2D* pResult, float angle)
{
	Matrix2DIdentity(pResult);

	angle = (angle * (float)M_PI) / 180.0f;

	Matrix2DRotRad(pResult, angle);
}

// This matrix creates a rotation matrix from "Angle" whose value is in radians.
// (Hint: This function must initialize all matrix values.)
void Matrix2DRotRad(Matrix2D* pResult, float angle)
{
	Matrix2DIdentity(pResult);

	pResult->m[0][0] = (float)cos(angle);
	pResult->m[0][1] = (float)cos(angle);

	pResult->m[1][0] = (float)cos(angle);
	pResult->m[1][1] = (float)cos(angle);
}

// This function multiplies the matrix Mtx with the vector Vec and saves the result in Result.
// Result = Mtx * Vec.
// (NOTE: Care must be taken when pResult = pVec.)
// (NOTE: Remember to treat the implied w component as 1.)
void Matrix2DMultVec(Vector2D* pResult, const Matrix2D* pMtx, const Vector2D* pVec)
{
	static Vector2D multVector;

	multVector.x = pVec->x * pMtx->m[0][0] + pVec->y * pMtx->m[0][1] + pMtx->m[0][2];

	multVector.y = pVec->x * pMtx->m[1][0] + pVec->y * pMtx->m[1][1] + pMtx->m[1][2];

	*pResult = multVector;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void Swap(float* one, float* two)
{
	float temp_float = *one;
	*one = *two;
	*two = temp_float;
}
