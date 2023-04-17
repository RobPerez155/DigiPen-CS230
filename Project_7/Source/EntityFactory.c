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
static EntityContainer* archetypes = nullptr;

// Build a single instance of the specified game object.
// Params:
//	 filename = The name of the file to be deserialized.
// Returns:
//	 If the filename is valid
//	   then return a pointer to a new instance of the specified game object,
//	   else nullptr.

//	The EntityFactoryBuild() function should work as follows :
//	If the filename pointer is not nullptr,
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
//	Return nullptr
//TraceMessage(" Error Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);

//Annotate ME
Entity* EntityFactoryBuild(const char* entityName)
{
	//If there is no entity to build exit this function
	if (entityName == nullptr)
	{
		return nullptr;
	}

	// Initialize an entity to store the archetype
	//Entity* archetype;

	// If the “archetypes” variable is nullptr, then create a new archetype by calling EntityContainerCreate.
	if (archetypes == nullptr)
	{
		archetypes = EntityContainerCreate();
	}

	// Checks to see if the archetype already exists
	Entity* entity = EntityContainerFindByName(archetypes, entityName);

	// If there is no existing archetype create then one
	if (!entity)
	{
		// initializes the pathname
		char pathName[FILENAME_MAX] = "";
		//Set the pathname equal to the entityName variable
		sprintf_s(pathName, _countof(pathName), "Data/%s.txt", entityName);

		// Pass the new pathanme into StreamOpen to open a new file and set it the value filestream
		Stream fileStream = StreamOpen(pathName);

		//If the file is opened successfully, 
		if (fileStream != nullptr) {

			//Use streamReadToken to read file.
			const char* token = StreamReadToken(fileStream);

			//check for the word Entity
			if (strncmp(token, "Entity", _countof("Entity")) == 0)
			{
				// if the there is an entity, proceed to create an new archetype
				Entity* archetype = EntityCreate();

				//Add data from stream to the new archetype
				EntityRead(archetype, fileStream);

				//Add the new archetype to the Archetypes Container
				EntityContainerAddEntity(archetypes, archetype);

				// Close the file we read from
				StreamClose(&fileStream);

				// If the archetype existed or was created successfully,
				// Clone the archetype Entity.
				// Return the cloned Entity.
				if (archetypes != nullptr)
				{
					return EntityClone(archetype);
				}
				return nullptr;
			}
			
		}
	}

	//TraceMessage(" Error Function %s\n File: %s\n Line: %d.", __FUNCTION__, __FILE__, __LINE__);
	return EntityClone(entity);
	}

// Free all archetype Entities.
// (Hint: If the "archetypes" container exists, then the EntityContainerFreeAll
//    function must be called.)
void EntityFactoryFreeAll()
{
	if (archetypes != nullptr) 
	{
		EntityContainerFreeAll(archetypes);
		archetypes = nullptr;
	}
}

	//------------------------------------------------------------------------------
