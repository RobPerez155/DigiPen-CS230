//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s): Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
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

	float rotationalVelocity;
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
	//	   else return nullptr.
	Physics* PhysicsCreate(void)
		{
			Physics* ptrPhysics = new Physics();

			if (ptrPhysics != nullptr)
			{
				return ptrPhysics;
			} else {
				return nullptr;
			}
		}
	//Physics* Physics::Create(void)
	//{
	//	Physics* ptrPhysics = new Physics();

	//	if (ptrPhysics != nullptr)
	//	{
	//		return ptrPhysics;
	//	}
	//	else {
	//		return nullptr;
	//	}
	//}

	// Dynamically allocate a clone of an existing Physics component.
	// (Hint: Perform a shallow copy of the member variables.)
	// Params:
	//	 other = Pointer to the component to be cloned.
	// Returns:
	//	 If 'other' is valid and the memory allocation was successful,
	//	   then return a pointer to the cloned component,
	//	   else return nullptr.
	Physics* PhysicsClone(const Physics* other)
	{
		if (other == nullptr)
		{
			return nullptr;
		}

		Physics* physicsClone = new Physics();

		if (physicsClone == nullptr)
		{
			return nullptr;
		}

		*physicsClone = *other;

		return physicsClone;
	}
	/*Physics* Physics::Clone(const Physics* other)
	{
		if (other == nullptr)
		{
			return nullptr;
		}

		Physics* physicsClone = new Physics();

		if (physicsClone == nullptr)
		{
			return nullptr;
		}

		*physicsClone = *other;

		return physicsClone;
	}*/

	// Get the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
// Returns:
//	 If the physics pointer is valid,
//		then return the component's rotational velocity value,
//		else return 0.0f.
	float PhysicsGetRotationalVelocity(const Physics* physics)
	{
		if (physics != nullptr)
		{
			return physics->rotationalVelocity;
		}
		else {
			return 0.0f;
		}
	}
	//float Physics::GetRotationalVelocity()
	//{
	//	if (this != nullptr)
	//	{
	//		return this->rotationalVelocity;
	//	}
	//	else {
	//		return 0.0f;
	//	}
	//}

		// Set the rotational velocity of a physics component.
// Params:
//	 physics = Pointer to the physics component.
//	 rotationalVelocity = The new rotational velocity.
	void PhysicsSetRotationalVelocity(Physics* physics, float rotationalVelocity)
	{
		physics->rotationalVelocity = rotationalVelocity;
	}
	//void Physics::SetRotationalVelocity(float rotationalVelocity)
	//{
	//	this->rotationalVelocity = rotationalVelocity;
	//}

	// Free the memory associated with a Physics component.
	// (NOTE: The Physics pointer must be set to nullptr.)
	// Params:
	//	 physics = Pointer to the Physics component pointer.
		void PhysicsFree(Physics** physics) 
		{
			if (*physics)
				delete(*physics);

			*physics = nullptr;
		}

		//void Physics::Free(Physics** physics)
		//{
		//	if (*physics)
		//		delete(*physics);

		//	*physics = nullptr;
		//}

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
	//void Physics::Read(Stream stream)
	//{
	//	StreamReadVector2D(stream, &this->acceleration);
	//	StreamReadVector2D(stream, &this->velocity);
	//	StreamReadVector2D(stream, &acceleration);
	//	StreamReadVector2D(stream, &velocity);
	//}

	// Get the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's acceleration structure,
	//		else return a nullptr pointer.
	const Vector2D* PhysicsGetAcceleration(const Physics* physics)
	{
		if (physics != nullptr)
		{
			return &physics->acceleration;
		}
		else {
			return nullptr;
		}
	}
		//const Vector2D* PhysicsGetAcceleration(const Physics* physics)
	//{
	//	if (physics != nullptr)
	//	{
	//		return &physics->acceleration;
	//	}
	//	else {
	//		return nullptr;
	//	}
	//}

	// Get the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's velocity structure,
	//		else return a nullptr pointer.
	const Vector2D* PhysicsGetVelocity(const Physics* physics)
	{
		if (physics != nullptr)
		{
			return &physics->velocity;
		}
		else {
			return nullptr;
		}
	}
	//const Vector2D* Physics::GetVelocity(const Physics* physics)
	//{
	//	return &velocity;
	//}



	// Get the old translation (position) of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	// Returns:
	//	 If the physics pointer is valid,
	//		then return a pointer to the component's oldTranslation structure,
	//		else return a nullptr pointer.
	const Vector2D* PhysicsGetOldTranslation(Physics* physics)
	{
		if (physics != nullptr)
		{
			return &physics->oldTranslation;
		}
		else {
			return nullptr;
		}
	}
	//const Vector2D* Physics::GetOldTranslation()
	//{
	//	if (this != nullptr)
	//	{
	//		return &oldTranslation;
	//	}
	//	else {
	//		return nullptr;
	//	}
	//}


	// Set the acceleration of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 acceleration = Pointer to an acceleration vector.
	void PhysicsSetAcceleration(Physics* physics, const Vector2D* acceleration)
	{
		physics->acceleration = *acceleration;
	}
	//void Physics::SetAcceleration(const Vector2D* acceleration)
	//{
	//	if (acceleration != nullptr)
	//	{
	//		this->acceleration = *acceleration;
	//	}
	//}


	// Set the velocity of a Physics component.
	// Params:
	//	 physics = Pointer to the Physics component.
	//	 velocity = Pointer to a velocity vector.
	void PhysicsSetVelocity(Physics* physics, const Vector2D* velocity)
	{
		physics->velocity = *velocity;
	}
	//void Physics::SetVelocity(const Vector2D* velocity)
	//{
	//	if (velocity != nullptr)
	//	{
	//		this->velocity = *velocity;
	//	}
	//}


	// Update the state of a Physics component using the Semi-Implicit Euler method,
	// Params:
	//	 physics = Pointer to the physics component.
	//	 transform = Pointer to the associated transform component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
	{	
		if (physics != nullptr && transform != nullptr)
		{
			// Update previous translation
			physics->oldTranslation = *TransformGetTranslation(transform);

			// Find translation after velocity and acceleration are applied with dt
			Vector2D result;

			//Update acceleration after dt is applied add acceleration from current velocity
			Vector2DScaleAdd(&physics->velocity, &physics->acceleration, &physics->velocity, dt);

			// Update velocity after dt is applied and add velocity to current translation
			Vector2DScaleAdd(&result, &physics->velocity, &physics->oldTranslation, dt);

			//Set new translation
			TransformSetTranslation(transform, &result);
			
			float rotation = TransformGetRotation(transform) + physics->rotationalVelocity * dt;

			TransformSetRotation(transform, rotation);
		}
	}

	//void Physics::Update(Transform* transform, float dt)
	//{
	//	if (this != nullptr && transform != nullptr)
	//	{
	//		// Update previous translation
	//		this->oldTranslation = *transform->GetTranslation();

	//		// Find translation after velocity and acceleration are applied with dt
	//		Vector2D result;

	//		//Update acceleration after dt is applied add acceleration from current velocity
	//		Vector2DScaleAdd(&this->velocity, &this->acceleration, &this->velocity, dt);

	//		// Update velocity after dt is applied and add velocity to current translation
	//		Vector2DScaleAdd(&result, &this->velocity, &this->oldTranslation, dt);

	//		//Set new translation
	//		transform->SetTranslation(result);

	//		float rotation = transform->GetRotation() + physics->rotationalVelocity * dt;

	//		transform->SetRotation(rotation);
	//	}
	//}

	//------------------------------------------------------------------------------

