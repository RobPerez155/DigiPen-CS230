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

#include "Entity.h"
#include "Transform.h"
#include "Vector2D.h"

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

	typedef void(*CollisionEventHandler)(Entity* entity1, Entity* entity2);

	typedef struct Collider
	{
		// Pointer to the collider's parent Entity.
		Entity* parent;

		// Pointer to a function that handles collisions between two objects.
		CollisionEventHandler	handler;

	} Collider;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Collider component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	Collider* ColliderCreate(void)
	{
		Collider* ptrCollider = calloc(1, sizeof(Collider));

		if (ptrCollider != NULL)
		{
			return ptrCollider;
		}
		else {
			return NULL;
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

		Collider* colliderClone = calloc(1, sizeof(Collider));

		if (colliderClone == NULL)
		{
			return NULL;
		}

		*colliderClone = *other;

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

	// Read the properties of a Collider component from a file.
	// [NOTE: No values need to be read at this time.]
	// Params:
	//	 collider = Pointer to the Collider component.
	//	 stream = Pointer to the data stream used for reading.
	void ColliderRead(Collider* collider, Stream stream)
	{
		UNREFERENCED_PARAMETER(collider);
		UNREFERENCED_PARAMETER(stream);
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
	void ColliderCheck(Collider* collider, Collider* other)
	{
		if (collider == NULL || other == NULL)
		{
			return;
		}


	}

	// Set the collision event handler for a collider.
	// (Hint: This allows other components, such as Behaviors, to respond to collision events.)
	// (Note: It is acceptable for the handler to be NULL.  This allows an existing handler to be removed.)
	// Params:
	//	 collider = Pointer to the Collider component.
	//	 handler = Pointer to the collision event handler (may be NULL).
	void ColliderSetCollisionHandler(Collider* collider, CollisionEventHandler handler);

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

