//------------------------------------------------------------------------------
//
// File Name:	Stub.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "SceneSystem.h"
#include "AsteroidsScene.h"
#include "DemoScene.h"
#include "DGL.h"
#include "EntityFactory.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SandboxScene.h"
#include "Scene.h"


#include "Entity.h"


//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct AsteroidsScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} AsteroidsScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void AsteroidsSceneLoad(void);
static void AsteroidsSceneInit(void);
static void AsteroidsSceneUpdate(float dt);
static void AsteroidsSceneExit(void);
static void AsteroidsSceneUnload(void);
static void AsteroidsSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static AsteroidsScene instance =
{
	// Initialize the base structure:
	{ "AsteroidsScene", AsteroidsSceneLoad, AsteroidsSceneInit, AsteroidsSceneUpdate, AsteroidsSceneRender, AsteroidsSceneExit, AsteroidsSceneUnload },

	// Initialize any scene-specific variables:

};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene* AsteroidsSceneGetInstance(void)
{
	return &(instance.base);
}


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void AsteroidsSceneLoad(void)
{

}

// Initialize the ...
void AsteroidsSceneInit()
{
	Entity* Spaceship = EntityFactoryBuild("Spaceship");
	
	if (Spaceship != NULL)
	{
		SceneAddEntity(Spaceship);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AsteroidsSceneUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	// Switch to Level 1
	if (DGL_Input_KeyTriggered('1'))
	{
		SceneSystemSetNext(Level1SceneGetInstance());
	}

	// Switch to Level 2
	if (DGL_Input_KeyTriggered('2'))
	{
		SceneSystemSetNext(Level2SceneGetInstance());
	}

	// Restart Asteroid Level
	if (DGL_Input_KeyTriggered('3'))
	{
		AsteroidsSceneInit();
	}

	// Switch to Sandbox Scene
	if (DGL_Input_KeyTriggered('9'))
	{
		SceneSystemSetNext(SandboxSceneGetInstance());
	}

	// Restarts Scene
	if (DGL_Input_KeyTriggered('0'))
	{
		SceneSystemSetNext(DemoSceneGetInstance());
	}
}

// Render the scene.
void AsteroidsSceneRender(void)
{
	//SpriteDraw(AsteroidsBackground, (DGL_Vec2) { 0.0f, 0.0f }, (DGL_Vec2) { 1440.0f, 810.0f }, 0.0f);

	//drawButton(AsteroidsButton);
}

// Shutdown the ...
void AsteroidsSceneExit()
{
}

static void AsteroidsSceneUnload(void)
{

}
