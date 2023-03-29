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
#include "Matrix2D.h"
#include "Stream.h"
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

// Testedd
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
bool ColliderLineIsCollidingWithCircle(const Collider* collider, const Collider* other);


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

