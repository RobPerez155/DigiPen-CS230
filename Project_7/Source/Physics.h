//------------------------------------------------------------------------------
//
// File Name:	Physics.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 5
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "DGL.h"
#include "Sprite.h"
#include "Stream.h"
#include "Vector2D.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//This makes the Physics class a member of the Component class
class Physics : public Component
{
public:
	
	__inline static Type type() { return Type::Physics; }

	//Using explicit to specify that we want to see the "Physics" call on creations of physics 
	explicit Physics(Entity& parent);

	Component* Clone(Entity& newParent) const override;
	
	void Read(Stream stream) override;

	const Vector2D& GetAcceleration();

	const Vector2D& GetVelocity() const;

	const Vector2D& GetOldTranslation();

	float GetRotationalVelocity() const;

	void SetAcceleration(const Vector2D& newAcceleration);
	
	void SetVelocity(const Vector2D& newVelocity);
	
	void SetRotationalVelocity(float newRotationalVelocity);
	
	void SetDrag(float drag);
	
	void Update(Transform* transform, float dt);

private:
	Vector2D	oldTranslation;

	// Acceleration = inverseMass * (sum of forces)
	Vector2D	acceleration;

	// Velocity may be stored as a direction vector and speed scalar, instead.
	Vector2D	velocity;

	// Rotational velocity (in radians).
	float rotationalVelocity;

	// Drag to be applied to moving objects in order to slow them down.
	float drag;

	// Used when calculating acceleration due to forces.
	// Used when resolving collision between two dynamic objects.
	//float		inverseMass;

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

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

