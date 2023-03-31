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

#include "Animation.h"
#include "AsteroidsScene.h"
#include "DemoScene.h"
#include "DGL.h"
#include "Entity.h"
#include "EntityContainer.h"
#include "EntityFactory.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Matrix2D.h"
#include "Mesh.h"
#include "Physics.h"
#include "SandboxScene.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "Sprite.h"
#include "SpriteSource.h"
#include "Stream.h"
#include "Transform.h"
#include "Vector2D.h"
#include "ColliderLine.h"



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
	Mesh* ptrMesh3x3;
	Mesh* ptrMesh16x8;
	SpriteSource* ptrSpriteMesh;
	SpriteSource* ptrSpriteMonkeyIdle;
	SpriteSource* ptrSpriteMonkeyWalk;
	SpriteSource* ptrSpriteMonkeyJump;
	SpriteSource* ptrSpriteLivesText;
	Entity* Planet;
	Entity* Monkey;
	Entity* LivesText;

} Level1Scene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

static const char* livesFileName = "./Data/Level1_Lives.txt";
//static const char* arena = "./Data/Arena.txt";
static const char* animFileName = "./Data/Level1_Lives.txt";
static const char* monkeyWalkFileName = "./Assets/MonkeyWalk.png";
static const char* monkeyIdleFileName = "./Assets/MonkeyIdle.png";
static const char* monkeyJumpFileName = "./Assets/MonkeyJump.png";
static const char* fontFileName = "./Assets/Roboto_Mono_black.png";
static const float groundHeight = -150.0f;
static const float moveVelocity = 500.0f;
static const float jumpVelocity = 1000.0f;
static const Vector2D gravityNormal = { 0.0f, -1500.0f };
static const Vector2D gravityNone = { 0.0f, 0.0f };
static const float wallDistance = 462.0f;
static const float CheckSquareDistance = (75.0f * 75.0f);


enum MonkeyStates
{
	MonkeyInvalid = -1,
	MonkeyIdle,
	MonkeyWalk,
	MonkeyJump
};

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

enum MonkeyStates monkeyState = MonkeyInvalid;

char livesBuffer[16];

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* livesFile;
static FILE* animFile;

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
static void Level1SceneSetMonkeyState(Entity* gameObject, enum MonkeyStates newState);
static void Level1SceneBounceController(Entity* planet);
static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB);

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
	instance.ptrMesh3x3 = MeshCreateQuad(0.5, 0.5, 1.0f / 3, 1.0f / 3, "Mesh3x3");
	instance.ptrMesh16x8 = MeshCreateQuad(0.5, 0.5, 1.0f / 16, 1.0f / 8, "Mesh16x8");

	//Planet
	SpriteSource* sprPlanet = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprPlanet, 1, 1, "./Assets/PlanetTexture.png");
	instance.ptrSpriteMesh = sprPlanet;


	//MonkeyIdle
	SpriteSource* sprMonkeyIdle = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprMonkeyIdle, 1, 1, monkeyIdleFileName);
	instance.ptrSpriteMonkeyIdle = sprMonkeyIdle;

	//MonkeyWalk
	SpriteSource* sprMonkeyWalk = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprMonkeyWalk, 3, 3, monkeyWalkFileName);
	instance.ptrSpriteMonkeyWalk = sprMonkeyWalk;

	//MonkeyJump
	SpriteSource* sprMonkeyJump = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprMonkeyJump, 1, 1, monkeyJumpFileName);
	instance.ptrSpriteMonkeyJump = sprMonkeyJump;

	//LivesText
	SpriteSource* sprLivesText = SpriteSourceCreate();
	SpriteSourceLoadTexture(sprLivesText, 16, 8, fontFileName);
	instance.ptrSpriteLivesText = sprLivesText;

	MeshCreateQuad(0.5, 0.5, 1.0f / 16, 1.0f / 8, "Mesh16x8");
}

static void Level1SceneSetMonkeyState(Entity* gameObject, enum MonkeyStates newState)
{
	if (monkeyState != newState) 
	{
		Sprite* sprMonkey = EntityGetSprite(gameObject);
		Animation* animMonkey = EntityGetAnimation(gameObject);

		switch (newState) 
		{
		case MonkeyIdle:
			SpriteSetMesh(sprMonkey, instance.ptrMesh);
			SpriteSetSpriteSource(sprMonkey, instance.ptrSpriteMonkeyIdle);
			AnimationPlay(animMonkey, 1, 0.0f, false);
		break;

		case MonkeyWalk:
			SpriteSetMesh(sprMonkey, instance.ptrMesh3x3);
			SpriteSetSpriteSource(sprMonkey, instance.ptrSpriteMonkeyWalk);
			AnimationPlay(animMonkey, 8, 0.05f, true);
		break;

		case MonkeyJump:
			SpriteSetMesh(sprMonkey, instance.ptrMesh);
			SpriteSetSpriteSource(sprMonkey, instance.ptrSpriteMonkeyJump);
			AnimationPlay(animMonkey, 1, 0.0f, false);
		break;


		}
		monkeyState = newState;
	}
};

static void Level1SceneBounceController(Entity* planet)
{
	Physics* planetPhysics = EntityGetPhysics(planet);
	Transform* planetTransform = EntityGetTransform(planet);

	if (!planetPhysics && !planetTransform)
	{
		return;
	}

	Vector2D currentPos = *TransformGetTranslation(planetTransform);
	Vector2D currentVelocity = *PhysicsGetVelocity(planetPhysics);

	if (currentPos.x <= -wallDistance)
	{
		currentPos.x = -wallDistance;
		currentVelocity.x = -currentVelocity.x;
	} 
	else if (currentPos.x >= wallDistance)
	{
		currentPos.x = wallDistance;
		currentVelocity.x = -currentVelocity.x;
	}

	if (currentPos.y <= groundHeight)
	{
		//conserve energy
		currentPos.y = groundHeight + (groundHeight - currentPos.y);
		currentVelocity.y = -currentVelocity.y;
	}

	TransformSetTranslation(planetTransform, &currentPos);
	PhysicsSetVelocity(planetPhysics, &currentVelocity);
}

