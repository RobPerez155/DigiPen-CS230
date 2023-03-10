//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s): Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright ? 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Physics.h"
#include "DGL.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	// An example of the structure to be defined in Physics.c.

typedef struct Physics
{
	// Previous position.  May be used for resolving collisions.
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;
} Physics;

		// Used when calculating acceleration due to forces.
		// Used when resolving collision between two dynamic objects.
		//float		inverseMass;


	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Physics component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
		Physics* PhysicsCreate(void)
		{
			Physics* ptrPhysics = calloc(1, sizeof(Physics));

			if (ptrPhysics != NULL)
			{
				return ptrPhysics;
			} else {
				return NULL;
			}
		}

	// Free the memory associated with a Physics component.
	// (NOTE: The Physics pointer must be set to NULL.)
	// Params:
	//	 physics = Pointer to the Physics component pointer.
		void PhysicsFree(Physics** physics) 
		{
			if (*physics)
				free(*physics);

			*physics = NULL;
		}

	// Read the properties of a Physics component from a file.
	// [NOTE: Read the acceleration and velocity values using StreamReadVector2D.]
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 stream = Pointer to the data stream used for reading.
	void PhysicsRead(Physics* physics, Stream stream)
	{
		StreamReadVector2D(stream, &physics->acceleration);
		StreamReadVector2D(stream, &physics->velocity);
	}

	// Get the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's acceleration structure,
	//		else return a NULL pointer.
	const Vector2D* PhysicsGetAcceleration(const Physics* physics)
	{
		if (physics != NULL)
		{
			return &physics->acceleration;
		}
		else {
			return NULL;
		}
	}
	// Get the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's velocity structure,
	//		else return a NULL pointer.
	const Vector2D* PhysicsGetVelocity(const Physics* physics)
	{
		if (physics != NULL)
		{
			return &physics->velocity;
		}
		else {
			return NULL;
		}
	}

	// Get the old translation (position) of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's oldTranslation structure,
	//		else return a NULL pointer.
	const Vector2D* PhysicsGetOldTranslation(Physics* physics)
	{
		if (physics != NULL)
		{
			return &physics->oldTranslation;
		}
		else {
			return NULL;
		}
	}

	// Set the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 acceleration = Pointer to an acceleration vector.
	void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
	{
		physics->acceleration = *acceleration;
	}

	// Set the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 velocity = Pointer to a velocity vector.
	void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
	{
		physics->velocity = *velocity;
	}

	// Update the state of a Physics component using the Semi-Implicit Euler method,
	// Params:
	//	 physics = Pointer to the physics component.
	//	 transform = Pointer to the associated transform component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
	{	
		if (physics != NULL && transform != NULL)
		{
			// Find translation after velocity and acceleration are applied with dt
			Vector2D result;
			Vector2D dtAccel;
			Vector2D dtVelocity;

			//REVIEW
			// Update previous translation
			physics->oldTranslation = *TransformGetTranslation(transform);

			// Update acceleration after dt is applied
			Vector2DScale(&dtAccel, &physics->acceleration, dt);
			//Subtract acceleration from current velocity
			Vector2DAdd(&physics->velocity, &physics->velocity, &dtAccel);

			// Update velocity after dt is applied
			Vector2DScale(&dtVelocity, &physics->velocity, dt);
			//Add velocity to current translation
			Vector2DAdd(&result, &dtVelocity, &physics->oldTranslation);

			//Set new translation
			TransformSetTranslation(transform, &result);
		}
	
	}

	//------------------------------------------------------------------------------

