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
#include "AsteroidsScene.h"
#include "SceneSystem.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "DemoScene.h"
#include "SandboxScene.h"
#include "Stream.h"
#include "SpriteSource.h"
#include "Mesh.h"
#include "DGL.h"
#include "Entity.h"
#include "Sprite.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Physics.h"
#include "EntityFactory.h"

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct Level2Scene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	//int numLives;
	//int numHealth;
	Mesh* ptrMesh;
	Entity* ptrEntity;
} Level2Scene;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float spaceshipSpeed = 500.0f;

//static const char* livesFileName = "./Data/Level2_Lives.txt";
//static const char* healthFileName = "./Data/Level2_Health.txt";

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
//static FILE* livesFile;
//static FILE* healthFile;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void Level2SceneLoad(void);
static void Level2SceneInit(void);
static void Level2SceneMovementController(Entity* entity);
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
	//Load spaceship mesh
	instance.ptrMesh = MeshCreateSpaceship();
}

// Initialize the variables used by the scene.
static void Level2SceneInit()
{
	Entity* Spaceship = EntityFactoryBuild("SpaceshipHoming");

	if (Spaceship != NULL)
	{
		DGL_Color black = { 0.0f, 0.0f, 0.0f, 0.0f };

		Sprite* sprSpaceship = EntityGetSprite(Spaceship);
		SpriteSetMesh(sprSpaceship, instance.ptrMesh);
		SpriteSetSpriteSource(sprSpaceship, NULL);
		DGL_Graphics_SetBackgroundColor(&black);
		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		instance.ptrEntity = Spaceship;
	}
}

static void Level2SceneMovementController(Entity* entity)
{
	Physics* ptrPhysics = EntityGetPhysics(entity);
	Transform* ptrTransform = EntityGetTransform(entity);

	// Check if pointers are valid
	if (ptrPhysics == NULL || ptrTransform == NULL)
	{
		return;
	}

	DGL_Vec2 mousePosition = DGL_Input_GetMousePosition();
	DGL_Vec2 mouseWorldCoord = DGL_Camera_ScreenCoordToWorld(&mousePosition);

	Vector2D translation = *TransformGetTranslation(ptrTransform);

	// Ship to mouse cursor math
	Vector2D shipToMouseDirectionVec;
	Vector2DSub(&shipToMouseDirectionVec, &mouseWorldCoord, &translation);
	Vector2DNormalize(&shipToMouseDirectionVec, &shipToMouseDirectionVec);
	
	// Set spaceship angle
	float shipAngleToMouse = Vector2DToAngleRad(&shipToMouseDirectionVec);
	TransformSetRotation(ptrTransform, shipAngleToMouse);

	//Sets the spaceship velocity
	Vector2DScale(&shipToMouseDirectionVec, &shipToMouseDirectionVec, spaceshipSpeed);
	PhysicsSetVelocity(ptrPhysics, &shipToMouseDirectionVec);
}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level2SceneUpdate(float dt)
{
	Level2SceneMovementController(instance.ptrEntity);
	EntityUpdate(instance.ptrEntity, dt);

	if (DGL_Input_KeyTriggered('Z'))
	{
		// Sets Spaceship's Alpha value
		Sprite* sprSpaceship = EntityGetSprite(instance.ptrEntity);
		SpriteSetAlpha(sprSpaceship, 0.5f);
	}

	if (DGL_Input_KeyTriggered('X'))
	{
		// Sets Spaceship's Alpha value
		Sprite* sprSpaceship = EntityGetSprite(instance.ptrEntity);
		SpriteSetAlpha(sprSpaceship, 1.0f);
	}

	// Hotkeys for scene advancing, when the key changes state from not pressed to pressed
	if (DGL_Input_KeyTriggered('1'))
	{
		// Restart Level 1
		SceneSystemSetNext(Level1SceneGetInstance());
	}

	if (DGL_Input_KeyTriggered('2'))
	{
		// Switch to Level 2
		Level2SceneInit();
	}

	if (DGL_Input_KeyTriggered('3'))
	{
		// Switch to Level 2
		SceneSystemSetNext(AsteroidsSceneGetInstance());
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
void Level2SceneRender(void)
{
	EntityRender(instance.ptrEntity);
}

// Exit the scene.
static void Level2SceneExit()
{
	EntityFree(&instance.ptrEntity);
}

// Unload any resources used by the scene.
static void Level2SceneUnload(void)
{
	MeshFree(&instance.ptrMesh);
}

