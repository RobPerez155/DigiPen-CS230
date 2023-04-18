//------------------------------------------------------------------------------
//
// File Name:	Physics.c
// Author(s): Rob Perez (rob.perez)
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

#include "Component.h"
#include "Physics.h"
#include "DGL.h"
#include "Stream.h"
#include "Vector2D.h"

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

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Physics::Physics(Entity& parent) : Component(parent)
{
  oldTranslation = {0, 0};
  acceleration = {0, 0};
  velocity = {0, 0};
  rotationalVelocity = 0.0f;
  drag = 0.0f;
}

Component* Physics::Clone(Entity& newParent) const
{
  Physics* physicsClone = new Physics([&]newParent);

  if (physicsClone == nullptr)
  {
    return nullptr;
  }

  physicsClone->oldTranslation = oldTranslation;
  physicsClone->acceleration = acceleration;
  physicsClone->velocity = velocity;
  physicsClone->rotationalVelocity = rotationalVelocity;
  physicsClone->drag = drag;

  return physicsClone;
}

void Physics::Read(Stream stream)
{
  if (stream != nullptr)
  {
    StreamReadVector2D(stream, &acceleration);
    StreamReadVector2D(stream, &velocity);
  }
}

float Physics::GetRotationalVelocity() const
{
  return rotationalVelocity;
}

//const Vector2D& Physics::GetAcceleration() const
const Vector2D& Physics::GetAcceleration()
{
  return acceleration;
}

const Vector2D& Physics::GetVelocity() const
{
  return velocity;
}

const Vector2D& Physics::GetOldTranslation()
{
  return oldTranslation;
}

void Physics::SetRotationalVelocity(float rotationalVelocity)
{
  this->rotationalVelocity = rotationalVelocity;
}

void Physics::SetAcceleration(const Vector2D& acceleration)
{
  this->acceleration = acceleration;
}

void Physics::SetVelocity(const Vector2D& velocity)
{
  this->velocity = velocity;
}

void Physics::Update(float dt)
{
  for (auto it = components.begin(); it != components.end(); ++it)
  {
    it->second->Update(dt);
  }
}

/*void PhysicsUpdate(Physics* physics, Transform* transform, float dt)
{	
  if (physics != nullptr && transform != nullptr)
  {
    // Update previous translation
    physics->oldTranslation = *TransformGetTranslation(transform);

    // Find translation after velocity and acceleration are applied with dt
    Vector2D result;

    //Update acceleration after dt is applied add acceleration from current velocity
    Vector2DScaleAdd(&physics->velocity, &physics->acceleration, &physics->velocity, dt);

    // Update velocity after dt is applied and add velocity to current translation
    Vector2DScaleAdd(&result, &physics->velocity, &physics->oldTranslation, dt);

    //Set new translation
    TransformSetTranslation(transform, &result);
    
    float rotation = TransformGetRotation(transform) + physics->rotationalVelocity * dt;

    TransformSetRotation(transform, rotation);
  }
}*/
//------------------------------------------------------------------------------
