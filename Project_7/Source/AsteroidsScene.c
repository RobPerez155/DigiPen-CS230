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
#include "ColliderCircle.h"
#include "DemoScene.h"
#include "DGL.h"
#include "EntityContainer.h"
#include "EntityFactory.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Mesh.h"
#include "SandboxScene.h"
#include "Scene.h"
#include "ScoreSystem.h"
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
	unsigned asteroidSpawnCount;

} AsteroidsScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static const unsigned cAsteroidSpawnInitial = 8;
static const unsigned cAsteroidSpawnMaximum = 20;
static unsigned asteroidsSpawnCount;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void AsteroidsSceneLoad(void);
static void AsteroidsSceneInit(void);
static void AsteroidsSceneUpdate(float dt);
static void AsteroidsSceneExit(void);
static void AsteroidsSceneUnload(void);
static void AsteroidsSceneRender(void);
static void AsteroidsSceneSpawnAsteroidWave(void);
static void AsteroidsSceneSpawnAsteroid(void);


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

// Initialize the ...
void AsteroidsSceneInit()
{
	Entity* Spaceship = EntityFactoryBuild("Spaceship");
	Entity* AsteroidsScore = EntityFactoryBuild("AsteroidsScore");
	Entity* AsteroidsHighScore = EntityFactoryBuild("AsteroidsHighScore");
	Entity* AsteroidsWave = EntityFactoryBuild("AsteroidsWave");

	SceneAddEntity(AsteroidsScore);
	SceneAddEntity(AsteroidsHighScore);
	SceneAddEntity(AsteroidsWave);

	ScoreSystemReset();

	asteroidsSpawnCount = cAsteroidSpawnInitial;

	AsteroidsSceneSpawnAsteroidWave();

	if (Spaceship != NULL)
	{
		SceneAddEntity(Spaceship);
	}

	//DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });
	DGL_Color backgroundColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	DGL_Graphics_SetBackgroundColor(&backgroundColor);

	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void AsteroidsSceneUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	if (SceneFindEntityByName("Asteroid") == NULL)
	{
		AsteroidsSceneSpawnAsteroidWave();
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
	//EntityFactoryFreeAll();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void AsteroidsSceneSpawnAsteroidWave(void)
{
	ScoreSystemIncreaseWave();
	for (unsigned i = 0; i < asteroidsSpawnCount; i++)
	{
		AsteroidsSceneSpawnAsteroid();
	}
	asteroidsSpawnCount++;
	
	// Limit how many asteroids there to max
	if (asteroidsSpawnCount > cAsteroidSpawnMaximum)
	{
		asteroidsSpawnCount = cAsteroidSpawnMaximum;
	}
}

static void AsteroidsSceneSpawnAsteroid(void)
{
	Entity* Asteroid = EntityFactoryBuild("Asteroid");
	Entity* clone = EntityClone(Asteroid);
	SceneAddEntity(clone);
}

static void AsteroidsSceneLoad(void)
{
	ScoreSystemClear();
}