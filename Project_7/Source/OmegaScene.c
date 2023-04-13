//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 6
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "ColliderCircle.h"
#include "ColliderLine.h"
#include "DGL.h"
#include "Entity.h"
#include "EntityContainer.h"
#include "EntityFactory.h"
#include "Mesh.h"
#include "Physics.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "ScoreSystem.h"
#include "Transform.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
typedef struct OmegaScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	unsigned asteroidSpawnCount;

} OmegaScene;

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
static void OmegaSceneLoad(void);
static void OmegaSceneInit(void);
static void OmegaSceneUpdate(float dt);
static void OmegaSceneExit(void);
static void OmegaSceneUnload(void);
static void OmegaSceneRender(void);
static void OmegaSceneSpawnAsteroidWave(void);
static void OmegaSceneSpawnAsteroid(void);


//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static OmegaScene instance =
{
	// Initialize the base structure:
	{ "OmegaScene", OmegaSceneLoad, OmegaSceneInit, OmegaSceneUpdate, OmegaSceneRender, OmegaSceneExit, OmegaSceneUnload },

	// Initialize any scene-specific variables:

};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene* OmegaSceneGetInstance(void)
{
	return &(instance.base);
}

// Initialize the ...
void OmegaSceneInit()
{
	Entity* SpaceshipOmega = EntityFactoryBuild("SpaceshipOmega");
	Entity* Arena = EntityFactoryBuild("Arena");
	Entity* OmegaScore = EntityFactoryBuild("OmegaScore");
	Entity* OmegaHighScore = EntityFactoryBuild("OmegaHighScore");
	Entity* OmegaWave = EntityFactoryBuild("OmegaWave");

	SceneAddEntity(Arena);
	SceneAddEntity(OmegaScore);
	SceneAddEntity(OmegaHighScore);
	SceneAddEntity(OmegaWave);

	ScoreSystemReset();

	asteroidsSpawnCount = cAsteroidSpawnInitial;

	OmegaSceneSpawnAsteroidWave();

	if (SpaceshipOmega != NULL)
	{
		SceneAddEntity(SpaceshipOmega);
	}

	DGL_Graphics_SetBackgroundColor(&(DGL_Color) { 0.0f, 0.0f, 0.0f, 0.0f });

	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void OmegaSceneUpdate(float dt)
{
	/* Tell the compiler that the 'dt' variable is unused. */
	UNREFERENCED_PARAMETER(dt);

	//if (DGL_Input_KeyTriggered("A"))
	//{
	//	
	//}

	if (SceneFindEntityByName("Asteroid") == NULL)
	{
		OmegaSceneSpawnAsteroidWave();
	}


}

// Render the scene.
void OmegaSceneRender(void)
{

}

// Shutdown the ...
void OmegaSceneExit()
{
}

static void OmegaSceneUnload(void)
{
	//EntityFactoryFreeAll();
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void OmegaSceneSpawnAsteroidWave(void)
{
	ScoreSystemIncreaseWave();
	for (unsigned i = 0; i < asteroidsSpawnCount; i++)
	{
		OmegaSceneSpawnAsteroid();
	}
	asteroidsSpawnCount++;

	// Limit how many asteroids there to max
	if (asteroidsSpawnCount > cAsteroidSpawnMaximum)
	{
		asteroidsSpawnCount = cAsteroidSpawnMaximum;
	}
}

static void OmegaSceneSpawnAsteroid(void)
{
	Entity* Asteroid = EntityFactoryBuild("Asteroid");
	Entity* clone = EntityClone(Asteroid);
	SceneAddEntity(clone);
}

static void OmegaSceneLoad(void)
{
	ScoreSystemClear();
}