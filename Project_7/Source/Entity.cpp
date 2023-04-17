//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 2
// Course:		CS230S23
//
// Copyright � 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "Animation.h"
#include "Behavior.h"
#include "BehaviorAsteroid.h"
#include "BehaviorBullet.h"
#include "BehaviorHudText.h"
#include "BehaviorSpaceship.h"
#include "Collider.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"
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

		// Flag to indicate that the Entity should be destroyed after it has been updated.
		bool isDestroyed;

		// Pointer to an attached Animation component.
		Animation* animation;

		// Pointer to an attached Behavior component.
		Behavior* behavior;

		// Pointer to an attached Collider component.
		Collider* collider;

		// Pointer to an attached Physics component.
		Physics* physics;

		// Pointer to an attached Sprite component.
		Sprite* sprite;

		// Pointer to an attached Transform component.
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
//	   else return nullptr.
	Entity* EntityCreate(void)
	{
		//Entity* ptrEntity = calloc(1, sizeof(Entity));
		Entity* ptrEntity = new Entity();


		if (ptrEntity != nullptr)
		{
			return ptrEntity;
		}
		else {
			return nullptr;
		}
	}

	// Free the memory associated with an Entity.
// (NOTE: All attached components must be freed using the corresponding Free() functions.)
// (NOTE: The Entity pointer must be set to nullptr.)
// Params:
//	 entity = Pointer to the Entity pointer.
// 
	// Free the memory associated with an Entity.
	// Params:
	//	 entity = Pointer to the Entity pointer.
	void EntityFree(Entity** entity) //post-it note to where ID is to house
	{
		//Look at header - free components first, then entity, then set to nullptr
		Physics* physics = EntityGetPhysics(*entity);
		PhysicsFree(&physics);

		Sprite* sprite = EntityGetSprite(*entity);
		SpriteFree(&sprite);

		Transform* transform = EntityGetTransform(*entity);
		TransformFree(&transform);

		Animation* animation = EntityGetAnimation(*entity);
		AnimationFree(&animation);

		Behavior* behavior = EntityGetBehavior(*entity);
		BehaviorFree(&behavior);

		Collider* collider = EntityGetCollider(*entity);
		ColliderFree(&collider);

		free(*entity); //Find the ID where the Post-it note says, 
		*entity = nullptr; 
	}

	// Params:
	//	 entity = Pointer to the Entity.
	//	 stream = The data stream used for reading.
	void EntityRead(Entity* entity, Stream stream)
	{
		if (entity != nullptr && stream != nullptr)
		{
			//Annotate me
			const char* token = StreamReadToken(stream);
			strcpy_s(entity->name, _countof(entity->name), token);

			token = StreamReadToken(stream);

			while (true) {

				if ((strncmp(token, "Transform", _countof("Transform")) == 0))
				{
					entity->transform = TransformCreate();
					TransformRead(entity->transform, stream);
				}
				else if ((strncmp(token, "Physics", _countof("Physics")) == 0))
				{
					//entity->physics = PhysicsCreate();
					Physics* physics = PhysicsCreate();
					PhysicsRead(physics, stream);
					EntityAddPhysics(entity, physics);
				}
				else if ((strncmp(token, "Sprite", _countof("Sprite")) == 0))
				{
					entity->sprite = SpriteCreate();
					SpriteRead(entity->sprite, stream);
				}
				else if ((strncmp(token, "Animation", _countof("Animation")) == 0))
				{
					Animation* tempAnim = AnimationCreate();
					AnimationRead(tempAnim, stream);
					EntityAddAnimation(entity, tempAnim);
				}
				else if ((strncmp(token, "BehaviorSpaceship", _countof("BehaviorSpaceship")) == 0))
				{
					Behavior* spaceship = BehaviorSpaceshipCreate();
					BehaviorRead(spaceship, stream);
					EntityAddBehavior(entity, spaceship);
				}
				else if ((strncmp(token, "BehaviorBullet", _countof("BehaviorBullet")) == 0))
				{
					Behavior* bullet = BehaviorBulletCreate();
					BehaviorRead(bullet, stream);
					EntityAddBehavior(entity, bullet);
				}
				else if ((strncmp(token, "BehaviorAsteroid", _countof("BehaviorAsteroid")) == 0))
				{
					Behavior* asteroid = BehaviorAsteroidCreate();
					BehaviorRead(asteroid, stream);
					EntityAddBehavior(entity, asteroid);
				}
				else if ((strncmp(token, "BehaviorHudText", _countof("BehaviorHudText")) == 0))
				{
					Behavior* hudText = BehaviorHudTextCreate();
					BehaviorHudTextRead(hudText, stream);
					EntityAddBehavior(entity, hudText);
				}
				else if ((strncmp(token, "ColliderCircle", _countof("ColliderCircle")) == 0))
				{
					Collider* circleCollider = ColliderCircleCreate();
 					ColliderCircleRead(circleCollider, stream);
					EntityAddCollider(entity, circleCollider);
				}
				else if ((strncmp(token, "ColliderLine", _countof("ColliderLine")) == 0))
				{
					Collider* lineCollider = ColliderLineCreate();
					ColliderLineRead(lineCollider, stream);
					EntityAddCollider(entity, lineCollider);
				}
				else if (token[0] == 0) {
					break;
				}

				//Steps through the stream each 
				token = StreamReadToken(stream);
			}
		}
	}

	// Attach an Animation component to an Entity.
