//------------------------------------------------------------------------------
//
// File Name:	Level1Scene.c
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
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Stream.h"

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* livesFileName = "./Data/Level1_Lives.txt";

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* livesFile;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneUpdate(float dt);
static void Level1SceneExit(void);
static void Level1SceneUnload(void);
static void Level1SceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static Level1Scene instance =
{
	// Initialize the base structure:
	{ "Level1", Level1SceneLoad, Level1SceneInit, Level1SceneUpdate, Level1SceneRender, Level1SceneExit, Level1SceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene * Level1SceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void Level1SceneLoad(void)
{
	Stream lifeFile = StreamOpen(livesFileName);

	if (lifeFile != NULL)
	{
		instance.numLives = StreamReadInt(lifeFile);
		StreamClose(&lifeFile);
	}
}

// Initialize the variables used by the scene.
static void Level1SceneInit()
{

}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{
	instance.numLives--;

	if (instance.numLives <= 0)
	{
		// NOTE: This call causes the engine to exit immediately.  Make sure to remove
		//   it when you are ready to test out a new scene.
		SceneSystemSetNext(Level2SceneGetInstance());
	}

	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);
}

// Render the scene.
void Level1SceneRender(void)
{
}

// Exit the scene.
static void Level1SceneExit()
{
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
}

