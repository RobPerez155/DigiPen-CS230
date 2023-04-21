//------------------------------------------------------------------------------
//
// File Name:	BehaviorSpaceship.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 7
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
#include <math.h>
#include "DGL.h"
#include "Behavior.h"
#include "BehaviorSpaceship.h"
#include "Collider.h"
#include "Entity.h"
#include "EntityFactory.h"
#include "Physics.h"
#include "Teleporter.h"
#include "Transform.h"
#include "Vector2D.h"
#include "Scene.h"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

/*typedef struct Behavior Behavior;*/

enum SpaceshipState {
  cSpaceshipInvalid = -1,
  cSpaceshipIdle,
  cSpaceshipThrust,
  cSpaceshipDead
};

class BehaviorSpaceship : public Behavior
{
public:
  explicit BehaviorSpaceship(Entity& parent);
  
  void Init() override;

  // Update the current state of the behavior component.
  // (Hint: Refer to the lecture notes on finite state machines (FSM).)
  // Params:
  //	 behavior = Pointer to the behavior component.
  //	 dt = Change in time (in seconds) since the last game loop.
  void Update(float dt) override;

  // Exit the current state of the behavior component.
  // (Hint: Refer to the lecture notes on finite state machines (FSM).)
  // Params:
  //	 behavior = Pointer to the behavior component.
  //	 dt = Change in time (in seconds) since the last game loop.
  void Exit() override;
  
  

private:
  const float spaceshipAcceleration = 150.0f;
  const float spaceshipSpeedMax = 500.0f;
  const float spaceshipTurnRateMax = (3.14159265358979323846f / 1.5f);
  const float spaceshipWeaponCooldownTime = 0.25f;
  const float spaceshipWeaponBulletSpeed = 750.0f;
  const float spaceshipDeathDuration = 5.0f;

  void UpdateRotation(float dt);
  void UpdateVelocity(float dt);
  void UpdateWeapon(float dt);
  void SpawnBullet();
  void CollisionHandler(Entity* entity1, Entity* entity2);
  void DeadAnimation();
  virtual Component* Clone(Entity& newParent) const override;
};