// (NOTE: This function must set the animation component's parent pointer by
//	  calling the AnimationSetParent() function.)
// Params:
//	 entity = Pointer to the Entity.
//   animation = Pointer to the Animation component to be attached.
	void EntityAddAnimation(Entity* entity, Animation* animation)
	{
		entity->animation = animation;
		AnimationSetParent(animation, entity);
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

	void EntityAddBehavior(Entity* entity, Behavior* behavior)
	{
		entity->behavior = behavior;
		BehaviorSetParent(behavior, entity);
	}

	// Set the Entity's name.
	// Params:
	//	 entity = Pointer to the Entity.
	//	 name = Pointer to the Entity's new name.
	void EntitySetName(Entity* entity, const char* name)
	{
		if (entity != nullptr && name != nullptr)
		{
			strcpy_s(entity->name, _countof(entity->name), name);
		}
	}

	// Get the Entity's name.
	// Params:
	//	 entity = Pointer to the Entity.
	const char* EntityGetName(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->name;
		}
		else {
			return nullptr;
		}
	}

	// Get the Physics component attached to an Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	Physics* EntityGetPhysics(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->physics;
		}
		else {
			return nullptr;
		}
	}

	// Get the Sprite component attached to a Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the attached Sprite component,
	//		else return nullptr.
	Sprite* EntityGetSprite(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->sprite;
		}
		else {
			return nullptr;
		}
	}

	// Get the Transform component attached to a Entity.
	// Returns:
	//	 If the Entity pointer is valid,
	//		then return a pointer to the attached Transform component,
	//		else return nullptr.
	Transform* EntityGetTransform(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->transform;
		}
		else {
			return nullptr;
		}
	}

	// Get the Animation component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Animation component,
//		else return nullptr.
	Animation* EntityGetAnimation(const Entity* entity)
	{
		if (entity != nullptr)
			return entity->animation;
		else
			return nullptr;
	}

// Get the Behavior component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Behavior component,
//		else return nullptr.
	Behavior* EntityGetBehavior(const Entity* entity)
	{
		if (entity != nullptr)
			return entity->behavior;
		else
			return nullptr;
	}

	// Update any components attached to the Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	//	 dt = Change in time (in seconds) since the last game loop.
	void EntityUpdate(Entity* entity, float dt)
	{
		if (entity != nullptr)
		{
			BehaviorUpdate(entity->behavior, dt);
			PhysicsUpdate(entity->physics, entity->transform, dt);
			AnimationUpdate(entity->animation, dt);
		}
	}

	// Render any visible components attached to the Entity.
	// Params:
	//	 entity = Pointer to the Entity.
	void EntityRender(Entity* entity) 
	{
		if (entity != nullptr)
		{
			SpriteRender(entity->sprite, entity->transform);
		}
	}

	// Compare the Entity's name with the specified name.
