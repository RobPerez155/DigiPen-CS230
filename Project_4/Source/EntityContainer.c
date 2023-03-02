//------------------------------------------------------------------------------
//
// File Name:	EntityContainer.h
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 4
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include <assert.h>
#include "Entity.h"
#include "EntityContainer.h"

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {	// Assume C declarations for C++.
#endif

	//------------------------------------------------------------------------------
	// Forward References:
	//------------------------------------------------------------------------------

	typedef struct Entity Entity;
	typedef struct EntityContainer EntityContainer;

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Private Constants:
	//------------------------------------------------------------------------------
	#define entityArraySize 100

	//------------------------------------------------------------------------------
	// Public Typedefs:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct EntityContainer
	{
		// This variable is not required but could be used for tracking the number
		//   of Entities currently in the list.  Instructions on how to do this
		//   are included in the function headers.
		unsigned entityCount;

		// This variable is not required but could be used for different purposes.
		// - For storing the maximum size of the container.
		// - For tracking peak usage of the container, used for testing purposes.
		unsigned entityMax;

		// This list can be a fixed-length array (minimum size of 100 entries)
		// or a dynamically sized array, such as a linked list.
		// (NOTE: The implementation details are left up to the student.  However,
		//    it is your responsiblity to ensure that memory is handled correctly.)
		Entity* entitiesList[entityArraySize];

	} EntityContainer;
	

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
	
	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------
	static void addEntity(EntityContainer* entities, Entity* entity);
	static Entity* findEntityByName(Entity** list, const char* name);

	// Dynamically allocate a new EntityContainer.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// (Hint: If your implementation requires any variables to be initialized to
	//    non-zero values, then do so here.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
	EntityContainer* EntityContainerCreate()
	{
		EntityContainer* ptrEntityContainer = calloc(1, sizeof(EntityContainer));		

		if (ptrEntityContainer != NULL)
		{
			return ptrEntityContainer;
		}
		else
		{
			return NULL;
		}
	}

	// Free the memory associated with an EntityContainer.
	// (NOTE: If necessary, call EntityContainerFreeAll to free any existing Entities.)
	// (NOTE: The EntityContainer pointer must be set to NULL.)
	// Params:
	//	 entities = Pointer to the EntityContainer pointer.
	void EntityContainerFree(EntityContainer** entities)
		{
			EntityContainerFreeAll(*entities);
			*entities = NULL;
		}

	// Add an Entity to the EntityContainer.
	// (NOTE: If the container is not full, then the Entity should be added to the list
	//    and the entityCount incremented by 1.)
	// Params:
	//   entities = Pointer to the EntityContainer.
	// Returns:
	//	 If the EntityContainer pointer is valid and the Entity was added successfully,
	//		then return true,
	//		else return false.
	bool EntityContainerAddEntity(EntityContainer* entities, Entity* entity)
		{
		if (entities == NULL)
			return false;

			if (entities->entityCount != entityArraySize)
			{
				addEntity(entities, entity);
				return true;
			}
			return false;
		}

	static void addEntity(EntityContainer* entities, Entity* entity)
	{
		for (int i = 0; i < entityArraySize; i++)
		{
			if (entities->entitiesList[i] == NULL)
			{
				entities->entitiesList[i] = entity;
				entities->entityCount++;
				return;
			}
		}
	}

	// Find an Entity in the EntityContainer that has a matching name.
	// (HINT: Use the new function, EntityIsNamed, to compare names.)
	// Params:
	//   entities = Pointer to the EntityContainer.
	//   entityName = The name of the Entity to be returned.
	// Returns:
	//	 If the EntityContainer pointer is valid and the Entity was located successfully,
	//		then return a pointer to the Entity,
	//		else return false.
	Entity* EntityContainerFindByName(EntityContainer* entities, const char* entityName)
		{
			return findEntityByName(entities->entitiesList, entityName);
		}

	static Entity* findEntityByName(Entity** list, const char* name)
	{
			//while (i < entityArraySize && !found)
			for(int i = 0; i < entityArraySize; i++)
			{
				if (list[i] != NULL)
				{
					if (EntityIsNamed(list[i], name))
					{
						return list[i];
					}
				}
			}
			return NULL;
		}	

	// Determines if the EntityContainer is empty (no Entities exist).
	// Params:
	//   entities = Pointer to the EntityContainer.
	// Returns:
	//	 If the EntityContainer pointer is valid and no Entities exist,
	//		then return true,
	//		else return false.
	bool EntityContainerIsEmpty(const EntityContainer* entities)
		{
			if (entities != NULL)
			{

				if (entities->entityCount == 0) 
				{
					return true;
				}
			}
			return false;
		}

	// Update all Entities in the EntityContainer.
	// (HINT: You must call EntityUpdate for all Entities.)
	// (NOTE: After an Entity has been updated, if it has been flagged as
	//    destroyed, then it must be removed from the list and freed properly.
	//    Additionally, the entityCount should be decremented by 1.)
	// Params:
	//   entities = Pointer to the EntityContainer.
	//	 dt = Change in time (in seconds) since the last game loop.
	void EntityContainerUpdateAll(EntityContainer* entities, float dt)
		{
			if (entities != NULL)
			{
				// Iterate through list
				for (unsigned int i = 0; i < entities->entityCount; i++)
				{
					// for each item run entity update
					EntityUpdate(entities->entitiesList[i], dt);

					//	// AFTER, if item has been flagged for destruction 
					// run entityDestroy, remove from the list, free properly, and decrement entity count
					if (EntityIsDestroyed(entities->entitiesList[i]))
					{
						EntityFree(&entities->entitiesList[i]);
						entities->entitiesList[i] = NULL;
						entities->entityCount--;

						for (unsigned int j = i; j < entities->entityCount; j++)
						{
							entities->entitiesList[j] = entities->entitiesList[j + 1];
						}

						i--;
					}
				}
			}
		}

	// Render all Entities in the EntityContainer.
	// (HINT: You must call EntityRender for all Entities.)
	// Params:
	//   entities = Pointer to the EntityContainer.
	void EntityContainerRenderAll(const EntityContainer* entities)
		{
			if (entities != NULL)
			{
				// Iterate through list
				for (unsigned int i = 0; i < entities->entityCount; i++)
				{
					// for each item run entity render
					EntityRender(entities->entitiesList[i]);
				}
			}
		}

	// Free all Entities in the EntityContainer.
	// (NOTE: You must call EntityFree for all Entities.)
	// (HINT: The container must be completely empty after this function is called.)
	// (HINT: The entityCount should be 0 after all of the Entities have been freed.)
	// Params:
	//   entities = Pointer to the EntityContainer.
	void EntityContainerFreeAll(EntityContainer* entities)
	{
		if (entities != NULL)
		{
			// Iterate through list
			// Break me for testing, using maxcount
			for (unsigned int i = 0; i < _countof(entities->entitiesList); i++)
			{
				// for each item run entity render
				if (entities->entitiesList[i] != NULL)
				{
					EntityFree(&entities->entitiesList[i]);
					entities->entityCount--;
				}
			}

			assert(EntityContainerIsEmpty(entities));
			
		}
	}
	//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       // End of extern "C" {
#endif

