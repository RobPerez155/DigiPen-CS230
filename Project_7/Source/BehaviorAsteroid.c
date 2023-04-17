//------------------------------------------------------------------------------
//
// File Name:	BehaviorAsteroid.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#pragma once

#include "stdafx.h"

#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "Collider.h"
#include "DGL.h"
#include "Entity.h"
#include "Physics.h"
#include "Random.h"
#include "Scene.h"
#include "ScoreSystem.h"
#include "Teleporter.h"
#include "Vector2D.h"
#include "Transform.h"



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

typedef struct Behavior Behavior;

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------
typedef enum
{
	cAsteroidOriginTlc,
	cAsteroidOriginTrc,
	cAsteroidOriginBlc,
	cAsteroidOriginBrc,
	cAsteroidOriginCount,

} AsteroidOrigin;

typedef enum
{
	cAsteroidInvalid = -1,
	cAsteroidIdle = 0,

} AsteroidState;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------
typedef struct BehaviorAsteroid
	{
		// Inherit the base behavior structure.
		Behavior	base;

		// Add asteroid-specific behavior variables.
		AsteroidOrigin	origin;

	} BehaviorAsteroid;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
// Speed range of the asteroids.
static const float asteroidSpeedMin = 50.0f;
static const float asteroidSpeedMax = 100.0f;

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
static void BehaviorAsteroidInit(Behavior*);
static void BehaviorAsteroidUpdate(Behavior*, float dt);
static void BehaviorAsteroidExit(Behavior*);
static void BehaviorAsteroidSetPosition(BehaviorAsteroid*);
static void BehaviorAsteroidSetVelocity(BehaviorAsteroid*);
static void BehaviorAsteroidCollisionHandler(Entity*, const Entity*);


// Dynamically allocate a new (Asteroid) behavior component.
// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
Behavior* BehaviorAsteroidCreate(void)
{
	//BehaviorAsteroid* ptrBehaviorAsteroid = calloc(1, sizeof(BehaviorAsteroid));
	BehaviorAsteroid* ptrBehaviorAsteroid = new BehaviorAsteroid();

	if (ptrBehaviorAsteroid != nullptr)
	{
		ptrBehaviorAsteroid->base.onInit = BehaviorAsteroidInit;
		ptrBehaviorAsteroid->base.onUpdate = BehaviorAsteroidUpdate;
		ptrBehaviorAsteroid->base.onExit = BehaviorAsteroidExit;
		ptrBehaviorAsteroid->base.memorySize = sizeof(BehaviorAsteroid);
		ptrBehaviorAsteroid->base.stateCurr = cAsteroidInvalid;
		ptrBehaviorAsteroid->base.stateNext = cAsteroidIdle;

		return (Behavior*)ptrBehaviorAsteroid;
	}
	else
		return nullptr;
}



void BehaviorAsteroidInit(Behavior* behavior)
{
	BehaviorAsteroid* asteroid = (BehaviorAsteroid*)behavior;
	
	if (asteroid->base.stateCurr == cAsteroidIdle)
	{
		int aOrigin = RandomRange(0, 3);

		//asteroid->origin = RandomRange(0, 3);
		switch (aOrigin)
		{
		case 0:
			asteroid->origin = cAsteroidOriginTlc;
			break;
		case 1:
			asteroid->origin = cAsteroidOriginTrc;
			break;
		case 2:
			asteroid->origin = cAsteroidOriginBlc;
			break;
		case 3:
			asteroid->origin = cAsteroidOriginBrc;
			break;
		default:
			asteroid->origin = cAsteroidOriginTlc;
			break;
		}
		BehaviorAsteroidSetPosition(asteroid);
		BehaviorAsteroidSetVelocity(asteroid);
		
		Collider* collider = EntityGetCollider(asteroid->base.parent);
		if (collider != nullptr)
		{
			//			ColliderSetCollisionHandler(collider, static_cast<CollisionEventHandler>(BehaviorAsteroidCollisionHandler(collider->parent, asteroid->base.parent)));
			ColliderSetCollisionHandler(collider, BehaviorAsteroidCollisionHandler);
		}
	}
}

