//------------------------------------------------------------------------------
//
// File Name:	Collider.h
// Author(s):	Doug Schilling (dschilling)
// Project:		Project 6
// Course:		CS230S23
//
// Copyright © 2023 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once
#include "Component.h"
#include "Entity.h"

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------



 /*enum ColliderType
{
	None,
	Circle,
	Line,
};

// This structure must now be declared publicly so that it may be included in
//   the private ColliderCircle and ColliderLine structures.
class Collider : public Component
{
	public:
	
	__inline static Type type() { return Type::Collider; }
	
	Component* Clone(Entity& newParent) const override;

	
	void SetParent(Entity* parent);

	void Check(const Collider* other) const;

	private:

	bool IsColliding(const Collider* collider1, const Collider* collider2);
	// Pointer to the collider's parent Entity.
	//Entity* parent;
	explicit Collider(Entity& parent);
	
	// The type of collider used by this component.
	// (Currently, Circle or Line).
	ColliderType type;

	// Pointer to a function that handles collisions between entities.
	CollisionEventHandler	handler;

	// The amount of memory to be allocated when cloning a component of this type.
	unsigned int	memorySize;

};*/
