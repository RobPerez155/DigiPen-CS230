//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.h
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
#include "Behavior.h"
#include "BehaviorBullet.h"
#include "Collider.h"
#include "Entity.h"
#include "Teleporter.h"
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
	// Private Variables:
	// 
	static const float spaceshipSpeedMax = 500.0f;

	enum BulletState {
		cBulletInvalid = -1,
		cBulletIdle,
		cBulletThrust
	};
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Functions:
	// 
		static void BehaviorBulletUpdateLifeTimer(Behavior* behavior, float dt);
		static void BehaviorBulletCollisionHandler(Entity* entity1, Entity* entity2);
	//------------------------------------------------------------------------------

	// Dynamically allocate a new (Bullet) behavior component.
	Behavior* BehaviorBulletCreate(void)
	{
		//Behavior* bullet = calloc(1, sizeof(Behavior));
		Behavior* bullet = new Behavior();

		if (bullet != nullptr)
		{
			bullet->stateCurr = cBulletInvalid;
			bullet->stateNext = cBulletInvalid;
			bullet->onInit = BehaviorBulletInit;
			bullet->onUpdate = BehaviorBulletUpdate;
			bullet->memorySize = sizeof(Behavior);
			bullet->onExit = BehaviorBulletExit;

			return bullet;
		}
		else
			return nullptr;
	}

	void BehaviorBulletCollisionHandler(Entity* entity1, Entity* entity2)
	{
		if (entity1 != nullptr && entity2 != nullptr)
		{
			const char* asteroid = "Asteroid";
			const char* ent2 = EntityGetName(entity2);
			if (strcmp(ent2, asteroid) == 0)
			{
				EntityDestroy(entity1);
			}
		}
	}

	// Initialize the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	void BehaviorBulletInit(Behavior* behavior)
	{
		if (behavior->stateCurr == cBulletIdle)
		{
			Collider* parentCollider = EntityGetCollider(behavior->parent);

			if (parentCollider != nullptr)
			{
				ColliderSetCollisionHandler(parentCollider, BehaviorBulletCollisionHandler);
			}
		}
	}

	// Update the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void BehaviorBulletUpdate(Behavior* behavior, float dt)
	{
		switch (behavior->stateCurr) 
		{
		case cBulletIdle:
			BehaviorBulletUpdateLifeTimer(behavior, dt);
			break;
		}

		TeleporterUpdateEntity(behavior->parent);
	}

	// Exit the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	//	 dt = Change in time (in seconds) since the last game loop.
	void BehaviorBulletExit(Behavior* behavior)
	{
		UNREFERENCED_PARAMETER(behavior);
	}

	void BehaviorBulletUpdateLifeTimer(Behavior* behavior, float dt)
	{
		if (behavior->timer > 0)
		{
			behavior->timer -= dt;
			if (behavior->timer <= 0)
			{
				EntityDestroy(behavior->parent);
				
			}
		}
	}

	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

