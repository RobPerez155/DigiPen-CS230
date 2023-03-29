//------------------------------------------------------------------------------
//
// File Name:	BehaviorHudText.c
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
#include "BehaviorHudText.h"
#include "Entity.h"
#include "ScoreSystem.h"
#include "Sprite.h"
#include "Stream.h"

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
	typedef FILE* Stream;

	//------------------------------------------------------------------------------
	// Public Consts:
	//------------------------------------------------------------------------------

	typedef enum HudTextStates
	{
		cHudTextInvalid = -1,	// HUD Text has not yet been initialized.
		cHudTextIdle,			// HUD Text will normally remain static.

	} HudTextStates;

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	typedef struct BehaviorHudText
	{
		// Inherit the base behavior structure.
		Behavior	base;

		// Add HUD Text-specific behavior variables.

		// The format string to be used with sprintf_s() when updating the HUD Text object.
		// (For example: "Score: %d")
		char formatString[32];

		// The buffer to be used with sprintf_s() when updating the HUD Text object.
		// (For example: "Score: 9001")
		// (NOTE: This buffer has an arbitrary length of 32 chars, which is sufficient for this project.
		//	Exercise caution when using buffers of a fixed length (e.g. use sprintf_s).
		char displayString[32];

		// Pointer to the int value to be used when displaying the HUD Text object.
		// (NOTE: This value will be compared against displayValue to determine when the text must be updated.)
		const int* watchValue;

		int scoreSystem;

		// The value currently being displayed by the HUD Text object.
		// (NOTE: This value can be compared with *watchValue to determine when the text must be updated.)
		// (NOTE: Make sure to update this value each time the text is updated.)
		unsigned displayValue;

	} BehaviorHudText;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------
	static void BehaviorHudTextInit(Behavior*);
	static void BehaviorHudTextUpdate(Behavior*, float dt);
	static void BehaviorHudTextExit(Behavior*);
	static void BehaviorHudTextUpdateText(BehaviorHudText*);


	// Dynamically allocate a new (HUD Text) behavior component.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	Behavior* BehaviorHudTextCreate(void)
	{
		BehaviorHudText* behaviorHudText = calloc(1, sizeof(BehaviorHudText));

		if (behaviorHudText != NULL)
		{
			behaviorHudText->base.memorySize = sizeof(BehaviorHudText);
			behaviorHudText->base.onInit = BehaviorHudTextInit;
			behaviorHudText->base.onUpdate = BehaviorHudTextUpdate;
			behaviorHudText->base.onExit = BehaviorHudTextExit;
			behaviorHudText->base.stateCurr = cHudTextInvalid;
			behaviorHudText->base.stateNext = cHudTextIdle;
			behaviorHudText->scoreSystem = SsiInvalid;

			return (Behavior*)behaviorHudText;
		}
		return NULL;
	}

	// Read the properties of a Behavior component from a file.
	// (NOTE: Read the base Behavior values using BehaviorRead.)
	// (NOTE: Read the formatString using StreamReadToken.)
	// (NOTE: Read the scoreSystemId using StreamReadInt.)
	// Params:
	//	 behavior = Pointer to the Behavior component.
	//	 stream = Pointer to the data stream used for reading.
	void BehaviorHudTextRead(Behavior* behavior, Stream stream)
	{
		if (behavior != NULL)
		{
			BehaviorRead(behavior, stream);
			BehaviorHudText* tempBehavior = (BehaviorHudText*)behavior;
			//behavior is empty
	
			strcpy_s(tempBehavior->formatString, _countof(tempBehavior->formatString), StreamReadToken(stream));
			tempBehavior->scoreSystem = StreamReadInt(stream);
		}
	}


	void BehaviorHudTextExit(Behavior* behavior)
	{
		UNREFERENCED_PARAMETER(behavior);
	}

	void BehaviorHudTextUpdate(Behavior* behavior, float dt)
	{
		BehaviorHudText* hudText = (BehaviorHudText*)behavior;
		BehaviorHudTextUpdateText(hudText);
		UNREFERENCED_PARAMETER(dt);
	}

	void BehaviorHudTextInit(Behavior* behavior)
	{
		BehaviorHudText* hudText = (BehaviorHudText*)behavior;
		Sprite* sprite = EntityGetSprite(behavior->parent);

		BehaviorHudTextUpdateText(hudText);

		if (sprite != NULL)
		{
			SpriteSetText(sprite, hudText->displayString);
		}


	}


	void BehaviorHudTextUpdateText(BehaviorHudText* behaviorText)
	{
		//UNREFERENCED_PARAMETER(behaviorText);
		//if (behaviorText->watchValue != NULL && *behaviorText->watchValue != behaviorText->displayValue)
		//{
		//	behaviorText->displayValue = *behaviorText->watchValue;
		//	sprintf_s(behaviorText->displayString, 32, behaviorText->formatString, behaviorText->displayValue);
		//	
		//}


		if (behaviorText->scoreSystem != SsiInvalid)
		{
			behaviorText->displayValue = ScoreSystemGetValue(behaviorText->scoreSystem);
			//sprintf_s(behaviorText->displayString, behaviorText->formatString, behaviorText->displayValue);
			sprintf_s(behaviorText->displayString, 32, behaviorText->formatString, behaviorText->displayValue);
		}
	}
	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

