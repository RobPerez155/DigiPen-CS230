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
    else
    {
        return nullptr;
    }
}

// Params:
//	 entity = Pointer to the Entity.
//	 stream = The data stream used for reading.
void Entity::Read(Stream stream)
{
    //Annotate me
    auto token = StreamReadToken(stream);
    name = token;

    token = StreamReadToken(stream);

    while (true)
    {
        Component* new_component = nullptr;
        if (token == "Transform")
        {
          new_component  = AddComponent<Transform>();
        }
        else if ((strncmp(token, "Physics", _countof("Physics")) == 0))
        {
            new_component = AddComponent<Physics>();
        }
        else if ((strncmp(token, "Sprite", _countof("Sprite")) == 0))
        {
            new_component = AddComponent<Sprite>();
        }
        else if ((strncmp(token, "Animation", _countof("Animation")) == 0))
        {
            Animation* tempAnim = AnimationCreate();
            AnimationRead(tempAnim, stream);
            EntityAddAnimation(entity, tempAnim);
        }
        /*else if ((strncmp(token, "BehaviorSpaceship", _countof("BehaviorSpaceship")) == 0))
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
        }*/
        else if (token[0] == 0)
        {
            break;
        }
        
        new_component->Read(stream);
        //Steps through the stream each 
        token = StreamReadToken(stream);
    }
}



// Set the Entity's name.
// Params:
//	 entity = Pointer to the Entity.
//	 name = Pointer to the Entity's new name.
void Entity::SetName(std::string name)
{
    this->name = name;
}

// Get the Entity's name.
// Params:
//	 entity = Pointer to the Entity.
std::string Entity::GetName()
{
    return name;
}

// Params:
//	 entity = Pointer to the Entity.
//	 dt = Change in time (in seconds) since the last game loop.
void Entity::Update(float dt)
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        it->second->Update(dt);
    }

}

// Render any visible components attached to the Entity.
// Params:
//	 entity = Pointer to the Entity.
void Entity::Render()
{
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        it->second->Render();
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
bool Entity::IsNamed(const char* name)
{
    if (entity != nullptr && strcmp(entity->name, name) == 0)
    {
        return true;
    }
    else
    {
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
    else
    {
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
void Entity::Destroy()
{
    isDestroyed = true;
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
Entity* Entity::Clone()
{
    Entity* newEntity = new Entity;

    newEntity->name = name;

    //for(auto [key, value] : components)
    //for each loop (first = key, second = value)
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        newEntity->components[it->first] = it->second->Clone(*newEntity);
    }

    return newEntity;
}

//------------------------------------------------------------------------------
