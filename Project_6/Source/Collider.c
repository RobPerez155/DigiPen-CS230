//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Collider.h"
#include "ColliderCircle.h"
#include "Entity.h"
#include "Transform.h"
#include "Vector2D.h"
#include <DGL.h>

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct Collider Collider;
	typedef struct Entity Entity;
	typedef FILE* Stream;

	//------------------------------------------------------------------------------
	// Public Consts:
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

	static bool ColliderIsColliding(const Collider* collider1, const Collider* collider2)
	{
		if (collider1->type == ColliderTypeCircle && collider2->type == ColliderTypeCircle)
		{
			return ColliderCircleIsCollidingWithCircle(collider1, collider2);
		}
		else if (collider1->type == ColliderTypeCircle && collider2->type == ColliderTypeLine)
		{
			//make sure order is correct for function call
			//return ColliderLineIsCollidingWithCircle(collider1, collider2);
			return false;
		}
		else if (collider1->type == ColliderTypeLine && collider2->type == ColliderTypeCircle)
		{
			//return ColliderLineIsCollidingWithCircle(collider1, collider2);
			return false;
		}
		else if (collider1->type == ColliderTypeLine && collider2->type == ColliderTypeLine)
		{
			printf(" Warning both colliders are Line colliders Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}
		else {
			return false;
		}
	}

	// Dynamically allocate a clone of an existing Collider component.
	// (Hint: Perform a shallow copy of the member variables.)
	// Params:
	//	 other = Pointer to the component to be cloned.
	// Returns:
	//	 If 'other' is valid and the memory allocation was successful,
	//	   then return a pointer to the cloned component,
	//	   else return NULL.
	Collider* ColliderClone(const Collider* other)
	{
		if (other == NULL)
		{
			return NULL;
		}

		Collider* colliderClone = calloc(1, other->memorySize);
		//Collider* colliderClone = calloc(1, sizeof(Collider));

		if (colliderClone == NULL)
		{
			return NULL;
		}

		memcpy(colliderClone, other, other->memorySize);
		//*colliderClone = *other;
		colliderClone->parent = NULL;

		return colliderClone;
	}

	// Free the memory associated with a Collider component.
	// (Also, set the collider pointer to NULL.)
	// Params:
	//	 collider = Pointer to the Collider component.
	void ColliderFree(Collider** collider)
	{
		if (*collider)
			free(*collider);

		*collider = NULL;
	}

	// ColliderRead has been replaced by the read func's in the ColliderCircle and ColliderLine components
 /*Read the properties of a Collider component from a file.
	 [NOTE: No values need to be read at this time.]
	 Params:
		 collider = Pointer to the Collider component.
		 stream = Pointer to the data stream used for reading.
	void ColliderRead(Collider* collider, Stream stream)
	{
		UNREFERENCED_PARAMETER(collider);
		UNREFERENCED_PARAMETER(stream);
	} */

	// Set the parent Entity for a Collider component.
	// Params:
	//	 collider = Pointer to the Collider component.
	//	 parent = Pointer to the parent Entity.
	void ColliderSetParent(Collider* collider, Entity* parent)
	{
		if (collider != NULL)
			collider->parent = parent;
	}

	// Check if two Entities are colliding.
	// (Hint: Refer to the project instructions for implementation suggestions.)
	// (Hint: Make sure to call the handler for both colliders, passing the 
	//	  parent Entity pointers in the correct order!)
	// Params:
	//	 collider1 = Pointer to the first Collider component.
	//	 collider2 = Pointer to the second Collider component.
	void ColliderCheck(const Collider* collider, const Collider* other)
	{
		if (collider != NULL && other != NULL)
		{ 
			//Original Proj 5 code
			/*
			Transform* colliderTransform = EntityGetTransform(collider->parent);
			Transform* otherTransform = EntityGetTransform(other->parent);

			const Vector2D* collPos = TransformGetTranslation(colliderTransform);
			const Vector2D* otherPos = TransformGetTranslation(otherTransform);

			const Vector2D* collScale = TransformGetScale(colliderTransform);
			const Vector2D* otherScale = TransformGetScale(otherTransform);

			
			float distanceSquared = Vector2DDistance(collPos, otherPos);


			float distanceScale = collScale->x * .5f + otherScale->x * .5f;

			if (distanceScale >= distanceSquared)
			{
				if (collider->handler)
					collider->handler(collider->parent, other->parent);

				if (other->handler)
					other->handler(other->parent, collider->parent);
			}*/

			//ColliderIsColliding(collider, other);
			if (ColliderIsColliding(collider, other))
			{
				if (collider->handler)
					collider->handler(collider->parent, other->parent);

				if (other->handler)
					other->handler(other->parent, collider->parent);
			}

			return;
		}
	}

	// Set the collision event handler for a collider.
	// (Hint: This allows other components, such as Behaviors, to respond to collision events.)
	// (Note: It is acceptable for the handler to be NULL.  This allows an existing handler to be removed.)
	// Params:
	//	 collider = Pointer to the Collider component.
	//	 handler = Pointer to the collision event handler (may be NULL).
	void ColliderSetCollisionHandler(Collider* collider, CollisionEventHandler handler)
	{
		collider->handler = handler;
	}

	//------------------------------------------------------------------------------
	
	//static bool ColliderIsColliding(const Collider* collider1, const Collider* collider2)
	//{
	//	if (collider1->type == ColliderTypeCircle && collider2->type == ColliderTypeCircle) 
	//	{
	//		return ColliderCircleIsCollidingWithCircle(collider1, collider2);
	//	}
	//	else if (collider1->type == ColliderTypeCircle && collider2->type == ColliderTypeLine)
	//	{
	//		//make sure order is correct for function call
	//		//return ColliderLineIsCollidingWithCircle(collider1, collider2);
	//	}
	//	else if (collider1->type == ColliderTypeLine && collider2->type == ColliderTypeCircle)
	//	{
	//		//return ColliderLineIsCollidingWithCircle(collider1, collider2);
	//	}
	//	else if (collider1->type == ColliderTypeLine && collider2->type == ColliderTypeLine)
	//	{
	//		printf(" Warning both colliders are Line colliders Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);
	//		return false;
	//	}
	//}

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

