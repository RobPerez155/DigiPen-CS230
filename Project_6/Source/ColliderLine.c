//------------------------------------------------------------------------------
//
// File Name:	ColliderCircle.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Collider.h"
#include "ColliderLine.h"
#include "DGL.h"
#include "Entity.h"
#include "Matrix2D.h"
#include "Physics.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
#define cLineSegmentMax 100
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderLineSegment
{
	// A single line segment (P0 and P1).
	Vector2D	point[2];
} ColliderLineSegment;

typedef struct ColliderLine
{
	// Inherit the base collider structure.
	Collider	base;

	// The number of line segments in the list.
	unsigned int		lineCount;

	// The individual line segments.
	// (NOTE: Make sure to allocate enough memory for all line segments!)
	ColliderLineSegment	lineSegments[cLineSegmentMax];

} ColliderLine;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (line) collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Make sure to initialize the ColliderType and memorySize correctly.)

//Tested
Collider* ColliderLineCreate(void)
{
	ColliderLine* ptrColliderLine = calloc(1, sizeof(ColliderLine));

	if (ptrColliderLine == NULL)
		return NULL;

	ptrColliderLine->base.type = ColliderTypeLine;
	ptrColliderLine->base.memorySize = sizeof(ColliderLine);

	return (Collider*)ptrColliderLine;
}

// Read the properties of a ColliderLine component from a file.
// (NOTE: First read an integer indicating the number of lines to be read.)
// (NOTE: For each line, read P0 and P1 using StreamReadVector2D.)
// (HINT: Call ColliderLineAddLineSegment() to add each line.)
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.

// Tested
void ColliderLineRead(Collider* collider, Stream stream)
{
	if (collider != NULL && stream != NULL)
	{
		ColliderLine* line = (ColliderLine*)collider;
		int numberOfLines = StreamReadInt(stream);

		for (int i = 0; i < numberOfLines; i++)
		{
			//read line
			// read stream read vector and save to p0
			Vector2D p0;
			Vector2D p1;
			StreamReadVector2D(stream, &p0);
			StreamReadVector2D(stream, &p1);
			// read stream read vector and save to p1
			ColliderLineAddLineSegment((Collider*)line, &p0, &p1);
		}
	}
}

// Add a line segment to the line collider's line segment list.
// Params:
//	 collider = Pointer to the line collider component.
//	 p0 = The line segment's starting position.
//	 p1 = The line segment's ending position.

// Tested
void ColliderLineAddLineSegment(Collider* collider, const Vector2D* p0, const Vector2D* p1)
{
	if (collider == NULL)
		return;

	if (collider->type != ColliderTypeLine)
		return;

	ColliderLine* line = (ColliderLine*)collider;
	line->lineSegments[line->lineCount].point[0] = *p0;
	line->lineSegments[line->lineCount].point[1] = *p1;
	line->lineCount++;
}

