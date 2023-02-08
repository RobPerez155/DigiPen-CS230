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
#include "SandboxScene.h"
#include "DemoScene.h"
#include "Stream.h"
#include "Sprite.h"
#include "Transform.h"
#include "Mesh.h"
#include "Physics.h"
#include "SpriteSource.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Vector2D.h"
#include "DGL.h"


//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level1Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	int numLives;
	Mesh* ptrMesh;
	SpriteSource* ptrSpriteMesh;
	Entity* ptrEntity;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* livesFileName = "./Data/Level1_Lives.txt";
static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };


//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* livesFile;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------
static void Level1SceneLoad(void);
static void Level1SceneInit(void);
static void Level1SceneMovementController(Entity* entity);
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

	instance.ptrMesh = MeshCreateQuad(0.5f, 0.5f, 1.0f, 1.0f, "Mesh1x1");

	SpriteSource* sprPlanet = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprPlanet, 1, 1, "./Assets/PlanetTexture.png");
	instance.ptrSpriteMesh = sprPlanet;
}

// Initialize the variables used by the scene.
static void Level1SceneInit()
{
	Entity* Planet = EntityFactoryBuild("./Data/PlanetJump.txt");

	if (Planet != NULL)
	{
		DGL_Color white = { 1.0f, 1.0f, 1.0f, 1.0f };

		Sprite* sprPlanet = EntityGetSprite(Planet);
		SpriteSetMesh(sprPlanet, instance.ptrMesh);
		SpriteSetSpriteSource(sprPlanet, instance.ptrSpriteMesh);
		DGL_Graphics_SetBackgroundColor(&white);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		instance.ptrEntity = Planet;
	}
}

static void Level1SceneMovementController(Entity* entity)
{
	Physics* ptrPhysics = EntityGetPhysics(entity);
	Transform* ptrTransform = EntityGetTransform(entity);

	if (ptrPhysics == NULL || ptrTransform == NULL)
	{
		return;
	}

	Vector2D currVelocity = *PhysicsGetVelocity(ptrPhysics);

	// Movement Mechanic
	if (DGL_Input_KeyDown(VK_LEFT))
	{
		currVelocity.x -= moveVelocity;
		printf("Move left - %f \n", currVelocity.x);
	}
	if (DGL_Input_KeyDown(VK_RIGHT))
	{
		currVelocity.x += moveVelocity;
		printf("Move right - %f \n", currVelocity.x);
	}
	if (!DGL_Input_KeyDown(VK_RIGHT) && !DGL_Input_KeyDown(VK_LEFT))
	{
		currVelocity.x = 0;
	}
	
	// Jump mechanic
	if (DGL_Input_KeyTriggered(VK_UP))
	{
		currVelocity.y = jumpVelocity;
		PhysicsSetAcceleration(ptrPhysics, &gravityNormal);
		printf("Move jump\n");	
	}


	// Check for Landing - Annotate
	Vector2D translation = *TransformGetTranslation(ptrTransform);
	Vector2D* currTranslation = &translation;

	if (currTranslation->y < groundHeight)
	{
		currTranslation->y = groundHeight;
		TransformSetTranslation(ptrTransform, &(*currTranslation));
		currVelocity.y = 0;
		PhysicsSetAcceleration(ptrPhysics, &gravityNone);
		instance.numLives--;
		if (instance.numLives <= 0)
		{
			SceneSystemSetNext(Level2SceneGetInstance());
		}
	}

	PhysicsSetVelocity(ptrPhysics, &currVelocity);
}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{	EntityUpdate(instance.ptrEntity, dt);
	Level1SceneMovementController(instance.ptrEntity);


	// Hotkeys for scene advancing, when the key changes state from not pressed to pressed
	if (DGL_Input_KeyTriggered('1'))
	{
		// Restart Level 1
		Level1SceneInit();
	}

	if (DGL_Input_KeyTriggered('2'))
	{
		// Switch to Level 2
		SceneSystemSetNext(Level2SceneGetInstance());
	}

	if (DGL_Input_KeyTriggered('9'))
	{
		// Switch to Sandbox Scene
		SceneSystemSetNext(SandboxSceneGetInstance());
	}

	// Restarts Scene (when the key changes state from not pressed to pressed).
	if (DGL_Input_KeyTriggered('0'))
	{
		// Restarts Scene
		SceneSystemSetNext(DemoSceneGetInstance());
	}
}

// Render the scene.
void Level1SceneRender(void)
{
	EntityRender(instance.ptrEntity);
}

// Exit the scene.
static void Level1SceneExit()
{
	EntityFree(&instance.ptrEntity);
}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	SpriteSourceFree(&instance.ptrSpriteMesh);
	MeshFree(&instance.ptrMesh);
}

