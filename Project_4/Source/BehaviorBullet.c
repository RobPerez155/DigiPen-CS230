//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.c
// Author(s):	Rob Perez(rob.perez)
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
#include "Entity.h"
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
	//------------------------------------------------------------------------------

	// Dynamically allocate a new (Bullet) behavior component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	Behavior* BehaviorBulletCreate(void)
	{
		Behavior* bullet = calloc(1, sizeof(Behavior));
		
		if (bullet != NULL)
		{
			bullet->stateCurr = cBulletInvalid;
			bullet->stateNext = cBulletInvalid;
			bullet->onInit = BehaviorBulletInit;
			bullet->onUpdate = BehaviorBulletUpdate;
			bullet->onExit = BehaviorBulletExit;

			return bullet;
		}
		else
			return NULL;
	}

	// Initialize the current state of the behavior component.
	// (Hint: Refer to the lecture notes on finite state machines (FSM).)
	// Params:
	//	 behavior = Pointer to the behavior component.
	void BehaviorBulletInit(Behavior* behavior)
	{
		UNREFERENCED_PARAMETER(behavior);
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

