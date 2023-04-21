//------------------------------------------------------------------------------
//
// File Name:	Entity.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 7
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include <string>
#include <array>
#include "Component.h"
#include <unordered_map>

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------


class Entity
{
public:
		Entity();
	~Entity();
    Entity* Clone();

    void Read( Stream stream);
	
    void Destroy();
	
    bool IsDestroyed() const;

	  bool IsNamed(const char* newName) const;
	
    void SetName(std::string newName);
	
    std::string GetName();

    void Update( float dt);
	
    void Render();
	

	template<typename ComponentType>
	ComponentType* GetComponent() const
	{
		// Returns the enum of the component we are looking for, which inturns gives us the component in question
		return static_cast<ComponentType*>(components[static_cast<std::size_t>(ComponentType::type())]);
	}

	template<typename ComponentType>
	Component* AddComponent()
	{
		components[static_cast<std::size_t>(ComponentType::type())]  = new ComponentType(*this);
		return static_cast<ComponentType*>(components[static_cast<std::size_t>(ComponentType::type())]);
	}
protected:
	void OnCollision(Entity* other);
	
private:
    std::string name;

    // Flag to indicate that the Entity should be destroyed after it has been updated.
    bool isDestroyed;

		std::array<Component*, static_cast<std::size_t>(Component::Type::Count)> components;
};

#ifdef __cplusplus
extern "C" {
/* Assume C declarations for C++ */
#endif

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
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------
//
// // Dynamically allocate a new Entity.
// // (Hint: Use calloc() to ensure that all member variables are initialized to 0.)
// // Returns:
// //	 If the memory allocation was successful,
// //	   then return a pointer to the allocated memory,
// //	   else return nullptr.
// Entity* EntityCreate(void);
//
// // Dynamically allocate a clone of an existing Entity.
// // (Hint: Make sure to perform a shallow copy or deep copy, as appropriate.)
// // (WARNING: You should use the EntityAdd* functions when attaching cloned
// //    components to the cloned Entity.  This will ensure that the 'parent'
// //    variable is set properly.)
// // Params:
// //	 other = Pointer to the Entity to be cloned.
// // Returns:
// //	 If 'other' is valid and the memory allocation was successful,
// //	   then return a pointer to the cloned Entity,
// //	   else return nullptr.
// Entity* EntityClone(const Entity* other);
//
// // Free the memory associated with an Entity.
// // (NOTE: All attached components must be freed using the corresponding Free() functions.)
// // (NOTE: The Entity pointer must be set to nullptr.)
// // Params:
// //	 entity = Pointer to the Entity pointer.
// void EntityFree(Entity** entity);
//
// // Read (and construct) the components associated with a entity.
// // [NOTE: See project instructions for implementation instructions.]
// // Params:
// //	 entity = Pointer to the Entity.
// //	 stream = The data stream used for reading.
// void EntityRead( Stream stream);
//
// // Flag an Entity for destruction.
// // (Note: This is to avoid Entities being destroyed while they are being processed.)
// // Params:
// //	 entity = Pointer to the Entity to be flagged for destruction.
// // Returns:
// //	 If 'entity' is valid,
// //	   then set the 'isDestroyed' flag,
// //	   else do nothing.
// void EntityDestroy(Entity* entity);
//
// // Check whether an Entity has been flagged for destruction.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return the value in the "isDestroyed" flag,
// //		else return false.
// bool EntityIsDestroyed(const Entity* entity);
//
// // Attach an Animation component to an Entity.
// // (NOTE: This function must also set the animation component's parent pointer
// //	  by calling the AnimationSetParent() function.)
// // Params:
// //	 entity = Pointer to the Entity.
// //   animation = Pointer to the Animation component to be attached.
// void EntityAddAnimation( Animation* animation);
//
// // Attach a Behavior component to an Entity.
// // (NOTE: This function must also set the Behavior component's parent pointer
// //	  by calling the BehaviorSetParent() function.)
// // Params:
// //	 entity = Pointer to the Entity.
// //   behavior = Pointer to the Behavior component to be attached.
// void EntityAddBehavior( Behavior* behavior);
//
// // Attach a Collider component to an Entity.
// // (NOTE: This function must also set the Collider component's parent pointer
// //	  by calling the ColliderSetParent() function.)
// // Params:
// //	 entity = Pointer to the Entity.
// //   collider = Pointer to the Collider component to be attached.
// void EntityAddCollider( Collider* collider);
//
// // Attach a Physics component to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// //   physics = Pointer to the Physics component to be attached.
// void EntityAddPhysics( Physics* physics);
//
// // Attach a sprite component to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// //   sprite = Pointer to the Sprite component to be attached.
// void EntityAddSprite( Sprite* sprite);
//
// // Attach a transform component to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// //   transform = Pointer to the Transform component to be attached.
// void EntityAddTransform( Transform* transform);
//
// // Set the Entity's name.
// // [NOTE: Verify that both pointers are valid before setting the name.]
// // [NOTE: When setting the name, use strcpy_s() to reduce the risk of
// //	 buffer overruns. Additionally, do NOT hardcode the number "32" when
// //	 calling this function!  Instead, use the _countof() macro to get the
// //	 size of the "name" array.]
// // Params:
// //	 entity = Pointer to the Entity.
// //	 name = Pointer to the Entity's new name.
// void EntitySetName( const char * name);
//
// // Get the Entity's name.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the Entity's name,
// //		else return nullptr.
// const char * EntityGetName(const Entity* entity);
//
// // Compare the Entity's name with the specified name.
// // Params:
// //	 entity = Pointer to the Entity.
// //   name = Pointer to the name to be checked.
// // Returns:
// //	 If the Entity pointer is valid and the two names match,
// //		then return true,
// //		else return false.
// bool EntityIsNamed( const char* name);
//
// // Get the Animation component attached to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Animation component,
// //		else return nullptr.
// Animation* EntityGetAnimation(const Entity* entity);
//
// // Get the Behavior component attached to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Behavior component,
// //		else return nullptr.
// Behavior* EntityGetBehavior(const Entity* entity);
//
// // Get the Collider component attached to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Collider component,
// //		else return nullptr.
// Collider* EntityGetCollider(const Entity* entity);
//
// // Get the Physics component attached to an Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Physics component,
// //		else return nullptr.
// Physics* EntityGetPhysics(const Entity* entity);
//
// // Get the Sprite component attached to a Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Sprite component,
// //		else return nullptr.
// Sprite* EntityGetSprite(const Entity* entity);
//
// // Get the Transform component attached to a Entity.
// // Params:
// //	 entity = Pointer to the Entity.
// // Returns:
// //	 If the Entity pointer is valid,
// //		then return a pointer to the attached Transform component,
// //		else return nullptr.
// Transform* EntityGetTransform(const Entity* entity);
//
// // Update any components attached to the Entity.
// // (NOTE: You must first check for a valid pointer before calling this function.)
// // (HINT: Update the Animation first, as it might affect Behavior.)
// // (HINT: Update the Behavior second, as it might affect Physics.)
// // (HINT: Update the Physics last, before checking for collisions.)
// // Params:
// //	 entity = Pointer to the Entity.
// //	 dt = Change in time (in seconds) since the last game loop.
// void EntityUpdate( float dt);
//
// // Render any visible components attached to the Entity.
// // (Hint: You will need to call SpriteRender(), passing the Sprite and Transform components.)
// // (NOTE: You must first check for valid pointers before calling this function.)
// // Params:
// //	 entity = Pointer to the Entity.
// void EntityRender(Entity* entity);

//------------------------------------------------------------------------------

#ifdef __cplusplus
} /* End of extern "C" { */
#endif