// Params:
//	 entity = Pointer to the Entity.
//   name = Pointer to the name to be checked.
// Returns:
//	 If the Entity pointer is valid and the two names match,
//		then return true,
//		else return false.
	bool EntityIsNamed(const Entity* entity, const char* name)
	{
		if (entity != nullptr && strcmp(entity->name, name) == 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	// Check whether an Entity has been flagged for destruction.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return the value in the "isDestroyed" flag,
//		else return false.
	bool EntityIsDestroyed(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->isDestroyed;
		}
		else {
			return false;
		}
	}

	// Flag an Entity for destruction.
// (Note: This is to avoid Entities being destroyed while they are being processed.)
// Params:
//	 entity = Pointer to the Entity to be flagged for destruction.
// Returns:
//	 If 'entity' is valid,
//	   then set the 'isDestroyed' flag,
//	   else do nothing.
	void EntityDestroy(Entity* entity)
	{
		if (entity != nullptr) 
		{
			entity->isDestroyed = true;
		}
	}

// Dynamically allocate a clone of an existing Entity.
// (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
// (WARNING: You should use the EntityAdd* functions when attaching cloned
//    components to the cloned Entity.  This will ensure that the 'parent'
//    variable is set properly.)
// Params:
//	 other = Pointer to the Entity to be cloned.
// Returns:
//	 If 'other' is valid and the memory allocation was successful,
//	   then return a pointer to the cloned Entity,
//	   else return nullptr.
	Entity* EntityClone(const Entity* other)
	{
		if (other != nullptr)
		{
			//Entity* clonedEntity = calloc(1, sizeof(Entity));
			Entity* clonedEntity = new Entity();

			if (clonedEntity != nullptr)
			{
				//Make shallow copy of entity
				*clonedEntity = *other;

				//Make deep copy
				clonedEntity->behavior = BehaviorClone(other->behavior);
				clonedEntity->sprite = SpriteClone(other->sprite);
				clonedEntity->animation = AnimationClone(other->animation);
				clonedEntity->physics = PhysicsClone(other->physics);
				clonedEntity->transform = TransformClone(other->transform);
				clonedEntity->collider = ColliderClone(other->collider);

				if (clonedEntity->behavior)
					BehaviorSetParent(clonedEntity->behavior, clonedEntity);

				if (clonedEntity->animation)
				{
					AnimationSetParent(clonedEntity->animation, clonedEntity);
				}

				if (clonedEntity->collider)
				{
					ColliderSetParent(clonedEntity->collider, clonedEntity);
				}

				return clonedEntity;
			}
			return nullptr;
		}
		return nullptr;
	}

	// Attach a Collider component to an Entity.
// (NOTE: This function must also set the Collider component's parent pointer
//	  by calling the ColliderSetParent() function.)
// Params:
//	 entity = Pointer to the Entity.
//   collider = Pointer to the Collider component to be attached.
	void EntityAddCollider(Entity* entity, Collider* collider)
	{
		entity->collider = collider;
		ColliderSetParent(collider, entity);
	}

	// Get the Collider component attached to an Entity.
// Params:
//	 entity = Pointer to the Entity.
// Returns:
//	 If the Entity pointer is valid,
//		then return a pointer to the attached Collider component,
//		else return nullptr.
	Collider* EntityGetCollider(const Entity* entity)
	{
		if (entity != nullptr)
		{
			return entity->collider;
		}
		else {
			return nullptr;
		}
	}

	//------------------------------------------------------------------------------

