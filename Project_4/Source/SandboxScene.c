//------------------------------------------------------------------------------
//
// File Name:	SandboxScene.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 1
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include <DGL.h>
#include "Scene.h"
#include "SceneSystem.h"
#include "SandboxScene.h"
#include "Trace.h"
#include "Stream.h"
#include "Matrix2D.h"
#include "Vector2D.h"

#include "EntityContainer.h"
#include "Entity.h"




//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SandboxScene
{
	// WARNING: The base class must always be included first.
	Scene	base;

	// Add any scene-specific variables second.

} SandboxScene;

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
static const char* VectorTestFileName = "./Data/VectorTests.txt";

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static FILE* VectorTest;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void SandboxSceneTraceFloat(const char* text, float f);
static void SandboxSceneTraceVector(const char* text, const DGL_Vec2* v);
static void SandboxSceneLoad(void);
static void SandboxSceneInit(void);
static void SandboxSceneUpdate(float dt);
static void SandboxSceneExit(void);
static void SandboxSceneUnload(void);
static void SandboxSceneRender(void);

//------------------------------------------------------------------------------
// Instance Variable:
//------------------------------------------------------------------------------

static SandboxScene instance =
{
	// Initialize the base structure:
	{ "Sandbox", SandboxSceneLoad, SandboxSceneInit, SandboxSceneUpdate, SandboxSceneRender, SandboxSceneExit, SandboxSceneUnload },

	// Initialize any scene-specific variables:
};

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

const Scene* SandboxSceneGetInstance(void)
{
	return &(instance.base);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void SandboxSceneTraceFloat(const char* text, float f) 
{
	TraceMessage("Vector Test: %s = %f", text, f);
}

static void SandboxSceneTraceVector(const char* text, const DGL_Vec2* v) {
	TraceMessage("Vector Test: %s = [%f, %f]", text, v->x, v->y);
}

//static void SandboxSceneTraceMatrix(const char* text, const DGL_Mat4* v) {
//	TraceMessage("Matrix Test: %s = [%f, %f]", text, v->m[0][0]);
//	for (int i = 0; i <= 3; i++)
//	{
//		for (int j = 0; j <= 3; j++) {
//			TraceMessage(v->m[i], v->m[j]);
//		}
//	}
//}

// Load any resources used by the scene.
static void SandboxSceneLoad(void)
{
}

// Initialize the variables used by the scene.
static void SandboxSceneInit()
{
	EntityContainer* pizza = EntityContainerCreate();


	EntityContainerFreeAll(pizza);
	//UNREFERENCED_PARAMETER(pizza);
	//printf("pizza");
}

// Update the the variables used by the scene and render objects (temporary).
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
static void SandboxSceneUpdate(float dt)
{
	// Tell the compiler that the 'dt' variable is unused.
	UNREFERENCED_PARAMETER(dt);

	Stream vectorTest = StreamOpen(VectorTestFileName);

	if (vectorTest != NULL)
	{
		DGL_Vec2* testInputA = malloc(sizeof * testInputA);
		DGL_Vec2* testInputB = malloc(sizeof * testInputB);
		DGL_Vec2* testInputC = malloc(sizeof * testInputC);
		DGL_Vec2* testInputD = malloc(sizeof * testInputD);

		Vector2DZero(testInputA);
		SandboxSceneTraceVector("Vector2DZero", testInputA);

		Vector2DSet(testInputA, 1.0f, 1.5f);
		SandboxSceneTraceVector("Vector2DSet", testInputA);

		Vector2DNeg(testInputA, testInputA);
		SandboxSceneTraceVector("Vector2DNeg", testInputA);

		Vector2DAdd(testInputA, testInputA, testInputA);
		SandboxSceneTraceVector("Vector2DAdd", testInputA);

		Vector2DSub(testInputA, testInputA, testInputA);
		SandboxSceneTraceVector("Vector2DSub", testInputA);

		StreamReadVector2D(vectorTest, testInputA);
		SandboxSceneTraceVector("StreamReadVector2D", testInputA);

		Vector2DNormalize(testInputA, testInputA);
		SandboxSceneTraceVector("Vector2DNormalize", testInputA);

		float scale = StreamReadFloat(vectorTest);
		SandboxSceneTraceFloat("StreamReadFloat", scale);

		Vector2DScale(testInputA, testInputA, scale);
		SandboxSceneTraceVector("Vector2DScale", testInputA);	

		Vector2DScaleAdd(testInputA, testInputA, testInputA, scale);
		SandboxSceneTraceVector("Vector2DScaleAdd", testInputA);

		Vector2DScaleSub(testInputA, testInputA, testInputA, scale);
		SandboxSceneTraceVector("Vector2DScaleSub", testInputA);

		float lengthA = Vector2DLength(testInputA);
		SandboxSceneTraceFloat("Vector2DLength", lengthA);

		float sqLengthA = Vector2DSquareLength(testInputA);
		SandboxSceneTraceFloat("Vector2DSquareLength", sqLengthA);

		StreamReadVector2D(vectorTest, testInputB);
		SandboxSceneTraceVector("StreamReadVector2D", testInputB);

		StreamReadVector2D(vectorTest, testInputC);
		SandboxSceneTraceVector("StreamReadVector2D", testInputC);

		float distanceBC = Vector2DDistance(testInputB, testInputC);
		SandboxSceneTraceFloat("Vector2DDistance", distanceBC);

		float sqDistanceBC = Vector2DSquareDistance(testInputB, testInputC);
		SandboxSceneTraceFloat("Vector2DSquareDistance", sqDistanceBC);

		float vectorDotProdBC = Vector2DDotProduct(testInputB, testInputC);
		SandboxSceneTraceFloat("Vector2DDotProduct", vectorDotProdBC);

		float angleDeg = StreamReadFloat(vectorTest);
		SandboxSceneTraceFloat("StreamReadFloat", angleDeg);

		Vector2DFromAngleDeg(testInputD, angleDeg);
		SandboxSceneTraceVector("Vector2DFromAngleDeg", testInputD);

		float angleRad = StreamReadFloat(vectorTest);
		SandboxSceneTraceFloat("StreamReadFloat", angleRad);

		Vector2DFromAngleRad(testInputD, angleRad);
		SandboxSceneTraceVector("Vector2DFromAngleRad", testInputD);

		float toAngleRad = Vector2DToAngleRad(testInputD);
		SandboxSceneTraceFloat("Vector2DToAngleRad", toAngleRad);

		StreamClose(&vectorTest);
	}

	// NOTE: This call causes the engine to exit immediately.  Make sure to remove
	//   it when you are ready to test out a new scene.
	//SceneSystemSetNext(NULL);
}

// Render the scene.
void SandboxSceneRender(void)
{
}

// Exit the scene.
static void SandboxSceneExit()
{
}

// Unload any resources used by the scene.
static void SandboxSceneUnload(void)
{
}
