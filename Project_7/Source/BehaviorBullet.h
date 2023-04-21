//------------------------------------------------------------------------------
//
// File Name:	BehaviorBullet.h
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
enum BulletState {
  cBulletInvalid = -1,
  cBulletIdle,
  cBulletThrust
};

class BehaviorBullet : public Behavior
{
public:
  explicit BehaviorBullet(Entity& parent);

  void Init() override;
  
  void Update(float dt) override;

  void Exit() override;

private:
  const float spaceshipSpeedMax = 500.0f;
    
  void UpdateLifeTimer(float dt);
  void CollisionHandler(Entity* entity1, Entity* entity2);

  // Inherited via Behavior
  virtual Component* Clone(Entity& newParent) const override;
};

//------------------------------------------------------------------------------

