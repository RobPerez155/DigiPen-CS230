//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Entity.h"
#include "Physics.h"
#include "Sprite.h"
#include "Stream.h"
#include "Transform.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Constants:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Structures:
	//------------------------------------------------------------------------------

	// An example of the structure to be defined in Entity.c.
// You are free to change the contents of this structure as long as you do not
//   change the public interface declared in the header.
	typedef struct Entity
	{
		// The name of the entity.
		// A buffer is used to allow each entity to have a unique name.
		// The buffer is hardcoded to an arbitrary length that will be sufficient
		//	 for all CS230 assignments.  You may, instead, use dynamically-allocated
		//	 arrays for this purpose but the additional complexity is unnecessary
		//	 and it is your responsibility to ensure that the memory is successfully
		//	 allocated and deallocated in all possible situations.
		// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
		//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
		//	 calling this function!  Instead, use the _countof() macro to get the
		//	 size of the "name" array.]
		char name[32];

		// Pointer to an attached physics component.
		Physics* physics;

		// Pointer to an attached sprite component.
		Sprite* sprite;

		// Pointer to an attached transform component.
		Transform* transform;

	} Entity;

	//------------------------------------------------------------------------------
	// Public Variables:
	//------------------------------------------------------------------------------

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Dynamically allocate a new Entity.
	// (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
	// Returns:
	//	 If the memory allocation was successful,
	//	   then return a pointer to the allocated memory,
	//	   else return NULL.
	Entity* EntityCreate(void)
	{
		Entity* ptrEntity = calloc(1, sizeof(Entity*));

		if (ptrEntity != NULL)
		{
			return ptrEntity;
		}
		else {
			return NULL;
		}
	}

	// Free the memory associated with an Entity.
	// (NOTE: All attached components must be freed using the corresponding Free() functions.)
	// (NOTE: The Entity pointer must be set to NULL.)
	// Params:
	//	 entity = Pointer to the Entity pointer.
	void EntityFree(Entity** entity) //post-it note to where ID is to house
	{
		free(&(*entity)); //Find the ID where the Post-it note says, 
		entity = NULL;
	}

	// Params:
	//	 entity = Pointer to the Entity.
	//	 stream = The data stream used for reading.
	void EntityRead(Entity* entity, Stream stream)
	{
		if (entity != NULL && stream != NULL)
		{
			//Annotate me
			const char* token = StreamReadToken(stream);
			// This might be a problem, strncpy_s(entity->name, sizeof(entity->name), "Entity", _countof("Entity"));
			strncpy_s(entity->name, _countof(entity->name), token, _countof("Entity"));

			while (true) {
				if ((strncmp(token, "Transform", _countof("Transform")) == 0))
				{
					entity->transform = TransformCreate();
					TransformRead(entity->transform, stream);
				}
				if ((strncmp(token, "Physics", _countof("Physics")) == 0))
				{
					entity->physics = PhysicsCreate();
					PhysicsRead(entity->physics, stream);
				}
				if ((strncmp(token, "Sprite", _countof("Sprite")) == 0))
				{
					entity->sprite = SpriteCreate();
					SpriteRead(entity->sprite, stream);
				}
				else if (token[0] == 0) {
					break;
				}
					//“token” is empty(zero - length string),
					//		o	Break out of the while - loop
			}

		}
	}

	// Attach a Physics component to an Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	//   physics = Pointer to the Physics component to be attached.
	void EntityAddPhysics(Entity* entity, Physics* physics)
	{
		entity->physics = physics;
	}

	// Attach a sprite component to an Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	//   sprite = Pointer to the Sprite component to be attached.
	void EntityAddSprite(Entity* entity, Sprite* sprite)
	{
		entity->sprite = sprite;
	}

	// Attach a transform component to an Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	//   transform = Pointer to the Transform component to be attached.
	void EntityAddTransform(Entity* entity, Transform* transform)
	{
		entity->transform = transform;
	}

	// Set the Entity's name.
	// [NOTE: Verify that both pointers are valid before setting the name.]
	// [NOTE: When setting the name, use strcpy_s() to reduce the risk of
	//	 buffer overruns. Additionally, do NOT hardcode the number "32" when
	//	 calling this function!  Instead, use the _countof() macro to get the
	//	 size of the "name" array.]
	// Params:
	//	 entity = Pointer to the Entity.
	//	 name = Pointer to the Entity's new name.
	void EntitySetName(Entity* entity, const char* name)
	{
		if (entity != NULL && name != NULL)
		{
			strcpy_s(entity->name, _countof(entity->name), name);
		}
	}

	// Get the Entity's name.
	// Params:
	//	 entity = Pointer to the Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the Entity's name,
	//		else return NULL.
	const char* EntityGetName(const Entity* entity)
	{
		if (entity != NULL)
		{
			return entity->name;
		}
		else {
			return NULL;
		}
	}

	// Get the Physics component attached to an Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the attached physics component,
	//		else return NULL.
	Physics* EntityGetPhysics(const Entity* entity)
	{
		if (entity != NULL)
		{
			return entity->physics;
		}
		else {
			return NULL;
		}
	}

	// Get the Sprite component attached to a Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the attached Sprite component,
	//		else return NULL.
	Sprite* EntityGetSprite(const Entity* entity)
	{
		if (entity != NULL)
		{
			return entity->sprite;
		}
		else {
			return NULL;
		}
	}

	// Get the Transform component attached to a Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the attached Transform component,
	//		else return NULL.
	Transform* EntityGetTransform(const Entity* entity)
	{
		if (entity != NULL)
		{
			return entity->transform;
		}
		else {
			return NULL;
		}
	}

	// Update any components attached to the Entity.
	// (Hint: You will need to call PhysicsUpdate().)
	// (NOTE: You must first check for a valid pointer before calling this function.)
	// Params:
	//	 entity = Pointer to the Entity.
	//	 dt = Change in time (in seconds) since the last game loop.
	void EntityUpdate(Entity* entity, float dt)
	{
		if (entity != NULL)
		{
			PhysicsUpdate(entity->physics, entity->transform, dt);
		}
	}

	// Render any visible components attached to the Entity.
	// (Hint: You will need to call SpriteRender(), passing the Sprite and Transform components.)
	// (NOTE: You must first check for valid pointers before calling this function.)
	// Params:
	//	 entity = Pointer to the Entity.
	void EntityRender(Entity* entity) 
	{
		if (entity != NULL)
		{
			SpriteRender(entity->sprite, entity->transform);
		}
	}

	//------------------------------------------------------------------------------

