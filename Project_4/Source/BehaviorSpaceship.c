//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 4
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
//#include <math.h>
#include "DGL.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Physics.h"
#include "Transform.h"
#include "Vector2D.h"

#define PI 3.14159265358979323846

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	typedef struct Behavior Behavior;

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
	// Private Variables:
	//------------------------------------------------------------------------------
	static const float spaceshipAcceleration = 150.0f;
	static const float spaceshipSpeedMax = 500.0f;
	static const float spaceshipTurnRateMax = (float) PI / 1.5f;
	static const float spaceshipWeaponCooldownTime = 0.034f;
	static const float spaceshipWeaponBulletSpeed = 750.0f;


	enum SpaceshipState {
		cSpaceshipInvalid = -1,
		cSpaceshipIdle,
		cSpaceshipThrust
	};

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Functions:
	//-----------------------------
	static void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt);
	static void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt);
	static void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt);
	static void BehaviorSpaceshipSpawnBullet(Behavior* behavior);



	// Dynamically allocate a new (Spaceship) behavior component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	Behavior* BehaviorSpaceshipCreate(void)
	{
		Behavior* ptrBehavior = calloc(1, sizeof(Behavior));

		if (ptrBehavior != NULL)
		{
			ptrBehavior->stateCurr = cSpaceshipInvalid;
			ptrBehavior->stateNext = cSpaceshipInvalid;
			ptrBehavior->onInit = BehaviorSpaceshipInit;
			ptrBehavior->onUpdate = BehaviorSpaceshipUpdate;
			ptrBehavior->onExit = BehaviorSpaceshipExit;

			return ptrBehavior;
		}
		else
			return NULL;
	}


	// Initialize the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	void BehaviorSpaceshipInit(Behavior* behavior)
	{
		UNREFERENCED_PARAMETER(behavior);
	}

	// Update the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void BehaviorSpaceshipUpdate(Behavior* behavior, float dt)
	{
		switch (behavior->stateCurr) {
		case cSpaceshipIdle:
			BehaviorSpaceshipUpdateRotation(behavior, dt);
			BehaviorSpaceshipUpdateWeapon(behavior, dt);
			
			if (DGL_Input_KeyDown(VK_UP))
			{
				behavior->stateNext = cSpaceshipThrust;
			}
			break;
		case cSpaceshipThrust:
			BehaviorSpaceshipUpdateRotation(behavior, dt);
			BehaviorSpaceshipUpdateVelocity(behavior, dt);
			BehaviorSpaceshipUpdateWeapon(behavior, dt);

			if (!DGL_Input_KeyDown(VK_UP))
			{
				behavior->stateNext = cSpaceshipIdle;
			}
			break;
		}
	}

	// Exit the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void BehaviorSpaceshipExit(Behavior* behavior)
	{
		UNREFERENCED_PARAMETER(behavior);
	}

	void BehaviorSpaceshipUpdateRotation(Behavior* behavior, float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		Physics* physics = EntityGetPhysics(behavior->parent);

		if (DGL_Input_KeyDown(VK_LEFT))
		{
			PhysicsSetRotationalVelocity(physics, spaceshipTurnRateMax);
		}
		else if (DGL_Input_KeyDown(VK_RIGHT))
		{
			PhysicsSetRotationalVelocity(physics, -spaceshipTurnRateMax);
		}
		else
		{
			PhysicsSetRotationalVelocity(physics, 0.0);
		}
	}
	
	void BehaviorSpaceshipUpdateVelocity(Behavior* behavior, float dt)
	{
		Transform* transform = EntityGetTransform(behavior->parent);
		Physics* physics = EntityGetPhysics(behavior->parent);

		if (transform == NULL || physics == NULL)
			return;
			
		// Get unit vector in direction of rotation
		float rotation = TransformGetRotation(transform);
		Vector2D rotation2D;
		
		Vector2DFromAngleRad(&rotation2D, rotation);
		Vector2DNormalize(&rotation2D, &rotation2D);

		// Get current velocity
		Vector2D velocity = *PhysicsGetVelocity(physics);
		
		float acceleration = spaceshipAcceleration * dt;
		Vector2DScale(&rotation2D, &rotation2D, acceleration);
		Vector2DAdd(&velocity, &velocity, &rotation2D);

		float speed = Vector2DLength(&velocity);

		// Cap max speed
		if (speed > spaceshipSpeedMax)
		{
			Vector2DScale(&velocity, &velocity, spaceshipSpeedMax / speed);
		}

		PhysicsSetVelocity(physics, &velocity);
	}

	void BehaviorSpaceshipUpdateWeapon(Behavior* behavior, float dt)
	{
		if (behavior == NULL)
		{
			return;
		}
		if (behavior->timer > 0)
		{
			behavior->timer -= dt;

			if (behavior->timer < 0)
			{
				behavior->timer = 0;
			}
		}

		if (DGL_Input_KeyDown(' '))
		{
			if (behavior->timer <= 0)
			{
				BehaviorSpaceshipSpawnBullet(behavior);
				behavior->timer = spaceshipWeaponCooldownTime;
			}
		}
	}

	void BehaviorSpaceshipSpawnBullet(Behavior* behavior)
	{
		
		Entity* bullet = EntityFactoryBuild("Bullet");

		if (bullet != NULL)
		{
			// Get transform info
			Transform* transform = EntityGetTransform(behavior->parent);
			float rotation = TransformGetRotation(transform);
			const Vector2D* position = TransformGetTranslation(transform);

			// Set bullet transform
			Transform* bulletTransform = EntityGetTransform(bullet);
			TransformSetRotation(bulletTransform, rotation);
			TransformSetTranslation(bulletTransform, position);

			// Set bullet physics
			Vector2D rotationVector;
			Vector2DToAngleRad(&rotationVector);
			Physics* bulletPhysics = EntityGetPhysics(bullet);
			Vector2DScale(&rotationVector, &rotationVector, spaceshipWeaponBulletSpeed);
			PhysicsSetVelocity(bulletPhysics, &rotationVector);

			EntityClone(bullet);			
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

