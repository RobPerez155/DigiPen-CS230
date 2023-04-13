//------------------------------------------------------------------------------
//
// File Name:	Collider.cpp
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 7
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Collider.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"
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
			return ColliderLineIsCollidingWithCircle(collider1, collider2);
			//return false;
		}
		else if (collider1->type == ColliderTypeLine && collider2->type == ColliderTypeCircle)
		{
			return ColliderLineIsCollidingWithCircle(collider1, collider2);
			//return false;
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

		//Collider* colliderClone = calloc(1, other->memorySize);
		Collider* colliderClone = new Collider;
		colliderClone = static_cast<Collider*>(::operator new(other->memorySize));

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

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