static bool Level1SceneIsColliding(const Entity* entityA, const Entity* entityB)
{
	Transform* transformA = EntityGetTransform(entityA);
	Transform* transformB = EntityGetTransform(entityB);

	if (Vector2DSquareDistance(TransformGetTranslation(transformA), TransformGetTranslation(transformB)) < CheckSquareDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Initialize the variables used by the scene.
static void Level1SceneInit()
{
	Entity* Planet = EntityFactoryBuild("PlanetBounce");
	Entity* Monkey = EntityFactoryBuild("Monkey");
	Entity* LivesText = EntityFactoryBuild("MonkeyLivesText");

	if (Planet != NULL)
	{
		//DGL_Color white = { 255.0f, 255.0f, 255.0f };

		Sprite* sprPlanet = EntityGetSprite(Planet);
		SpriteSetMesh(sprPlanet, instance.ptrMesh);
		SpriteSetSpriteSource(sprPlanet, instance.ptrSpriteMesh);

		DGL_Color clear = { 255.0f, 255.0f, 255.0f, 0.0f };
		DGL_Graphics_SetBackgroundColor(&clear);

		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		instance.Planet = Planet;
	}

	if (Monkey != NULL)
	{
		monkeyState = MonkeyInvalid;

		Level1SceneSetMonkeyState(Monkey, MonkeyIdle);
		instance.Monkey = Monkey;
	}

	if (LivesText != NULL)
	{
		Sprite* sprLivesText = EntityGetSprite(LivesText);
		SpriteSetMesh(sprLivesText, instance.ptrMesh16x8);
		SpriteSetSpriteSource(sprLivesText, instance.ptrSpriteLivesText);

		sprintf_s(livesBuffer, _countof(livesBuffer), "Lives: %d", instance.numLives);

		DGL_Graphics_SetBlendMode(DGL_BM_BLEND);

		instance.LivesText = LivesText;
		SpriteSetText(sprLivesText, livesBuffer);
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
		currVelocity.x = -moveVelocity;

		if (monkeyState != MonkeyJump) 
		{
			Level1SceneSetMonkeyState(instance.Monkey, MonkeyWalk);
		}

		printf("Move left - %f \n", currVelocity.x);
	}
	if (DGL_Input_KeyDown(VK_RIGHT))
	{
		currVelocity.x = moveVelocity;
		printf("Move right - %f \n", currVelocity.x);

		if (monkeyState != MonkeyJump)
		{
			Level1SceneSetMonkeyState(instance.Monkey, MonkeyWalk);
		}
	}
	if (!DGL_Input_KeyDown(VK_RIGHT) && !DGL_Input_KeyDown(VK_LEFT))
	{
		currVelocity.x = 0;
		if (monkeyState != MonkeyJump)
		{
			Level1SceneSetMonkeyState(instance.Monkey, MonkeyIdle);
		}
	}
	
	// Jump mechanic
	if (DGL_Input_KeyTriggered(VK_UP))
	{
		currVelocity.y = jumpVelocity;
		PhysicsSetAcceleration(ptrPhysics, &gravityNormal);
		printf("Move jump\n");

		Level1SceneSetMonkeyState(instance.Monkey, MonkeyJump);
	}


	// Check for Landing
	Vector2D translation = *TransformGetTranslation(ptrTransform);
	Vector2D* currTranslation = &translation;

	if (currTranslation->y < groundHeight)
	{
		Level1SceneSetMonkeyState(instance.Monkey, MonkeyIdle);

		currTranslation->y = groundHeight;
		TransformSetTranslation(ptrTransform, &(*currTranslation));
		currVelocity.y = 0;
		PhysicsSetAcceleration(ptrPhysics, &gravityNone);
	}

	PhysicsSetVelocity(ptrPhysics, &currVelocity);
}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void Level1SceneUpdate(float dt)
{	
	Level1SceneMovementController(instance.Monkey);
	Level1SceneBounceController(instance.Planet);
	EntityUpdate(instance.Monkey, dt);
	EntityUpdate(instance.Planet, dt);
	EntityUpdate(instance.LivesText, dt);

	if (Level1SceneIsColliding(instance.Monkey, instance.Planet))
	{
		instance.numLives--;
		if (instance.numLives <= 0)
		{
			// Switch to Level 2
			SceneSystemSetNext(Level2SceneGetInstance());
		}
		else {
			// Restart Level 1
			Level1SceneInit();
		}
	}

	//if (DGL_Input_KeyTriggered('P'))
	//{
	//	// Switch to Sandbox Scene
	//	Stream sand = StreamOpen(arena);
	//	Entity* test = EntityCreate();
	//	EntityRead(test, sand);
	//	//Collider* pizza = ColliderLineCreate();
	//	//ColliderLineRead(pizza, sand);

	//	//pizza;
	//	StreamClose(&sand);
	//}
}

// Render the scene.
void Level1SceneRender(void)
{

	EntityRender(instance.Planet);
	EntityRender(instance.Monkey);
	EntityRender(instance.LivesText);
	
}

// Exit the scene.
static void Level1SceneExit()
{

}

// Unload any resources used by the scene.
static void Level1SceneUnload(void)
{
	SpriteSourceFree(&instance.ptrSpriteMesh);
	MeshFree(&instance.ptrMesh);
}

