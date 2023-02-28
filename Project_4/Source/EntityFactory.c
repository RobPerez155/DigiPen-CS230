//------------------------------------------------------------------------------
//
// File Name:	EntityFactory.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
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

#include "EntityFactory.h"
#include "EntityContainer.h"
#include "Entity.h"
#include "Stream.h"
#include "Trace.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static EntityContainer* archetypes = NULL;
//static EntityContainer* archetypes = NULL;

// Build a single instance of the specified game object.
// Params:
//	 filename = The name of the file to be deserialized.
// Returns:
//	 If the filename is valid
//	   then return a pointer to a new instance of the specified game object,
//	   else NULL.

//	The EntityFactoryBuild() function should work as follows :
//	If the filename pointer is not NULL,
//	Open the file using StreamOpen()
//	If the stream was opened successfully,
//	Read the first token from the file using StreamReadToken()
// 
//	Verify that the first token is “Entity” using strncmp()
//	Hint : Use _countof(“Entity”) for _MaxCount
//	If the first token is “Entity”,
//	Create a new entity using EntityCreate()
//	Call EntityRead(), passing the created Entity
//	Close the file using StreamClose()
//	Return the created entity
//	Close the file using StreamClose()
//	Return NULL
//TraceMessage(" Error Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);

//Annotate ME
Entity* EntityFactoryBuild(const char* entityName)
{
	if (entityName == NULL)
	{
		return NULL;
	}

	//EntityContainer* newEntContainer = NULL;
	Entity* entityNotFound;

	// If the “archetypes” variable is NULL, then initialize the variable by calling EntityContainerCreate.
	if (archetypes == NULL)
	{
		archetypes = EntityContainerCreate();
	}

	entityNotFound = EntityContainerFindByName(archetypes, entityName);
	
	if (entityNotFound == NULL)
	{
		char pathName[FILENAME_MAX] = "";
		sprintf_s(pathName, _countof(pathName), "Data/%s.txt", entityName);

		Stream fileStream = StreamOpen(pathName);
		if (fileStream != NULL) {

			const char* token = StreamReadToken(fileStream);

			if (strncmp(token, "Entity", _countof("Entity")) == 0)
			{
				Entity* entity = EntityCreate();
				EntityRead(entity, fileStream);
				EntityContainerAddEntity(archetypes, entity);
				StreamClose(&fileStream);

				// If the archetype existed or was created successfully,
				// Clone the archetype Entity.
				// Return the cloned Entity.
				if (archetypes != NULL)
				{
					EntityClone(entity);
				}
				return entity;
			}

			StreamClose(&fileStream);
			return NULL;
		}

	}

	TraceMessage(" Error Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);
	return NULL;
	}

// Free all archetype Entities.
// (Hint: If the "archetypes" container exists, then the EntityContainerFreeAll
//    function must be called.)
void EntityFactoryFreeAll(EntityContainer* archetype)
{
	if (archetype != NULL) 
	{
		EntityContainerFreeAll(archetype);
	}
}

	//------------------------------------------------------------------------------
