//------------------------------------------------------------------------------
//
// File Name:	OmegaScene.c
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
#include "OmegaScene.h"
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

typedef struct OmegaScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.
	//int numLives;
	//int numHealth;
	Mesh* ptrMesh;
	Entity* ptrEntity;
} OmegaScene;


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const float spaceshipSpeed = 500.0f;

//static const char* livesFileName = "./Data/Omega_Lives.txt";
//static const char* healthFileName = "./Data/Omega_Health.txt";

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
//static FILE* livesFile;
//static FILE* healthFile;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void OmegaSceneLoad(void);
static void OmegaSceneInit(void);
static void OmegaSceneMovementController(Entity* entity);
static void OmegaSceneUpdate(float dt);
static void OmegaSceneExit(void);
static void OmegaSceneUnload(void);
static void OmegaSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static OmegaScene instance =
{
	// Initialize the base structure:
	{ "Omega", OmegaSceneLoad, OmegaSceneInit, OmegaSceneUpdate, OmegaSceneRender, OmegaSceneExit, OmegaSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene* OmegaSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Load any resources used by the scene.
static void OmegaSceneLoad(void)
{
	//Load spaceship mesh
	instance.ptrMesh = MeshCreateSpaceship();
}

// Initialize the variables used by the scene.
static void OmegaSceneInit()
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

static void OmegaSceneMovementController(Entity* entity)
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
static void OmegaSceneUpdate(float dt)
{
	OmegaSceneMovementController(instance.ptrEntity);
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
		OmegaSceneInit();
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
void OmegaSceneRender(void)
{
	EntityRender(instance.ptrEntity);
}

// Exit the scene.
static void OmegaSceneExit()
{

}

// Unload any resources used by the scene.
static void OmegaSceneUnload(void)
{
	MeshFree(&instance.ptrMesh);
}

