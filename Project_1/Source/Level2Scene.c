//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Scene.h"
#include "SceneSystem.h"
#include "Level2Scene.h"

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} Level2Scene;

typedef struct Level2Scene
{
	int numLives;
	int numHealth;
};

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* livesFileName = "Level2_Lives.txt";
static const char* healthFileName = "Level2_Health.txt";

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* livesFile;
static FILE* healthFile;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneUpdate(float dt);
static void Level2SceneExit(void);
static void Level2SceneUnload(void);
static void Level2SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level2Scene instance =
{
	// Initialize the base structure:
	{ "Level2", Level2SceneLoad, Level2SceneInit, Level2SceneUpdate, Level2SceneRender, Level2SceneExit, Level2SceneUnload },

	// Initialize any scene-specific variables:
	Level2Scene.numLives = 0;
	Level2Scene.numHealth = 0;
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene* Level2SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level2SceneLoad(void)
{
	if (StreamOpen(livesFileName) != NULL)//..\Data\Level2_Lives.txt
	{
		StreamReadInt(livesFileName);
		StreamClose(livesFileName);
	}
}

// Initialize the variables used by the scene.
static void Level2SceneInit()
{
	if (StreamOpen(healthFileName) != NULL)//..\Data\Level2_Lives.txt
	{
		StreamReadInt(healthFileName);
		StreamClose(healthFileName);
	}
}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	numHealth -= 1;

	if (numHealth <= 0)
	{
		numLives -= 1;

		if (numLives > 0) 
		{
			Level2SceneInit();
		}
		else {
			// TO-DO Switch the scene System to "Sandbox"
			SceneSystemSetNext(NULL);
		}
		// NOTE: This call causes the engine to exit immediately.  Make sure to remove
		//   it when you are ready to test out a new scene.
		SceneSystemSetNext(NULL);
	}

	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render the scene.
void Level2SceneRender(void)
{
}

// Exit the scene.
static void Level2SceneExit()
{
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
}