void BehaviorAsteroidUpdate(Behavior* behavior, float dt)
{
	UNREFERENCED_PARAMETER(dt);
	switch (behavior->stateCurr)
	{
		case cAsteroidIdle:

			break;
		default:
			break;
	}
	
	TeleporterUpdateEntity(behavior->parent);
}

void BehaviorAsteroidCollisionHandler(Entity* entity1, const Entity* entity2)
{
	if (entity1 != nullptr && entity2 != nullptr)
	{
		const char* entity2Name = EntityGetName(entity2);
		if (strcmp(entity2Name, "Bullet") == 0 || strcmp(entity2Name, "Spaceship") == 0)
		{
			ScoreSystemIncreaseScore(20);
			EntityDestroy(entity1);
		}
	}
}

void BehaviorAsteroidSetPosition(BehaviorAsteroid* behaviorAsteroid)
{
	Vector2D newPosition;
	Vector2DZero(&newPosition);

	DGL_Vec2 windowSize = DGL_Window_GetSize();

	//Call Vector2DScale to scale the dimensions by 0.5f to get the window half size.
	DGL_Vec2 halfWindowSize;
	Vector2DScale(&halfWindowSize, &windowSize, 0.5);

	//The bottom - left corner of the window is at –halfSize.
	DGL_Vec2 botLeft = { -halfWindowSize.x, -halfWindowSize.y };

	//The top - right corner of the window is at + halfSize.
	DGL_Vec2 topRight = halfWindowSize;

	switch (behaviorAsteroid->origin)
	{
	case cAsteroidOriginTlc:
		newPosition.x = botLeft.x;/*+ behaviorAsteroid->origin;*/
		newPosition.y = topRight.y ;/*- behaviorAsteroid->origin;*/
	break;

	case cAsteroidOriginTrc:
		newPosition.x = topRight.x ;/*- behaviorAsteroid->origin;*/
		newPosition.y = topRight.y ;/*- behaviorAsteroid->origin;*/
	break;

	case cAsteroidOriginBlc:
		newPosition.x = botLeft.x ;/*+ behaviorAsteroid->origin;*/
		newPosition.y = botLeft.y ;/*+ behaviorAsteroid->origin;*/
	break;

	case cAsteroidOriginBrc:
		newPosition.x = topRight.x ;/*- behaviorAsteroid->origin;*/
		newPosition.y = botLeft.y ;/*+ behaviorAsteroid->origin;*/
	break;

	default:
	break;
	}
	Transform* t = EntityGetTransform(behaviorAsteroid->base.parent);
	TransformSetTranslation(t, &newPosition);
}

void BehaviorAsteroidSetVelocity(BehaviorAsteroid* behaviorAsteroid)
{
	float newAngle = 0;

	switch (behaviorAsteroid->origin)
	{
	case cAsteroidOriginTlc:
		newAngle = RandomRangeFloat(-80, -10);
		break;

	case cAsteroidOriginTrc:
		newAngle = RandomRangeFloat(-170, -100);
		break;

	case cAsteroidOriginBlc:
		newAngle = RandomRangeFloat(10, 80);
		break;

	case cAsteroidOriginBrc:
		newAngle = RandomRangeFloat(100, 170);
		break;

	default:
		break;
	}

	float newSpeed = RandomRangeFloat(asteroidSpeedMin, asteroidSpeedMax);
	Physics* physics = EntityGetPhysics(behaviorAsteroid->base.parent);

	if (physics != nullptr)
	{
		Vector2D newVelocity;

		// Get the degree in vector form
		Vector2DFromAngleDeg(&newVelocity, newAngle);

		Vector2DNormalize(&newVelocity, &newVelocity);

		Vector2DScale(&newVelocity, &newVelocity, newSpeed);

		PhysicsSetVelocity(physics, &newVelocity);
	}
}

void BehaviorAsteroidExit(Behavior* behavior)
{
	UNREFERENCED_PARAMETER(behavior);
}

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

