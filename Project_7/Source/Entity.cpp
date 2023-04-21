//------------------------------------------------------------------------------
//
// File Name:	Entity.c
// Author(s):	Rob Perez (rob.perez)
// Project:		Project 7
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
#include "Collider.h"
#include "Entity.h"

#include "BehaviorHudText.h"
#include "BehaviorBullet.h"
#include "BehaviorSpaceship.h"
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
      new_component = AddComponent<Transform>();
    }
    //else if ((strncmp(token, "Physics", _countof("Physics")) == 0))
    else if (token == "Physics")
    {
      new_component = AddComponent<Physics>();
    }
    //else if ((strncmp(token, "Sprite", _countof("Sprite")) == 0))
    else if (token == "Sprite")
    {
      new_component = AddComponent<Sprite>();
    }
    //else if ((strncmp(token, "Animation", _countof("Animation")) == 0))
    else if (token == "Animation")
    {
      new_component = AddComponent<Animation>();
      /*Animation* tempAnim = Animation::Create();
      Animation::Read(tempAnim, stream);
      EntityAddAnimation(entity, tempAnim);*/
    }
    else if (token == "BehaviorSpaceship")
    {
      new_component = AddComponent<BehaviorSpaceship>();
        //Behavior* spaceship = BehaviorSpaceshipCreate();
        //BehaviorRead(spaceship, stream);
        //EntityAddBehavior(entity, spaceship);
    }
    else if (token == "BehaviorBullet")
    {
      new_component = AddComponent<BehaviorBullet>();
        //Behavior* bullet = BehaviorBulletCreate();
        //BehaviorRead(bullet, stream);
        //EntityAddBehavior(entity, bullet);
    }
    /*else if ((strncmp(token, "BehaviorAsteroid", _countof("BehaviorAsteroid")) == 0))
    {
        Behavior* asteroid = BehaviorAsteroidCreate();
        BehaviorRead(asteroid, stream);
        EntityAddBehavior(entity, asteroid);
    }*/
    else if (token == "BehaviorHudText")
    {
      new_component = AddComponent<BehaviorHudText>();
    }
   /* else if ((strncmp(token, "ColliderCircle", _countof("ColliderCircle")) == 0))
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

    if(new_component)
      new_component->Read(stream);
    //Steps through the stream each 
    token = StreamReadToken(stream);
  }
}

void Entity::SetName(std::string newName)
{
  this->name = newName;
}

std::string Entity::GetName()
{
  return name;
}

void Entity::Update(float dt)
{
  for (auto it = components.begin(); it != components.end(); ++it)
  {
    if(*it)
      (*it)->Update(dt);
  }
}

void Entity::Render()
{
  for (auto it = components.begin(); it != components.end(); ++it)
  {
    if(*it)
      (*it)->Render();
  }
}

void Entity::OnCollision(Entity* other)
{
  // Go through all the components in the list and if that component has an OnCollision handler then call it.
  for(auto component : components)
    if(component)
      component->OnCollision(other);
}

bool Entity::IsNamed(const char* newName) const
{
  //if (this != nullptr && strcmp(this->name, name) == 0)
  return newName == name;
}

bool Entity::IsDestroyed() const
{
  //issue
  if (this != nullptr)
  {
    return this->isDestroyed;
  }
  else
  {
    return false;
  }
}

void Entity::Destroy()
{
  isDestroyed = true;
}

// Constructor - sets defaults to all member variables
Entity::Entity(): isDestroyed(false), components()
{
  // Runs through all the elements in Components and sets them all to a Nullptr
  std::fill(components.begin(), components.end(), nullptr);
}

Entity::~Entity()
{
  for(Component*& component : components)
  {
    delete component;
    component = nullptr;
  }
}

Entity* Entity::Clone()
{
  Entity* newEntity = new Entity;

  newEntity->name = name;

  //for(auto [key, value] : components)
  //for each loop (first = key, second = value)
  for (int i = 0; i < (int)Component::Type::Count; ++i)
  {
    if(components[i])
      newEntity->components[i] = components[i]->Clone(*newEntity);
  }

  return newEntity;
}

//------------------------------------------------------------------------------