// Check for collision between a line collider and a circle collider.
// Params:
//	 collider1 = Pointer to the line collider component.
//	 collider2 = Pointer to the circle collider component.
// Returns:
//	 If the pointers are valid,
//	   then return the results of a line-circle collision check,
//	   else return false.
bool ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	Entity* parentEnt = other->parent;
	ColliderLine* lineCollider = (ColliderLine*)collider;
	
	Physics* spacePhys = EntityGetPhysics(parentEnt);
	Transform* spaceTrans = EntityGetTransform(parentEnt);

	const Vector2D* Bs = PhysicsGetOldTranslation(spacePhys);
	const Vector2D* Be = TransformGetTranslation(spaceTrans);

	// v = Be - Bs;
	// Tested
	Vector2D v;
	v.x = Be->x - Bs->x;
	v.y = Be->y - Bs->y;

	// Edge Vector
	Vector2D e = { 0 };

	// Vector normal
	Vector2D n = { 0 };

	// Tested
	for (unsigned int i = 0; i < lineCollider->lineCount; i++)
	{

		// Tested
		Vector2D P0 = lineCollider->lineSegments[i].point[0];
		Vector2D P1 = lineCollider->lineSegments[i].point[1];

		// Tested
		e.x = P1.x - P0.x;
		e.y = P1.y - P0.y;

		// Tested
		n.y =	-e.x;
		n.x = e.y;

		//Vector2D normalizedN = { 0 };

		Vector2DNormalize(&n, &n);

		float dotProd = Vector2DDotProduct(&n, &v);
		if (dotProd == 0)
			continue;

		float dotProdA = Vector2DDotProduct(&n,Bs);
		float dotProdB = Vector2DDotProduct(&n,&P0);
		float dotProdC = Vector2DDotProduct(&n,Be);
		float dotProdD = Vector2DDotProduct(&n,&P0);

		// Second trivial check for non-collision:
		// Check if both Bs and Be are in the inside half-plane
		if ((dotProdA <= dotProdB) && (dotProdC < dotProdD))
			continue;

		// Third trivial check for non-collision:
		// Check if both Bs and Be are in the outside half-plane
		if ((dotProdA >= dotProdB) && (dotProdC > dotProdD))
			continue;

		Vector2D vNew = { (Be->x - Bs->x), 0 };
		float nvDotProd = Vector2DDotProduct(&n, &vNew);

		// Slide 19 - Time of intersection
		float ti = 0.0;
		ti = ((dotProdD) - (dotProdA)) / (nvDotProd);

		Vector2D Bi = { 0 };
		Vector2D VxTi = { 0 };

		VxTi.x = vNew.x * ti;
		VxTi.y = vNew.y * ti;

		Vector2DAdd(&Bi, Bs, &VxTi);

		// Slide 21 Line Segment Check - Check outside of P0
		// Tested
		Vector2D p1MinusP0 = { 0 };
		Vector2DSub(&p1MinusP0, &P1, &P0);

		Vector2D biMinusP0 = { 0 };
		Vector2DSub(&biMinusP0, &Bi, &P0);

		float p1MinusP0xBiMinusP0 = Vector2DDotProduct(&p1MinusP0, &biMinusP0);

		if (p1MinusP0xBiMinusP0 < 0)
			continue;

		// Slide 21 Line Segment Check - Check outside of P1
		// Tested
		Vector2D p0MinusP1 = { 0 };
		Vector2DSub(&p0MinusP1, &P0, &P1);

		Vector2D biMinusP1 = { 0 };
		Vector2DSub(&biMinusP1, &Bi, &P1);

		float p0MinusP1xBiMinusP1 = Vector2DDotProduct(&p0MinusP1, &biMinusP1);

		if (p0MinusP1xBiMinusP1 < 0)
			continue;

		// Slide 24 - Reflection
		// Incident Vector
		Vector2D i = { 0 };
		i.x = Be->x - Bi.x;
		i.x = Be->y - Bi.y;

		// Slide 24 - Penetration Vector
		Vector2D s = { 0 };
		float IxN = 0.0;
		Vector2D NxIN = { 0 };

		IxN = Vector2DDotProduct(&i, &n);
		NxIN.x = IxN * n.x;
		NxIN.y = IxN * n.y;

		s = NxIN;

		// Slide 24 - Reflection Vector
		Vector2D r = { 0 };
		Vector2D twoXs = { 0 };
		twoXs.x = 2 * s.x;
		twoXs.y = 2 * s.y;

		Vector2DSub(&r, &i, &twoXs);

		// Slide 24 new endpoint, Br
		Vector2D Br = { 0 };
		Vector2DAdd(&Br, &Bi, &r);

		UNREFERENCED_PARAMETER(P0);
		UNREFERENCED_PARAMETER(P1);
		UNREFERENCED_PARAMETER(e);
		UNREFERENCED_PARAMETER(n);
		UNREFERENCED_PARAMETER(Bi);
		//UNREFERENCED_PARAMETER(normalizedN);
		continue;
	}


	UNREFERENCED_PARAMETER(Bs);
	UNREFERENCED_PARAMETER(Be);
	UNREFERENCED_PARAMETER(collider);
	return true;
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

//static bool PointLineIntersection(const Vector2D* Bs, const Vector2D* Be, Vector2D v, ColliderLineSegment P0, ColliderLineSegment P1)
//{
//
//}

	//Physics* spacePhys = EntityGetPhysics(SpaceshipOmega);
	//Transform* spaceTrans = EntityGetTransform(SpaceshipOmega);
	////Vector2D* sum;

	//const Vector2D* Bs = PhysicsGetOldTranslation(spacePhys);
	//const Vector2D* Be = TransformGetTranslation(spaceTrans);
	//UNREFERENCED_PARAMETER(Bs);
	//UNREFERENCED_PARAMETER(Be);