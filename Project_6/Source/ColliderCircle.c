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

#include "ColliderCircle.h"
#include "Collider.h"
#include "Entity.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct ColliderCircle
{
	// Inherit the base collider structure.
	Collider	base;

	// Radius of the circle collider.
	float radius;

} ColliderCircle;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Dynamically allocate a new (circle) collider component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// (Hint: Make sure to initialize the ColliderType and memorySize correctly.)
// (Note: Set the radius to a non-zero value.  Typical values are 0.5f or 1.0f.)

// Tested 
Collider* ColliderCircleCreate(void)
{
	ColliderCircle* ptrCircleCollider = calloc(1, sizeof(ColliderCircle));

	if (ptrCircleCollider == NULL)
		return NULL;
	
	ptrCircleCollider->base.type = ColliderTypeCircle;
	ptrCircleCollider->base.memorySize = sizeof(ColliderCircle);
	ptrCircleCollider->radius = 1.0f;

	return (Collider*)ptrCircleCollider;
}

// Read the properties of a ColliderCircle component from a file.
// (NOTE: Read the radius value using StreamReadFloat.)
// Params:
//	 collider = Pointer to the Collider component.
//	 stream = Pointer to the data stream used for reading.

// Tested
void ColliderCircleRead(Collider* collider, Stream stream)
{
	if (collider != NULL && stream != NULL)
	{
		// Need to set collider to be a circleCollider
		ColliderCircle* circle = (ColliderCircle*)collider;
		circle->radius = StreamReadFloat(stream);
	}
}

// Get the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
// Returns:
//	 If the pointer is valid,
//	   then return the circle collider's radius,
//	   else return 0.0f.

// Tested
float ColliderCircleGetRadius(const Collider* collider) 
{
	if (collider != NULL)
	{
		ColliderCircle* circle = (ColliderCircle*)collider;

		return circle->radius;
	}
	else {
		return 0.0f;
	}
}

// Set the circle collider's radius.
// Params:
//	 collider = Pointer to the circle collider component.
//   radius = the circle collider's new radius.

//Tested
void ColliderCircleSetRadius(Collider* collider, float radius)
{
	ColliderCircle* circle = (ColliderCircle*)collider;
	circle->radius = radius;
}

// Check for collision between two circle colliders.
// Params:
//	 collider1 = Pointer to the first circle collider component.
//	 collider2 = Pointer to the second circle collider component.

// Tested
bool ColliderCircleIsCollidingWithCircle(const Collider* collider, const Collider* other)
{
	// Convert both colliders to circleColliders
	ColliderCircle* collider1 = (ColliderCircle*)collider;
	ColliderCircle* collider2 = (ColliderCircle*)other;

	// Check if both are null
	if (collider1 == NULL || collider2 == NULL)
		return false;

	// Check if both are circles
	if (collider1->base.type != ColliderTypeCircle || collider2->base.type != ColliderTypeCircle)
		return false;

	// Get the distance between both circles assign to new value
	Transform* lineA = EntityGetTransform(collider1->base.parent);
	Transform* lineB = EntityGetTransform(collider2->base.parent);

	// Square the new distance
	float sqDistBetweenColliders = Vector2DSquareDistance(TransformGetTranslation(lineA), TransformGetTranslation(lineB));

	// Get sum of radii
	float sqRadiiSum = (collider1->radius * collider1->radius + collider2->radius * collider2->radius);

	// if the sum of both the squared circle radii is greater than the new distance return true
	if (sqRadiiSum > sqDistBetweenColliders)
	{
		if (collider->handler != NULL)
		{
			collider->handler(collider->parent, other->parent);
		}

		if (other->handler != NULL)
		{
			other->handler(other->parent, collider->parent);
		}
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

