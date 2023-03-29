//------------------------------------------------------------------------------
//
// File Name:	CheatSystem.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <Windows.h>

#include "AsteroidsScene.h"
#include "BaseSystem.h"
#include "CheatSystem.h"
#include "DGL.h"
#include "DemoScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "OmegaScene.h"
#include "SandboxScene.h"
#include "SceneSystem.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct CheatSystem
{
	// WARNING: The base class must always be included first.
	BaseSystem	base;

	// Add any system-specific variables second.

} CheatSystem;

typedef struct
{
	char key;
	const Scene* (*getInstance)(void);

} CheatSystemKeyBinding;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//  System-specific State functions:
static bool CheatSystemInit(void);
static void CheatSystemUpdate(float dt);
static void CheatSystemRender(void);
static void CheatSystemExit(void);

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static CheatSystem instance =
{
	{ "CheatSystem", CheatSystemInit, CheatSystemUpdate, CheatSystemRender, CheatSystemExit},
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Get the instance of the Cheat System.
BaseSystem* CheatSystemGetInstance()
{
	// Initialize any system-specific variables here:

	// Return a reference to the instance of this system.
	return (BaseSystem*)&instance;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Initialize the System.
static bool CheatSystemInit(void)
{
	return true;
}

// Make an array of scenes
static const CheatSystemKeyBinding keyBindings[] =
{
		{'1', Level1SceneGetInstance},
		{'2', Level2SceneGetInstance},
		{'3', AsteroidsSceneGetInstance},
		{'4', SandboxSceneGetInstance},
		{'5', DemoSceneGetInstance},
		{'6', OmegaSceneGetInstance}
};

int arrLength = 6;

// Update the System.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void CheatSystemUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
	// Create for loop to check for key presses
	for (int i = 0; i <= arrLength; i++)
	{
		if (DGL_Input_KeyTriggered(keyBindings[i].key))
		{
			const Scene* nextScene = keyBindings[i].getInstance();
			SceneSystemSetNext(nextScene);
		}
	}
}

// Render the System.
static void CheatSystemRender(void)
{
}

//// Make an array of scenes
//static const CheatSystemKeyBinding keyBindings[] =
//{
//		{'1', Level1SceneGetInstance},
//		{'2', Level2SceneGetInstance},
//		{'3', AsteroidsSceneGetInstance},
//		{'4', SandboxSceneGetInstance},
//		{'5', DemoSceneGetInstance},
//		{'6', OmegaSceneGetInstance}
//}
//;
// Create for loop to check for key presses

// Shutdown the System.
//   (HINT: Free any allocated resources and/or opened files).
static void CheatSystemExit(void)
{
}

