//------------------------------------------------------------------------------
//
// File Name:	Scene.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 0
// Course:		CS230S23
//
// Copyright � 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <assert.h>

#include "EntityContainer.h"
#include "EntityFactory.h"
#include "MeshLibrary.h"
#include "Scene.h"
#include "SceneSystem.h"
#include "ScoreSystem.h"
#include "SpriteSourceLibrary.h"
#include "Trace.h"

//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Typedefs:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

static EntityContainer* entities = NULL;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Verify that a scene is valid (no NULL pointers).
// Params:
//   scene	Pointer to the scene to be checked.
bool SceneIsValid(const Scene* scene)
{
	// This function should never be called with a "NULL" scene.
	assert(scene && "SceneIsValid Error: A NULL pointer was passed as a parameter.");

	if (scene->name && scene->load && scene->init && scene->update && scene->render && scene->exit && scene->unload)
	{
		return true;
	}

	return false;
}

// Load the scene.
void SceneLoad(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->load != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Load" and the name of the scene.
		TraceMessage("%s: Load", scene->name);

		// Initialize the Mesh Library.
		MeshLibraryInit();

		// Initialize the SpriteSource Library.
		SpriteSourceLibraryInit();

		// Create a container for managing Entities.
		entities = EntityContainerCreate();

		// Execute the Load function.
		(*scene->load)();
	}
}

// Initialize the scene.
void SceneInit(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->init != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Init" and the name of the scene.
		TraceMessage("%s: Init", scene->name);

		// Execute the Init function.
		(*scene->init)();
	}
}

// Update the scene.
void SceneUpdate(const Scene* scene, float dt)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->update != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Update" and the name of the scene.
		TraceMessage("%s: Update", scene->name);

		// Execute the Update function.
		(*scene->update)(dt);

		// Update all Entities within the Scene.
		EntityContainerUpdateAll(entities, dt);

		// Check for collisions between Entities.
		EntityContainerCheckCollisions(entities);
	}
}

// Render the scene.
void SceneRender(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->render != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Render" and the name of the scene.
		TraceMessage("%s: Render", scene->name);

		// Render all Entities within the Scene.
		EntityContainerRenderAll(entities);

		// Execute the Render function.
		(*scene->render)();
	}
}

// Exit the scene.
void SceneExit(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->exit != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Exit" and the name of the scene.
		TraceMessage("%s: Exit", scene->name);

		// Execute the Exit function.
		(*scene->exit)();

		// Free all Entities within the Scene.
		EntityContainerFreeAll(entities);
		EntityFactoryFreeAll();
	}
}

// Unload the scene.
void SceneUnload(const Scene* scene)
{
	// Verify that the function pointer is valid.
	if (scene && (scene->unload != NULL))
	{
		// TODO: Call TraceMessage, passing the format string "%s: Unload" and the name of the scene.
		TraceMessage("%s: Unload", scene->name);

		// Execute the Unload function.
		(*scene->unload)();

		// Free the container for managing Entities.
		EntityContainerFree(&entities);

		// Free all allocated Mesh objects and associated DGL_Mesh resources.
		MeshLibraryFreeAll();

		// Free all allocated SpriteSources and associated DGL_Texture resources.
		SpriteSourceLibraryFreeAll();
	}
}

// Restart the active scene.
void SceneRestart(void)
{
	// Tell the Scene System to restart the active scene.
	ScoreSystemReset();
	SceneSystemRestart();
}

// Add an Entity to the Scene.
// (NOTE: This is done by storing the Entity within an EntityContainer.)
// Params:
//   entity = Pointer to the Entity to be added.
void SceneAddEntity(Entity* entity)
{
	assert(entities && "SceneAddEntity Error: No entity container has been created.");

	if (entity)
	{
		EntityContainerAddEntity(entities, entity);
	}
}

// Find a named Entity within the Scene.
// (Hint: Use the function, EntityContainerFindByName, for this purpose.)
// Params:
//   entityName = The name of the Entity to be returned.
// Returns:
//	 If entityName is valid and the Entity was located successfully,
//		then return a pointer to the Entity,
//		else return NULL.
Entity* SceneFindEntityByName(const char* entityName)
{
	return EntityContainerFindByName(entities, entityName);
}

// Add an Entity to the Scene.
// (NOTE: This is done by storing the Entity within an EntityContainer.)
// Params:
//   entity = Pointer to the Entity to be added.
//void SceneAddEntity(Entity* entity)
//{
//	EntityContainerAddEntity(entities, entity);
//}
//
//// Find a named Entity within the Scene.
//// (Hint: Use the function, EntityContainerFindByName, for this purpose.)
//// Params:
////   entityName = The name of the Entity to be returned.
//// Returns:
////	 If entityName is valid and the Entity was located successfully,
////		then return a pointer to the Entity,
////		else return NULL.
//Entity* SceneFindEntityByName(const char* entityName)
//{
//	Entity* entityFound = EntityContainerFindByName(entities, entityName);
//
//	if (entityFound != NULL)
//	{
//		return entityFound;
//	}
//	else {
//		return NULL;
//	}
//}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

